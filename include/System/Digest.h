#pragma once

#include "globaldefs.h"

// The NitroSDK's DGT library: message digests. "Hash 1" is MD5 and "hash 2" is SHA-1, and both can compute an
// HMAC.

#define MD5_DIGEST_SIZE 16 // DGT_HASH1_DIGEST_SIZE
#define SHA1_DIGEST_SIZE 20 // DGT_HASH2_DIGEST_SIZE
#define DIGEST_BLOCK_SIZE 64 // DGT_HASH_BLOCK_SIZE

// DGTHash1Context
struct MD5Context
{
    unsigned long a, b, c, d;
    unsigned long long length; // in bytes
    union
    {
        unsigned long buffer32[16];
        unsigned char buffer8[DIGEST_BLOCK_SIZE];
    };
};

// DGTHash2Context, the SHA1Context of RFC 3174's code
struct SHA1Context
{
    unsigned long intermediateHash[5];
    unsigned long lengthLow; // in bits
    unsigned long lengthHigh;
    int messageBlockIndex;
    unsigned char messageBlock[DIGEST_BLOCK_SIZE];
    int computed;
    int corrupted;
};

// A hash function for HmacCalc
struct HmacHash
{
    int digestSize;
    int blockSize;
    void* context;
    void* digest; // the inner hash
    void (*reset)(void* context);
    void (*setSource)(void* context, const void* input, unsigned long length);
    void (*getDigest)(void* context, void* digest);
};

extern "C"
{
    // DGT_Hash1Reset
    void func_020c0328(MD5Context* context);
    // DGT_Hash1SetSource
    void func_020c0368(MD5Context* context, const void* input, unsigned long length);
    // DGT_Hash1GetDigest_R
    void func_020c0430(unsigned char* digest, MD5Context* context);

    // DGT_Hash2Reset
    void func_020c089c(SHA1Context* context);
    // DGT_Hash2SetSource
    void func_020c08ec(SHA1Context* context, const void* input, unsigned long length);
    // DGT_Hash2GetDigest
    void func_020c0a40(SHA1Context* context, unsigned char* digest);
    // DGT_Hash2CalcHmac
    void func_020c0c3c(void* digest, const void* input, int length, const void* key, int keyLength);
}
