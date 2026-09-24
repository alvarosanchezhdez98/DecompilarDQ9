#include "System/Digest.h"

// The NitroSDK's SHA-1 block function, DGTi_hash2_arm4_small, which it wrote in assembly. Its constants are before
// it, and it loads them relative to its address. Nothing references them, so the linker keeps them because they're in
// FORCE_ACTIVE (see tools/configure.py).

extern "C"
{
#ifdef __MWERKS__
    // The byte swap mask and the constants of SHA-1's rounds
    asm void sha1Constants()
    {
        dcd 0x00ff00ff
        dcd 0x5a827999
        dcd 0x6ed9eba1
        dcd 0x8f1bbcdc
        dcd 0xca62c1d6
    }

    // usa: func_020c0e9c
    // DGTi_hash2_arm4_small: processes the blocks of 64 bytes at input
    asm void func_020c0e9c(SHA1Context* context, const void* input, unsigned long length)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
        ldmia r0, {r3, r9, r10, r11, r12}
        sub sp, sp, #0x84
        str r2, [sp, #0x80]
    @L020c0ebc:
        ldr r8, [pc, #-0x28]
        ldr r7, [pc, #-0x30]
        mov r6, sp
        mov r5, #0x0
    @L020c0ecc:
        ldr r4, [r1], #0x4
        add r2, r8, r12
        add r2, r2, r3, ror #0x1b
        and lr, r4, r7
        and r4, r7, r4, ror #0x18
        orr r4, r4, lr, ror #0x8
        str r4, [r6, #0x40]
        str r4, [r6], #0x4
        add r2, r2, r4
        eor r4, r10, r11
        and r4, r4, r9
        eor r4, r4, r11
        add r2, r2, r4
        mov r9, r9, ror #0x2
        mov r12, r11
        mov r11, r10
        mov r10, r9
        mov r9, r3
        mov r3, r2
        add r5, r5, #0x4
        cmp r5, #0x40
        blt @L020c0ecc
        mov r7, #0x0
        mov r6, sp
    @L020c0f2c:
        ldr r2, [r6, #0x0]
        ldr r5, [r6, #0x8]
        ldr r4, [r6, #0x20]
        ldr lr, [r6, #0x34]
        eor r2, r2, r5
        eor r4, r4, lr
        eor r2, r2, r4
        mov r2, r2, ror #0x1f
        str r2, [r6, #0x40]
        str r2, [r6], #0x4
        add r2, r2, r12
        add r2, r2, r8
        add r2, r2, r3, ror #0x1b
        eor r4, r10, r11
        and r4, r4, r9
        eor r4, r4, r11
        add r2, r2, r4
        mov r9, r9, ror #0x2
        mov r12, r11
        mov r11, r10
        mov r10, r9
        mov r9, r3
        mov r3, r2
        add r7, r7, #0x4
        cmp r7, #0x10
        blt @L020c0f2c
        ldr r8, [pc, #-0xfc]
        mov r7, #0x0
    @L020c0f9c:
        ldr r2, [r6, #0x0]
        ldr r4, [r6, #0x8]
        ldr lr, [r6, #0x20]
        ldr r5, [r6, #0x34]
        eor r2, r2, r4
        eor lr, lr, r5
        eor r2, r2, lr
        mov r2, r2, ror #0x1f
        str r2, [r6, #0x40]
        str r2, [r6], #0x4
        add r2, r2, r12
        add r2, r2, r8
        add r2, r2, r3, ror #0x1b
        eor lr, r9, r10
        eor lr, lr, r11
        add r2, r2, lr
        mov r9, r9, ror #0x2
        mov r12, r11
        mov r11, r10
        mov r10, r9
        mov r9, r3
        mov r3, r2
        add r7, r7, #0x1
        cmp r7, #0xc
        moveq r6, sp
        cmp r7, #0x14
        blt @L020c0f9c
        ldr r8, [pc, #-0x16c]
        mov r7, #0x0
    @L020c1010:
        ldr r2, [r6, #0x0]
        ldr lr, [r6, #0x8]
        ldr r5, [r6, #0x20]
        ldr r4, [r6, #0x34]
        eor r2, r2, lr
        eor r5, r5, r4
        eor r2, r2, r5
        mov r2, r2, ror #0x1f
        str r2, [r6, #0x40]
        str r2, [r6], #0x4
        add r2, r2, r12
        add r2, r2, r8
        add r2, r2, r3, ror #0x1b
        orr r5, r9, r10
        and r5, r5, r11
        and r4, r9, r10
        orr r5, r5, r4
        add r2, r2, r5
        mov r9, r9, ror #0x2
        mov r12, r11
        mov r11, r10
        mov r10, r9
        mov r9, r3
        mov r3, r2
        add r7, r7, #0x1
        cmp r7, #0x8
        moveq r6, sp
        cmp r7, #0x14
        blt @L020c1010
        ldr r8, [pc, #-0x1e4]
        mov r7, #0x0
    @L020c108c:
        ldr r2, [r6, #0x0]
        ldr r5, [r6, #0x8]
        ldr r4, [r6, #0x20]
        ldr lr, [r6, #0x34]
        eor r2, r2, r5
        eor r4, r4, lr
        eor r2, r2, r4
        mov r2, r2, ror #0x1f
        str r2, [r6, #0x40]
        str r2, [r6], #0x4
        add r2, r2, r12
        add r2, r2, r8
        add r2, r2, r3, ror #0x1b
        eor r4, r9, r10
        eor r4, r4, r11
        add r2, r2, r4
        mov r9, r9, ror #0x2
        mov r12, r11
        mov r11, r10
        mov r10, r9
        mov r9, r3
        mov r3, r2
        add r7, r7, #0x1
        cmp r7, #0x4
        moveq r6, sp
        cmp r7, #0x14
        blt @L020c108c
        ldmia r0, {r2, r4, r6, r7, lr}
        add r3, r3, r2
        add r9, r9, r4
        add r10, r10, r6
        add r11, r11, r7
        add r12, r12, lr
        stmia r0, {r3, r9, r10, r11, r12}
        ldr lr, [sp, #0x80]
        subs lr, lr, #0x40
        str lr, [sp, #0x80]
        bgt @L020c0ebc
        add sp, sp, #0x84
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
    }
#endif
}
