#pragma once
#include <globaldefs.h>
#include "Memory/HMRFAllocator.h"
#include "Memory/SignedAllocator.h"
#include "Filesystem/NitroVM.h"
#include "System/PowerManagement.h"

// NitroSystem's sound library (NNS_Snd*), which plays the sound archive (.sdat) with the NitroSDK's sound driver (SND)

// The NitroSDK's SND_COMMAND_NOBLOCK and SND_COMMAND_BLOCK
#define COMMAND_NO_BLOCK 0
#define COMMAND_BLOCK 1

// The NitroSDK's SND_PLAYER_NUM: the sound driver's players
#define DRIVER_PLAYER_COUNT 16
// NitroSystem's NNS_SND_PLAYER_NUM: NitroSystem's players, each playing a number of sequences
#define PLAYER_COUNT 32

// NitroSystem's NNSFndLink: the link of an object in a list. SignedAllocatorList is NitroSystem's NNSFndList, which
// finds the links at an offset in its objects.
struct ListLink
{
    void* prevObject;
    void* nextObject;
};

// The offset of a list's links in its objects (NitroSystem's NNS_FND_INIT_LIST)
#define LIST_LINK_OFFSET(type, link) ((unsigned short)(unsigned long)&((type*)0)->link)

// NitroSystem's NNS_FndInitList, NNS_FndAppendListObject, NNS_FndInsertListObject, NNS_FndRemoveListObject and
// NNS_FndGetNextListObject and NNS_FndGetPrevListObject, for any object
static inline void InitList(SignedAllocatorList* list, unsigned short linkOffset)
{
    list->Initialize(linkOffset);
}

static inline void AppendListObject(SignedAllocatorList* list, void* object)
{
    list->InsertAtEnd((SignedAllocatorHeader*)object);
}

// Inserts object before target, or at the end if target is NULL
static inline void InsertListObject(SignedAllocatorList* list, void* target, void* object)
{
    list->InsertBefore((SignedAllocatorHeader*)target, (SignedAllocatorHeader*)object);
}

static inline void RemoveListObject(SignedAllocatorList* list, void* object)
{
    list->Remove((SignedAllocatorHeader*)object);
}

// The first object if object is NULL
static inline void* GetNextListObject(SignedAllocatorList* list, void* object)
{
    return list->ElementAfter((SignedAllocatorHeader*)object);
}

// The last object if object is NULL
static inline void* GetPrevListObject(SignedAllocatorList* list, void* object)
{
    return list->ElementBefore((SignedAllocatorHeader*)object);
}

// NitroSystem's NNSSndFader: moves a value from origin to target in a number of frames
struct SoundFader
{
    int origin;
    int target;
    int counter;
    int frame;
};

// NitroSystem's NNSSndHeap
struct SoundHeap;

// NitroSystem's NNS_SND_STRM_CHANNEL_MAX
#define STREAM_CHANNEL_MAX 16

// NitroSystem's NNSSndStrmFormat, the same as the NitroSDK's SNDWaveFormat for PCM
enum StreamFormat
{
    StreamFormat_PCM8,
    StreamFormat_PCM16,
};

// NitroSystem's NNSSndStrmCallbackStatus
enum StreamCallbackStatus
{
    StreamCallbackStatus_Setup,
    StreamCallbackStatus_Interval,
};

typedef void (*StreamCallback)(StreamCallbackStatus status, int numChannels, void* buffer[], unsigned long length,
    StreamFormat format, void* arg);

// NitroSystem's NNSSndStrm: plays a stream of sound with the sound driver's channels, filling a buffer for each
// channel as it plays
struct SoundStream
{
    ListLink link;
    SleepCallbackInfo preSleepInfo;
    SleepCallbackInfo postSleepInfo;
    StreamFormat format;
    int activeFlag : 1;
    int startFlag : 1;
    unsigned long chBufLen;
    int interval; // the number of parts of the buffers, each filled by a call of callback
    StreamCallback callback;
    void* callbackArg;
    int curBuffer;
    int volume;
    int alarmNo;
    unsigned long chBitMask;
    int numChannels;
    unsigned char channelNo[STREAM_CHANNEL_MAX];
};

