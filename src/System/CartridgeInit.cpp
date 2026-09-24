// Compiled with -ipa file, which must come before the declarations: the compiler generates the code at the end of the
// file, so it sorts all of the file's data by size, including the function-local statics (see Decompiling.md)
#pragma ipa file

#include "System/Cartridge.h"
#include "System/Cache.h"
#include "System/DMA.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "System/ProcessorContext.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's ctrdg_proc.c: initializes the cartridge library, and stops the game when the cartridge is pulled
// out. CTRDG_SetPulledOutCallback, CTRDG_SendToARM7, CTRDG_CheckPulledOut and CTRDG_SetPhiClock aren't in the ROM,
// but CTRDG_CheckPulledOut is here for its data.

// The IPC command that sets the GBA slot's clock (the NitroSDK's PXI_FIFO_TAG_CTRDG_PHI)
#define IPC_COMMAND_CARTRIDGE_PHI 17

// HW_CTRDG_ROM, where the header is
#define CARTRIDGE_ROM 0x08000000
// The Nintendo logo in the ARM9's BIOS (CTRDG_SYSROM9_NINLOGO_ADR)
#define BIOS_NINTENDO_LOGO 0xffff0020
// HW_IS_CTRDG_EXIST and HW_SET_CTRDG_MODULE_INFO_ONCE, in the system's work area
#define CARTRIDGE_EXISTS (*(unsigned char*)0x027fff9b)
#define MODULE_INFO_SET_ONCE (*(unsigned char*)0x027fff9a)

// POSTFLG's flag that the system booted (REG_OS_PAUSE_CHK_MASK)
#define POSTFLG (*(volatile unsigned short*)0x04000300)
#define POSTFLG_BOOTED 1
#define INTERRUPT_MASTER_ENABLE (*(volatile unsigned short*)0x04000208)
// EXMEMCNT's bit of the processor with the priority on the main memory (MI_GetMainMemoryPriority)
#define EXMEMCNT (*(volatile unsigned short*)0x04000204)
#define MAIN_MEMORY_PRIORITY_MASK 0x8000
#define MAIN_MEMORY_PRIORITY_SHIFT 15

// CTRDGPulledOutCallback: returns whether to stop the game right away
typedef int (*PulledOutCallback)();

// CTRDGi_Lock
static int isSettingPhi = false;
// CTRDG_UserCallback
PulledOutCallback pulledOutCallback = NULL;
// isCartridgePullOut and skipCheck, for CTRDG_CheckPulledOut
static int isCartridgePulledOut = false;
static int skipCheck = false;
// ctrdg_already_pullout
static int isAlreadyPulledOut = false;
// CTRDG_Init's isInitialized
static int isInitialized;
// CTRDG_Init's CTRDGTaskList
static CartridgeTaskWork taskWork;

