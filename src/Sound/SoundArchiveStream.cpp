#include "Sound/Sound.h"
#include "Filesystem/FileAccessor.h"
#include "Filesystem/LowNitroHandle.h"
#include "System/Cache.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include "System/Mutex.h"
#include "System/ProcessorContext.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's sndarc_stream.c: plays the streams (.strm) of the sound archive, reading them from the file (or from
// memory) in a thread as they play, and decoding IMA ADPCM. The functions that aren't in the ROM are
// NNS_SndArcStrmCreatePrepareThread, NNS_SndArcStrmPrepareEx and ...Ex2, NNS_SndArcStrmStartEx and ...Ex2,
// NNS_SndArcStrmIsPrepared, NNS_SndArcStrmStopAll, NNS_SndArcStrmMoveVolume, NNS_SndArcStrmSetChannelVolume and
// ...Pan, NNS_SndArcStrmGetChannelCount, NNS_SndArcStrmAllocChannel and ...FreeChannel, and the NNSi_ functions
// other than NNSi_SndArcStrmMain.

// NitroSystem's NNS_SND_STRM_PLAYER_NUM
#define STREAM_PLAYER_COUNT 4
// NitroSystem's NNS_SND_STRM_THREAD_STACK_SIZE
#define THREAD_STACK_SIZE 1024

// The size of each block of the buffers, and their number
#define BLOCK_SIZE 512
#define BLOCK_COUNT 4
#define COMMAND_BUFFER_COUNT (STREAM_PLAYER_COUNT * (BLOCK_COUNT - 2))
#define ADPCM_INDEX_COUNT 89
#define STREAM_CHANNEL_COUNT 6

// NitroSystem's NNS_SND_ARC_STRM_FORCE_STEREO
#define FORCE_STEREO 1

// The NitroSDK's FS_SEEK_SET
#define SEEK_SET 0

struct StreamPlayer;

// NitroSystem's NNSSndStrmHandle
struct StreamHandle
{
    StreamPlayer* player;
};

// NitroSystem's NNSSndArcStrmCallbackStatus, NNSSndArcStrmCallbackInfo and NNSSndArcStrmCallbackParam: a callback
// at the end of the data, which can play another stream
enum ArchiveStreamCallbackStatus
{
    ArchiveStreamCallbackStatus_DataEnd,
};

struct ArchiveStreamCallbackInfo
{
    int playerNo;
    int strmNo;
};

struct ArchiveStreamCallbackParameters
{
    int strmNo;
    unsigned long offset;
};

typedef int (*ArchiveStreamCallback)(ArchiveStreamCallbackStatus status, const ArchiveStreamCallbackInfo* info,
    ArchiveStreamCallbackParameters* param, void* arg);

typedef int (*OpenStreamFunction)(StreamPlayer* player, unsigned long fileId);
typedef void (*CloseStreamFunction)(StreamPlayer* player);
typedef long (*ReadStreamFunction)(StreamPlayer* player, void* dest, unsigned long size, unsigned long offset);
typedef void (*CancelStreamFunction)(StreamPlayer* player);

// NitroSystem's StrmFormat: the format of the stream's file
enum StreamFileFormat
{
    StreamFileFormat_PCM8,
    StreamFileFormat_PCM16,
    StreamFileFormat_ADPCM,
};

// NitroSystem's NNSSndStrmData: the header of a stream (.strm)
struct StreamData
{
    SoundFileHeader fileHeader;
    SoundBlockHeader blockHeader;
    unsigned char format; // StreamFileFormat
    unsigned char loopFlag;
    unsigned char numChannels;
    unsigned char pad;
    unsigned short sampleRate;
    unsigned short timer;
    unsigned long loopStart;
    unsigned long loopEnd;
    unsigned long dataOffset;
    unsigned long numBlocks;
    unsigned long blockSize;
    unsigned long blockSamples;
    unsigned long lastBlockSize;
    unsigned long lastBlockSamples;
};

// NitroSystem's AdpcmState
struct AdpcmState
{
    short prevSample;
    unsigned char prevIndex;
    unsigned char padding;
};

// How C copies an AdpcmState
struct AdpcmStateCopy
{
    unsigned short data[2];
};

// NitroSystem's NNSSndStrmPlayer
struct StreamPlayer
{
    SoundStream stream;
    NitroVM file;
    unsigned long fileOffset;
    StreamData info;
    SoundFader fader;
    AdpcmState adpcmState[STREAM_CHANNEL_COUNT];
    int activeFlag : 1;
    int playFlag : 1;
    int startFlag : 1;
    int fadeOutFlag : 1;
    int dirtyFlag : 1;
    int finishFlag : 1;
    int monoFlag : 1;
    volatile int finishCounter;
    volatile int prepareFlag;
    volatile int commandCount;
    int allocChannelCount;
    unsigned char numChannels;
    unsigned char padding;
    unsigned char chNoList[STREAM_CHANNEL_COUNT];
    void* buffer;
    unsigned long bufSize;
    StreamCallback strmCallback;
    void* strmCallbackArg;
    ArchiveStreamCallback sndArcStrmCallback;
    void* sndArcStrmCallbackArg;
    int strmNo;
    int playerNo;
    StreamHandle* handle;
    int prio;
    int initVolume;
    int extVolume;
    int volume;
    unsigned long curSample;
    OpenStreamFunction openStreamFunc;
    CloseStreamFunction closeStreamFunc;
    ReadStreamFunction readStreamFunc;
    CancelStreamFunction cancelStreamFunc;
};