typedef void (*SoundHeapDisposeCallback)(void* memory, unsigned long size, unsigned long data1, unsigned long data2);

struct SequencePlayer;
struct SoundPlayer;
struct PlayerHeap;

// NitroSystem's NNSSndHandle: what the game plays a sequence with
struct SoundHandle
{
    SequencePlayer* player;
};

// NitroSystem's NNSSndSeqPlayerStatus
enum SequencePlayerStatus
{
    SequencePlayerStatus_Stop,
    SequencePlayerStatus_Play,
    SequencePlayerStatus_FadeOut,
};

// NitroSystem's NNSSndPlayerSeqType
enum SequenceType
{
    SequenceType_Invalid,
    SequenceType_Sequence,
    SequenceType_SequenceArchive,
};

// NitroSystem's NNSSndSeqPlayer: plays a sequence with one of the sound driver's players
struct SequencePlayer
{
    SoundHandle* handle;
    SoundPlayer* player;
    PlayerHeap* heap;
    ListLink playerLink;
    ListLink prioLink;
    SoundFader fader;
    unsigned char status; // SequencePlayerStatus
    unsigned char startFlag;
    unsigned char pauseFlag;
    unsigned char prepareFlag;
    unsigned long commandTag;
    unsigned short seqType; // SequenceType
    unsigned short pad2;
    unsigned short seqNo;
    unsigned short seqArcIndex;
    unsigned char playerNo;
    unsigned char prio;
    short volume;
    unsigned char initVolume;
    unsigned char extVolume;
    unsigned short pad3;
};

// NitroSystem's NNSSndPlayer: one of the players that the sound archive defines, which plays up to playableSeqCount
// sequences
struct SoundPlayer
{
    SignedAllocatorList playerList; // SequencePlayer
    SignedAllocatorList heapList; // PlayerHeap
    unsigned long playableSeqCount;
    unsigned long allocChBitFlag;
    unsigned char volume;
    unsigned char pad;
    unsigned short pad2;
};

// The NitroSDK's SNDBinaryFileHeader and SNDBinaryBlockHeader: the headers of the sound files
struct SoundFileHeader
{
    char signature[4];
    unsigned short byteOrder;
    unsigned short version;
    unsigned long fileSize;
    unsigned short headerSize;
    unsigned short dataBlocks;
};

struct SoundBlockHeader
{
    unsigned long kind;
    unsigned long size;
};

struct SoundWaveArchive;

// The NitroSDK's SNDWaveArcLink: links the banks that use a wave archive
struct SoundWaveArchiveLink
{
    SoundWaveArchive* waveArc;
    SoundWaveArchiveLink* next;
};

// The NitroSDK's SND_BANK_TO_WAVEARC_MAX
#define BANK_WAVE_ARCHIVE_COUNT 4

// The NitroSDK's SNDBankData: an instrument bank (.sbnk). instOffset has the type of each instrument in its low byte,
// and the offset of its data in the others.
struct SoundBank
{
    SoundFileHeader fileHeader;
    SoundBlockHeader blockHeader;
    SoundWaveArchiveLink waveArcLink[BANK_WAVE_ARCHIVE_COUNT];
    unsigned long instCount;
    unsigned long instOffset[];
};

// The NitroSDK's SND_INST_PCM: an instrument that plays a wave
#define INSTRUMENT_PCM 1

// The NitroSDK's SNDInstParam and SNDInstData: an instrument of a bank. wave is the wave number and the bank's wave
// archive.
struct InstrumentParameters
{
    unsigned short wave[2];
    unsigned char originalKey;
    unsigned char attack;
    unsigned char decay;
    unsigned char sustain;
    unsigned char release;
    unsigned char pan;
};

