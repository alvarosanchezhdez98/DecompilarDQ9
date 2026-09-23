#include "Sound/Sound.h"
#include "System/Cache.h"
#include "System/MessageQueue.h"
#include "System/ProcessorContext.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's capture.c: captures the sound output, for reverb and effects. Only the functions that NitroSystem
// calls are in the ROM, but all the variables are, including the ones of the capture thread.

// NitroSystem's NNSSndCaptureType
enum CaptureType
{
    CaptureType_Reverb,
    CaptureType_Effect,
    CaptureType_Sampling,
};

// The NitroSDK's SND_CHANNEL_DATASHIFT_NONE
#define CHANNEL_DATA_SHIFT_NONE 0
// The NitroSDK's OS_MESSAGE_NOBLOCK
#define MESSAGE_NO_BLOCK 0
// The NitroSDK's SND_OUTPUT_MIXER and SND_CHANNEL_OUT_MIXER
#define OUTPUT_MIXER 0

#define THREAD_STACK_SIZE 1024
#define THREAD_MESSAGE_COUNT 8

typedef void (*CaptureCallback)(void* bufferL, void* bufferR, unsigned long length, int format, void* arg);

// NitroSystem's CaptureParam
struct CaptureParameters
{
    int activeFlag;
    int type; // CaptureType
    int format;
    void* bufferL;
    void* bufferR;
    unsigned long bufLen;
    unsigned long blockSize;
    int curBuffer;
    unsigned long chBitMask;
    unsigned long playChBitMask;
    unsigned long capBitMask;
    int alarmNo;
    int interval;
    CaptureCallback callback;
    void* callbackArg;
    SoundFader fader;
    int fadeOutFlag;
    int volume;
};

// NitroSystem's EffectInfo
struct EffectInfo
{
    CaptureParameters* cap;
    unsigned long blockSize;
    unsigned long offset;
    void* bufferL;
    void* bufferR;
};

// The compiler places these in the order isThreadCreated, currentEffectInfo, messageQueue, messages,
// captureParameters, effectInfos, thread and threadStack
static ProcessorContext thread;
static EffectInfo effectInfos[THREAD_MESSAGE_COUNT];
static CaptureParameters captureParameters;
static void* messages[THREAD_MESSAGE_COUNT];
static MessageQueue messageQueue;
static int currentEffectInfo;
static volatile int isThreadCreated;
static unsigned long long threadStack[THREAD_STACK_SIZE / sizeof(unsigned long long)];

extern "C"
{
    // usa: func_020ca3ec
    // The NitroSDK's MI_CpuClear32
    void func_020ca3ec(int value, void* dst, unsigned int len);
    // usa: func_020d2104
    // The NitroSDK's SND_SetOutputSelector
    void func_020d2104(int left, int right, int channel1, int channel3);

    // usa: func_020bce9c
    // NNSi_SndCaptureInit
    void func_020bce9c()
    {
        isThreadCreated = 0;
        captureParameters.activeFlag = 0;
    }

    // usa: func_020bceb4
    // NNSi_SndCaptureMain: fades the reverb
    void func_020bceb4()
    {
        CaptureParameters* cap;
        SoundFader* fader;
        int volume;

        cap = &captureParameters;
        if (cap->activeFlag && cap->type == CaptureType_Reverb)
        {
            fader = &cap->fader;
            func_020c0260(fader);

            if (cap->fadeOutFlag)
            {
                if (func_020c0278(fader))
                {
                    func_020bcf3c();
                    return;
                }
            }

            volume = func_020c022c(fader) >> 8;
            if (volume != cap->volume)
            {
                func_020d1ff0(cap->playChBitMask, volume, CHANNEL_DATA_SHIFT_NONE);
                cap->volume = volume;
            }
        }
    }

    // usa: func_020bcf3c
    // NNSi_SndCaptureStop
    void func_020bcf3c()
    {
        CaptureParameters* cap = &captureParameters;
        unsigned long commandTag;
        int useAlarm;

        if (!cap->activeFlag)
            return;

        useAlarm = cap->alarmNo >= 0 ? 1 : 0;

        func_020d1f0c(cap->playChBitMask, cap->capBitMask, useAlarm ? 1 << cap->alarmNo : 0, 0);

        if (useAlarm)
        {
            commandTag = func_020d26ec();
            func_020d24c4(COMMAND_BLOCK);
            func_020d2680(commandTag);

            while (func_020c7ea0(&messageQueue, NULL, MESSAGE_NO_BLOCK))
            {
            }
        }

        if (cap->capBitMask)
            func_020bbe94(cap->capBitMask);
        if (cap->chBitMask)
            func_020bbe64(cap->chBitMask);
        if (useAlarm)
            func_020bbef8(cap->alarmNo);

        if (cap->type == CaptureType_Effect)
            func_020d2104(OUTPUT_MIXER, OUTPUT_MIXER, OUTPUT_MIXER, OUTPUT_MIXER);

        cap->activeFlag = 0;
    }

    // usa: func_020bd02c
    // NNSi_SndCaptureBeginSleep
    void func_020bd02c()
    {
        CaptureParameters* cap;
        unsigned long commandTag;

        cap = &captureParameters;
        if (!cap->activeFlag)
            return;

        func_020d1f0c(cap->playChBitMask, cap->capBitMask, cap->alarmNo >= 0 ? 1 << cap->alarmNo : 0, 0);

        commandTag = func_020d26ec();
        func_020d24c4(COMMAND_BLOCK);
        func_020d2680(commandTag);
    }

    // usa: func_020bd08c
    // NNSi_SndCaptureEndSleep
    void func_020bd08c()
    {
        CaptureParameters* cap;

        cap = &captureParameters;
        if (!cap->activeFlag)
            return;

        cap->curBuffer = 0;

        func_020ca3ec(0, cap->bufferL, cap->bufLen);
        func_020ca3ec(0, cap->bufferR, cap->bufLen);
        CleanInvalidateCacheRange(cap->bufferL, cap->bufLen);
        CleanInvalidateCacheRange(cap->bufferR, cap->bufLen);

        func_020d1ee4(cap->playChBitMask, cap->capBitMask, cap->alarmNo >= 0 ? 1 << cap->alarmNo : 0, 0);
    }
}
