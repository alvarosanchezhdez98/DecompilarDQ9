#include "Sound/SoundDriver.h"
#include "System/Cache.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_work.c: reads the state that the ARM7's driver shares

SoundSharedWork* data_021142c0;

extern "C"
{
    unsigned long func_020d29f4()
    {
        InvalidateDataCacheRange((const void*)&data_021142c0->playerStatus, sizeof(data_021142c0->playerStatus));
        return data_021142c0->playerStatus;
    }

    unsigned long func_020d2a20()
    {
        InvalidateDataCacheRange((const void*)&data_021142c0->finishCommandTag,
                                 sizeof(data_021142c0->finishCommandTag));
        return data_021142c0->finishCommandTag;
    }

    void func_020d2a48(SoundSharedWork* work)
    {
        int i;
        int j;
        work->playerStatus = 0;
        work->channelStatus = 0;
        work->captureStatus = 0;
        work->finishCommandTag = 0;
        for (i = 0; i < 16; i++)
        {
            work->player[i].tickCounter = 0;
            for (j = 0; j < 16; j++)
                work->player[i].localVariable[j] = -1;
        }
        for (j = 0; j < 16; j++)
            work->globalVariable[j] = -1;
        CleanInvalidateCacheRange(work, sizeof(SoundSharedWork));
    }
}