struct InstrumentData
{
    unsigned char type;
    unsigned char padding;
    InstrumentParameters param;
};

// The NitroSDK's SNDInstPos: where SND_GetNextInstData continues
struct InstrumentPosition
{
    unsigned long prgNo;
    unsigned long index;
};

// NitroSystem's NNSSndSeqData: a sequence (.sseq)
struct SoundSequence
{
    SoundFileHeader fileHeader;
    SoundBlockHeader blockHeader;
    unsigned long baseOffset;
    unsigned long data[];
};

// The NitroSDK's SNDWaveArc: a wave archive (.swar). waveOffset has the offsets of the waves in the file, and after
// being loaded, their addresses.
struct SoundWaveArchive
{
    SoundFileHeader fileHeader;
    SoundBlockHeader blockHeader;
    SoundWaveArchiveLink* topLink;
    unsigned long reserved[7];
    unsigned long waveCount;
    unsigned long waveOffset[];
};

// NitroSystem's NNSSndSeqParam: how to play a sequence
struct SequenceParameters
{
    unsigned short bankNo;
    unsigned char volume;
    unsigned char channelPrio;
    unsigned char playerPrio;
    unsigned char playerNo;
    unsigned short reserved;
};

// NitroSystem's NNSSndSeqArcSeqInfo: a sequence of a sequence archive, at offset from its base (INVALID_OFFSET if
// there isn't one)
struct SequenceArchiveEntry
{
    unsigned long offset;
    SequenceParameters param;
};

#define SEQUENCE_ARCHIVE_INVALID_OFFSET 0xffffffff

// NitroSystem's NNSSndSeqArc: a sequence archive (.ssar)
struct SequenceArchive
{
    SoundFileHeader fileHeader;
    SoundBlockHeader blockHeader;
    unsigned long baseOffset;
    unsigned long count;
    SequenceArchiveEntry info[];
};

// NitroSystem's NNS_SND_ARC_BANK_TO_WAVEARC_NUM: the wave archives of a bank
#define BANK_WAVE_ARCHIVE_COUNT 4
// NitroSystem's NNS_SND_ARC_INVALID_WAVEARC_NO
#define INVALID_WAVE_ARCHIVE 0xffff

// NitroSystem's NNSSndArcSeqInfo: a sequence of the sound archive
struct ArchiveSequenceInfo
{
    unsigned long fileId;
    SequenceParameters param;
};

// NitroSystem's NNSSndArcSeqArcInfo
struct ArchiveSequenceArchiveInfo
{
    unsigned long fileId;
};

// NitroSystem's NNSSndArcBankInfo
struct ArchiveBankInfo
{
    unsigned long fileId;
    unsigned short waveArcNo[BANK_WAVE_ARCHIVE_COUNT];
};

// NitroSystem's NNS_SND_ARC_WAVEARC_SINGLE_LOAD: the wave archive's waves are loaded one by one, when a bank needs them
#define WAVE_ARCHIVE_SINGLE_LOAD 1

// NitroSystem's NNSSndArcWaveArcInfo
struct ArchiveWaveArchiveInfo
{
    unsigned long fileId : 24;
    unsigned long flags : 8;
};

// NitroSystem's NNSSndArcStrmInfo: a stream of the sound archive
struct ArchiveStreamInfo
{
    unsigned long fileId;
    unsigned char volume;
    unsigned char playerPrio;
    unsigned char playerNo;
    unsigned char flags;
};

// NitroSystem's NNSSndArcPlayerInfo: a player of the sound archive
struct ArchivePlayerInfo
{
    unsigned char seqMax;
    unsigned char padding;
    unsigned short allocChBitFlag;
    unsigned long heapSize;
};

// NitroSystem's NNSSndArcStrmPlayerInfo
struct ArchiveStreamPlayerInfo
{
    unsigned char numChannels;
    unsigned char chNoList[2];
};