// NitroSystem's LoadCommand: a request to the thread to fill a block of the buffers
struct LoadCommand
{
    ListLink link;
    StreamPlayer* player;
    StreamCallbackStatus status;
    int numChannels;
    void* buffer[STREAM_CHANNEL_COUNT];
    unsigned long bufLen;
};

// NitroSystem's NNSSndStrmThread
struct StreamThread
{
    ProcessorContext thread;
    unsigned long long stack[THREAD_STACK_SIZE / sizeof(unsigned long long)];
    BlockedContextList threadQ;
    Mutex mutex;
    SignedAllocatorList commandList; // LoadCommand
};

static const signed char adpcmIndexTable[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8,
};

static const short adpcmStepSizeTable[ADPCM_INDEX_COUNT] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107,
    118, 130, 143, 157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796, 876, 963,
    1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358, 5894,
    6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794,
    32767,
};

// The compiler sorts the variables that are defined before the first function by size, and places the ones after it
// in order: isInitialized, prepareThread, decodeBuffer, freeCommandList, decodeBufferMutex, loadCommandBuffer,
// strmThread and strmPlayers, then decodeBufferArea, which is after NNSi_SndArcStrmGetThread.
static unsigned char* decodeBuffer;
static StreamThread* prepareThread;
static int isInitialized;
static SignedAllocatorList freeCommandList; // LoadCommand
static Mutex decodeBufferMutex;
static LoadCommand loadCommandBuffer[COMMAND_BUFFER_COUNT];
static StreamThread strmThread;
static StreamPlayer strmPlayers[STREAM_PLAYER_COUNT];

// NitroSystem's NNS_SndStrmHandleIsValid
static inline bool IsStreamHandleValid(const StreamHandle* handle)
{
    return handle->player != NULL;
}

// NitroSystem's DecodeAdpcm
static inline short DecodeAdpcm(int code, AdpcmState* state)
{
    int step;
    int sample;
    int index;
    int d;

    sample = state->prevSample;
    index = state->prevIndex;
    step = adpcmStepSizeTable[index];

    d = step >> 3;
    if (code & 4)
        d += step;
    if (code & 2)
        d += step >> 1;
    if (code & 1)
        d += step >> 2;

    if (code & 8)
    {
        sample -= d;
        if (sample < -32768)
            sample = -32768;
    }
    else
    {
        sample += d;
        if (sample > 32767)
            sample = 32767;
    }

    index += adpcmIndexTable[code];
    if (index < 0)
        index = 0;
    else if (index > ADPCM_INDEX_COUNT - 1)
        index = ADPCM_INDEX_COUNT - 1;

    state->prevSample = (short)sample;
    state->prevIndex = (unsigned char)index;
    return (short)sample;
}

