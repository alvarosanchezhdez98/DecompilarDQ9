#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's sndarc_player.c: plays the sequences of the sound archive, loading their banks to the player's heap.
// NNS_SndArcPlayerStartSeqEx and NNS_SndArcPlayerStartSeqArcEx aren't in the ROM.

// NitroSystem's NNS_SND_ARC_LOAD_SEQ, NNS_SND_ARC_LOAD_BANK and NNS_SND_ARC_LOAD_WAVE
#define LOAD_SEQUENCE (1 << 0)
#define LOAD_BANK (1 << 1)
#define LOAD_WAVE (1 << 2)

// NitroSystem's NNS_SND_ARC_LOAD_SUCESS
#define LOAD_SUCCESS 0

extern "C"
{
    int func_020be828(SoundHandle* handle, int playerNo, int bankNo, int playerPrio, const ArchiveSequenceInfo* info,
        int seqNo);
    int func_020be924(SoundHandle* handle, int playerNo, int bankNo, int playerPrio, const SequenceArchiveEntry* sound,
        const SequenceArchive* seqArc, int seqArcNo, int index);

    // usa: func_020be6c4
    // NNS_SndArcPlayerSetup: sets up the players of the sound archive, with their heaps
    int func_020be6c4(SoundHeap* heap)
    {
        SoundArchive* arc = func_020bd444();
        int playerNo;
        const ArchivePlayerInfo* playerInfo;

        for (playerNo = 0; playerNo < PLAYER_COUNT; ++playerNo)
        {
            playerInfo = func_020bd648(playerNo);
            if (playerInfo == NULL)
                continue;

            func_020bbf4c(playerNo, playerInfo->seqMax);
            func_020bbf6c(playerNo, playerInfo->allocChBitFlag);

            if (playerInfo->heapSize > 0 && heap != NULL)
            {
                int i;
                for (i = 0; i < playerInfo->seqMax; i++)
                {
                    if (!func_020bbf84(playerNo, heap, playerInfo->heapSize))
                        return 0;
                }
            }
        }
        return 1;
    }

    // usa: func_020be760
    // NNS_SndArcPlayerStartSeq
    int func_020be760(SoundHandle* handle, int seqNo)
    {
        const ArchiveSequenceInfo* info;

        info = func_020bd454(seqNo);
        if (info == NULL)
            return 0;

        return func_020be828(handle, info->param.playerNo, info->param.bankNo, info->param.playerPrio, info, seqNo);
    }

    // usa: func_020be7a8
    // NNS_SndArcPlayerStartSeqArc
    int func_020be7a8(SoundHandle* handle, int seqArcNo, int index)
    {
        const ArchiveSequenceArchiveInfo* info;
        const SequenceArchiveEntry* sound;
        const SequenceArchive* seqArc;

        info = func_020bd4b8(seqArcNo);
        if (info == NULL)
            return 0;

        seqArc = (SequenceArchive*)func_020bd8ac(info->fileId);
        if (seqArc == NULL)
            return 0;

        sound = func_020c01ac(seqArc, index);
        if (sound == NULL)
            return 0;

        return func_020be924(handle, sound->param.playerNo, sound->param.bankNo, sound->param.playerPrio, sound,
            seqArc, seqArcNo, index);
    }

    // usa: func_020be828
    // StartSeq
    int func_020be828(SoundHandle* handle, int playerNo, int bankNo, int playerPrio, const ArchiveSequenceInfo* info,
        int seqNo)
    {
        SequencePlayer* player;
        SoundHeap* heap;
        SoundSequence* seq;
        SoundBank* bank;
        int result;

        player = func_020bc454(handle, playerNo, playerPrio);
        if (player == NULL)
            return 0;

        heap = func_020bc5bc(playerNo, player);

        result = func_020bded0(bankNo, LOAD_BANK | LOAD_WAVE, heap, 0, &bank);
        if (result != LOAD_SUCCESS)
        {
            func_020bc4ec(player);
            return 0;
        }

        result = func_020bddec(seqNo, LOAD_SEQUENCE, heap, 0, &seq);
        if (result != LOAD_SUCCESS)
        {
            func_020bc4ec(player);
            return 0;
        }

        func_020bc4f8(player, (unsigned char*)seq + seq->baseOffset, 0, bank);

        func_020bc16c(handle, info->param.volume);
        func_020bc1ac(handle, info->param.channelPrio);
        func_020bc1ec(handle, seqNo);
        return 1;
    }

    // usa: func_020be924
    // StartSeqArc
    int func_020be924(SoundHandle* handle, int playerNo, int bankNo, int playerPrio, const SequenceArchiveEntry* sound,
        const SequenceArchive* seqArc, int seqArcNo, int index)
    {
        SequencePlayer* player;
        SoundHeap* heap;
        SoundBank* bank;
        int result;

        player = func_020bc454(handle, playerNo, playerPrio);
        if (player == NULL)
            return 0;

        heap = func_020bc5bc(playerNo, player);

        result = func_020bded0(bankNo, LOAD_BANK | LOAD_WAVE, heap, 0, &bank);
        if (result != LOAD_SUCCESS)
        {
            func_020bc4ec(player);
            return 0;
        }

        func_020bc4f8(player, (unsigned char*)seqArc + seqArc->baseOffset, sound->offset, bank);

        func_020bc16c(handle, sound->param.volume);
        func_020bc1ac(handle, sound->param.channelPrio);
        func_020bc210(handle, seqArcNo, index);
        return 1;
    }
}
