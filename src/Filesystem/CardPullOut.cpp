#include "System/DMA.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's card_pullOut.c: stops the game when the card is pulled out. CARD_SetPulledOutCallback and
// CARD_CheckPulledOut aren't in the ROM.

// The IPC command of the card's removal (the NitroSDK's PXI_FIFO_TAG_CARD), and its commands (CARD_PXI_COMMAND_*)
#define IPC_COMMAND_CARD_PULL_OUT 14
#define CARD_COMMAND_MASK 0x3f
#define CARD_COMMAND_TERMINATE 0x01
#define CARD_COMMAND_PULLED_OUT 0x11

// HW_BUTTON_XY_BUF, where the ARM7 writes the buttons X and Y, and whether the DS is closed (PAD_DetectFold)
#define BUTTONS_XY (*(volatile unsigned short*)0x027fffa8)
#define BUTTONS_XY_FOLDED 0x8000
// HW_CHECK_DEBUGGER_SW, and where the card's ID is: HW_RED_RESERVED on a debugger, HW_BOOT_CHECK_INFO_BUF otherwise
#define DEBUGGER_SWITCH (*(unsigned short*)0x027ffc10)
#define DEBUGGER_CARD_ID 0x027ff800
#define CARD_ID 0x027ffc00

// PM_RESULT_SUCCESS, and SPI_PXI_RESULT_EXCLUSIVE, when the ARM7 is busy with another command
#define POWER_SUCCESS 0
#define POWER_BUSY 4

// CARDPulledOutCallback: returns whether to stop the game right away
typedef int (*PulledOutCallback)();

// CARDi_IsPulledOutFlag
static int isPulledOut = false;
// CARD_UserCallback
static PulledOutCallback userCallback;

// PAD_DetectFold
static inline int IsFolded()
{
    return (BUTTONS_XY & BUTTONS_XY_FOLDED) >> 15;
}

extern "C"
{
    // usa: func_020c9be0
    // OS_Terminate
    void func_020c9be0();
    // usa: func_020c976c
    // OS_SpinWait
    void func_020c976c(unsigned long cycles);
    // usa: func_020ce7a4
    // PM_ForceToPowerOff
    unsigned long func_020ce7a4();
    // BIOS: waits for a number of loops of 4 cycles
    void WaitByLoop(int count);

    void func_020d1144(unsigned int command, unsigned int data, unsigned int error);
    void func_020d11a8();
    void func_020d1294(unsigned long data, unsigned long wait);

    // usa: func_020d1118
    // CARD_InitPulledOutCallback
    void func_020d1118()
    {
        InitializeInterProcessorCommunication();
        SetArm9IPCCommandHandler(IPC_COMMAND_CARD_PULL_OUT, func_020d1144);
        userCallback = NULL;
    }

    // usa: func_020d1144
    // CARDi_PulledOutCallback
    void func_020d1144(unsigned int command, unsigned int data, unsigned int error)
    {
        unsigned long cardCommand = data & CARD_COMMAND_MASK;

        if (cardCommand == CARD_COMMAND_PULLED_OUT)
        {
            if (isPulledOut == false)
            {
                int terminate = true;

                isPulledOut = true;
                if (userCallback)
                {
                    terminate = userCallback();
                }
                if (terminate)
                {
                    func_020d11a8();
                }
            }
        }
        else
        {
            func_020c9be0();
        }
    }

    // usa: func_020d1198
    // CARD_IsPulledOut
    int func_020d1198()
    {
        return isPulledOut;
    }

    // usa: func_020d11a8
    // CARD_TerminateForPulledOut: turns the power off if the DS is closed, and stops the game
    void func_020d11a8()
    {
        int shouldHalt = true;

        ResetDMAChannel(0);
        ResetDMAChannel(1);
        ResetDMAChannel(2);
        ResetDMAChannel(3);

        if (IsFolded())
        {
            unsigned long result;
            while ((result = func_020ce7a4()) == POWER_BUSY)
            {
                // 10 ms
                func_020c976c(67027964 / 100);
            }
            if (result == POWER_SUCCESS)
            {
                shouldHalt = false;
            }
        }

        if (shouldHalt)
        {
            func_020d1294(CARD_COMMAND_TERMINATE, 1);
        }

        func_020c9be0();
    }

    // usa: func_020d1234
    // CARDi_CheckPulledOutCore: calls the callback if the card's ID changed
    void func_020d1234(unsigned long id)
    {
        volatile unsigned long cardID = *(volatile unsigned long*)(DEBUGGER_SWITCH == 0 ? DEBUGGER_CARD_ID : CARD_ID);

        if (id != (unsigned long)cardID)
        {
            int priorState = DisableIRQInterrupts();
            func_020d1144(IPC_COMMAND_CARD_PULL_OUT, CARD_COMMAND_PULLED_OUT, false);
            SetIRQInterruptState(priorState);
        }
    }

    // usa: func_020d1294
    // CARDi_SendtoPxi
    void func_020d1294(unsigned long data, unsigned long wait)
    {
        while (SendCommandToArm7(IPC_COMMAND_CARD_PULL_OUT, data, false) != IPCResult_Success)
        {
            WaitByLoop((long)wait);
        }
    }
}
