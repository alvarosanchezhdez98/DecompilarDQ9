#include "System/PowerManagement.h"
#include "System/Cartridge.h"
#include "System/DMA.h"
#include "System/Graphics.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "System/Timing.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's pm.c (spi/ARM9), in a newer version than the public decompilations: each command is a utility
// command with a parameter, and the commands retry while the ARM7 is busy

// The IPC command of the power management (PXI_FIFO_TAG_PM)
#define IPC_COMMAND_PM 8

// The commands to the ARM7 (SPI_PXI_COMMAND_PM_*), in bits 8-14 of the first word
#define COMMAND_SYNC 0x60
#define COMMAND_UTILITY 0x61
#define COMMAND_SLEEP_START 0x62
#define COMMAND_SLEEP_END 0x63
// The first and the last word of a command (SPI_PXI_START_BIT and SPI_PXI_END_BIT)
#define PXI_START_BIT 0x2000000
#define PXI_END_BIT 0x1000000
// The index of a word in the command
#define PXI_INDEX_SHIFT 16

// The utility commands (PM_UTIL_*)
#define UTIL_LED_ON 1
#define UTIL_LED_BLINK_HIGH_SPEED 2
#define UTIL_LED_BLINK_LOW_SPEED 3
#define UTIL_LCD1_BACKLIGHT_ON 4
#define UTIL_LCD1_BACKLIGHT_OFF 5
#define UTIL_LCD2_BACKLIGHT_ON 6
#define UTIL_LCD2_BACKLIGHT_OFF 7
#define UTIL_LCD12_BACKLIGHT_ON 8
#define UTIL_LCD12_BACKLIGHT_OFF 9
#define UTIL_FORCE_POWER_OFF 14
// Reads a status of the power management chip: its parameter says which
#define UTIL_GET_STATUS 15
#define UTIL_STATUS_BACKLIGHT 1
#define UTIL_STATUS_LED_PATTERN 6
// A command that PMi_SetLCDPower sends while the LCDs are on: with 0 before it turns them off, and with sCommand16Value
// after it turns them on
#define UTIL_COMMAND_16 16
#define UTIL_SET_LED_PATTERN 18

// The backlights' bits in the status (PMIC_CTL_BKLT1 and PMIC_CTL_BKLT2)
#define STATUS_BACKLIGHT_BOTTOM 0x4
#define STATUS_BACKLIGHT_TOP 0x8

// The bits of PM_GoSleepMode's trigger that turn the backlights on again (PM_BACKLIGHT_RECOVER_*)
#define BACKLIGHT_RECOVER_TOP_ON 0x40
#define BACKLIGHT_RECOVER_BOTTOM_ON 0x80

// What a command's result is until the ARM7 answers it
#define RESULT_NONE 0xffff0000
// The results of the commands that the IPC didn't send: the utility and sleep commands may be retried
#define RESULT_SEND_FAILED 1
#define RESULT_ERROR 2

// PMi_WAIT_FRAME: the LCDs stay off for this many frames
#define LCD_OFF_WAIT_FRAMES 7
// The LCDs aren't turned off for this many frames after PM_Init
#define LCD_INIT_WAIT_FRAMES 2
// The cycles that the functions wait before retrying a command: 10 ms
#define RETRY_WAIT_CYCLES 0xa3a47
// The cycles that the LCDs take to turn on or off
#define LCD_POWER_WAIT_CYCLES 0x360000

// The interrupts' master switch (REG_IME), the requests (REG_IF), and the ones that wake the console up
#define IME (*(volatile unsigned short*)0x04000208)
#define IF (*(volatile unsigned long*)0x04000214)
#define IE_TIMER0 0x8
#define IE_FIFO_RECV 0x40000
#define IE_CARD_IREQ 0x100000
// OS_IRQ_TABLE_MAX: all the interrupts
#define IE_ALL 0x3fffff
// The CPSR's IRQ mode (OS_PROCMODE_IRQ), and its bit that disables the IRQs (OS_INTRMODE_IRQ_DISABLE)
#define PROCESSOR_MODE_IRQ 0x12
#define IRQ_DISABLED 0x80