extern "C"
{
    // usa: func_020c9be0
    // OS_Terminate
    void func_020c9be0();
    // usa: func_020ca408
    // MIi_CpuCopy32
    void func_020ca408(const void* src, void* dst, unsigned int length);
    // BIOS: waits for a number of loops of 4 cycles
    void WaitByLoop(int count);

    void func_020d16b0();
    void func_020d18a4(unsigned int command, unsigned int data, unsigned int error);
    void func_020d18d0(unsigned int command, unsigned int data, unsigned int error);
    void func_020d192c();
    void func_020d1940(unsigned int command, unsigned int data, unsigned int error);

    // usa: func_020d15fc
    // CTRDG_Init
    void func_020d15fc()
    {
        if (isInitialized)
        {
            return;
        }
        isInitialized = true;

        func_020d12e4();
        isAlreadyPulledOut = false;

        InitializeInterProcessorCommunication();
        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_CARTRIDGE, IPCSide_Arm7))
        {
        }
        SetArm9IPCCommandHandler(IPC_COMMAND_CARTRIDGE, func_020d18a4);
        func_020d16b0();
        SetArm9IPCCommandHandler(IPC_COMMAND_CARTRIDGE, NULL);
        SetArm9IPCCommandHandler(IPC_COMMAND_CARTRIDGE, func_020d18d0);

        pulledOutCallback = NULL;
        func_020d1954(&taskWork);

        SetArm9IPCCommandHandler(IPC_COMMAND_CARTRIDGE_PHI, func_020d1940);
        func_020d15b4(false);
    }

    // usa: func_020d16b0
    // CTRDGi_InitModuleInfo: reads the cartridge's header, and gives it to the ARM7
    void func_020d16b0()
    {
        // Function-local, like in the original: the compiler then knows that reading POSTFLG doesn't change it, and
        // reads it before setting it
        static int isModuleInfoInitialized = false;
        // headerBuf: the header of the cartridge, for the ARM7. Defined after isModuleInfoInitialized, it's after it in
        // the order of the data, like in the original.
        static GBACartridgeHeader header __attribute__((aligned(32)));
        CartridgeLock lock;
        unsigned int lastInterrupts;
        unsigned short lastMasterEnable;

        if (isModuleInfoInitialized)
        {
            return;
        }
        isModuleInfoInitialized = true;

        if (!(POSTFLG & POSTFLG_BOOTED))
        {
            return;
        }

        lastInterrupts = SetSpecificInterruptsEnabled(IRQ_MASK_FIFO_RECEIVE_NOT_EMPTY);
        lastMasterEnable = INTERRUPT_MASTER_ENABLE;
        INTERRUPT_MASTER_ENABLE = 1;

        func_020d14e4(cartridgeWork.lockID, &lock);
        {
            int priority = (EXMEMCNT & MAIN_MEMORY_PRIORITY_MASK) >> MAIN_MEMORY_PRIORITY_SHIFT;
            CartridgeRomCycle cycle;

            func_020d1468(&cycle);
            EXMEMCNT &= ~MAIN_MEMORY_PRIORITY_MASK;
            InvalidateDataCacheRange(&((unsigned char*)&header)[0x80], sizeof(header) - 0x80);
            DMAMemcpySynchronous16Bit(1, CARTRIDGE_ROM + 0x80, (unsigned int)&((unsigned char*)&header)[0x80],
                sizeof(header) - 0x80);
            EXMEMCNT = (unsigned short)((EXMEMCNT & ~MAIN_MEMORY_PRIORITY_MASK) | (priority << MAIN_MEMORY_PRIORITY_SHIFT));
            func_020d14b0(&cycle);
        }
        func_020d1540(cartridgeWork.lockID, &lock);

        if (CARTRIDGE_EXISTS || !MODULE_INFO_SET_ONCE)
        {
            int i;
            GBACartridgeHeader* src = &header;
            CartridgeModuleInfo* info = CARTRIDGE_MODULE_INFO;

            info->moduleID = src->moduleID;
            for (i = 0; i < 3; i++)
            {
                info->exLsiID[i] = src->exLsiID[i];
            }
            info->makerCode = src->makerCode;
            info->gameCode = src->gameCode;
            CARTRIDGE_EXISTS = (unsigned char)(func_020d135c() ? 1 : 0);
            MODULE_INFO_SET_ONCE = true;
        }

        func_020ca408((const void*)BIOS_NINTENDO_LOGO, &header.nintendoLogo, sizeof(header.nintendoLogo));
        CleanInvalidateDataCache();
        func_020d1564(CARTRIDGE_COMMAND_INIT_MODULE_INFO |
            ((((unsigned long)&header - 0x02000000) >> 5) << CARTRIDGE_COMMAND_PARAM_SHIFT));

        while (cartridgeWork.subProcessorInitialized != true)
        {
            WaitByLoop(1);
        }

        // OS_RestoreIrq, which reads the previous state to return it
        (void)INTERRUPT_MASTER_ENABLE;
        INTERRUPT_MASTER_ENABLE = lastMasterEnable;
        SetSpecificInterruptsEnabled(lastInterrupts);
    }

    // usa: func_020d18a4
    // CTRDGi_CallbackForInitModuleInfo
    void func_020d18a4(unsigned int command, unsigned int data, unsigned int error)
    {
        if ((data & CARTRIDGE_COMMAND_MASK) == CARTRIDGE_COMMAND_INIT_MODULE_INFO)
        {
            cartridgeWork.subProcessorInitialized = true;
        }
        else
        {
            func_020c9be0();
        }
    }

    // usa: func_020d18d0
    // CTRDGi_PulledOutCallback
    void func_020d18d0(unsigned int command, unsigned int data, unsigned int error)
    {
        if ((data & CARTRIDGE_COMMAND_MASK) == CARTRIDGE_COMMAND_PULLED_OUT)
        {
            if (isAlreadyPulledOut == false)
            {
                int terminate = false;

                if (pulledOutCallback)
                {
                    terminate = pulledOutCallback();
                }
                if (terminate)
                {
                    func_020d192c();
                }
                isAlreadyPulledOut = true;
            }
        }
        else
        {
            func_020c9be0();
        }
    }

    // usa: func_020d192c
    // CTRDG_TerminateForPulledOut
    void func_020d192c()
    {
        func_020d1564(CARTRIDGE_COMMAND_TERMINATE);
        func_020c9be0();
    }

    // CTRDG_IsPulledOut, in Cartridge.cpp
    int CTRDG_IsPulledOut();

    // CTRDG_CheckPulledOut: it isn't in the ROM, but without it, the compiler would remove isCartridgePulledOut and
    // skipCheck, which are in the ROM's data

    void CTRDG_CheckPulledOut()
    {
        if (skipCheck || isCartridgePulledOut)
        {
            return;
        }

        isCartridgePulledOut = CTRDG_IsPulledOut();
        if (!func_020d135c())
        {
            if (!isCartridgePulledOut)
            {
                skipCheck = true;
                return;
            }
        }
        if (isCartridgePulledOut)
        {
            func_020d18d0(IPC_COMMAND_CARTRIDGE, CARTRIDGE_COMMAND_PULLED_OUT, false);
        }
    }

    // usa: func_020d1940
    // CTRDGi_CallbackForSetPhi
    void func_020d1940(unsigned int command, unsigned int data, unsigned int error)
    {
        isSettingPhi = false;
    }
}
