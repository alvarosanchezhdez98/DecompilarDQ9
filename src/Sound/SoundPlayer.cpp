#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's player.c: plays sequences with the sound driver's players, by priority, with the limits of each of
// the sound archive's players. The functions that aren't in the ROM are NNS_SndPlayerStopSeqByPlayerNo, ...BySeqNo,
// ...BySeqArcNo and ...BySeqArcIdx, NNS_SndPlayerPauseByPlayerNo and ...All,
// NNS_SndPlayerCountPlayingSeqByPlayerNo and ...BySeqArcNo, NNS_SndPlayerSetPlayerPriority, the track functions
// other than NNS_SndPlayerSetTrackPitch, NNS_SndPlayerSetTempoRatio, the getters, the variable functions and the
// functions that read the driver's information.

// The fader's volume is shifted by 8 bits
#define FADER_SHIFT 8
// The NitroSDK's SND_VOLUME_DB_MIN
#define VOLUME_DB_MIN -723

// NitroSystem's NNSSndPlayerHeap: a heap of a player, for the data of one of its sequences
struct PlayerHeap
{
    ListLink link;
    SoundHeap* handle;
    SequencePlayer* player;
    int playerNo;
};

// NitroSystem's NNS_SndHandleIsValid: whether the handle is playing a sequence
static inline bool IsHandleValid(const SoundHandle* handle)
{
    return handle->player != NULL;
}

// The compiler places these in the order freeList, prioList, seqPlayers and players
static SequencePlayer seqPlayers[DRIVER_PLAYER_COUNT];
static SignedAllocatorList prioList; // SequencePlayer, by priority
static SignedAllocatorList freeList; // SequencePlayer
static SoundPlayer players[PLAYER_COUNT];

