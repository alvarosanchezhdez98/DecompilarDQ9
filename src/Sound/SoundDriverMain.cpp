#include "Sound/SoundDriver.h"
#include "System/Mutex.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_main.c: initializes the sound driver's ARM9 side

// The mutex that NitroSystem's sound library locks around its calls (SNDi_LockMutex)
static Mutex sSoundMutex;

extern "C"
{
    // SND_Init
    void func_020d21c0()
    {
        static int initialized = false;
        if (initialized)
            return;
        initialized = true;
        ZeroInitializeMutex(&sSoundMutex);
        func_020d2220();
        func_020d2930();
    }

    // SNDi_LockMutex
    void func_020d21f8()
    {
        LockMutex(&sSoundMutex);
    }

    // SNDi_UnlockMutex
    void func_020d220c()
    {
        UnlockMutex(&sSoundMutex);
    }
}