// OS_GetVBlankCount
#define VBLANK_COUNT (*(volatile unsigned long*)0x027ffc3c)
// OS_GetBootType? What started the program: 2 for DS Download Play (MB_IsMultiBootChild)
#define BOOT_TYPE (*(volatile unsigned short*)0x027ffc40)
#define BOOT_TYPE_MULTIBOOT 2

// The command being sent (PMiWork)
struct PMiWork
{
    volatile int lock;
    PMCallback callback;
    void* callbackArg;
    // Where the result of a utility command goes
    void* work;
};

typedef void (*PMWaitBusyMethod)();

// OS_DisableIrq, OS_EnableIrq and OS_RestoreIrq
static inline int DisableIrq()
{
    const unsigned short prep = IME;
    IME = 0;
    return prep;
}

static inline int EnableIrq()
{
    const unsigned short prep = IME;
    IME = 1;
    return prep;
}

static inline int RestoreIrq(int enable)
{
    const unsigned short prep = IME;
    IME = enable;
    return prep;
}

// OS_GetVBlankCount
static inline unsigned long GetVBlankCount()
{
    return VBLANK_COUNT;
}

// The words of a command (PMi_MakeData1 and PMi_MakeData2)
static inline unsigned long MakeData1(unsigned long bit, unsigned long seq, unsigned long command, unsigned long data)
{
    return bit | (seq << PXI_INDEX_SHIFT) | (command << 8) | (data & 0xff);
}

static inline unsigned long MakeData2(unsigned long bit, unsigned long seq, unsigned long data)
{
    return bit | (seq << PXI_INDEX_SHIFT) | (data & 0xffff);
}

// The variables are defined in the order that lays them out like the original
static SleepCallbackInfo* PMi_PreSleepCallbackList;
static SleepCallbackInfo* PMi_PostSleepCallbackList;
static unsigned long sCommand16Value;
static unsigned short PMi_IsInit;
static unsigned long sInitCount;
static unsigned long PMi_LCDCount;
static PMiWork PMi_Work;
static volatile int PMi_SleepEndFlag;

extern "C"
{
    // OS_SpinWait, OS_WaitVBlankIntr and OS_Halt
    void func_020c976c(unsigned long cycles);
    void func_020c9820();
    void func_020c9bf0();
    // BIOS: waits for a number of loops of 4 cycles
    void WaitByLoop(int count);

    static void func_020ce148();
    static void func_020ce234(unsigned long result, void* arg);
    void func_020ce308(unsigned int tag, unsigned int data, unsigned int err);
    unsigned long func_020ce4e8(unsigned long number, unsigned short parameter, unsigned short* retValue,
                                PMCallback callback, void* arg);
    unsigned long func_020ce614(int status);
    unsigned long func_020ce6d0(int target, int sw);
    unsigned long func_020ce810(int* top, int* bottom);
    void func_020ce870(unsigned long data);
    int func_020ceba8(int sw, int led, int skip, int isSync);
    void func_020cee54(SleepCallbackInfo** listp, SleepCallbackInfo* info);
    void func_020cee68(SleepCallbackInfo** listp, SleepCallbackInfo* info);
    void func_020ceeb4(SleepCallbackInfo** listp, SleepCallbackInfo* info);
    void func_020cef0c(SleepCallbackInfo* listp);
    void func_020cef94();
}

// How the synchronous functions wait for the ARM7's answer
static PMWaitBusyMethod PMi_WaitBusyMethod = func_020ce148;