// NitroSystem's NNSSndArcGroupItem and NNSSndArcGroupInfo: a group of sounds that are loaded together
struct ArchiveGroupItem
{
    unsigned char type;
    unsigned char loadFlag;
    unsigned short padding;
    unsigned long index;
};

struct ArchiveGroupInfo
{
    unsigned long count;
    ArchiveGroupItem item[];
};

// NitroSystem's NNSSndArcOffsetTable: the offsets of the information of each sound, from the info block
struct ArchiveOffsetTable
{
    unsigned long count;
    unsigned long offset[];
};

// NitroSystem's NNSSndArcFileInfo and NNSSndArcFat: the files of the sound archive, and where they're loaded
struct ArchiveFileInfo
{
    unsigned long offset;
    unsigned long size;
    void* mem;
    unsigned long reserved;
};

struct ArchiveFat
{
    SoundBlockHeader blockHeader;
    unsigned long count;
    ArchiveFileInfo files[];
};

// NitroSystem's NNSSndArcInfo: the offsets of the tables of each kind of sound
struct ArchiveInfo
{
    SoundBlockHeader blockHeader;
    unsigned long seqOffset;
    unsigned long seqArcOffset;
    unsigned long bankOffset;
    unsigned long waveArcOffset;
    unsigned long playerInfoOffset;
    unsigned long groupInfoOffset;
    unsigned long strmPlayerInfoOffset;
    unsigned long strmOffset;
};

// NitroSystem's NNSSndArcSymbol
struct ArchiveSymbols;

// NitroSystem's NNSSndArcHeader
struct ArchiveHeader
{
    SoundFileHeader fileHeader;
    unsigned long symbolDataOffset;
    unsigned long symbolDataSize;
    unsigned long infoOffset;
    unsigned long infoSize;
    unsigned long fatOffset;
    unsigned long fatSize;
    unsigned long fileImageOffset;
    unsigned long fileImageSize;
};

// NitroSystem's NNSSndArc: the sound archive (.sdat), read from a file or in memory
struct SoundArchive
{
    ArchiveHeader header;
    int fileOpen;
    NitroVM file;
    NitroFileAccessor fileId;
    ArchiveFat* fat;
    ArchiveSymbols* symbol;
    ArchiveInfo* info;
    long loadBlockSize; // how much NNS_SndArcReadFile reads at a time, everything if 0
};

