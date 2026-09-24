#include "System/Digest.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's MD5 ("hash 1" of its DGT library), like RFC 1321's code

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

static unsigned char padding = 0x80;

// The words of the block that rounds 2 to 4 use
static int roundWords[48] = {
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9,
};

static unsigned long sineTable[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

extern "C"
{
    void func_020c04e8(MD5Context* context);

    // usa: func_020c0328
    // DGT_Hash1Reset
    void func_020c0328(MD5Context* context)
    {
        context->a = 0x67452301;
        context->b = 0xefcdab89;
        context->c = 0x98badcfe;
        context->d = 0x10325476;
        context->length = 0;
    }

    // usa: func_020c0368
    // DGT_Hash1SetSource
    void func_020c0368(MD5Context* context, const void* input, unsigned long length)
    {
        unsigned long index;
        unsigned long partLength;
        int blocks;
        const unsigned char* src;

        index = (unsigned long)(context->length & (DIGEST_BLOCK_SIZE - 1));
        context->length += length;
        partLength = DIGEST_BLOCK_SIZE - index;
        if (partLength > length)
        {
            if (length != 0)
                VectorizedInvertedMemcpy(input, &context->buffer8[index], length);
            return;
        }

        VectorizedInvertedMemcpy(input, &context->buffer8[index], partLength);
        func_020c04e8(context);
        length -= partLength;
        src = (const unsigned char*)input + partLength;
        for (blocks = length / DIGEST_BLOCK_SIZE; blocks > 0; blocks--)
        {
            VectorizedInvertedMemcpy(src, context->buffer8, DIGEST_BLOCK_SIZE);
            src += DIGEST_BLOCK_SIZE;
            func_020c04e8(context);
        }

        length &= DIGEST_BLOCK_SIZE - 1;
        if (length != 0)
            VectorizedInvertedMemcpy(src, context->buffer8, length);
    }

    // usa: func_020c0430
    // DGT_Hash1GetDigest_R
    void func_020c0430(unsigned char* digest, MD5Context* context)
    {
        unsigned long long bitLength;
        unsigned long index;
        unsigned long padLength;

        bitLength = context->length << 3;
        func_020c0368(context, &padding, 1);
        index = (unsigned long)(context->length & (DIGEST_BLOCK_SIZE - 1));
        padLength = DIGEST_BLOCK_SIZE - index;
        if (padLength < sizeof(bitLength))
        {
            VectorizedMemset(&context->buffer8[index], 0, padLength);
            func_020c04e8(context);
            index = 0;
            padLength = DIGEST_BLOCK_SIZE;
        }
        if (padLength > sizeof(bitLength))
            VectorizedMemset(&context->buffer8[index], 0, padLength - sizeof(bitLength));

        context->buffer32[14] = (unsigned long)bitLength;
        context->buffer32[15] = (unsigned long)(bitLength >> 32);
        func_020c04e8(context);
        VectorizedInvertedMemcpy(context, digest, MD5_DIGEST_SIZE);
        VectorizedMemset(context, 0, sizeof(MD5Context));
    }

    // usa: func_020c04e8
    // ProcessBlock
    // NONMATCHING: the C matches 55.3 %, so the build uses the original's instructions after #else (see
    // Decompiling.md). The instructions are the same, but the original increments the pointers right after their last
    // loads, in the middle of each loop, and the loop counter after the last step, and the third and fourth rounds use
    // other registers. Neither the order of the declarations nor the forms of the loops change that.
#ifdef NONMATCHING
    void func_020c04e8(MD5Context* context)
    {
        const int* indices;
        unsigned long a;
        unsigned long b;
        unsigned long c;
        unsigned long d;
        unsigned long* x;
        const unsigned long* t;
        const unsigned long* words;
        int i;

        a = context->a;
        b = context->b;
        c = context->c;
        d = context->d;
        x = context->buffer32;
        t = sineTable;

        words = x;
        for (i = 0; i < 4; i++)
        {
            a = b + ROTATE_LEFT(a + F(b, c, d) + words[0] + t[0], 7);
            d = a + ROTATE_LEFT(d + F(a, b, c) + words[1] + t[1], 12);
            c = d + ROTATE_LEFT(c + F(d, a, b) + words[2] + t[2], 17);
            b = c + ROTATE_LEFT(b + F(c, d, a) + words[3] + t[3], 22);
            words += 4;
            t += 4;
        }

        indices = roundWords;
        for (i = 0; i < 4; i++)
        {
            a = b + ROTATE_LEFT(a + G(b, c, d) + x[indices[0]] + t[0], 5);
            d = a + ROTATE_LEFT(d + G(a, b, c) + x[indices[1]] + t[1], 9);
            c = d + ROTATE_LEFT(c + G(d, a, b) + x[indices[2]] + t[2], 14);
            b = c + ROTATE_LEFT(b + G(c, d, a) + x[indices[3]] + t[3], 20);
            indices += 4;
            t += 4;
        }

        for (i = 0; i < 4; i++)
        {
            a = b + ROTATE_LEFT(a + H(b, c, d) + x[indices[0]] + t[0], 4);
            d = a + ROTATE_LEFT(d + H(a, b, c) + x[indices[1]] + t[1], 11);
            c = d + ROTATE_LEFT(c + H(d, a, b) + x[indices[2]] + t[2], 16);
            b = c + ROTATE_LEFT(b + H(c, d, a) + x[indices[3]] + t[3], 23);
            indices += 4;
            t += 4;
        }

        for (i = 0; i < 4; i++)
        {
            a = b + ROTATE_LEFT(a + I(b, c, d) + x[indices[0]] + t[0], 6);
            d = a + ROTATE_LEFT(d + I(a, b, c) + x[indices[1]] + t[1], 10);
            c = d + ROTATE_LEFT(c + I(d, a, b) + x[indices[2]] + t[2], 15);
            b = c + ROTATE_LEFT(b + I(c, d, a) + x[indices[3]] + t[3], 21);
            indices += 4;
            t += 4;
        }
        context->a += a;
        context->b += b;
        context->c += c;
        context->d += d;
    }
#else
    asm void func_020c04e8(MD5Context* context)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
        ldmia r0, {r2, r3, r12, lr}
        add r4, r0, #0x18
        ldr r5, =sineTable
        mov r7, r4
        mov r8, #0x0
    @L020c0510:
        mvn r1, r3
        and r6, r3, r12
        and r1, r1, lr
        orr r1, r6, r1
        ldr r6, [r7, #0x0]
        add r1, r2, r1
        ldr r2, [r5, #0x0]
        add r1, r6, r1
        add r2, r2, r1
        mov r1, r2, lsr #0x19
        orr r1, r1, r2, lsl #0x7
        add r2, r3, r1
        mvn r1, r2
        and r6, r2, r3
        and r1, r1, r12
        orr r1, r6, r1
        ldr r6, [r7, #0x4]
        add r1, lr, r1
        ldr r9, [r5, #0x4]
        add r1, r6, r1
        add r6, r9, r1
        mov r1, r6, lsr #0x14
        orr r1, r1, r6, lsl #0xc
        add lr, r2, r1
        mvn r1, lr
        and r6, lr, r2
        and r1, r1, r3
        orr r1, r6, r1
        ldr r9, [r7, #0x8]
        add r6, r12, r1
        ldr r1, [r7, #0xc]
        add r9, r9, r6
        ldr r10, [r5, #0x8]
        ldr r6, [r5, #0xc]
        add r10, r10, r9
        mov r9, r10, lsr #0xf
        orr r9, r9, r10, lsl #0x11
        add r12, lr, r9
        add r5, r5, #0x10
        add r7, r7, #0x10
        and r10, r12, lr
        mvn r9, r12
        and r9, r9, r2
        orr r9, r10, r9
        add r3, r3, r9
        add r1, r1, r3
        add r3, r6, r1
        mov r1, r3, lsr #0xa
        orr r1, r1, r3, lsl #0x16
        add r3, r12, r1
        add r8, r8, #0x1
        cmp r8, #0x4
        blt @L020c0510
        ldr r1, =roundWords
        mov r6, #0x0
    @L020c05ec:
        mvn r7, lr
        ldr r9, [r1, #0x0]
        and r8, r3, lr
        and r7, r12, r7
        orr r7, r8, r7
        ldr r8, [r4, r9, lsl #0x2]
        add r2, r2, r7
        ldr r7, [r5, #0x0]
        add r2, r8, r2
        add r7, r7, r2
        mov r2, r7, lsr #0x1b
        orr r2, r2, r7, lsl #0x5
        add r2, r3, r2
        mvn r8, r12
        ldr r7, [r1, #0x4]
        and r9, r2, r12
        and r8, r3, r8
        orr r10, r9, r8
        mvn r8, r3
        ldr r9, [r1, #0x8]
        ldr r11, [r4, r7, lsl #0x2]
        add r7, lr, r10
        add r7, r11, r7
        ldr r10, [r5, #0x4]
        ldr r9, [r4, r9, lsl #0x2]
        add r10, r10, r7
        ldr r7, [r1, #0xc]
        and r8, r2, r8
        ldr r7, [r4, r7, lsl #0x2]
        mov r11, r10, lsr #0x17
        orr r10, r11, r10, lsl #0x9
        add lr, r2, r10
        ldr r10, [r5, #0x8]
        and r11, lr, r3
        orr r8, r11, r8
        add r8, r12, r8
        add r8, r9, r8
        add r9, r10, r8
        mov r8, r9, lsr #0x12
        orr r8, r8, r9, lsl #0xe
        add r12, lr, r8
        mvn r8, r2
        and r9, lr, r8
        ldr r8, [r5, #0xc]
        add r5, r5, #0x10
        add r1, r1, #0x10
        and r10, r12, r2
        orr r9, r10, r9
        add r3, r3, r9
        add r3, r7, r3
        add r7, r8, r3
        mov r3, r7, lsr #0xc
        orr r3, r3, r7, lsl #0x14
        add r3, r12, r3
        add r6, r6, #0x1
        cmp r6, #0x4
        blt @L020c05ec
        mov r6, #0x0
    @L020c06d4:
        ldr r8, [r1, #0x0]
        eor r7, r3, r12
        eor r7, lr, r7
        ldr r8, [r4, r8, lsl #0x2]
        add r2, r2, r7
        ldr r7, [r5, #0x0]
        add r2, r8, r2
        add r7, r7, r2
        mov r2, r7, lsr #0x1c
        orr r2, r2, r7, lsl #0x4
        add r2, r3, r2
        ldr r8, [r1, #0x4]
        eor r7, r2, r3
        eor r7, r12, r7
        ldr r8, [r4, r8, lsl #0x2]
        add r7, lr, r7
        ldr r9, [r1, #0x8]
        ldr r10, [r5, #0x4]
        add r7, r8, r7
        add r8, r10, r7
        mov r7, r8, lsr #0x15
        orr r7, r7, r8, lsl #0xb
        add lr, r2, r7
        eor r8, lr, r2
        ldr r7, [r1, #0xc]
        ldr r9, [r4, r9, lsl #0x2]
        eor r8, r3, r8
        add r8, r12, r8
        add r9, r9, r8
        ldr r10, [r5, #0x8]
        ldr r8, [r4, r7, lsl #0x2]
        add r9, r10, r9
        mov r7, r9, lsr #0x10
        orr r7, r7, r9, lsl #0x10
        add r12, lr, r7
        eor r7, r12, lr
        eor r7, r2, r7
        add r3, r3, r7
        add r3, r8, r3
        ldr r7, [r5, #0xc]
        add r5, r5, #0x10
        add r7, r7, r3
        add r1, r1, #0x10
        mov r3, r7, lsr #0x9
        orr r3, r3, r7, lsl #0x17
        add r3, r12, r3
        add r6, r6, #0x1
        cmp r6, #0x4
        blt @L020c06d4
        mov r8, #0x0
    @L020c079c:
        mvn r6, lr
        ldr r7, [r1, #0x0]
        orr r6, r3, r6
        eor r6, r12, r6
        ldr r7, [r4, r7, lsl #0x2]
        add r2, r2, r6
        ldr r6, [r5, #0x0]
        add r2, r7, r2
        add r6, r6, r2
        mov r2, r6, lsr #0x1a
        orr r2, r2, r6, lsl #0x6
        add r2, r3, r2
        mvn r6, r12
        ldr r9, [r1, #0x4]
        orr r6, r2, r6
        eor r7, r3, r6
        ldr r6, [r1, #0x8]
        ldr r9, [r4, r9, lsl #0x2]
        add r7, lr, r7
        ldr r10, [r5, #0x4]
        add r7, r9, r7
        add r9, r10, r7
        mov r7, r9, lsr #0x16
        orr r9, r7, r9, lsl #0xa
        ldr r7, [r1, #0xc]
        add lr, r2, r9
        mvn r9, r3
        ldr r6, [r4, r6, lsl #0x2]
        orr r9, lr, r9
        eor r9, r2, r9
        add r9, r12, r9
        add r9, r6, r9
        ldr r10, [r5, #0x8]
        ldr r6, [r4, r7, lsl #0x2]
        add r9, r10, r9
        mov r7, r9, lsr #0x11
        orr r9, r7, r9, lsl #0xf
        ldr r7, [r5, #0xc]
        add r12, lr, r9
        add r5, r5, #0x10
        add r1, r1, #0x10
        mvn r9, r2
        orr r9, r12, r9
        eor r9, lr, r9
        add r3, r3, r9
        add r3, r6, r3
        add r6, r7, r3
        mov r3, r6, lsr #0xb
        orr r3, r3, r6, lsl #0x15
        add r3, r12, r3
        add r8, r8, #0x1
        cmp r8, #0x4
        blt @L020c079c
        ldr r1, [r0, #0x0]
        add r1, r1, r2
        str r1, [r0, #0x0]
        ldr r1, [r0, #0x4]
        add r1, r1, r3
        str r1, [r0, #0x4]
        ldr r1, [r0, #0x8]
        add r1, r1, r12
        str r1, [r0, #0x8]
        ldr r1, [r0, #0xc]
        add r1, r1, lr
        str r1, [r0, #0xc]
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    }
#endif
}
