#include "Sound/Sound.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's stream.c: plays streams of sound with the sound driver's channels and an alarm, which calls back to
// fill each part of the buffers as they play. NNS_SndStrmSetChannelVolume isn't in the ROM.

// The NitroSDK's SND_CHANNEL_NUM
#define CHANNEL_COUNT 16
// The NitroSDK's SND_CHANNEL_LOOP_REPEAT
#define CHANNEL_LOOP_REPEAT 1
// The NitroSDK's SND_CHANNEL_DATASHIFT_NONE
#define CHANNEL_DATA_SHIFT_NONE 0

// NitroSystem's NNSSndStrmChannel
struct StreamChannel
{
    void* buffer;
    int volume;
};

// The compiler places these in the order isInitialized, streamList, callbackBuffers and streamChannels. In NitroSystem,
// isInitialized is a static variable of NNS_SndStrmInit, and callbackBuffers one of StrmCallback.
static StreamChannel streamChannels[CHANNEL_COUNT];
// The parts of the buffers that the stream's callback fills
static void* callbackBuffers[STREAM_CHANNEL_MAX];
static SignedAllocatorList streamList; // SoundStream
static int isInitialized;

extern "C"
{
    void func_020bcc7c(SoundStream* stream);
    void func_020bccf0(SoundStream* stream);
    void func_020bcd20(void* arg);
    void func_020bcd30(SoundStream* stream, StreamCallbackStatus status);
    void func_020bcde0(void* arg);
    void func_020bce2c(void* arg);

    // usa: func_020bc8d0
    // NNS_SndStrmInit
    void func_020bc8d0(SoundStream* stream)
    {
        if (!isInitialized)
        {
            InitList(&streamList, LIST_LINK_OFFSET(SoundStream, link));
            isInitialized = 1;
        }

        SetSleepCallbackInfo(&stream->preSleepInfo, func_020bcde0, stream);
        SetSleepCallbackInfo(&stream->postSleepInfo, func_020bce2c, stream);

        stream->chBitMask = 0;
        stream->numChannels = 0;
        stream->activeFlag = 0;
        stream->startFlag = 0;
    }

    // usa: func_020bc948
    // NNS_SndStrmAllocChannel
    int func_020bc948(SoundStream* stream, int numChannels, const unsigned char channelNoList[])
    {
        unsigned long channelMask;
        int i;

        channelMask = 0;
        for (i = 0; i < numChannels; i++)
        {
            stream->channelNo[i] = channelNoList[i];
            channelMask |= 1 << channelNoList[i];
        }

        if (!func_020bbe1c(channelMask))
            return 0;

        stream->numChannels = numChannels;
        stream->chBitMask = channelMask;
        return 1;
    }

    // usa: func_020bc9a8
    // NNS_SndStrmFreeChannel
    void func_020bc9a8(SoundStream* stream)
    {
        if (stream->chBitMask == 0)
            return;

        func_020bbe64(stream->chBitMask);
        stream->chBitMask = 0;
        stream->numChannels = 0;
    }

    // usa: func_020bc9d0
    // NNS_SndStrmSetup
    int func_020bc9d0(SoundStream* stream, StreamFormat format, void* buffer, unsigned long bufferSize, int timer,
        int interval, StreamCallback callback, void* arg)
    {
        StreamChannel* channel;
        unsigned int samples;
        unsigned int alarmTimer;
        int channelNo;
        int index;

        if (stream->activeFlag)
            func_020bcbc4(stream);

        bufferSize /= 32 * interval * stream->numChannels;
        stream->chBufLen = bufferSize * interval * 32;

        samples = stream->chBufLen;
        if (format == StreamFormat_PCM16)
            samples >>= 1;
        alarmTimer = timer * samples / interval;

        stream->alarmNo = func_020bbeb0();
        if (stream->alarmNo < 0)
            return 0;

        for (index = 0; index < stream->numChannels; index++)
        {
            channelNo = stream->channelNo[index];
            channel = &streamChannels[channelNo];
            channel->buffer = (unsigned char*)buffer + stream->chBufLen * index;
            channel->volume = 0;
            func_020d2038(channelNo, format, channel->buffer, CHANNEL_LOOP_REPEAT, 0, (int)(stream->chBufLen >> 2),
                127, CHANNEL_DATA_SHIFT_NONE, timer << 5, 64);
        }

        func_020d1f70(stream->alarmNo, alarmTimer, alarmTimer, func_020bcd20, stream);
        AppendListObject(&streamList, stream);

        stream->format = format;
        stream->interval = interval;
        stream->callback = callback;
        stream->callbackArg = arg;
        stream->curBuffer = 0;
        stream->volume = 0;
        stream->activeFlag = 1;

        {
            int oldState = DisableIRQInterrupts();
            stream->interval = 1;
            func_020bcd30(stream, StreamCallbackStatus_Setup);
            stream->interval = interval;
            SetIRQInterruptState(oldState);
        }
        return 1;
    }

    // usa: func_020bcb70
    // NNS_SndStrmStart
    void func_020bcb70(SoundStream* stream)
    {
        func_020d1ee4(stream->chBitMask, 0, 1 << stream->alarmNo, 0);

        if (!stream->startFlag)
        {
            func_020cef34(&stream->preSleepInfo);
            func_020cef4c(&stream->postSleepInfo);
            stream->startFlag = 1;
        }
    }

    // usa: func_020bcbc4
    // NNS_SndStrmStop
    void func_020bcbc4(SoundStream* stream)
    {
        if (!stream->activeFlag)
            return;

        func_020bcc7c(stream);
    }

    // usa: func_020bcbe0
    // NNS_SndStrmSetVolume
    void func_020bcbe0(SoundStream* stream, int volume)
    {
        unsigned short channelVolume;
        int decibels;
        int channelNo;
        int i;

        stream->volume = volume;

        for (i = 0; i < stream->numChannels; i++)
        {
            channelNo = stream->channelNo[i];
            decibels = stream->volume + streamChannels[channelNo].volume;
            channelVolume = func_020d2ac4(decibels);
            func_020d1ff0(1 << channelNo, channelVolume & 0xff, channelVolume >> 8);
        }
    }

    // usa: func_020bcc4c
    // NNS_SndStrmSetChannelPan
    void func_020bcc4c(SoundStream* stream, int channel, int pan)
    {
        if (channel > stream->numChannels - 1)
            return;

        func_020d2018(1 << stream->channelNo[channel], pan);
    }

    // usa: func_020bcc7c
    // ForceStopStrm
    void func_020bcc7c(SoundStream* stream)
    {
        unsigned long commandTag;

        if (stream->startFlag)
        {
            func_020d1f0c(stream->chBitMask, 0, 1 << stream->alarmNo, 0);
            func_020cef64(&stream->preSleepInfo);
            func_020cef7c(&stream->postSleepInfo);
            stream->startFlag = 0;

            commandTag = func_020d26ec();
            func_020d24c4(COMMAND_BLOCK);
            func_020d2680(commandTag);
        }

        func_020bccf0(stream);
    }

    // usa: func_020bccf0
    // ShutdownStrm
    void func_020bccf0(SoundStream* stream)
    {
        func_020bbef8(stream->alarmNo);
        RemoveListObject(&streamList, stream);
        stream->activeFlag = 0;
    }

    // usa: func_020bcd20
    // AlarmCallback
    void func_020bcd20(void* arg)
    {
        func_020bcd30((SoundStream*)arg, StreamCallbackStatus_Interval);
    }

    // usa: func_020bcd30
    // StrmCallback: calls the stream's callback to fill the next part of the buffers
    void func_020bcd30(SoundStream* stream, StreamCallbackStatus status)
    {
        const unsigned long blockSize = stream->chBufLen / stream->interval;
        const unsigned long offset = blockSize * stream->curBuffer;
        int index;
        int channelNo;

        for (index = 0; index < stream->numChannels; index++)
        {
            channelNo = stream->channelNo[index];
            callbackBuffers[index] = (unsigned char*)streamChannels[channelNo].buffer + offset;
        }

        stream->callback(status, stream->numChannels, callbackBuffers, blockSize, stream->format, stream->callbackArg);

        stream->curBuffer++;
        if (stream->curBuffer >= stream->interval)
            stream->curBuffer = 0;
    }

    // usa: func_020bcde0
    // BeginSleep
    void func_020bcde0(void* arg)
    {
        SoundStream* stream = (SoundStream*)arg;
        unsigned long commandTag;

        if (!stream->startFlag)
            return;

        func_020d1f0c(stream->chBitMask, 0, 1 << stream->alarmNo, 0);

        commandTag = func_020d26ec();
        func_020d24c4(COMMAND_BLOCK);
        func_020d2680(commandTag);
    }

    // usa: func_020bce2c
    // EndSleep
    void func_020bce2c(void* arg)
    {
        SoundStream* stream = (SoundStream*)arg;

        if (!stream->startFlag)
            return;

        while (stream->curBuffer != 0)
        {
            int oldState = DisableIRQInterrupts();
            func_020bcd30(stream, StreamCallbackStatus_Interval);
            SetIRQInterruptState(oldState);
        }

        func_020d1ee4(stream->chBitMask, 0, 1 << stream->alarmNo, 0);
    }
}
