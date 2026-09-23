#include "System/Memory.h"

// The NitroSDK's mi_memory.c: copies and fills memory with the CPU. The NitroSDK wrote these functions in assembly.
// In the original, each conditional instruction became a conditional branch over an unconditional one, like in
// OS_GetLockID (see GamecardBusOwnership.cpp), so the branches are written out.

extern "C"
{
#ifdef __MWERKS__
    // usa: func_020ca390
    // MIi_CpuClear16
    asm void func_020ca390(int value, void* dst, unsigned int len)
    {
        mov r3, #0x0
    @L020ca3a4:
        cmp r3, r2
        blt @L020ca3b0
        b @L020ca3b4
    @L020ca3b0:
        strh r0, [r1, r3]
    @L020ca3b4:
        blt @L020ca3bc
        b @L020ca3c0
    @L020ca3bc:
        add r3, r3, #0x2
    @L020ca3c0:
        blt @L020ca3a4
        bx lr
    }

    // usa: func_020ca3b8
    // MIi_CpuCopy16
    asm void func_020ca3b8(const void* src, void* dst, unsigned int len)
    {
        mov r12, #0x0
    @L020ca3cc:
        cmp r12, r2
        blt @L020ca3d8
        b @L020ca3dc
    @L020ca3d8:
        ldrh r3, [r0, r12]
    @L020ca3dc:
        blt @L020ca3e4
        b @L020ca3e8
    @L020ca3e4:
        strh r3, [r1, r12]
    @L020ca3e8:
        blt @L020ca3f0
        b @L020ca3f4
    @L020ca3f0:
        add r12, r12, #0x2
    @L020ca3f4:
        blt @L020ca3cc
        bx lr
    }

    // usa: func_020ca3ec
    // MIi_CpuClear32
    asm void func_020ca3ec(int value, void* dst, unsigned int len)
    {
        add r12, r1, r2
    @L020ca400:
        cmp r1, r12
        blt @L020ca40c
        b @L020ca410
    @L020ca40c:
        stmia r1!, {r0}
    @L020ca410:
        blt @L020ca400
        bx lr
    }

    // usa: func_020ca408
    // MIi_CpuCopy32
    asm void func_020ca408(const void* src, void* dst, unsigned int len)
    {
        add r12, r1, r2
    @L020ca41c:
        cmp r1, r12
        blt @L020ca428
        b @L020ca42c
    @L020ca428:
        ldmia r0!, {r2}
    @L020ca42c:
        blt @L020ca434
        b @L020ca438
    @L020ca434:
        stmia r1!, {r2}
    @L020ca438:
        blt @L020ca41c
        bx lr
    }

    // usa: func_020ca430
    // MIi_CpuSend32: copies to a register
    asm void func_020ca430(const void* src, volatile void* dst, unsigned int len)
    {
        add r12, r0, r2
    @L020ca444:
        cmp r0, r12
        blt @L020ca450
        b @L020ca454
    @L020ca450:
        ldmia r0!, {r2}
    @L020ca454:
        blt @L020ca45c
        b @L020ca460
    @L020ca45c:
        str r2, [r1, #0x0]
    @L020ca460:
        blt @L020ca444
        bx lr
    }

    // usa: func_020ca458
    // MIi_CpuClearFast: 32 bytes at a time
    asm void func_020ca458(int value, void* dst, unsigned int len)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9}
        add r9, r1, r2
        mov r12, r2, lsr #0x5
        add r12, r1, r12, lsl #0x5
        mov r2, r0
        mov r3, r2
        mov r4, r2
        mov r5, r2
        mov r6, r2
        mov r7, r2
        mov r8, r2
    @L020ca494:
        cmp r1, r12
        blt @L020ca4a0
        b @L020ca4a4
    @L020ca4a0:
        stmia r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
    @L020ca4a4:
        blt @L020ca494
    @L020ca4a8:
        cmp r1, r9
        blt @L020ca4b4
        b @L020ca4b8
    @L020ca4b4:
        stmia r1!, {r0}
    @L020ca4b8:
        blt @L020ca4a8
        ldmia sp!, {r4, r5, r6, r7, r8, r9}
        bx lr
    }

    // usa: func_020ca4b4
    // MIi_CpuCopyFast: 32 bytes at a time
    asm void func_020ca4b4(const void* src, void* dst, unsigned int len)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10}
        add r10, r1, r2
        mov r12, r2, lsr #0x5
        add r12, r1, r12, lsl #0x5
    @L020ca4d4:
        cmp r1, r12
        blt @L020ca4e0
        b @L020ca4e4
    @L020ca4e0:
        ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    @L020ca4e4:
        blt @L020ca4ec
        b @L020ca4f0
    @L020ca4ec:
        stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    @L020ca4f0:
        blt @L020ca4d4
    @L020ca4f4:
        cmp r1, r10
        blt @L020ca500
        b @L020ca504
    @L020ca500:
        ldmia r0!, {r2}
    @L020ca504:
        blt @L020ca50c
        b @L020ca510
    @L020ca50c:
        stmia r1!, {r2}
    @L020ca510:
        blt @L020ca4f4
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10}
        bx lr
    }

    // usa: func_020ca50c
    // MI_Copy32B
    asm void func_020ca50c(const void* src, void* dst)
    {
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3}
        stmia r1!, {r2, r3}
        bx lr
    }

    // usa: func_020ca528
    // MI_Copy36B
    asm void func_020ca528(const void* src, void* dst)
    {
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        bx lr
    }

    // usa: func_020ca544
    // MI_Copy48B
    asm void func_020ca544(const void* src, void* dst)
    {
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        bx lr
    }

    // usa: func_020ca568
    // MI_Copy64B
    asm void func_020ca568(const void* src, void* dst)
    {
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1!, {r2, r3, r12}
        ldmia r0, {r0, r2, r3, r12}
        stmia r1!, {r0, r2, r3, r12}
        bx lr
    }

    // usa: func_020ca594
    // MI_CpuFill8
    asm void VectorizedMemset(void* dst, int value, unsigned int length)
    {
        cmp r2, #0x0
        beq @L020ca5b0
        b @L020ca5b4
    @L020ca5b0:
        bx lr
    @L020ca5b4:
        tst r0, #0x1
        beq @L020ca5e0
        ldrh r12, [r0, #-0x1]
        and r12, r12, #0xff
        orr r3, r12, r1, lsl #0x8
        strh r3, [r0, #-0x1]
        add r0, r0, #0x1
        subs r2, r2, #0x1
        beq @L020ca5dc
        b @L020ca5e0
    @L020ca5dc:
        bx lr
    @L020ca5e0:
        cmp r2, #0x2
        blo @L020ca638
        orr r1, r1, r1, lsl #0x8
        tst r0, #0x2
        beq @L020ca608
        strh r1, [r0], #0x2
        subs r2, r2, #0x2
        beq @L020ca604
        b @L020ca608
    @L020ca604:
        bx lr
    @L020ca608:
        orr r1, r1, r1, lsl #0x10
        bics r3, r2, #0x3
        beq @L020ca628
        sub r2, r2, r3
        add r12, r3, r0
    @L020ca61c:
        str r1, [r0], #0x4
        cmp r0, r12
        blo @L020ca61c
    @L020ca628:
        tst r2, #0x2
        bne @L020ca634
        b @L020ca638
    @L020ca634:
        strh r1, [r0], #0x2
    @L020ca638:
        tst r2, #0x1
        beq @L020ca644
        b @L020ca648
    @L020ca644:
        bx lr
    @L020ca648:
        ldrh r3, [r0, #0x0]
        and r3, r3, #0xff00
        and r1, r1, #0xff
        orr r1, r1, r3
        strh r1, [r0, #0x0]
        bx lr
    }

    // usa: func_020ca650
    // MI_CpuCopy8
    asm void VectorizedInvertedMemcpy(const void* src, void* dst, unsigned int length)
    {
        cmp r2, #0x0
        beq @L020ca66c
        b @L020ca670
    @L020ca66c:
        bx lr
    @L020ca670:
        tst r1, #0x1
        beq @L020ca6c8
        ldrh r12, [r1, #-0x1]
        and r12, r12, #0xff
        tst r0, #0x1
        bne @L020ca68c
        b @L020ca690
    @L020ca68c:
        ldrh r3, [r0, #-0x1]
    @L020ca690:
        bne @L020ca698
        b @L020ca69c
    @L020ca698:
        mov r3, r3, lsr #0x8
    @L020ca69c:
        beq @L020ca6a4
        b @L020ca6a8
    @L020ca6a4:
        ldrh r3, [r0, #0x0]
    @L020ca6a8:
        orr r3, r12, r3, lsl #0x8
        strh r3, [r1, #-0x1]
        add r0, r0, #0x1
        add r1, r1, #0x1
        subs r2, r2, #0x1
        beq @L020ca6c4
        b @L020ca6c8
    @L020ca6c4:
        bx lr
    @L020ca6c8:
        eor r12, r1, r0
        tst r12, #0x1
        beq @L020ca724
        bic r0, r0, #0x1
        ldrh r12, [r0], #0x2
        mov r3, r12, lsr #0x8
        subs r2, r2, #0x2
        blo @L020ca700
    @L020ca6e8:
        ldrh r12, [r0], #0x2
        orr r12, r3, r12, lsl #0x8
        strh r12, [r1], #0x2
        mov r3, r12, lsr #0x10
        subs r2, r2, #0x2
        bhs @L020ca6e8
    @L020ca700:
        tst r2, #0x1
        beq @L020ca70c
        b @L020ca710
    @L020ca70c:
        bx lr
    @L020ca710:
        ldrh r12, [r1, #0x0]
        and r12, r12, #0xff00
        orr r12, r12, r3
        strh r12, [r1, #0x0]
        bx lr
    @L020ca724:
        tst r12, #0x2
        beq @L020ca750
        bics r3, r2, #0x1
        beq @L020ca7b4
        sub r2, r2, r3
        add r12, r3, r1
    @L020ca73c:
        ldrh r3, [r0], #0x2
        strh r3, [r1], #0x2
        cmp r1, r12
        blo @L020ca73c
        b @L020ca7b4
    @L020ca750:
        cmp r2, #0x2
        blo @L020ca7b4
        tst r1, #0x2
        beq @L020ca778
        ldrh r3, [r0], #0x2
        strh r3, [r1], #0x2
        subs r2, r2, #0x2
        beq @L020ca774
        b @L020ca778
    @L020ca774:
        bx lr
    @L020ca778:
        bics r3, r2, #0x3
        beq @L020ca798
        sub r2, r2, r3
        add r12, r3, r1
    @L020ca788:
        ldr r3, [r0], #0x4
        str r3, [r1], #0x4
        cmp r1, r12
        blo @L020ca788
    @L020ca798:
        tst r2, #0x2
        bne @L020ca7a4
        b @L020ca7a8
    @L020ca7a4:
        ldrh r3, [r0], #0x2
    @L020ca7a8:
        bne @L020ca7b0
        b @L020ca7b4
    @L020ca7b0:
        strh r3, [r1], #0x2
    @L020ca7b4:
        tst r2, #0x1
        beq @L020ca7c0
        b @L020ca7c4
    @L020ca7c0:
        bx lr
    @L020ca7c4:
        ldrh r2, [r1, #0x0]
        ldrh r0, [r0, #0x0]
        and r2, r2, #0xff00
        and r0, r0, #0xff
        orr r0, r2, r0
        strh r0, [r1, #0x0]
        bx lr
    }

#pragma thumb on
    // usa: func_020ca7d0
    // MI_Zero36B
    asm void func_020ca7d0(void* dst)
    {
        mov r1, #0x0
        mov r2, #0x0
        mov r3, #0x0
        stmia r0!, {r1, r2, r3}
        stmia r0!, {r1, r2, r3}
        stmia r0!, {r1, r2, r3}
        bx lr
        lsl r0, r0, #0x0
    }

#pragma thumb off
#endif
}