extern "C"
{
    int func_020beaec(SoundHeap* heap);
    int func_020bebb4(StreamHandle* handle, int strmNo, unsigned long offset);
    void func_020bec10(StreamHandle* handle);
    void func_020bec80(StreamHandle* handle);
    StreamPlayer* func_020bee20(StreamHandle* handle, int playerNo, int prio);
    void func_020beeac(StreamPlayer* player);
    int func_020beed8(StreamHandle* handle, const ArchiveStreamInfo* strmInfo, int playerNo, int playerPrio,
        int strmNo, unsigned long offset, StreamCallback strmCallback, void* strmCallbackArg,
        ArchiveStreamCallback sndArcStrmCallback, void* sndArcStrmCallbackArg);
    void func_020bf148(StreamPlayer* player, int fadeFrame);
    void func_020bf1a0(StreamPlayer* player);
    void func_020bf238(StreamPlayer* player);
    int func_020bf29c(StreamPlayer* player, int numChannels, const unsigned char channelNoList[]);
    void func_020bf2d4(StreamPlayer* player);
    void func_020bf2f8(StreamThread* thread, unsigned long threadPrio);
    void func_020bf358(SignedAllocatorList* commandList, const StreamPlayer* player);
    LoadCommand* func_020bf3c8(SignedAllocatorList* commandList);
    LoadCommand* func_020bf418();
    void func_020bf458(LoadCommand* command);
    void func_020bf484(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020bf520(StreamCallbackStatus status, int numChannels, void* buffer[], unsigned long length,
        StreamFormat format, void* arg);
    void func_020bf658(StreamPlayer* player);
    void func_020bf79c(LoadCommand* command);
    void func_020bffc4(StreamPlayer* player, unsigned long fileId);
    int func_020c0044(StreamPlayer* player, unsigned long fileId);
    void func_020c00b8(StreamPlayer* player);
    long func_020c00c8(StreamPlayer* player, void* dest, unsigned long size, unsigned long offset);
    void func_020c0100(StreamPlayer* player);
    int func_020c0110(StreamPlayer* player, unsigned long fileId);
    void func_020c0138(StreamPlayer* player);
    long func_020c013c(StreamPlayer* player, void* dest, unsigned long size, unsigned long offset);
    void func_020c0158(StreamPlayer* player);
    void func_020c015c(void* arg);

    // NNSi_SndArcStrmGetThread: it isn't in the ROM, but decodeBufferArea is defined after it
    ProcessorContext* NNSi_SndArcStrmGetThread()
    {
        return &strmThread.thread;
    }
}

// Where the thread decodes the ADPCM streams. In the original, it's 4 bytes after strmPlayers, and the .bss doesn't
// start at a multiple of 32, so it's aligned to 16 bytes rather than 32.
static unsigned char decodeBufferArea[BLOCK_SIZE] __attribute__((aligned(16)));

extern "C"
{
    // usa: func_020be9e8
    // NNS_SndArcStrmInit: sets up the stream players and starts their thread
    void func_020be9e8(unsigned long threadPrio, SoundHeap* heap)
    {
        int playerNo;
        StreamPlayer* player;
        int i;
        int result;

        if (isInitialized)
        {
            result = func_020beaec(heap);
            return;
        }
        isInitialized = 1;

        InitList(&freeCommandList, LIST_LINK_OFFSET(LoadCommand, link));
        for (i = 0; i < COMMAND_BUFFER_COUNT; i++)
            AppendListObject(&freeCommandList, &loadCommandBuffer[i]);

        ZeroInitializeMutex(&decodeBufferMutex);
        decodeBuffer = decodeBufferArea;

        for (playerNo = 0; playerNo < STREAM_PLAYER_COUNT; ++playerNo)
        {
            player = &strmPlayers[playerNo];
            player->activeFlag = 0;
            NitroVM_Initialize(&player->file);
            func_020bc8d0(&player->stream);
            player->playerNo = playerNo;
            player->numChannels = 0;
            player->buffer = NULL;
            player->bufSize = 0;
            player->allocChannelCount = 0;
        }

        result = func_020beaec(heap);
        func_020bf2f8(&strmThread, threadPrio);
    }

    // usa: func_020beaec
    // NNS_SndArcStrmSetupPlayer: allocates the buffers of the players that the sound archive defines
    int func_020beaec(SoundHeap* heap)
    {
        int playerNo;
        const ArchiveStreamPlayerInfo* playerInfo;
        StreamPlayer* player;
        void* buffer;
        unsigned long bufSize;
        int i;

        for (playerNo = 0; playerNo < STREAM_PLAYER_COUNT; ++playerNo)
        {
            player = &strmPlayers[playerNo];

            playerInfo = func_020bd6ac(playerNo);
            if (playerInfo == NULL)
                continue;

            player->numChannels = playerInfo->numChannels;
            for (i = 0; i < playerInfo->numChannels; i++)
                player->chNoList[i] = playerInfo->chNoList[i];

            if (heap != NULL)
            {
                bufSize = (unsigned long)(BLOCK_SIZE * BLOCK_COUNT * player->numChannels);
                buffer = func_020bda58(heap, bufSize, func_020bf484, (unsigned long)player, 0);
                if (buffer == NULL)
                    return 0;

                func_020bf1a0(player);
                player->buffer = buffer;
                player->bufSize = bufSize;
            }
        }
        return 1;
    }

    // usa: func_020bebb4
    // NNS_SndArcStrmPrepare
    int func_020bebb4(StreamHandle* handle, int strmNo, unsigned long offset)
    {
        const ArchiveStreamInfo* strmInfo;

        strmInfo = func_020bd5e4(strmNo);
        if (strmInfo == NULL)
            return 0;

        return func_020beed8(handle, strmInfo, strmInfo->playerNo, strmInfo->playerPrio, strmNo, offset, NULL, NULL,
            NULL, NULL);
    }

    // usa: func_020bec10
    // NNS_SndArcStrmStartPrepared
    void func_020bec10(StreamHandle* handle)
    {
        if (!IsStreamHandleValid(handle))
            return;

        handle->player->startFlag = 1;
    }

    // usa: func_020bec30
    // NNS_SndArcStrmStart
    int func_020bec30(StreamHandle* handle, int strmNo, unsigned long offset)
    {
        int result;

        result = func_020bebb4(handle, strmNo, offset);
        if (!result)
            return 0;

        func_020bec10(handle);
        return 1;
    }

    // usa: func_020bec58
    // NNS_SndArcStrmStop
    void func_020bec58(StreamHandle* handle, int fadeFrame)
    {
        if (!IsStreamHandleValid(handle))
            return;

        func_020bf148(handle->player, fadeFrame);
    }

    // usa: func_020bec74
    // NNS_SndStrmHandleInit
    void func_020bec74(StreamHandle* handle)
    {
        handle->player = NULL;
    }

    // usa: func_020bec80
    // NNS_SndStrmHandleRelease
    void func_020bec80(StreamHandle* handle)
    {
        if (handle->player == NULL)
            return;

        handle->player->handle = NULL;
        handle->player = NULL;
    }

    // usa: func_020bec98
    // NNS_SndArcStrmGetCurrentPlayingPos: in milliseconds
    unsigned long func_020bec98(StreamHandle* handle)
    {
        StreamPlayer* player;
        unsigned long long pos;

        if (!IsStreamHandleValid(handle))
            return 0;

        player = handle->player;
        pos = player->curSample;
        pos *= 1000;
        pos /= player->info.sampleRate;
        return (unsigned long)pos;
    }

    // usa: func_020becd4
    // NNS_SndArcStrmGetTimeLength: in milliseconds
    unsigned long func_020becd4(StreamHandle* handle)
    {
        StreamPlayer* player;
        unsigned long long length;

        if (!IsStreamHandleValid(handle))
            return 0;

        player = handle->player;
        length = player->info.loopEnd;
        length *= 1000;
        length /= player->info.sampleRate;
        return (unsigned long)length;
    }

    // usa: func_020bed10
    // NNSi_SndArcStrmMain: starts the prepared streams and fades them
    void func_020bed10()
    {
        StreamPlayer* player;
        int playerNo;
        int volume;

        for (playerNo = 0; playerNo < STREAM_PLAYER_COUNT; ++playerNo)
        {
            player = &strmPlayers[playerNo];
            if (!player->activeFlag)
                continue;

            if (player->finishCounter == 0)
            {
                func_020bf1a0(player);
                continue;
            }

            if (player->startFlag)
            {
                if (player->prepareFlag)
                {
                    func_020bcb70(&player->stream);
                    player->playFlag = 1;
                    player->startFlag = 0;
                }
            }

            if (!player->playFlag)
                continue;

            func_020c0260(&player->fader);

            volume = CalculateDecibel(func_020c022c(&player->fader) >> 8) + CalculateDecibel(player->initVolume)
                + CalculateDecibel(player->extVolume);
            if (volume != player->volume)
            {
                func_020bcbe0(&player->stream, volume);
                player->volume = volume;
            }

            if (player->fadeOutFlag)
            {
                if (func_020c0278(&player->fader))
                    func_020bf1a0(player);
            }
        }
    }

    // usa: func_020bee20
    // AllocPlayer
    StreamPlayer* func_020bee20(StreamHandle* handle, int playerNo, int prio)
    {
        StreamPlayer* player;

        if (handle->player != NULL)
            func_020bec80(handle);

        player = &strmPlayers[playerNo];
        if (player->buffer == NULL)
            return NULL;

        if (player->activeFlag)
        {
            if (prio < player->prio)
                return NULL;
            func_020bf1a0(player);
        }

        player->prio = prio;
        player->activeFlag = 1;
        player->handle = handle;
        handle->player = player;
        return player;
    }

    // usa: func_020beeac
    // FreePlayer
    void func_020beeac(StreamPlayer* player)
    {
        if (player->handle != NULL)
        {
            player->handle->player = NULL;
            player->handle = NULL;
        }

        player->activeFlag = 0;
        player->startFlag = 0;
        player->playFlag = 0;
    }

    // usa: func_020beed8
    // PrepareStrm: opens the stream and fills the buffers
    int func_020beed8(StreamHandle* handle, const ArchiveStreamInfo* strmInfo, int playerNo, int playerPrio,
        int strmNo, unsigned long offset, StreamCallback strmCallback, void* strmCallbackArg,
        ArchiveStreamCallback sndArcStrmCallback, void* sndArcStrmCallbackArg)
    {
        StreamPlayer* player;
        StreamFormat format;
        int numChannels;
        int result;

        player = func_020bee20(handle, playerNo, playerPrio);
        if (player == NULL)
            return 0;

        func_020bffc4(player, strmInfo->fileId);
        if (!player->openStreamFunc(player, strmInfo->fileId))
        {
            func_020beeac(player);
            return 0;
        }

        player->curSample = (unsigned long long)player->info.sampleRate * offset / 1000;
        if (player->curSample != 0 && player->info.format == StreamFileFormat_ADPCM)
            player->dirtyFlag = 1;
        else
            player->dirtyFlag = 0;

        player->finishCounter = BLOCK_COUNT;
        player->finishFlag = 0;
        player->playFlag = 0;
        player->prepareFlag = 0;
        player->startFlag = 0;
        player->fadeOutFlag = 0;
        player->commandCount = 0;

        player->strmCallback = strmCallback;
        player->strmCallbackArg = strmCallbackArg;
        player->sndArcStrmCallback = sndArcStrmCallback;
        player->sndArcStrmCallbackArg = sndArcStrmCallbackArg;
        player->strmNo = strmNo;

        player->volume = 0;
        player->initVolume = strmInfo->volume;
        player->extVolume = 127;
        func_020c01ec(&player->fader);
        func_020c0204(&player->fader, 127 << 8, 1);

        switch (player->info.format)
        {
            case StreamFileFormat_PCM8:
                format = StreamFormat_PCM8;
                break;
            case StreamFileFormat_PCM16:
            case StreamFileFormat_ADPCM:
                format = StreamFormat_PCM16;
                break;
        }

        numChannels = player->info.numChannels;
        if (strmInfo->flags & FORCE_STEREO)
            numChannels = 2;
        if (numChannels > player->numChannels)
            numChannels = player->numChannels;
        player->monoFlag = numChannels == 1 ? 1 : 0;

        result = func_020bf29c(player, numChannels, player->chNoList);
        if (!result)
        {
            player->closeStreamFunc(player);
            func_020beeac(player);
            return 0;
        }

        result = func_020bc9d0(&player->stream, format, player->buffer,
            player->bufSize * numChannels / player->numChannels, player->info.timer, BLOCK_COUNT, func_020bf520,
            player);
        if (!result)
        {
            func_020bf2d4(player);
            player->closeStreamFunc(player);
            func_020beeac(player);
            return 0;
        }

        if (numChannels == 2)
        {
            func_020bcc4c(&player->stream, 0, 0);
            func_020bcc4c(&player->stream, 1, 127);
        }
        return 1;
    }

    // usa: func_020bf148
    // StopStrm
    void func_020bf148(StreamPlayer* player, int fadeFrame)
    {
        if (!player->playFlag)
        {
            func_020bf1a0(player);
            return;
        }

        if (fadeFrame == 0)
        {
            func_020bf1a0(player);
            return;
        }

        func_020c0204(&player->fader, 0, fadeFrame);
        player->fadeOutFlag = 1;
        player->prio = 0;
    }

    // usa: func_020bf1a0
    // ForceStopStrm
    void func_020bf1a0(StreamPlayer* player)
    {
        LockMutex(&strmThread.mutex);
        if (prepareThread)
            LockMutex(&prepareThread->mutex);

        if (player->playFlag)
            func_020bcbc4(&player->stream);

        if (player->activeFlag)
            player->cancelStreamFunc(player);

        func_020bf238(player);

        UnlockMutex(&strmThread.mutex);
        if (prepareThread)
            UnlockMutex(&prepareThread->mutex);
    }

    // usa: func_020bf238
    // ShutdownPlayer
    void func_020bf238(StreamPlayer* player)
    {
        if (!player->activeFlag)
            return;

        func_020bf2d4(player);
        player->closeStreamFunc(player);

        func_020bf358(&strmThread.commandList, player);
        if (prepareThread)
            func_020bf358(&prepareThread->commandList, player);

        func_020beeac(player);
    }

    // usa: func_020bf29c
    // AllocChannel
    int func_020bf29c(StreamPlayer* player, int numChannels, const unsigned char channelNoList[])
    {
        if (player->allocChannelCount == 0)
        {
            if (!func_020bc948(&player->stream, numChannels, channelNoList))
                return 0;
        }

        player->allocChannelCount++;
        return 1;
    }

    // usa: func_020bf2d4
    // FreeChannel
    void func_020bf2d4(StreamPlayer* player)
    {
        if (player->allocChannelCount == 0)
            return;

        player->allocChannelCount--;
        if (player->allocChannelCount == 0)
            func_020bc9a8(&player->stream);
    }

    // usa: func_020bf2f8
    // CreateThread
    void func_020bf2f8(StreamThread* thread, unsigned long threadPrio)
    {
        PopulateContext(&thread->thread, (unsigned int)func_020c015c, (unsigned int)thread,
            (unsigned int)(thread->stack + THREAD_STACK_SIZE / sizeof(unsigned long long)), THREAD_STACK_SIZE,
            threadPrio);
        InitList(&thread->commandList, LIST_LINK_OFFSET(LoadCommand, link));
        ZeroInitializeMutex(&thread->mutex);
        thread->threadQ.first = thread->threadQ.last = NULL;
        MarkContextReadyAndSwitch(&thread->thread);
    }

    // usa: func_020bf358
    // RemoveCommandByPlayer
    void func_020bf358(SignedAllocatorList* commandList, const StreamPlayer* player)
    {
        int oldState;
        LoadCommand* command;
        LoadCommand* next;

        oldState = DisableIRQInterrupts();

        for (command = (LoadCommand*)GetNextListObject(commandList, NULL); command != NULL; command = next)
        {
            next = (LoadCommand*)GetNextListObject(commandList, command);
            if (command->player == player)
            {
                RemoveListObject(commandList, command);
                func_020bf458(command);
            }
        }

        SetIRQInterruptState(oldState);
    }

    // usa: func_020bf3c8
    // ReadCommandBuffer
    LoadCommand* func_020bf3c8(SignedAllocatorList* commandList)
    {
        int oldState;
        LoadCommand* command;

        oldState = DisableIRQInterrupts();

        command = (LoadCommand*)GetNextListObject(commandList, NULL);
        if (command != NULL)
        {
            RemoveListObject(commandList, command);
            command->player->commandCount--;
        }

        SetIRQInterruptState(oldState);
        return command;
    }

    // usa: func_020bf418
    // AllocCommandBuffer
    LoadCommand* func_020bf418()
    {
        int oldState;
        LoadCommand* command;

        oldState = DisableIRQInterrupts();

        command = (LoadCommand*)GetNextListObject(&freeCommandList, NULL);
        if (command != NULL)
            RemoveListObject(&freeCommandList, command);

        SetIRQInterruptState(oldState);
        return command;
    }

    // usa: func_020bf458
    // FreeCommandBuffer
    void func_020bf458(LoadCommand* command)
    {
        int oldState;

        oldState = DisableIRQInterrupts();
        AppendListObject(&freeCommandList, command);
        SetIRQInterruptState(oldState);
    }

    // usa: func_020bf484
    // DisposeCallback: stops the player when its buffer is freed
    void func_020bf484(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        StreamPlayer* player = (StreamPlayer*)data1;

        if (memory == player->buffer)
        {
            LockMutex(&strmThread.mutex);
            if (prepareThread)
                LockMutex(&prepareThread->mutex);

            func_020bf1a0(player);
            player->buffer = NULL;
            player->bufSize = 0;
            player->numChannels = 0;

            if (player->allocChannelCount > 0)
            {
                func_020bc9a8(&player->stream);
                player->allocChannelCount = 0;
            }

            UnlockMutex(&strmThread.mutex);
            if (prepareThread)
                UnlockMutex(&prepareThread->mutex);
        }
    }

    // usa: func_020bf520
    // StrmCallback: asks the thread to fill the next block of the buffers
    void func_020bf520(StreamCallbackStatus status, int numChannels, void* buffer[], unsigned long length,
        StreamFormat format, void* arg)
    {
        StreamPlayer* player = (StreamPlayer*)arg;
        LoadCommand* command;
        StreamThread* thread;
        int ch;

        if (player->commandCount >= BLOCK_COUNT - 2)
        {
            command = NULL;
            while ((command = (LoadCommand*)GetNextListObject(&strmThread.commandList, command)) != NULL)
            {
                if (command->player == player)
                    break;
            }

            for (ch = 0; ch < command->numChannels; ch++)
                VectorizedMemset(command->buffer[ch], 0, command->bufLen);

            RemoveListObject(&strmThread.commandList, command);
            player->commandCount--;
            func_020bf458(command);
        }

        command = func_020bf418();
        command->player = player;
        command->status = status;
        command->numChannels = numChannels;
        for (ch = 0; ch < numChannels; ch++)
            command->buffer[ch] = buffer[ch];
        command->bufLen = length;

        thread = &strmThread;
        if (status == StreamCallbackStatus_Setup && prepareThread)
            thread = prepareThread;

        player->commandCount++;
        AppendListObject(&thread->commandList, command);
        UnblockContexts(&thread->threadQ);
    }

    // usa: func_020bf658
    // OnDataEnd: asks the callback which stream to play next
    void func_020bf658(StreamPlayer* player)
    {
        ArchiveStreamCallbackInfo info;
        ArchiveStreamCallbackParameters param;
        const ArchiveStreamInfo* strmInfo;
        unsigned char oldFormat;
        unsigned short oldSampleRate;
        int result;

        info.playerNo = player->playerNo;
        info.strmNo = player->strmNo;

        param.strmNo = player->strmNo;
        param.offset = 0;

        result = player->sndArcStrmCallback(ArchiveStreamCallbackStatus_DataEnd, &info, &param,
            player->sndArcStrmCallbackArg);
        if (!result)
            return;

        strmInfo = func_020bd5e4(param.strmNo);
        if (strmInfo == NULL)
            return;

        oldFormat = player->info.format;
        oldSampleRate = player->info.sampleRate;

        player->closeStreamFunc(player);

        func_020bffc4(player, strmInfo->fileId);
        if (!player->openStreamFunc(player, strmInfo->fileId))
            return;

        if (oldSampleRate != player->info.sampleRate)
            return;

        if (oldFormat == StreamFileFormat_PCM8 && player->info.format != StreamFileFormat_PCM8
            || oldFormat != StreamFileFormat_PCM8 && player->info.format == StreamFileFormat_PCM8)
            return;

        player->strmNo = param.strmNo;
        player->curSample = (unsigned long long)player->info.sampleRate * param.offset / 1000;
        if (player->curSample != 0 && player->info.format == StreamFileFormat_ADPCM)
            player->dirtyFlag = 1;
        else
            player->dirtyFlag = 0;

        player->finishFlag = 0;
    }

    // usa: func_020bf79c
    // MakeWaveData: reads the next block of the stream to the buffers, decoding it
    void func_020bf79c(LoadCommand* command)
    {
        StreamPlayer* player = command->player;
        int loopFlag;
        unsigned long destOffset;
        unsigned int restSize;
        unsigned long blockNo;
        unsigned long blockSize;
        unsigned long blockSamples;
        unsigned long blockOffsetSample;
        unsigned long blockOffset;
        unsigned long offset;
        unsigned long samples;
        unsigned int size;
        unsigned long readSize;
        int ch;

        if (player->finishFlag && player->finishCounter > 0)
            player->finishCounter--;

        destOffset = 0;
        restSize = command->bufLen;

        while (restSize > 0)
        {
            if (player->finishFlag)
            {
                for (ch = 0; ch < command->numChannels; ch++)
                    VectorizedMemset((unsigned char*)command->buffer[ch] + destOffset, 0, restSize);
                break;
            }

            blockNo = player->curSample / player->info.blockSamples;
            if (blockNo < player->info.numBlocks - 1)
            {
                blockSize = player->info.blockSize;
                blockSamples = player->info.blockSamples;
            }
            else
            {
                blockSize = player->info.lastBlockSize;
                blockSamples = player->info.lastBlockSamples;
            }

            blockOffsetSample = player->curSample;
            blockOffsetSample -= blockNo * player->info.blockSamples;

            samples = restSize;
            if (player->info.format != StreamFileFormat_PCM8)
                samples >>= 1;

            if (player->dirtyFlag)
            {
                if (blockOffsetSample == 0)
                {
                    player->dirtyFlag = 0;
                }
                else
                {
                    samples = blockOffsetSample;
                    blockOffsetSample = 0;
                }
            }

            loopFlag = 0;
            if (blockOffsetSample + samples >= blockSamples)
            {
                samples = blockSamples - blockOffsetSample;
                if (blockNo >= player->info.numBlocks - 1)
                {
                    if (player->info.loopFlag)
                        loopFlag = 1;
                    else
                        player->finishFlag = 1;
                }
            }

            blockOffset = blockOffsetSample;
            size = samples;

            switch (player->info.format)
            {
                case StreamFileFormat_PCM8:
                    readSize = size;
                    break;
                case StreamFileFormat_PCM16:
                    blockOffset <<= 1;
                    size <<= 1;
                    readSize = size;
                    break;
                case StreamFileFormat_ADPCM:
                {
                    unsigned long endSample = blockOffsetSample + samples;
                    blockOffset >>= 1;
                    endSample++;
                    endSample >>= 1;
                    readSize = endSample - blockOffset;
                    if (blockOffsetSample == 0)
                        readSize += sizeof(AdpcmState);
                    else
                        blockOffset += sizeof(AdpcmState);
                    size <<= 1;
                    break;
                }
            }

            offset = blockOffset;
            offset += blockNo * player->info.blockSize * player->info.numChannels;
            offset += player->info.dataOffset;

            for (ch = 0; ch < command->numChannels; ch++)
            {
                void* dest;
                void* readDest;

                dest = readDest = (unsigned char*)command->buffer[ch] + destOffset;

                if (ch < player->info.numChannels)
                {
                    long resultSize;

                    if (player->info.format == StreamFileFormat_ADPCM)
                    {
                        LockMutex(&decodeBufferMutex);
                        readDest = decodeBuffer;
                    }

                    resultSize = player->readStreamFunc(player, readDest, readSize, offset + ch * blockSize);
                    if (resultSize != readSize)
                    {
                        size = 0;
                        samples = 0;
                        loopFlag = 0;
                        player->finishFlag = 1;
                        if (player->info.format == StreamFileFormat_ADPCM)
                            UnlockMutex(&decodeBufferMutex);
                        break;
                    }

                    if (player->info.format == StreamFileFormat_ADPCM)
                    {
                        AdpcmState* state = &player->adpcmState[ch];
                        unsigned char* src = decodeBuffer;
                        short* destSamples = (short*)dest;
                        unsigned long i;
                        unsigned long end;

                        if (blockOffsetSample == 0)
                        {
                            // In C, NitroSystem's language, a structure is copied as a block
                            AdpcmStateCopy* header = (AdpcmStateCopy*)src;
                            src += sizeof(AdpcmState);
                            *(AdpcmStateCopy*)state = *header;
                        }

                        end = blockOffsetSample + samples;
                        i = blockOffsetSample;

                        if (i & 1)
                        {
                            *destSamples++ = DecodeAdpcm((*src >> 4) & 0xf, state);
                            i++;
                            src++;
                        }

                        while (i < (end & ~1))
                        {
                            *destSamples++ = DecodeAdpcm(*src & 0xf, state);
                            i++;
                            *destSamples++ = DecodeAdpcm((*src >> 4) & 0xf, state);
                            i++;
                            src++;
                        }

                        if (i < end)
                        {
                            *destSamples++ = DecodeAdpcm(*src & 0xf, state);
                            i++;
                        }

                        UnlockMutex(&decodeBufferMutex);
                    }
                }
                else
                {
                    if (player->monoFlag)
                        VectorizedMemset(dest, 0, size);
                    else
                        VectorizedInvertedMemcpy((unsigned char*)command->buffer[0] + destOffset, dest, size);
                }
            }

            if (player->dirtyFlag)
            {
                player->dirtyFlag = 0;
                continue;
            }

            if (loopFlag)
                player->curSample = player->info.loopStart;
            else
                player->curSample += samples;

            destOffset += size;
            restSize -= size;

            if (player->finishFlag && player->sndArcStrmCallback)
                func_020bf658(player);
        }

        if (player->strmCallback != NULL)
        {
            player->strmCallback(command->status, command->numChannels, command->buffer, command->bufLen,
                player->info.format == StreamFileFormat_PCM8 ? StreamFormat_PCM8 : StreamFormat_PCM16,
                player->strmCallbackArg);
        }

        for (ch = 0; ch < command->numChannels; ch++)
            CleanInvalidateCacheRange(command->buffer[ch], command->bufLen);

        if (command->status == StreamCallbackStatus_Setup)
            player->prepareFlag = 1;
    }

    // usa: func_020bffc4
    // SetupStreamFunction: reads the stream from memory if it's loaded, otherwise from the file
    void func_020bffc4(StreamPlayer* player, unsigned long fileId)
    {
        if (func_020bd8ac(fileId) == NULL)
        {
            player->openStreamFunc = func_020c0044;
            player->closeStreamFunc = func_020c00b8;
            player->readStreamFunc = func_020c00c8;
            player->cancelStreamFunc = func_020c0100;
        }
        else
        {
            player->openStreamFunc = func_020c0110;
            player->closeStreamFunc = func_020c0138;
            player->readStreamFunc = func_020c013c;
            player->cancelStreamFunc = func_020c0158;
        }
    }

    // usa: func_020c0044
    // OpenFileStream
    int func_020c0044(StreamPlayer* player, unsigned long fileId)
    {
        if (func_020bd7c4(fileId, &player->info, sizeof(player->info), 0) != sizeof(player->info))
            return 0;

        if (!NitroVM_PrepareReadFileByID(&player->file, func_020bd88c()))
            return 0;

        player->fileOffset = func_020bd774(fileId);
        return 1;
    }

    // usa: func_020c00b8
    // CloseFileStream
    void func_020c00b8(StreamPlayer* player)
    {
        NitroVM_FinishRead(&player->file);
    }

    // usa: func_020c00c8
    // ReadFileStream
    long func_020c00c8(StreamPlayer* player, void* dest, unsigned long size, unsigned long offset)
    {
        int result;

        result = NitroVM_Seek(&player->file, (long)(player->fileOffset + offset), SEEK_SET);
        return NitroVM_ReadSync(&player->file, dest, (long)size);
    }

    // usa: func_020c0100
    // CancelFileStream
    void func_020c0100(StreamPlayer* player)
    {
        NitroVM_CancelCommand(&player->file);
    }

    // usa: func_020c0110
    // OpenMemoryStream
    int func_020c0110(StreamPlayer* player, unsigned long fileId)
    {
        player->fileOffset = (unsigned long)func_020bd8ac(fileId);
        VectorizedInvertedMemcpy((const void*)player->fileOffset, &player->info, sizeof(player->info));
        return 1;
    }

    // usa: func_020c0138
    // CloseMemoryStream
    void func_020c0138(StreamPlayer* player)
    {
    }

    // usa: func_020c013c
    // ReadMemoryStream
    long func_020c013c(StreamPlayer* player, void* dest, unsigned long size, unsigned long offset)
    {
        const unsigned char* src = (const unsigned char*)player->fileOffset;
        VectorizedInvertedMemcpy(src + offset, dest, size);
        return (long)size;
    }

    // usa: func_020c0158
    // CancelMemoryStream
    void func_020c0158(StreamPlayer* player)
    {
    }

    // usa: func_020c015c
    // StrmThread: fills the blocks that the players ask for
    void func_020c015c(void* arg)
    {
        StreamThread* thread = (StreamThread*)arg;

        while (1)
        {
            LoadCommand* command;

            BlockCurrentContext(&thread->threadQ);

            while (1)
            {
                LockMutex(&thread->mutex);

                command = func_020bf3c8(&thread->commandList);
                if (command == NULL)
                {
                    UnlockMutex(&thread->mutex);
                    break;
                }

                func_020bf79c(command);
                func_020bf458(command);
                UnlockMutex(&thread->mutex);
            }
        }
    }
}
