#include "System/ProcessorContext.h"

// The NitroSDK's os_context.c: saves and restores the registers of a context, in assembly

extern "C"
{
    // The NitroSDK's CP_SaveContext and CPi_RestoreContext: save and restore the divider and square root registers
    void func_020cd594(void* mathRegisters);
    void func_020cd5d4(void* mathRegisters);

#ifdef __MWERKS__
    // OS_SaveContext: returns 0 when saving, and 1 when the context is restored
    asm int SaveContext(register ProcessorContext* context)
    {
        stmfd sp!, {r0, lr}
        add r0, r0, #0x48 // mathRegisters
        ldr r1, =func_020cd594
        blx r1
        ldmfd sp!, {r0, lr}

        add r1, r0, #0 // cpsr
        mrs r2, cpsr
        str r2, [r1], #4

        mov r0, #0xd3 // supervisor mode, interrupts disabled
        msr cpsr_c, r0
        str sp, [r1, #0x40] // supervisor stack pointer
        msr cpsr_c, r2

        mov r0, #1 // value of r0 once restored
        stmia r1, {r0-r14}
        add r0, pc, #8
        str r0, [r1, #0x3c] // pc + 4, returning after "bx lr" below

        mov r0, #0
        bx lr
    }

    // OS_LoadContext: restores the registers, and continues where the context was saved
    asm void RestoreContext(register ProcessorContext* context)
    {
        stmfd sp!, {r0, lr}
        add r0, r0, #0x48 // mathRegisters
        ldr r1, =func_020cd5d4
        blx r1
        ldmfd sp!, {r0, lr}

        mrs r1, cpsr
        bic r1, r1, #0x1f
        orr r1, r1, #0xd3 // supervisor mode, interrupts disabled
        msr cpsr_c, r1

        ldr r1, [r0], #4 // cpsr
        msr spsr_fsxc, r1

        ldr sp, [r0, #0x40] // supervisor stack pointer
        ldr lr, [r0, #0x3c] // pc + 4
        ldmia r0, {r0-r14}^
        nop

        subs pc, lr, #4
    }
#endif
}
