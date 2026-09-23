#include "System/Arena.h"
#include "System/GamecardBusOwnership.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "Filesystem/CardReadManager.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_init.c

extern "C"
{
    // usa: func_020c6d48
    // OS_SetIrqStackChecker
    void func_020c6d48();
    // usa: func_020c8a3c
    // OS_InitException
    void func_020c8a3c();
    // usa: func_020cad00
    // MI_Init
    void func_020cad00();
    // usa: func_020c9288
    // OS_InitVAlarm
    void func_020c9288();
    // usa: func_020c9a54
    // OSi_InitVramExclusive
    void func_020c9a54();
    // usa: func_020c745c
    // OS_InitThread
    void func_020c745c();
    // usa: func_020c983c
    // OS_InitReset
    void func_020c983c();
    // usa: func_020d15fc
    // CTRDG_Init
    void func_020d15fc();
    // usa: func_020ce270
    // PM_Init
    void func_020ce270();

    // usa: func_020c8348
    // OSi_WaitVCount0: waits for the first line of the screen, with interrupts disabled
#ifdef __MWERKS__
    asm void func_020c8348()
    {
        mov r12, #0x04000000
        ldr r1, [r12, #0x208] // REG_IME
        str r12, [r12, #0x208] // disables interrupts, since bit 0 is clear
    @wait:
        ldrh r0, [r12, #6] // REG_VCOUNT
        cmp r0, #0
        bne @wait
        str r1, [r12, #0x208]
        bx lr
    }
#else
    void func_020c8348()
    {
        volatile unsigned int* ime = (volatile unsigned int*)0x04000208;
        unsigned int priorState = *ime;
        *ime = 0;
        while (*(volatile unsigned short*)0x04000006 != 0)
        {
        }
        *ime = priorState;
    }
#endif

    // usa: func_020c8368
    // OS_Init: initializes the NitroSDK's systems
    void func_020c8368()
    {
        func_020c83b0();
        InitializeInterProcessorCommunication();
        InitializeGamecardBusOwnership();
        func_020c84b4();
        InitializeInterruptContextBlock_020c6ad4();
        func_020c6d48();
        func_020c8a3c();
        func_020cad00();
        func_020c9288();
        func_020c9a54();
        func_020c745c();
        func_020c983c();
        func_020d15fc();
        InitializeCardReading();
        func_020ce270();
        func_020c8348();
    }
}
