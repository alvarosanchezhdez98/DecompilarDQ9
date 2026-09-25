#include "System/DTCM.h"
#include "System/ProcessorContext.h"

// The NitroSDK's os_irqHandler.c: the handler of the interrupts, which the NitroSDK wrote in assembly. It's in the
// ITCM, so that it's fast.

extern "C"
{
    // CP_SaveContext
    void func_020cd594();
    // CPi_RestoreContext
    void func_020cd5d4();
    void func_01ff8068();

    // OS_IrqHandler: calls the handler of the interrupt with the highest priority (data_027e0000 is the table of the
    // handlers, OS_IRQTable), and returns to OS_IrqHandler_ThreadSwitch
    asm void func_01ff8000()
    {
        stmdb sp!, {lr}
        mov r12, #0x4000000
        add r12, r12, #0x210
        ldr r1, [r12, #-0x8]
        cmp r1, #0x0
        beq @L01ff801c
        b @L01ff8020
    @L01ff801c:
        ldmia sp!, {pc}
    @L01ff8020:
        ldmia r12, {r1, r2}
        ands r1, r1, r2
        beq @L01ff8030
        b @L01ff8034
    @L01ff8030:
        ldmia sp!, {pc}
    @L01ff8034:
        mov r3, #0x80000000
    @L01ff8038:
        clz r0, r1
        bics r1, r1, r3, lsr r0
        bne @L01ff8038
        mov r1, r3, lsr r0
        str r1, [r12, #0x4]
        rsbs r0, r0, #0x1f
        ldr r1, =data_027e0000
        ldr r0, [r1, r0, lsl #0x2]
        ldr lr, =func_01ff8068
        bx r0
    }

    // OS_IrqHandler_ThreadSwitch: wakes the threads that wait for an interrupt (data_027e0060), and switches to the
    // thread with the highest priority if it has to (data_02111304, OSi_ThreadInfo)
    asm void func_01ff8068()
    {
        ldr r12, =data_027e0060
        mov r3, #0x0
        ldr r12, [r12, #0x0]
        mov r2, #0x1
        cmp r12, #0x0
        beq @L01ff80b8
    @L01ff8080:
        str r2, [r12, #0x64]
        str r3, [r12, #0x78]
        str r3, [r12, #0x7c]
        ldr r0, [r12, #0x80]
        str r3, [r12, #0x80]
        mov r12, r0
        cmp r12, #0x0
        bne @L01ff8080
        ldr r12, =data_027e0060
        str r3, [r12, #0x0]
        str r3, [r12, #0x4]
        ldr r12, =data_02111304
        mov r1, #0x1
        strh r1, [r12, #0x0]
    @L01ff80b8:
        ldr r12, =data_02111304
        ldrh r1, [r12, #0x0]
        cmp r1, #0x0
        beq @L01ff80cc
        b @L01ff80d0
    @L01ff80cc:
        ldr pc, [sp], #0x4
    @L01ff80d0:
        mov r1, #0x0
        strh r1, [r12, #0x0]
        mov r3, #0xd2
        msr cpsr_c, r3
        add r2, r12, #0x8
        ldr r1, [r2, #0x0]
    @L01ff80e8:
        cmp r1, #0x0
        bne @L01ff80f4
        b @L01ff80f8
    @L01ff80f4:
        ldrh r0, [r1, #0x64]
    @L01ff80f8:
        bne @L01ff8100
        b @L01ff8104
    @L01ff8100:
        cmp r0, #0x1
    @L01ff8104:
        bne @L01ff810c
        b @L01ff8110
    @L01ff810c:
        ldr r1, [r1, #0x68]
    @L01ff8110:
        bne @L01ff80e8
        cmp r1, #0x0
        bne @L01ff8128
    @L01ff811c:
        mov r3, #0x92
        msr cpsr_c, r3
        ldr pc, [sp], #0x4
    @L01ff8128:
        ldr r0, [r12, #0x4]
        cmp r1, r0
        beq @L01ff811c
        ldr r3, [r12, #0xc]
        cmp r3, #0x0
        beq @L01ff8150
        stmdb sp!, {r0, r1, r12}
        mov lr, pc
        bx r3
        ldmia sp!, {r0, r1, r12}
    @L01ff8150:
        str r1, [r12, #0x4]
        mrs r2, spsr
        str r2, [r0, #0x0]!
        stmdb sp!, {r0, r1}
        add r0, r0, #0x0
        add r0, r0, #0x48
        ldr r1, =func_020cd594
        blx r1
        ldmia sp!, {r0, r1}
        ldmib sp!, {r2, r3}
        stmib r0!, {r2, r3}
        ldmib sp!, {r2, r3, r12, lr}
        stmib r0!, {r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr}^
        stmib r0!, {lr}
        mov r3, #0xd3
        msr cpsr_c, r3
        stmib r0!, {sp}
        stmdb sp!, {r1}
        add r0, r1, #0x0
        add r0, r0, #0x48
        ldr r1, =func_020cd5d4
        blx r1
        ldmia sp!, {r1}
        ldr sp, [r1, #0x44]
        mov r3, #0xd2
        msr cpsr_c, r3
        ldr r2, [r1, #0x0]!
        msr spsr_fc, r2
        ldr lr, [r1, #0x40]
        ldmib r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr}^
        mov r0, r0
        stmda sp!, {r0, r1, r2, r3, r12, lr}
        ldmia sp!, {pc}
    }
}
