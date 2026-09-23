#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's main.c (nns_snd_main.c): initializes the sound library and updates it every frame.
// NNS_SndStopSoundAll, NNS_SndStopChannelAll, NNS_SndUpdateDriverInfo and the functions that read the driver's
// information aren't in the ROM, but their variables are.

// The NitroSDK's SNDDriverInfo: a copy of the sound driver's state
struct SoundDriverInfo
{
    unsigned char data[0x11e0];
};

// The compiler places these in the order currentDriverInfo, isFirstDriverInfo, driverInfoCommandTag, isInitialized,
// preSleepCallback, postSleepCallback and driverInfo
static SleepCallbackInfo postSleepCallback;
static SleepCallbackInfo preSleepCallback;
static int isInitialized;
static unsigned long driverInfoCommandTag;
static int isFirstDriverInfo;
static signed char currentDriverInfo;
static SoundDriverInfo driverInfo[2] __attribute__((aligned(32)));

extern "C"
{
    // usa: func_020d20e4
    // The NitroSDK's SND_SetMasterVolume
    void func_020d20e4(int volume);

    void func_020bbdd8(void* arg);
    void func_020bbe10(void* arg);

    // usa: func_020bbd14
    // NNS_SndInit
    void func_020bbd14()
    {
        if (isInitialized)
            return;
        isInitialized = 1;

        func_020d21c0();

        SetSleepCallbackInfo(&preSleepCallback, func_020bbdd8, NULL);
        SetSleepCallbackInfo(&postSleepCallback, func_020bbe10, NULL);
        func_020cef34(&preSleepCallback);
        func_020cef4c(&postSleepCallback);

        func_020bbf18();
        func_020bce9c();
        func_020bc23c();

        currentDriverInfo = -1;
        isFirstDriverInfo = 1;
    }

    // usa: func_020bbd9c
    // NNS_SndMain
    void func_020bbd9c()
    {
        while (func_020d22f4(COMMAND_NO_BLOCK) != NULL)
        {
        }

        func_020bc2f0();
        func_020bceb4();
        func_020bed10();

        func_020d24c4(COMMAND_NO_BLOCK);
    }

    // usa: func_020bbdcc
    // NNS_SndSetMasterVolume
    void func_020bbdcc(int volume)
    {
        func_020d20e4(volume);
    }

    // usa: func_020bbdd8
    // BeginSleep
    void func_020bbdd8(void* arg)
    {
        unsigned long commandTag;

        func_020bd02c();

        func_020d1f0c(0, 0, 0, 0);

        commandTag = func_020d26ec();
        func_020d24c4(COMMAND_BLOCK);
        func_020d2680(commandTag);
    }

    // usa: func_020bbe10
    // EndSleep
    void func_020bbe10(void* arg)
    {
        func_020bd08c();
    }
}