extern "C"
{
    // The NitroSDK's SNDi_DecibelTable, which SND_CalcDecibel reads: the volume in decibels (x10) of each linear
    // volume from 0 to 127
    extern const short data_020ed82c[];

    // The NitroSDK's sound driver (SND)

    // usa: func_020d1de8
    // SND_StopSeq
    void func_020d1de8(int playerNo);
    // usa: func_020d1e08
    // SND_PrepareSeq
    void func_020d1e08(int playerNo, const void* seqBase, unsigned long seqOffset, const SoundBank* bank);
    // usa: func_020d1e30
    // SND_StartPreparedSeq
    void func_020d1e30(int playerNo);
    // usa: func_020d1e50
    // SND_PauseSeq
    void func_020d1e50(int playerNo, int flag);
    // usa: func_020d1e70
    // SND_SetPlayerVolume
    void func_020d1e70(int playerNo, int volume);
    // usa: func_020d1e88
    // SND_SetPlayerChannelPriority
    void func_020d1e88(int playerNo, int prio);
    // usa: func_020d1ea0
    // SND_SetTrackPitch
    void func_020d1ea0(int playerNo, unsigned long trackBitMask, int pitch);
    // usa: func_020d1ebc
    // SND_SetTrackAllocatableChannel
    void func_020d1ebc(int playerNo, unsigned long trackBitMask, unsigned long channelMask);
    // usa: func_020d1ee4
    // SND_StartTimer
    void func_020d1ee4(unsigned long channelMask, unsigned long captureMask, unsigned long alarmMask,
        unsigned long flags);
    // usa: func_020d1f0c
    // SND_StopTimer
    void func_020d1f0c(unsigned long channelMask, unsigned long captureMask, unsigned long alarmMask,
        unsigned long flags);
    // usa: func_020d1f70
    // SND_SetupAlarm
    void func_020d1f70(int alarmNo, unsigned long tick, unsigned long period, void (*handler)(void* arg), void* arg);
    // usa: func_020d1ff0
    // SND_SetChannelVolume
    void func_020d1ff0(unsigned long channelMask, int volume, int shift);
    // usa: func_020d2018
    // SND_SetChannelPan
    void func_020d2018(unsigned long channelMask, int pan);
    // usa: func_020d2038
    // SND_SetupChannelPcm
    void func_020d2038(int channelNo, int format, const void* data, int loop, int loopStart, int loopLength,
        int volume, int shift, int timer, int pan);
    // usa: func_020d21c0
    // SND_Init
    void func_020d21c0();
    // usa: func_020d22f4
    // SND_RecvCommandReply
    void* func_020d22f4(unsigned long flags);
    // usa: func_020d24c4
    // SND_FlushCommand
    int func_020d24c4(unsigned long flags);
    // usa: func_020d2680
    // SND_WaitForCommandProc
    void func_020d2680(unsigned long tag);
    // usa: func_020d26ec
    // SND_GetCurrentCommandTag
    unsigned long func_020d26ec();
    // usa: func_020d2718
    // SND_IsFinishedCommandTag
    int func_020d2718(unsigned long tag);
    // usa: func_020d29f4
    // SND_GetPlayerStatus: a bit for each of the driver's players that's playing
    unsigned long func_020d29f4();
    // usa: func_020d2ac4
    // SND_CalcChannelVolume: the volume in the low byte and the shift in the high byte
    unsigned short func_020d2ac4(int decibels);

    // NitroSystem's sound library

    // usa: func_020bbe1c
    // NNS_SndLockChannel
    int func_020bbe1c(unsigned long channelMask);
    // usa: func_020bbe64
    // NNS_SndUnlockChannel
    void func_020bbe64(unsigned long channelMask);
    // usa: func_020bbe94
    // NNS_SndUnlockCapture
    void func_020bbe94(unsigned long captureMask);
    // usa: func_020bbeb0
    // NNS_SndAllocAlarm
    int func_020bbeb0();
    // usa: func_020bbef8
    // NNS_SndFreeAlarm
    void func_020bbef8(int alarmNo);
    // usa: func_020bbf18
    // NNSi_SndInitResourceMgr
    void func_020bbf18();

    // usa: func_020bbf4c
    // NNS_SndPlayerSetPlayableSeqCount
    void func_020bbf4c(int playerNo, int seqCount);
    // usa: func_020bbf6c
    // NNS_SndPlayerSetAllocatableChannel
    void func_020bbf6c(int playerNo, unsigned long channelMask);
    // usa: func_020bbf84
    // NNS_SndPlayerCreateHeap
    int func_020bbf84(int playerNo, SoundHeap* heap, unsigned long size);
    // usa: func_020bc084
    // NNS_SndHandleReleaseSeq
    void func_020bc084(SoundHandle* handle);
    // usa: func_020bc16c
    // NNS_SndPlayerSetInitialVolume
    void func_020bc16c(SoundHandle* handle, int volume);
    // usa: func_020bc1ac
    // NNS_SndPlayerSetChannelPriority
    void func_020bc1ac(SoundHandle* handle, int prio);
    // usa: func_020bc1ec
    // NNS_SndPlayerSetSeqNo
    void func_020bc1ec(SoundHandle* handle, int seqNo);
    // usa: func_020bc210
    // NNS_SndPlayerSetSeqArcNo
    void func_020bc210(SoundHandle* handle, int seqArcNo, int index);
    // usa: func_020bc23c
    // NNSi_SndPlayerInit
    void func_020bc23c();
    // usa: func_020bc2f0
    // NNSi_SndPlayerMain
    void func_020bc2f0();
    // usa: func_020bc454
    // NNSi_SndPlayerAllocSeqPlayer
    SequencePlayer* func_020bc454(SoundHandle* handle, int playerNo, int prio);
    // usa: func_020bc4ec
    // NNSi_SndPlayerFreeSeqPlayer
    void func_020bc4ec(SequencePlayer* seqPlayer);
    // usa: func_020bc4f8
    // NNSi_SndPlayerStartSeq
    void func_020bc4f8(SequencePlayer* seqPlayer, const void* seqBase, unsigned long seqOffset, const SoundBank* bank);
    // usa: func_020bc548
    // NNSi_SndPlayerStopSeq
    void func_020bc548(SequencePlayer* seqPlayer, int fadeFrame);
    // usa: func_020bc594
    // NNSi_SndPlayerPause
    void func_020bc594(SequencePlayer* seqPlayer, int flag);
    // usa: func_020bc5bc
    // NNSi_SndPlayerAllocHeap
    SoundHeap* func_020bc5bc(int playerNo, SequencePlayer* seqPlayer);

    // usa: func_020bc8d0
    // NNS_SndStrmInit
    void func_020bc8d0(SoundStream* stream);
    // usa: func_020bc948
    // NNS_SndStrmAllocChannel
    int func_020bc948(SoundStream* stream, int numChannels, const unsigned char channelNoList[]);
    // usa: func_020bc9a8
    // NNS_SndStrmFreeChannel
    void func_020bc9a8(SoundStream* stream);
    // usa: func_020bc9d0
    // NNS_SndStrmSetup
    int func_020bc9d0(SoundStream* stream, StreamFormat format, void* buffer, unsigned long bufferSize, int timer,
        int interval, StreamCallback callback, void* arg);
    // usa: func_020bcb70
    // NNS_SndStrmStart
    void func_020bcb70(SoundStream* stream);
    // usa: func_020bcbc4
    // NNS_SndStrmStop
    void func_020bcbc4(SoundStream* stream);
    // usa: func_020bcbe0
    // NNS_SndStrmSetVolume
    void func_020bcbe0(SoundStream* stream, int volume);
    // usa: func_020bcc4c
    // NNS_SndStrmSetChannelPan
    void func_020bcc4c(SoundStream* stream, int channel, int pan);

    // usa: func_020bce9c
    // NNSi_SndCaptureInit
    void func_020bce9c();
    // usa: func_020bceb4
    // NNSi_SndCaptureMain
    void func_020bceb4();
    // usa: func_020bcf3c
    // NNSi_SndCaptureStop
    void func_020bcf3c();
    // usa: func_020bd02c
    // NNSi_SndCaptureBeginSleep
    void func_020bd02c();
    // usa: func_020bd08c
    // NNSi_SndCaptureEndSleep
    void func_020bd08c();

    // usa: func_020bd914
    // NNS_SndHeapCreate
    SoundHeap* func_020bd914(void* start, unsigned long size);
    // usa: func_020bd984
    // NNS_SndHeapDestroy
    void func_020bd984(SoundHeap* heap);
    // usa: func_020bd99c
    // NNS_SndHeapClear
    void func_020bd99c(SoundHeap* heap);
    // usa: func_020bda58
    // NNS_SndHeapAlloc
    void* func_020bda58(SoundHeap* heap, unsigned long size, SoundHeapDisposeCallback callback, unsigned long data1,
        unsigned long data2);

    // usa: func_020bd110
    // NNS_SndArcInit
    void func_020bd110(SoundArchive* arc, const char* filePath, SoundHeap* heap, int symbolLoadFlag);
    // usa: func_020bd190
    // NNS_SndArcSetup
    int func_020bd190(SoundArchive* arc, SoundHeap* heap, int symbolLoadFlag);
    // usa: func_020bd368
    // NNS_SndArcInitOnMemory
    void func_020bd368(SoundArchive* arc, void* data);
    // usa: func_020bd42c
    // NNS_SndArcSetCurrent
    SoundArchive* func_020bd42c(SoundArchive* arc);
    // usa: func_020bd444
    // NNS_SndArcGetCurrent
    SoundArchive* func_020bd444();
    // usa: func_020bd454
    // NNS_SndArcGetSeqInfo
    const ArchiveSequenceInfo* func_020bd454(int seqNo);
    // usa: func_020bd4b8
    // NNS_SndArcGetSeqArcInfo
    const ArchiveSequenceArchiveInfo* func_020bd4b8(int seqArcNo);
    // usa: func_020bd51c
    // NNS_SndArcGetBankInfo
    const ArchiveBankInfo* func_020bd51c(int bankNo);
    // usa: func_020bd580
    // NNS_SndArcGetWaveArcInfo
    const ArchiveWaveArchiveInfo* func_020bd580(int waveArcNo);
    // usa: func_020bd5e4
    // NNS_SndArcGetStrmInfo
    const ArchiveStreamInfo* func_020bd5e4(int strmNo);
    // usa: func_020bd648
    // NNS_SndArcGetPlayerInfo
    const ArchivePlayerInfo* func_020bd648(int playerNo);
    // usa: func_020bd6ac
    // NNS_SndArcGetStrmPlayerInfo
    const ArchiveStreamPlayerInfo* func_020bd6ac(int playerNo);
    // usa: func_020bd710
    // NNS_SndArcGetGroupInfo
    const ArchiveGroupInfo* func_020bd710(int groupNo);
    // usa: func_020bd774
    // NNS_SndArcGetFileOffset
    unsigned long func_020bd774(unsigned long fileId);
    // usa: func_020bd79c
    // NNS_SndArcGetFileSize
    unsigned long func_020bd79c(unsigned long fileId);
    // usa: func_020bd7c4
    // NNS_SndArcReadFile
    long func_020bd7c4(unsigned long fileId, void* buffer, long size, long offset);
    // usa: func_020bd88c
    // NNS_SndArcGetFileID
    NitroFileAccessor func_020bd88c();
    // usa: func_020bd8ac
    // NNS_SndArcGetFileAddress
    void* func_020bd8ac(unsigned long fileId);
    // usa: func_020bd8d4
    // NNS_SndArcSetFileAddress
    void func_020bd8d4(unsigned long fileId, void* address);

    // usa: func_020bddec
    // NNSi_SndArcLoadSeq
    int func_020bddec(int seqNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundSequence** data);
    // usa: func_020bded0
    // NNSi_SndArcLoadBank
    int func_020bded0(int bankNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundBank** data);
    // usa: func_020be09c
    // NNSi_SndArcLoadFile
    void* func_020be09c(unsigned long fileId, SoundHeapDisposeCallback callback, unsigned long data1,
        unsigned long data2, SoundHeap* heap);

    // usa: func_020bed10
    // NNSi_SndArcStrmMain
    void func_020bed10();

    // usa: func_020c01ac
    // NNSi_SndSeqArcGetSeqInfo
    const SequenceArchiveEntry* func_020c01ac(const SequenceArchive* seqArc, int index);

    // usa: func_020c01ec
    // NNSi_SndFaderInit
    void func_020c01ec(SoundFader* fader);
    // usa: func_020c0204
    // NNSi_SndFaderSet
    void func_020c0204(SoundFader* fader, int target, int frame);
    // usa: func_020c022c
    // NNSi_SndFaderGet
    int func_020c022c(const SoundFader* fader);
    // usa: func_020c0260
    // NNSi_SndFaderUpdate
    void func_020c0260(SoundFader* fader);
    // usa: func_020c0278
    // NNSi_SndFaderIsFinished
    int func_020c0278(const SoundFader* fader);
}

// The NitroSDK's SND_CalcDecibel
static inline short CalculateDecibel(int scale)
{
    return data_020ed82c[scale];
}
