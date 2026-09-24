#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_terminate_proc.c

extern "C"
{
    void func_020c9bf0();

    // usa: func_020c9be0
    // OS_Terminate: stops the program
    void func_020c9be0()
    {
        while (true)
        {
            DisableIRQInterrupts();
            func_020c9bf0();
        }
    }

    // usa: func_020c9bf0
    // OS_Halt: waits for an interrupt
    asm void func_020c9bf0()
    {
        mov r0, #0
        mcr p15, 0, r0, c7, c0, 4
        bx lr
    }
}
