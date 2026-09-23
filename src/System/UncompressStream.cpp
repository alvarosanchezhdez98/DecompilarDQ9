// The NitroSDK's mi_uncomp_stream.c, written in assembly: uncompresses data as it's read. Each function takes a
// context (the game's Decompressor, see ExtendedNitroVM.h), the next compressed bytes and their length, and returns
// how many bytes are left to write. Their names don't say which compression they are for yet.

extern "C"
{
#ifdef __MWERKS__
    // usa: DecompressC
    // MI_ReadUncompRL8: run-length encoding
    asm long DecompressC(void* context, const void* data, unsigned int length)
    {
        stmdb sp!, {r4, r5, r6, r7, r8}
        ldr r3, [r0, #0x0]
        ldr r4, [r0, #0x4]
        ldrb r5, [r0, #0xb]
        ldrh r6, [r0, #0xc]
    @L020ca980:
        cmp r4, #0x0
        ble @L020caa04
        tst r5, #0x80
        bne @L020ca9b8
    @L020ca990:
        cmp r6, #0x0
        ble @L020ca9e0
        sub r6, r6, #0x1
        ldrb r7, [r1], #0x1
        sub r4, r4, #0x1
        swpb r8, r7, [r3]
        add r3, r3, #0x1
        subs r2, r2, #0x1
        beq @L020caa04
        b @L020ca990
    @L020ca9b8:
        cmp r6, #0x0
        ble @L020ca9e0
        ldrb r7, [r1], #0x1
    @L020ca9c4:
        sub r4, r4, #0x1
        swpb r8, r7, [r3]
        add r3, r3, #0x1
        subs r6, r6, #0x1
        bgt @L020ca9c4
        subs r2, r2, #0x1
        beq @L020caa04
    @L020ca9e0:
        ldrb r5, [r1], #0x1
        and r6, r5, #0x7f
        tst r5, #0x80
        bne @L020ca9f4
        b @L020ca9f8
    @L020ca9f4:
        add r6, r6, #0x2
    @L020ca9f8:
        add r6, r6, #0x1
        subs r2, r2, #0x1
        bne @L020ca980
    @L020caa04:
        str r3, [r0, #0x0]
        str r4, [r0, #0x4]
        strb r5, [r0, #0xb]
        strh r6, [r0, #0xc]
        mov r0, r4
        ldmia sp!, {r4, r5, r6, r7, r8}
        bx lr
    }

    // usa: DecompressA
    // MI_ReadUncompLZ8: LZ77
    asm long DecompressA(void* context, const void* data, unsigned int length)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11}
        ldr r3, [r0, #0x0]
        ldr r4, [r0, #0x4]
        ldrb r5, [r0, #0xf]
        ldrb r6, [r0, #0x10]
        ldr r7, [r0, #0x8]
        ldrb r8, [r0, #0x11]
        ldrb r11, [r0, #0x12]
    @L020caa40:
        cmp r4, #0x0
        ble @L020cab7c
        cmp r6, #0x0
        beq @L020cab64
    @L020caa50:
        cmp r2, #0x0
        beq @L020cab7c
        tst r5, #0x80
        bne @L020caa78
        ldrb r9, [r1], #0x1
        sub r4, r4, #0x1
        sub r2, r2, #0x1
        swpb r9, r9, [r3]
        add r3, r3, #0x1
        b @L020cab50
    @L020caa78:
        cmp r8, #0x0
        beq @L020cab14
        cmp r11, #0x1
        bne @L020cab00
        subs r8, r8, #0x1
        beq @L020caae8
        cmp r8, #0x1
        beq @L020caadc
        ldrb r7, [r1], #0x1
        tst r7, #0xe0
        beq @L020caab0
        add r7, r7, #0x10
        mov r8, #0x0
        b @L020cab0c
    @L020caab0:
        mov r10, #0x110
        tst r7, #0x10
        beq @L020caacc
        and r7, r7, #0xf
        add r10, r10, #0x1000
        add r7, r10, r7, lsl #0x10
        b @L020caaf4
    @L020caacc:
        and r7, r7, #0xf
        add r7, r10, r7, lsl #0x8
        mov r8, #0x1
        b @L020caaf4
    @L020caadc:
        ldrb r10, [r1], #0x1
        add r7, r7, r10, lsl #0x8
        b @L020caaf4
    @L020caae8:
        ldrb r10, [r1], #0x1
        add r7, r7, r10
        b @L020cab0c
    @L020caaf4:
        subs r2, r2, #0x1
        beq @L020cab7c
        b @L020caa78
    @L020cab00:
        ldrb r7, [r1], #0x1
        add r7, r7, #0x30
        mov r8, #0x0
    @L020cab0c:
        subs r2, r2, #0x1
        beq @L020cab7c
    @L020cab14:
        and r9, r7, #0xf
        mov r10, r9, lsl #0x8
        ldrb r9, [r1], #0x1
        mov r8, #0x3
        sub r2, r2, #0x1
        orr r9, r9, r10
        add r9, r9, #0x1
        movs r7, r7, asr #0x4
        beq @L020cab50
    @L020cab38:
        ldrb r10, [r3, -r9]
        sub r4, r4, #0x1
        swpb r10, r10, [r3]
        add r3, r3, #0x1
        subs r7, r7, #0x1
        bgt @L020cab38
    @L020cab50:
        cmp r4, #0x0
        beq @L020cab7c
        mov r5, r5, lsl #0x1
        subs r6, r6, #0x1
        bne @L020caa50
    @L020cab64:
        cmp r2, #0x0
        beq @L020cab7c
        ldrb r5, [r1], #0x1
        mov r6, #0x8
        sub r2, r2, #0x1
        b @L020caa40
    @L020cab7c:
        str r3, [r0, #0x0]
        str r4, [r0, #0x4]
        strb r5, [r0, #0xf]
        strb r6, [r0, #0x10]
        str r7, [r0, #0x8]
        strb r8, [r0, #0x11]
        strb r11, [r0, #0x12]
        mov r0, r4
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11}
        bx lr
    }

    // usa: DecompressB
    // MI_ReadUncompHuffman
    asm long DecompressB(void* context, const void* data, unsigned int length)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
        ldr r3, [r0, #0x0]
        ldr r4, [r0, #0x4]
        ldr r5, [r0, #0x8]
        ldr r6, [r0, #0xc]
        ldr r7, [r0, #0x10]
        ldrsh r8, [r0, #0x14]
        ldrb r9, [r0, #0x16]
        ldrb r10, [r0, #0x17]
        ldrb r11, [r0, #0x18]
        cmp r8, #0x0
        beq @L020cac18
        bgt @L020cabf0
        ldrb r8, [r1], #0x1
        sub r2, r2, #0x1
        strb r8, [r5], #0x1
        add r8, r8, #0x1
        mov r8, r8, lsl #0x1
        sub r8, r8, #0x1
    @L020cabf0:
        cmp r2, #0x0
        beq @L020cace0
        ldrb r12, [r1], #0x1
        sub r2, r2, #0x1
        strb r12, [r5], #0x1
        subs r8, r8, #0x1
        beq @L020cac10
        b @L020cac14
    @L020cac10:
        add r5, r0, #0x1d
    @L020cac14:
        bgt @L020cabf0
    @L020cac18:
        cmp r4, #0x0
        ble @L020cace0
    @L020cac20:
        cmp r9, #0x20
        bge @L020cac48
    @L020cac28:
        cmp r2, #0x0
        beq @L020cace0
        ldr r12, [r1], #0x1
        sub r2, r2, #0x1
        orr r6, r6, r12, lsl r9
        add r9, r9, #0x8
        cmp r9, #0x20
        blt @L020cac28
    @L020cac48:
        mov r12, r6, lsr #0x1f
        ldrb lr, [r5, #0x0]
        mov r5, r5, lsr #0x1
        mov r5, r5, lsl #0x1
        and r8, lr, #0x3f
        add r8, r8, #0x1
        add r5, r5, r8, lsl #0x1
        add r5, r5, r12
        mov r8, #0x0
        mov lr, lr, lsl r12
        ands lr, lr, #0x80
        mov r6, r6, lsl #0x1
        sub r9, r9, #0x1
        beq @L020cacd0
        mov r7, r7, lsr r11
        ldrb r12, [r5, #0x0]
        rsb lr, r11, #0x20
        orr r7, r7, r12, lsl lr
        add r5, r0, #0x1d
        add r10, r10, r11
        cmp r4, r10, asr #0x3
        bgt @L020cacac
        rsb r12, r10, #0x20
        mov r7, r7, asr r12
        mov r10, #0x20
    @L020cacac:
        cmp r10, #0x20
        bne @L020cacd0
        str r7, [r3], #0x4
        mov r10, #0x0
        subs r4, r4, #0x4
        ble @L020cacc8
        b @L020caccc
    @L020cacc8:
        mov r4, #0x0
    @L020caccc:
        ble @L020cace0
    @L020cacd0:
        cmp r9, #0x0
        bgt @L020cac48
        cmp r4, #0x0
        bgt @L020cac20
    @L020cace0:
        str r3, [r0, #0x0]
        str r4, [r0, #0x4]
        str r5, [r0, #0x8]
        str r6, [r0, #0xc]
        str r7, [r0, #0x10]
        strh r8, [r0, #0x14]
        strb r9, [r0, #0x16]
        strb r10, [r0, #0x17]
        strb r11, [r0, #0x18]
        mov r0, r4
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
        bx lr
    }
#endif
}
