#include "Filesystem/CardReadManager.h"
#include "System/DMA.h"
#include "System/DTCM.h"
#include "System/GamecardBusOwnership.h"
#include "System/IPC.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_reset.c: resets the system, together with the ARM7. OSi_DoResetSystem and the functions that it
// calls are in the ITCM. OS_IsResetOccurred isn't in the ROM.

// The IPC command of the OS (the NitroSDK's PXI_FIFO_TAG_OS), and what the ARM7 sends with it
#define IPC_COMMAND_OS 12
#define OS_COMMAND_RESET 0x10
#define OS_COMMAND_MASK 0x7f00
#define OS_COMMAND_SHIFT 8

// HW_BOOT_CHECK_INFO_BUF: 2 when the program was downloaded (a multiboot child)
#define BOOT_TYPE (*(unsigned short*)0x027ffc40)
#define BOOT_TYPE_MULTIBOOT 2
// HW_RESET_PARAMETER_BUF
#define RESET_PARAMETER (*(volatile unsigned long*)0x027ffc20)

// OSi_IsResetOccurred: the ARM7 is ready to reset. OSi_DoResetSystem, in the ITCM, waits for it.
volatile unsigned short isResetOccurred;
// OSi_IsInitReset
static unsigned short isInitialized;

// MB_IsMultiBootChild
static inline int IsMultiBootChild()
{
    return BOOT_TYPE == BOOT_TYPE_MULTIBOOT;
}

extern "C"
{
    // usa: func_020c9be0
    // OS_Terminate
    void func_020c9be0();
    // OSi_DoResetSystem, in the ITCM
    void func_01ff81e4();

    void func_020c9890(unsigned int command, unsigned int data, unsigned int error);

    // usa: func_020c983c
    // OS_InitReset
    void func_020c983c()
    {
        if (isInitialized)
        {
            return;
        }
        isInitialized = true;

        InitializeInterProcessorCommunication();
        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_OS, IPCSide_Arm7))
        {
        }
        SetArm9IPCCommandHandler(IPC_COMMAND_OS, func_020c9890);
    }

    // usa: func_020c9890
    // OSi_CommonCallback: receives the ARM7's commands
    void func_020c9890(unsigned int command, unsigned int data, unsigned int error)
    {
        unsigned short osCommand = (unsigned short)((data & OS_COMMAND_MASK) >> OS_COMMAND_SHIFT);

        if (osCommand == OS_COMMAND_RESET)
        {
            isResetOccurred = true;
        }
        else
        {
            func_020c9be0();
        }
    }

    // usa: func_020c98c4
    // OSi_SendToPxi: sends a command to the ARM7
    void func_020c98c4(unsigned short osCommand)
    {
        unsigned long data = (unsigned long)osCommand << OS_COMMAND_SHIFT;

        while (SendCommandToArm7(IPC_COMMAND_OS, data, false) != IPCResult_Success)
        {
        }
    }

    // usa: func_020c98f0
    // OS_ResetSystem: resets the system, passing a parameter to the program after the reset
    void func_020c98f0(unsigned long parameter)
    {
        if (IsMultiBootChild())
        {
            func_020c9be0();
        }

        NitroVM_Command_AcquireCardReadResources((unsigned short)GenerateLockOwnerID());

        SetSpecificInterruptsEnabled(IRQ_MASK_FIFO_RECEIVE_NOT_EMPTY);
        AcknowledgeSpecificInterrupts(~IRQ_MASK_FIFO_RECEIVE_NOT_EMPTY);
        ResetDMAChannel(0);
        ResetDMAChannel(1);
        ResetDMAChannel(2);
        ResetDMAChannel(3);

        RESET_PARAMETER = parameter;
        func_020c98c4(OS_COMMAND_RESET);

        // Resets from the ITCM, with the stack below the IRQ's
        asm
        {
            ldr r0, =0x027e3f80
            ldr r1, =SDK_IRQ_STACKSIZE
            sub r0, r0, r1
            mov sp, r0
            bl func_01ff81e4
        }
    }
}
