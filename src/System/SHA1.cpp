#include "System/Digest.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4
#pragma pool_strings off

// The NitroSDK's SHA-1 ("hash 2" of its DGT library), like RFC 3174's code

extern "C"
{
    // DGTi_hash2_arm4_small
    void func_020c0e9c(SHA1Context* context, const void* input, unsigned long length);

    // usa: func_020ca3ec
    // MIi_CpuClear32
    void func_020ca3ec(int value, void* dst, unsigned int len);

    // usa: func_020c089c
    // DGT_Hash2Reset
    void func_020c089c(SHA1Context* context)
    {
        context->intermediateHash[0] = 0x67452301;
        context->intermediateHash[1] = 0xefcdab89;
        context->intermediateHash[2] = 0x98badcfe;
        context->intermediateHash[3] = 0x10325476;
        context->intermediateHash[4] = 0xc3d2e1f0;
        context->lengthLow = 0;
        context->lengthHigh = 0;
        context->messageBlockIndex = 0;
    }
}

// RFC 3174's test vectors, for a test that isn't in the ROM. The linker keeps them because they're in the section of
// processMessageBlock, and their strings are in sections of their own (pool_strings off). The compiler sorts the data
// that's defined before the end of the first function by size, and the original's order isn't sorted, so they're
// defined after it.
static char test3[] = "a";

// DGTi_Hash2ProcessMessageBlockFunc
void (*processMessageBlock)(SHA1Context* context, const void* input, unsigned long length) = func_020c0e9c;

static char test1[] = "abc";
static char result3[] = "\x34\xaa\x97\x3c\xd4\xc4\xda\xa4\xf6\x1e\xeb\x2b\xdb\xad\x27\x31\x65\x34\x01\x6f";
static char result4[] = "\xde\xa3\x56\xa2\xcd\xdd\x90\xc7\xa7\xec\xed\xc5\xeb\xb5\x63\x93\x4f\x46\x04\x52";
static char result1[] = "\xa9\x99\x3e\x36\x47\x06\x81\x6a\xba\x3e\x25\x71\x78\x50\xc2\x6c\x9c\xd0\xd8\x9d";
static char result2[] = "\x84\x98\x3e\x44\x1c\x3b\xd2\x6e\xba\xae\x4a\xa1\xf9\x51\x29\xe5\xe5\x46\x70\xf1";
static char test2[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
static char test4[] = "0123456701234567012345670123456701234567012345670123456701234567";

static char* resultArray[4] = {result1, result2, result3, result4};
static char* testArray[4] = {test1, test2, test3, test4};
static long repeatCount[4] = {1, 1, 1000000, 10};

extern "C"
{
    // usa: func_020c08ec
    // DGT_Hash2SetSource
    void func_020c08ec(SHA1Context* context, const void* input, unsigned long length)
    {
        const unsigned char* src = (const unsigned char*)input;
        unsigned char* block = context->messageBlock;
        unsigned long lengthLow;

        if (length == 0)
            return;

        lengthLow = context->lengthLow + (length << 3);
        if (lengthLow < context->lengthLow)
            context->lengthHigh++;
        context->lengthHigh += length >> 29;
        context->lengthLow = lengthLow;

        if (context->messageBlockIndex != 0)
        {
            if (context->messageBlockIndex + length >= DIGEST_BLOCK_SIZE)
            {
                unsigned long rest = DIGEST_BLOCK_SIZE - context->messageBlockIndex;
                VectorizedInvertedMemcpy(src, block + context->messageBlockIndex, rest);
                length -= rest;
                src += rest;
                processMessageBlock(context, block, DIGEST_BLOCK_SIZE);
                context->messageBlockIndex = 0;
            }
            else
            {
                VectorizedInvertedMemcpy(src, block + context->messageBlockIndex, length);
                context->messageBlockIndex += length;
                return;
            }
        }

        if (length >= DIGEST_BLOCK_SIZE)
        {
            long size = length & ~(DIGEST_BLOCK_SIZE - 1);
            length -= size;
            if (((unsigned long)src & 3) == 0)
            {
                processMessageBlock(context, src, size);
                src += size;
            }
            else
            {
                do
                {
                    VectorizedInvertedMemcpy(src, block, DIGEST_BLOCK_SIZE);
                    src += DIGEST_BLOCK_SIZE;
                    processMessageBlock(context, block, DIGEST_BLOCK_SIZE);
                    size -= DIGEST_BLOCK_SIZE;
                } while (size > 0);
            }
        }

        context->messageBlockIndex = length;
        if (length != 0)
            VectorizedInvertedMemcpy(src, block, length);
    }

    // usa: func_020c0a40
    // DGT_Hash2GetDigest
    void func_020c0a40(SHA1Context* context, unsigned char* digest)
    {
        unsigned long* block32 = (unsigned long*)context->messageBlock;
        int index = context->messageBlockIndex;
        int word = index >> 2;
        unsigned char* block8;
        unsigned long value;

        if ((index & 3) == 0)
            block32[word] = 0;
        block8 = context->messageBlock;
        block8[index++] = 0x80;
        while ((index & 3) != 0)
            block8[index++] = 0;
        word++;

        if (context->messageBlockIndex >= DIGEST_BLOCK_SIZE - 8)
        {
            for (; word < 16; word++)
                block32[word] = 0;
            processMessageBlock(context, block32, DIGEST_BLOCK_SIZE);
            word = 0;
        }
        for (; word < 14; word++)
            block32[word] = 0;

        value = context->lengthLow;
        block8[63] = value;
        block8[62] = value >> 8;
        block8[61] = value >> 16;
        block8[60] = value >> 24;
        value = context->lengthHigh;
        block8[59] = value;
        block8[58] = value >> 8;
        block8[57] = value >> 16;
        block8[56] = value >> 24;
        processMessageBlock(context, block32, DIGEST_BLOCK_SIZE);

        value = context->intermediateHash[0];
        digest[0] = value >> 24;
        digest[1] = value >> 16;
        digest[2] = value >> 8;
        digest[3] = value;
        value = context->intermediateHash[1];
        digest[4] = value >> 24;
        digest[5] = value >> 16;
        digest[6] = value >> 8;
        digest[7] = value;
        value = context->intermediateHash[2];
        digest[8] = value >> 24;
        digest[9] = value >> 16;
        digest[10] = value >> 8;
        digest[11] = value;
        value = context->intermediateHash[3];
        digest[12] = value >> 24;
        digest[13] = value >> 16;
        digest[14] = value >> 8;
        digest[15] = value;
        value = context->intermediateHash[4];
        digest[16] = value >> 24;
        digest[17] = value >> 16;
        digest[18] = value >> 8;
        digest[19] = value;

        context->messageBlockIndex = 0;
        // Clears the pointer instead of the context
        func_020ca3ec(0, &context, sizeof(context));
    }
}