extern "C"
{
    // PMi_Lock
    static int func_020ce128()
    {
        if (PMi_Work.lock)
            return false;
        PMi_Work.lock = true;
        return true;
    }

    // PMi_WaitBusy: in an interrupt handler, the IPC's interrupt can't come
    static void func_020ce148()
    {
        volatile int* p = &PMi_Work.lock;
        while (*p)
        {
            if (GetProcessorMode() == PROCESSOR_MODE_IRQ)
                HandleCommandReceivedFromArm7();
        }
    }

    // How PMi_ForceToPowerOff waits: the interrupts may be disabled
    static void func_020ce188()
    {
        volatile int* p = &PMi_Work.lock;
        while (*p)
        {
            if (GetIRQInterruptState() == IRQ_DISABLED || IME == 0)
                HandleCommandReceivedFromArm7();
        }
    }

    // How PM_ForceToPowerOffAsync waits while it turns the LCDs on
    static void func_020ce1d8()
    {
        volatile int* p = &PMi_Work.lock;
        while (*p)
        {
            if (GetIRQInterruptState() == IRQ_DISABLED || IME == 0 || GetProcessorMode() == PROCESSOR_MODE_IRQ)
                HandleCommandReceivedFromArm7();
        }
    }

    // PMi_DummyCallback
    static void func_020ce234(unsigned long result, void* arg)
    {
        if (arg)
            *(unsigned long*)arg = result;
    }

    // PMi_CallCallbackAndUnlock
    static void func_020ce240(unsigned long result)
    {
        const PMCallback callback = PMi_Work.callback;
        void* const arg = PMi_Work.callbackArg;
        PMi_Work.lock = false;
        if (callback)
        {
            PMi_Work.callback = NULL;
            callback(result, arg);
        }
    }

    // PM_Init
    void func_020ce270()
    {
        if (PMi_IsInit)
            return;
        PMi_IsInit = true;
        PMi_Work.lock = false;
        PMi_Work.callback = NULL;
        InitializeInterProcessorCommunication();
        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_PM, IPCSide_Arm7))
            WaitByLoop(100);
        SetArm9IPCCommandHandler(IPC_COMMAND_PM, func_020ce308);
        PMi_LCDCount = sInitCount = VBLANK_COUNT;
    }

    // PMi_CommonCallback: the ARM7's answer
    void func_020ce308(unsigned int tag, unsigned int data, unsigned int err)
    {
        const unsigned short command = (data & 0x7f00) >> 8;
        unsigned short result = data & 0xff;
        if (err)
        {
            switch (command)
            {
            case COMMAND_UTILITY:
            case COMMAND_SLEEP_START:
                result = RESULT_SEND_FAILED;
                break;
            default:
                result = RESULT_ERROR;
                break;
            }
            func_020ce240(result);
            return;
        }
        switch (command)
        {
        case COMMAND_UTILITY:
            if (PMi_Work.work)
                *(unsigned short*)PMi_Work.work = result;
            result = PM_SUCCESS;
            break;
        case COMMAND_SYNC:
            result = PM_SUCCESS;
            break;
        case COMMAND_SLEEP_START:
            break;
        case COMMAND_SLEEP_END:
            PMi_SleepEndFlag = true;
            break;
        }
        func_020ce240(result);
    }

    // Sends the words of a command and waits for the answer, until the ARM7 runs it
    static void func_020ce39c(const unsigned long* data, int count)
    {
        for (;;)
        {
            volatile unsigned long result;
            int i;
            const int lastState = DisableIRQInterrupts();
            if (!func_020ce128())
            {
                SetIRQInterruptState(lastState);
                continue;
            }
            result = RESULT_NONE;
            PMi_Work.callback = func_020ce234;
            PMi_Work.callbackArg = (void*)&result;
            for (i = 0; i < count; i++)
                func_020ce870(data[i]);
            SetIRQInterruptState(lastState);
            while (result == RESULT_NONE)
                func_020c976c(RETRY_WAIT_CYCLES);
            if (result == PM_SUCCESS)
                break;
            func_020c976c(RETRY_WAIT_CYCLES);
        }
    }

    // PMi_SendSleepStart
    unsigned long func_020ce45c(unsigned short trigger, unsigned short keyIntrData)
    {
        unsigned long data[2];
        data[0] = MakeData1(PXI_START_BIT | PXI_END_BIT, 0, COMMAND_SYNC, 0);
        func_020ce39c(data, 1);
        while (func_020ceba8(PM_LCD_POWER_OFF, PM_LED_BLINK_LOW, false, true) != true)
        {
        }
        data[0] = MakeData1(PXI_START_BIT, 0, COMMAND_SLEEP_START, trigger);
        data[1] = MakeData2(PXI_END_BIT, 1, keyIntrData);
        func_020ce39c(data, 2);
        return PM_SUCCESS;
    }

    // PM_SendUtilityCommandAsync
    unsigned long func_020ce4e8(unsigned long number, unsigned short parameter, unsigned short* retValue,
                                PMCallback callback, void* arg)
    {
        const int lastState = DisableIRQInterrupts();
        if (!func_020ce128())
        {
            SetIRQInterruptState(lastState);
            return PM_BUSY;
        }
        PMi_Work.callback = callback;
        PMi_Work.callbackArg = arg;
        PMi_Work.work = retValue;
        func_020ce870(MakeData1(PXI_START_BIT, 0, COMMAND_UTILITY, number));
        func_020ce870(MakeData2(PXI_END_BIT, 1, parameter));
        SetIRQInterruptState(lastState);
        return PM_SUCCESS;
    }

    // PM_SendUtilityCommand
    unsigned long func_020ce56c(unsigned long number, unsigned short parameter, unsigned short* retValue)
    {
        unsigned long commandResult;
        const unsigned long sendResult = func_020ce4e8(number, parameter, retValue, func_020ce234, &commandResult);
        if (sendResult == PM_SUCCESS)
        {
            PMi_WaitBusyMethod();
            return commandResult;
        }
        return sendResult;
    }

    // PMi_SetLEDAsync
    unsigned long func_020ce5b0(int status, PMCallback callback, void* arg)
    {
        unsigned long command;
        switch (status)
        {
        case PM_LED_ON:
            command = UTIL_LED_ON;
            break;
        case PM_LED_BLINK_HIGH:
            command = UTIL_LED_BLINK_HIGH_SPEED;
            break;
        case PM_LED_BLINK_LOW:
            command = UTIL_LED_BLINK_LOW_SPEED;
            break;
        default:
            command = 0;
        }
        return command ? func_020ce4e8(command, 0, NULL, callback, arg) : PM_INVALID_COMMAND;
    }

    // PMi_SetLED
    unsigned long func_020ce614(int status)
    {
        unsigned long commandResult;
        const unsigned long sendResult = func_020ce5b0(status, func_020ce234, &commandResult);
        if (sendResult == PM_SUCCESS)
        {
            PMi_WaitBusyMethod();
            return commandResult;
        }
        return sendResult;
    }

    // PM_SetBackLightAsync
    unsigned long func_020ce648(int target, int sw, PMCallback callback, void* arg)
    {
        unsigned long command = 0;
        if (target == PM_LCD_TOP)
        {
            if (sw == PM_BACKLIGHT_ON)
                command = UTIL_LCD2_BACKLIGHT_ON;
            if (sw == PM_BACKLIGHT_OFF)
                command = UTIL_LCD2_BACKLIGHT_OFF;
        }
        else if (target == PM_LCD_BOTTOM)
        {
            if (sw == PM_BACKLIGHT_ON)
                command = UTIL_LCD1_BACKLIGHT_ON;
            if (sw == PM_BACKLIGHT_OFF)
                command = UTIL_LCD1_BACKLIGHT_OFF;
        }
        else if (target == PM_LCD_ALL)
        {
            if (sw == PM_BACKLIGHT_ON)
                command = UTIL_LCD12_BACKLIGHT_ON;
            if (sw == PM_BACKLIGHT_OFF)
                command = UTIL_LCD12_BACKLIGHT_OFF;
        }
        return command ? func_020ce4e8(command, 0, NULL, callback, arg) : PM_INVALID_COMMAND;
    }

    // PM_SetBackLight
    unsigned long func_020ce6d0(int target, int sw)
    {
        unsigned long commandResult;
        const unsigned long sendResult = func_020ce648(target, sw, func_020ce234, &commandResult);
        if (sendResult == PM_SUCCESS)
        {
            PMi_WaitBusyMethod();
            return commandResult;
        }
        return sendResult;
    }

    // PM_ForceToPowerOffAsync: turns the LCDs on first
    unsigned long func_020ce704(PMCallback callback, void* arg)
    {
        const PMWaitBusyMethod method = PMi_WaitBusyMethod;
        PMi_WaitBusyMethod = func_020ce1d8;
        func_020cef94();
        PMi_WaitBusyMethod = method;
        return func_020ce4e8(UTIL_FORCE_POWER_OFF, 0, NULL, callback, arg);
    }

    // PMi_ForceToPowerOff
    unsigned long func_020ce758()
    {
        unsigned long commandResult;
        const unsigned long sendResult = func_020ce704(func_020ce234, &commandResult);
        if (sendResult == PM_SUCCESS)
        {
            PMi_WaitBusyMethod = func_020ce188;
            PMi_WaitBusyMethod();
            PMi_WaitBusyMethod = func_020ce148;
            return commandResult;
        }
        return sendResult;
    }

    // PM_ForceToPowerOff
    unsigned long func_020ce7a4()
    {
        while (func_020ce758() != PM_SUCCESS)
            func_020c976c(RETRY_WAIT_CYCLES);
        DisableIRQInterrupts();
        ResetAllDMAChannels();
        for (;;)
            func_020c9bf0();
    }

    // Sends utility command 16 while the LCDs are on
    unsigned long func_020ce7e0(unsigned long value)
    {
        if (func_020cede0() == PM_LCD_POWER_OFF)
            return PM_SUCCESS;
        return func_020ce56c(UTIL_COMMAND_16, value, NULL);
    }

    // PM_GetBackLight
    unsigned long func_020ce810(int* top, int* bottom)
    {
        unsigned short status;
        unsigned long result;
        if ((result = func_020ce56c(UTIL_GET_STATUS, UTIL_STATUS_BACKLIGHT, &status)) == PM_SUCCESS)
        {
            if (top)
                *top = (status & STATUS_BACKLIGHT_TOP) ? PM_BACKLIGHT_ON : PM_BACKLIGHT_OFF;
            if (bottom)
                *bottom = (status & STATUS_BACKLIGHT_BOTTOM) ? PM_BACKLIGHT_ON : PM_BACKLIGHT_OFF;
        }
        return result;
    }

    // PMi_SendPxiData
    void func_020ce870(unsigned long data)
    {
        while (SendCommandToArm7(IPC_COMMAND_PM, data, false) != IPCResult_Success)
        {
        }
    }

    // PM_GoSleepMode
    void func_020ce89c(int trigger, int logic, unsigned short keyPattern)
    {
        int prepIrq;
        int prepIntrMode;
        unsigned int prepIntrMask;
        int powerOffFlag = false;
        int preTop;
        int preBottom;
        unsigned long preGX;
        unsigned long preGXS;
        int preLCDPower;

        func_020cef0c(PMi_PreSleepCallbackList);

        // Only the IPC and the tick's timer can interrupt the sleep
        prepIrq = DisableIrq();
        prepIntrMode = DisableIRQInterrupts();
        prepIntrMask = DisableSpecificInterrupts(IE_ALL);
        SetSpecificInterruptsEnabled(IE_FIFO_RECV | (Is64BitTimerInitialized() ? IE_TIMER0 : 0));
        SetIRQInterruptState(prepIntrMode);
        EnableIrq();

        // A DS Download Play child has no card to wake it up
        if (trigger & PM_TRIGGER_CARD)
        {
            if (BOOT_TYPE == BOOT_TYPE_MULTIBOOT)
                trigger &= ~PM_TRIGGER_CARD;
        }
        if (trigger & PM_TRIGGER_CARTRIDGE)
        {
            if (!func_020d135c())
                trigger &= ~PM_TRIGGER_CARTRIDGE;
        }

        preGX = DISPCNT;
        preGXS = DISPCNTSUB;
        preLCDPower = func_020cede0();
        while (func_020ce810(&preTop, &preBottom) != PM_SUCCESS)
            func_020c976c(RETRY_WAIT_CYCLES);
        while (func_020ce6d0(PM_LCD_ALL, PM_BACKLIGHT_OFF) != PM_SUCCESS)
            func_020c976c(RETRY_WAIT_CYCLES);

        // Turns the displays off between V-blanks
        {
            volatile unsigned long vcount = GetVBlankCount();
            while (vcount == GetVBlankCount())
            {
            }
            vcount = GetVBlankCount();
            DISPCNT = DISPCNT & ~0x30000;
            DISPCNTSUB = DISPCNTSUB & ~0x10000;
            while (vcount == GetVBlankCount())
            {
            }
            vcount = GetVBlankCount();
            while (vcount == GetVBlankCount())
            {
            }
        }

        PMi_SleepEndFlag = false;
        func_020ce45c(trigger | (preTop ? BACKLIGHT_RECOVER_TOP_ON : 0) | (preBottom ? BACKLIGHT_RECOVER_BOTTOM_ON : 0),
                      logic | keyPattern);
        while (!PMi_SleepEndFlag)
            func_020c9bf0();

        // The card was pulled out while the console slept
        if ((trigger & PM_TRIGGER_CARD) && (IF & IE_CARD_IREQ))
            powerOffFlag = true;

        if (!powerOffFlag)
        {
            if (preLCDPower == PM_LCD_POWER_ON)
            {
                while (func_020ceba8(PM_LCD_POWER_ON, PM_LED_ON, true, true) != true)
                {
                }
            }
            else
            {
                while (func_020ce614(PM_LED_ON) != PM_SUCCESS)
                    func_020c976c(RETRY_WAIT_CYCLES);
            }
            DISPCNT = preGX;
            DISPCNTSUB = preGXS;
        }

        func_020c976c(LCD_POWER_WAIT_CYCLES);

        DisableIRQInterrupts();
        SetSpecificInterruptsEnabled(prepIntrMask);
        SetIRQInterruptState(prepIntrMode);
        RestoreIrq(prepIrq);

        if (powerOffFlag)
            func_020ce7a4();

        func_020cef0c(PMi_PostSleepCallbackList);
    }

    // PMi_SetLCDPower
    int func_020ceba8(int sw, int led, int skip, int isSync)
    {
        switch (sw)
        {
        case PM_LCD_POWER_ON:
            if (!skip && VBLANK_COUNT - PMi_LCDCount <= LCD_OFF_WAIT_FRAMES)
                return false;
            if (led != PM_LED_NONE)
            {
                if (isSync)
                {
                    while (func_020ce614(led) != PM_SUCCESS)
                        func_020c976c(RETRY_WAIT_CYCLES);
                }
                else
                {
                    while (func_020ce5b0(led, NULL, NULL) != PM_SUCCESS)
                        func_020c976c(RETRY_WAIT_CYCLES);
                }
            }
            POWCNT |= 1;
            while (func_020ce7e0(sCommand16Value) != PM_SUCCESS)
                func_020c976c(RETRY_WAIT_CYCLES);
            break;
        case PM_LCD_POWER_OFF:
            while (func_020ce7e0(0) != PM_SUCCESS)
                func_020c976c(RETRY_WAIT_CYCLES);
            if (VBLANK_COUNT - sInitCount <= LCD_INIT_WAIT_FRAMES)
            {
                func_020c9820();
                func_020c9820();
            }
            POWCNT &= ~1;
            PMi_LCDCount = VBLANK_COUNT;
            if (led != PM_LED_NONE)
            {
                if (isSync)
                {
                    while (func_020ce614(led) != PM_SUCCESS)
                        func_020c976c(RETRY_WAIT_CYCLES);
                }
                else
                {
                    while (func_020ce5b0(led, NULL, NULL) != PM_SUCCESS)
                        func_020c976c(RETRY_WAIT_CYCLES);
                }
            }
            break;
        }
        return true;
    }

    // PM_SetLCDPower
    int func_020cedc0(int sw)
    {
        if (sw != PM_LCD_POWER_ON)
            sw = PM_LCD_POWER_OFF;
        return func_020ceba8(sw, PM_LED_NONE, false, true);
    }

    // PM_GetLCDPower
    int func_020cede0()
    {
        return (POWCNT & 1) ? PM_LCD_POWER_ON : PM_LCD_POWER_OFF;
    }

    // PM_SetLEDPattern
    unsigned long func_020cedfc(unsigned long pattern)
    {
        return func_020ce56c(UTIL_SET_LED_PATTERN, pattern, NULL);
    }

    // PM_GetLEDPattern
    unsigned long func_020cee18(unsigned long* patternBuf)
    {
        unsigned short status;
        unsigned long result;
        if ((result = func_020ce56c(UTIL_GET_STATUS, UTIL_STATUS_LED_PATTERN, &status)) == PM_SUCCESS)
        {
            if (patternBuf)
                *patternBuf = status;
        }
        return result;
    }

    // PMi_PrependList
    void func_020cee54(SleepCallbackInfo** listp, SleepCallbackInfo* info)
    {
        if (!listp)
            return;
        info->next = *listp;
        *listp = info;
    }

    // PMi_AppendList
    void func_020cee68(SleepCallbackInfo** listp, SleepCallbackInfo* info)
    {
        if (!listp)
            return;
        if (!*listp)
        {
            info->next = NULL;
            *listp = info;
        }
        else
        {
            SleepCallbackInfo* p = *listp;
            while (p->next)
                p = p->next;
            info->next = p->next;
            p->next = info;
        }
    }

    // PMi_DeleteList
    void func_020ceeb4(SleepCallbackInfo** listp, SleepCallbackInfo* info)
    {
        SleepCallbackInfo* p;
        SleepCallbackInfo* pre;
        int lastState;
        if (!listp)
            return;
        lastState = DisableIRQInterrupts();
        pre = p = *listp;
        while (p)
        {
            if (p == info)
            {
                if (p == pre)
                    *listp = p->next;
                else
                    pre->next = p->next;
                break;
            }
            pre = p;
            p = p->next;
        }
        SetIRQInterruptState(lastState);
    }

    // PMi_ExecuteList
    void func_020cef0c(SleepCallbackInfo* listp)
    {
        while (listp)
        {
            listp->callback(listp->arg);
            listp = listp->next;
        }
    }

    // PM_PrependPreSleepCallback
    void func_020cef34(SleepCallbackInfo* info)
    {
        func_020cee54(&PMi_PreSleepCallbackList, info);
    }

    // PM_AppendPostSleepCallback
    void func_020cef4c(SleepCallbackInfo* info)
    {
        func_020cee68(&PMi_PostSleepCallbackList, info);
    }

    // PM_DeletePreSleepCallback
    void func_020cef64(SleepCallbackInfo* info)
    {
        func_020ceeb4(&PMi_PreSleepCallbackList, info);
    }

    // PM_DeletePostSleepCallback
    void func_020cef7c(SleepCallbackInfo* info)
    {
        func_020ceeb4(&PMi_PostSleepCallbackList, info);
    }

    // Turns the LCDs on before the console is turned off, with the backlights off
    void func_020cef94()
    {
        func_020c976c(LCD_POWER_WAIT_CYCLES);
        if (func_020cede0() == PM_LCD_POWER_ON)
            return;
        while (func_020ce6d0(PM_LCD_ALL, PM_BACKLIGHT_OFF) != PM_SUCCESS)
            func_020c976c(RETRY_WAIT_CYCLES);
        while (!func_020cedc0(PM_LCD_POWER_ON))
            func_020c976c(10);
    }
}
