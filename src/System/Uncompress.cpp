// The NitroSDK's mi_uncompress.c, written in assembly. Its other functions aren't in the ROM.

extern "C"
{
#ifdef __MWERKS__
    // usa: func_020ca7e8
    // MI_UncompressLZ8: uncompresses LZ77 data
    asm void func_020ca7e8(const void* src, void* dst)
    {
        stmdb sp!, {r4, r5, r6, r7, lr}
        ldr r5, [r0], #0x4
        mov r2, r5, lsr #0x8
        mov r7, #0x0
        tst r5, #0xf
        bne @L020ca814
        b @L020ca818
    @L020ca814:
        mov r7, #0x1
    @L020ca818:
        cmp r2, #0x0
        ble @L020ca8f0
        ldrb lr, [r0], #0x1
        mov r4, #0x8
    @L020ca828:
        subs r4, r4, #0x1
        blt @L020ca818
        tst lr, #0x80
        bne @L020ca84c
        ldrb r6, [r0], #0x1
        swpb r6, r6, [r1]
        add r1, r1, #0x1
        sub r2, r2, #0x1
        b @L020ca8d8
    @L020ca84c:
        ldrb r5, [r0, #0x0]
        cmp r7, #0x0
        beq @L020ca85c
        b @L020ca860
    @L020ca85c:
        mov r6, #0x3
    @L020ca860:
        beq @L020ca8a4
        tst r5, #0xe0
        bne @L020ca870
        b @L020ca874
    @L020ca870:
        mov r6, #0x1
    @L020ca874:
        bne @L020ca8a4
        add r0, r0, #0x1
        and r6, r5, #0xf
        mov r6, r6, lsl #0x4
        tst r5, #0x10
        beq @L020ca89c
        mov r6, r6, lsl #0x8
        ldrb r5, [r0], #0x1
        add r6, r6, r5, lsl #0x4
        add r6, r6, #0x100
    @L020ca89c:
        add r6, r6, #0x11
        ldrb r5, [r0, #0x0]
    @L020ca8a4:
        add r3, r6, r5, asr #0x4
        add r0, r0, #0x1
        and r5, r5, #0xf
        mov r12, r5, lsl #0x8
        ldrb r6, [r0], #0x1
        orr r5, r6, r12
        add r12, r5, #0x1
        sub r2, r2, r3
    @L020ca8c4:
        ldrb r5, [r1, -r12]
        swpb r5, r5, [r1]
        add r1, r1, #0x1
        subs r3, r3, #0x1
        bgt @L020ca8c4
    @L020ca8d8:
        cmp r2, #0x0
        bgt @L020ca8e4
        b @L020ca8e8
    @L020ca8e4:
        mov lr, lr, lsl #0x1
    @L020ca8e8:
        bgt @L020ca828
        b @L020ca818
    @L020ca8f0:
        ldmia sp!, {r4, r5, r6, r7, lr}
        bx lr
    }
#endif
}
