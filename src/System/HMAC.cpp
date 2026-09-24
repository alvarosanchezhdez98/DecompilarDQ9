#include "System/Digest.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's HMAC for the hashes of its DGT library

extern "C"
{
    void func_020c0cd0(void* digest, const void* input, int length, const void* key, int keyLength, HmacHash* hash);

    // usa: func_020c0c3c
    // DGT_Hash2CalcHmac
    void func_020c0c3c(void* digest, const void* input, int length, const void* key, int keyLength)
    {
        SHA1Context context;
        unsigned char innerDigest[SHA1_DIGEST_SIZE];
        HmacHash hash = {SHA1_DIGEST_SIZE, DIGEST_BLOCK_SIZE};

        hash.context = &context;
        hash.digest = innerDigest;
        hash.reset = (void (*)(void*))func_020c089c;
        hash.setSource = (void (*)(void*, const void*, unsigned long))func_020c08ec;
        hash.getDigest = (void (*)(void*, void*))func_020c0a40;
        func_020c0cd0(digest, input, length, key, keyLength, &hash);
    }

    // usa: func_020c0cd0
    // HmacCalc
    void func_020c0cd0(void* digest, const void* input, int length, const void* key, int keyLength, HmacHash* hash)
    {
        unsigned char keyDigest[DIGEST_BLOCK_SIZE];
        unsigned char innerPad[DIGEST_BLOCK_SIZE];
        unsigned char outerPad[DIGEST_BLOCK_SIZE];
        const unsigned char* keyBytes;
        int i;

        if (digest == NULL || input == NULL || length == 0 || key == NULL || keyLength == 0 || hash == NULL)
            return;

        if (keyLength > hash->blockSize)
        {
            hash->reset(hash->context);
            hash->setSource(hash->context, key, keyLength);
            hash->getDigest(hash->context, keyDigest);
            key = keyDigest;
            keyLength = hash->digestSize;
        }
        keyBytes = (const unsigned char*)key;

        for (i = 0; i < keyLength; i++)
            innerPad[i] = keyBytes[i] ^ 0x36;
        for (; i < hash->blockSize; i++)
            innerPad[i] = 0x36;
        hash->reset(hash->context);
        hash->setSource(hash->context, innerPad, hash->blockSize);
        hash->setSource(hash->context, input, length);
        hash->getDigest(hash->context, hash->digest);

        for (i = 0; i < keyLength; i++)
            outerPad[i] = keyBytes[i] ^ 0x5c;
        for (; i < hash->blockSize; i++)
            outerPad[i] = 0x5c;
        hash->reset(hash->context);
        hash->setSource(hash->context, outerPad, hash->blockSize);
        hash->setSource(hash->context, hash->digest, hash->digestSize);
        hash->getDigest(hash->context, digest);
    }
}

// The original has two more descriptions of SHA-1 like the one of DGT_Hash2CalcHmac, probably from functions that
// aren't in the ROM. The linker keeps them because they're in the section of the one that it uses.
static const HmacHash unusedHashes[2] = {
    {SHA1_DIGEST_SIZE, DIGEST_BLOCK_SIZE},
    {SHA1_DIGEST_SIZE, DIGEST_BLOCK_SIZE},
};