extern "C"
{
    void func_020bc610(SequencePlayer* seqPlayer);
    void func_020bc658(SoundPlayer* player, SequencePlayer* seqPlayer);
    void func_020bc6a8(SequencePlayer* seqPlayer);
    void func_020bc6fc(SequencePlayer* seqPlayer);
    SequencePlayer* func_020bc734(int prio);
    void func_020bc79c(SequencePlayer* seqPlayer);
    void func_020bc820(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020bc870(SequencePlayer* seqPlayer, int prio);

    // usa: func_020bbf34
    // NNS_SndPlayerSetPlayerVolume
    void func_020bbf34(int playerNo, int volume)
    {
        players[playerNo].volume = (unsigned char)volume;
    }

    // usa: func_020bbf4c
    // NNS_SndPlayerSetPlayableSeqCount
    void func_020bbf4c(int playerNo, int seqCount)
    {
        players[playerNo].playableSeqCount = (unsigned short)seqCount;
    }

    // usa: func_020bbf6c
    // NNS_SndPlayerSetAllocatableChannel
    void func_020bbf6c(int playerNo, unsigned long channelMask)
    {
        players[playerNo].allocChBitFlag = channelMask;
    }

    // usa: func_020bbf84
    // NNS_SndPlayerCreateHeap
    int func_020bbf84(int playerNo, SoundHeap* heap, unsigned long size)
    {
        SoundHeap* playerHeapHandle;
        PlayerHeap* playerHeap;
        void* buffer;

        buffer = func_020bda58(heap, sizeof(PlayerHeap) + size, func_020bc820, 0, 0);
        if (buffer == NULL)
            return 0;

        playerHeap = (PlayerHeap*)buffer;
        playerHeap->player = NULL;
        playerHeap->playerNo = playerNo;
        playerHeap->handle = NULL;

        playerHeapHandle = func_020bd914((unsigned char*)buffer + sizeof(PlayerHeap), size);
        if (playerHeapHandle == NULL)
            return 0;

        playerHeap->handle = playerHeapHandle;
        AppendListObject(&players[playerNo].heapList, playerHeap);
        return 1;
    }

    // usa: func_020bc018
    // NNS_SndPlayerStopSeq
    void func_020bc018(SoundHandle* handle, int fadeFrame)
    {
        func_020bc548(handle->player, fadeFrame);
    }

    // usa: func_020bc028
    // NNS_SndPlayerStopSeqAll
    void func_020bc028(int fadeFrame)
    {
        SequencePlayer* seqPlayer;
        int i;

        for (i = 0; i < DRIVER_PLAYER_COUNT; i++)
        {
            seqPlayer = &seqPlayers[i];
            if (seqPlayer->status != SequencePlayerStatus_Stop)
                func_020bc548(seqPlayer, fadeFrame);
        }
    }

    // usa: func_020bc068
    // NNS_SndPlayerPause
    void func_020bc068(SoundHandle* handle, int flag)
    {
        func_020bc594(handle->player, flag);
    }

    // usa: func_020bc078
    // NNS_SndHandleInit
    void func_020bc078(SoundHandle* handle)
    {
        handle->player = NULL;
    }

    // usa: func_020bc084
    // NNS_SndHandleReleaseSeq
    void func_020bc084(SoundHandle* handle)
    {
        if (!IsHandleValid(handle))
            return;

        handle->player->handle = NULL;
        handle->player = NULL;
    }

    // usa: func_020bc0a4
    // NNS_SndPlayerCountPlayingSeqBySeqNo
    int func_020bc0a4(int seqNo)
    {
        int count = 0;
        SequencePlayer* seqPlayer = NULL;

        while ((seqPlayer = (SequencePlayer*)GetNextListObject(&prioList, seqPlayer)) != NULL)
        {
            if (seqPlayer->seqType == SequenceType_Sequence && seqPlayer->seqNo == seqNo)
                count++;
        }
        return count;
    }

    // usa: func_020bc0f8
    // NNS_SndPlayerCountPlayingSeqBySeqArcIdx
    int func_020bc0f8(int seqArcNo, int index)
    {
        int count = 0;
        SequencePlayer* seqPlayer = NULL;

        while ((seqPlayer = (SequencePlayer*)GetNextListObject(&prioList, seqPlayer)) != NULL)
        {
            if (seqPlayer->seqType == SequenceType_SequenceArchive && seqPlayer->seqNo == seqArcNo
                && seqPlayer->seqArcIndex == index)
                count++;
        }
        return count;
    }

    // usa: func_020bc158
    // NNS_SndPlayerSetVolume
    void func_020bc158(SoundHandle* handle, int volume)
    {
        if (!IsHandleValid(handle))
            return;

        handle->player->extVolume = (unsigned char)volume;
    }

    // usa: func_020bc16c
    // NNS_SndPlayerSetInitialVolume
    void func_020bc16c(SoundHandle* handle, int volume)
    {
        if (!IsHandleValid(handle))
            return;

        handle->player->initVolume = (unsigned char)volume;
    }

    // usa: func_020bc180
    // NNS_SndPlayerMoveVolume
    void func_020bc180(SoundHandle* handle, int targetVolume, int frames)
    {
        if (!IsHandleValid(handle))
            return;
        if (handle->player->status == SequencePlayerStatus_FadeOut)
            return;

        func_020c0204(&handle->player->fader, targetVolume << FADER_SHIFT, frames);
    }

    // usa: func_020bc1ac
    // NNS_SndPlayerSetChannelPriority
    void func_020bc1ac(SoundHandle* handle, int prio)
    {
        if (!IsHandleValid(handle))
            return;

        func_020d1e88(handle->player->playerNo, prio);
    }

    // usa: func_020bc1cc
    // NNS_SndPlayerSetTrackPitch
    void func_020bc1cc(SoundHandle* handle, unsigned short trackBitMask, int pitch)
    {
        if (!IsHandleValid(handle))
            return;

        func_020d1ea0(handle->player->playerNo, trackBitMask, pitch);
    }

    // usa: func_020bc1ec
    // NNS_SndPlayerSetSeqNo
    void func_020bc1ec(SoundHandle* handle, int seqNo)
    {
        if (!IsHandleValid(handle))
            return;

        handle->player->seqType = SequenceType_Sequence;
        handle->player->seqNo = (unsigned short)seqNo;
    }

    // usa: func_020bc210
    // NNS_SndPlayerSetSeqArcNo
    void func_020bc210(SoundHandle* handle, int seqArcNo, int index)
    {
        if (!IsHandleValid(handle))
            return;

        handle->player->seqType = SequenceType_SequenceArchive;
        handle->player->seqNo = (unsigned short)seqArcNo;
        handle->player->seqArcIndex = (unsigned short)index;
    }

    // usa: func_020bc23c
    // NNSi_SndPlayerInit
    void func_020bc23c()
    {
        SoundPlayer* player;
        int playerNo;

        InitList(&prioList, LIST_LINK_OFFSET(SequencePlayer, prioLink));
        InitList(&freeList, LIST_LINK_OFFSET(SequencePlayer, prioLink));

        for (playerNo = 0; playerNo < DRIVER_PLAYER_COUNT; playerNo++)
        {
            seqPlayers[playerNo].status = SequencePlayerStatus_Stop;
            seqPlayers[playerNo].playerNo = (unsigned char)playerNo;
            AppendListObject(&freeList, &seqPlayers[playerNo]);
        }

        for (playerNo = 0; playerNo < PLAYER_COUNT; playerNo++)
        {
            player = &players[playerNo];
            InitList(&player->playerList, LIST_LINK_OFFSET(SequencePlayer, playerLink));
            InitList(&player->heapList, LIST_LINK_OFFSET(PlayerHeap, link));
            player->volume = 127;
            player->playableSeqCount = 1;
            player->allocChBitFlag = 0;
        }
    }

    // usa: func_020bc2f0
    // NNSi_SndPlayerMain
    void func_020bc2f0()
    {
        SequencePlayer* seqPlayer;
        SequencePlayer* next;
        unsigned long status;
        int fader;

        status = func_020d29f4();

        for (seqPlayer = (SequencePlayer*)GetNextListObject(&prioList, NULL); seqPlayer != NULL; seqPlayer = next)
        {
            next = (SequencePlayer*)GetNextListObject(&prioList, seqPlayer);

            if (!seqPlayer->startFlag)
            {
                if (func_020d2718(seqPlayer->commandTag))
                    seqPlayer->startFlag = 1;
            }

            if (seqPlayer->startFlag)
            {
                if ((status & (1 << seqPlayer->playerNo)) == 0)
                {
                    func_020bc79c(seqPlayer);
                    continue;
                }
            }

            func_020c0260(&seqPlayer->fader);

            fader = CalculateDecibel(seqPlayer->initVolume) + CalculateDecibel(seqPlayer->extVolume)
                + CalculateDecibel(seqPlayer->player->volume)
                + CalculateDecibel(func_020c022c(&seqPlayer->fader) >> FADER_SHIFT);

            if (fader < -32768)
                fader = -32768;
            else if (fader > 32767)
                fader = 32767;

            if (fader != seqPlayer->volume)
            {
                func_020d1e70(seqPlayer->playerNo, fader);
                seqPlayer->volume = (short)fader;
            }

            if (seqPlayer->status == SequencePlayerStatus_FadeOut)
            {
                if (func_020c0278(&seqPlayer->fader))
                    func_020bc6fc(seqPlayer);
            }

            if (seqPlayer->prepareFlag)
            {
                func_020d1e30(seqPlayer->playerNo);
                seqPlayer->prepareFlag = 0;
            }
        }
    }

    // usa: func_020bc454
    // NNSi_SndPlayerAllocSeqPlayer
    SequencePlayer* func_020bc454(SoundHandle* handle, int playerNo, int prio)
    {
        SequencePlayer* seqPlayer;
        SoundPlayer* player;

        player = &players[playerNo];

        if (IsHandleValid(handle))
            func_020bc084(handle);

        if (player->playerList.numElements >= player->playableSeqCount)
        {
            seqPlayer = (SequencePlayer*)GetNextListObject(&player->playerList, NULL);
            if (seqPlayer == NULL)
                return NULL;
            if (prio < seqPlayer->prio)
                return NULL;
            func_020bc6fc(seqPlayer);
        }

        seqPlayer = func_020bc734(prio);
        if (seqPlayer == NULL)
            return NULL;

        func_020bc658(player, seqPlayer);
        seqPlayer->handle = handle;
        handle->player = seqPlayer;
        return seqPlayer;
    }

    // usa: func_020bc4ec
    // NNSi_SndPlayerFreeSeqPlayer
    void func_020bc4ec(SequencePlayer* seqPlayer)
    {
        func_020bc79c(seqPlayer);
    }

    // usa: func_020bc4f8
    // NNSi_SndPlayerStartSeq
    void func_020bc4f8(SequencePlayer* seqPlayer, const void* seqBase, unsigned long seqOffset, const SoundBank* bank)
    {
        SoundPlayer* player;

        player = seqPlayer->player;

        func_020d1e08(seqPlayer->playerNo, seqBase, seqOffset, bank);

        if (player->allocChBitFlag)
            func_020d1ebc(seqPlayer->playerNo, 0xffff, player->allocChBitFlag);

        func_020bc610(seqPlayer);
        seqPlayer->commandTag = func_020d26ec();
        seqPlayer->prepareFlag = 1;
        seqPlayer->status = SequencePlayerStatus_Play;
    }

    // usa: func_020bc548
    // NNSi_SndPlayerStopSeq
    void func_020bc548(SequencePlayer* seqPlayer, int fadeFrame)
    {
        if (seqPlayer == NULL)
            return;
        if (seqPlayer->status == SequencePlayerStatus_Stop)
            return;

        if (fadeFrame == 0)
        {
            func_020bc6fc(seqPlayer);
            return;
        }

        func_020c0204(&seqPlayer->fader, 0, fadeFrame);
        func_020bc870(seqPlayer, 0);
        seqPlayer->status = SequencePlayerStatus_FadeOut;
    }

    // usa: func_020bc594
    // NNSi_SndPlayerPause
    void func_020bc594(SequencePlayer* seqPlayer, int flag)
    {
        if (seqPlayer == NULL)
            return;

        if (flag != seqPlayer->pauseFlag)
        {
            func_020d1e50(seqPlayer->playerNo, flag);
            seqPlayer->pauseFlag = (unsigned char)flag;
        }
    }

    // usa: func_020bc5bc
    // NNSi_SndPlayerAllocHeap
    SoundHeap* func_020bc5bc(int playerNo, SequencePlayer* seqPlayer)
    {
        SoundPlayer* player;
        PlayerHeap* heap;

        player = &players[playerNo];

        heap = (PlayerHeap*)GetNextListObject(&player->heapList, NULL);
        if (heap == NULL)
            return NULL;

        RemoveListObject(&player->heapList, heap);
        heap->player = seqPlayer;
        seqPlayer->heap = heap;

        func_020bd99c(heap->handle);
        return heap->handle;
    }

    // usa: func_020bc610
    // InitPlayer
    void func_020bc610(SequencePlayer* seqPlayer)
    {
        seqPlayer->pauseFlag = 0;
        seqPlayer->startFlag = 0;
        seqPlayer->prepareFlag = 0;
        seqPlayer->seqType = SequenceType_Invalid;
        seqPlayer->volume = 0;
        seqPlayer->initVolume = 127;
        seqPlayer->extVolume = 127;

        func_020c01ec(&seqPlayer->fader);
        func_020c0204(&seqPlayer->fader, 127 << FADER_SHIFT, 1);
    }

    // usa: func_020bc658
    // InsertPlayerList: inserts a sequence player in its player's list, by priority
    void func_020bc658(SoundPlayer* player, SequencePlayer* seqPlayer)
    {
        SequencePlayer* next = NULL;

        while ((next = (SequencePlayer*)GetNextListObject(&player->playerList, next)) != NULL)
        {
            if (seqPlayer->prio < next->prio)
                break;
        }

        InsertListObject(&player->playerList, next, seqPlayer);
        seqPlayer->player = player;
    }

    // usa: func_020bc6a8
    // InsertPrioList
    void func_020bc6a8(SequencePlayer* seqPlayer)
    {
        SequencePlayer* next = NULL;

        while ((next = (SequencePlayer*)GetNextListObject(&prioList, next)) != NULL)
        {
            if (seqPlayer->prio < next->prio)
                break;
        }

        InsertListObject(&prioList, next, seqPlayer);
    }

    // usa: func_020bc6fc
    // ForceStopSeq
    void func_020bc6fc(SequencePlayer* seqPlayer)
    {
        if (seqPlayer->status == SequencePlayerStatus_FadeOut)
            func_020d1e70(seqPlayer->playerNo, VOLUME_DB_MIN);

        func_020d1de8(seqPlayer->playerNo);
        func_020bc79c(seqPlayer);
    }

    // usa: func_020bc734
    // AllocSeqPlayer: a free sequence player, or the one with the lowest priority if prio is at least its priority
    SequencePlayer* func_020bc734(int prio)
    {
        SequencePlayer* seqPlayer;

        seqPlayer = (SequencePlayer*)GetNextListObject(&freeList, NULL);
        if (seqPlayer == NULL)
        {
            seqPlayer = (SequencePlayer*)GetNextListObject(&prioList, NULL);
            if (prio < seqPlayer->prio)
                return NULL;
            func_020bc6fc(seqPlayer);
        }

        RemoveListObject(&freeList, seqPlayer);
        seqPlayer->prio = (unsigned char)prio;
        func_020bc6a8(seqPlayer);
        return seqPlayer;
    }

    // usa: func_020bc79c
    // ShutdownPlayer
    void func_020bc79c(SequencePlayer* seqPlayer)
    {
        SoundPlayer* player;

        if (seqPlayer->handle != NULL)
        {
            seqPlayer->handle->player = NULL;
            seqPlayer->handle = NULL;
        }

        player = seqPlayer->player;
        RemoveListObject(&player->playerList, seqPlayer);
        seqPlayer->player = NULL;

        if (seqPlayer->heap != NULL)
        {
            AppendListObject(&player->heapList, seqPlayer->heap);
            seqPlayer->heap->player = NULL;
            seqPlayer->heap = NULL;
        }

        RemoveListObject(&prioList, seqPlayer);
        AppendListObject(&freeList, seqPlayer);
        seqPlayer->status = SequencePlayerStatus_Stop;
    }

    // usa: func_020bc820
    // PlayerHeapDisposeCallback
    void func_020bc820(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        PlayerHeap* heap = (PlayerHeap*)memory;
        SequencePlayer* seqPlayer;

        if (heap->handle == NULL)
            return;

        func_020bd984(heap->handle);

        seqPlayer = heap->player;
        if (seqPlayer != NULL)
            seqPlayer->heap = NULL;
        else
            RemoveListObject(&players[heap->playerNo].heapList, heap);
    }

    // usa: func_020bc870
    // SetPlayerPriority
    void func_020bc870(SequencePlayer* seqPlayer, int prio)
    {
        SoundPlayer* player;

        player = seqPlayer->player;
        if (player != NULL)
        {
            RemoveListObject(&player->playerList, seqPlayer);
            seqPlayer->player = NULL;
        }

        RemoveListObject(&prioList, seqPlayer);
        seqPlayer->prio = (unsigned char)prio;

        if (player != NULL)
            func_020bc658(player, seqPlayer);
        func_020bc6a8(seqPlayer);
    }
}
