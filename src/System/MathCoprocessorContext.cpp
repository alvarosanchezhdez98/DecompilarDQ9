#include "System/ProcessorContext.h"

// The NitroSDK's cp_context.c: saves and restores the registers of the divider and square root unit, for the
// contexts (see SaveRestoreContext.cpp). Written in assembly.

extern "C"
{
    // usa: func_020cd594
    // CP_SaveContext
    asm void func_020cd594(ProcessorContext::MathRegisters* registers)
    {
        ldr r1, =0x04000290 // REG_DIV_NUMER
        stmdb sp!, {r4}
        ldmia r1, {r2, r3, r4, r12}
        stmia r0!, {r2, r3, r4, r12}
        ldrh r12, [r1, #-0x10] // REG_DIVCNT
        add r1, r1, #0x28 // REG_SQRT_PARAM
        ldmia r1, {r2, r3}
        stmia r0!, {r2, r3}
        and r12, r12, #0x3
        ldrh r2, [r1, #-0x8] // REG_SQRTCNT
        strh r12, [r0, #0x0]
        and r2, r2, #0x1
        strh r2, [r0, #0x2]
        ldmia sp!, {r4}
        bx lr
    }

    // usa: func_020cd5d4
    // CPi_RestoreContext
    asm void func_020cd5d4(const ProcessorContext::MathRegisters* registers)
    {
        stmdb sp!, {r4}
        ldr r1, =0x04000290 // REG_DIV_NUMER
        ldmia r0, {r2, r3, r4, r12}
        stmia r1, {r2, r3, r4, r12}
        ldrh r2, [r0, #0x18] // div_control
        ldrh r3, [r0, #0x1a] // sqrt_control
        strh r2, [r1, #-0x10] // REG_DIVCNT
        strh r3, [r1, #0x20] // REG_SQRTCNT
        add r0, r0, #0x10 // sqrt_param
        add r1, r1, #0x28 // REG_SQRT_PARAM
        ldmia r0, {r2, r3}
        stmia r1, {r2, r3}
        ldmia sp!, {r4}
        bx lr
    }
}
