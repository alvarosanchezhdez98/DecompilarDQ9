#include "MultiBoot/MultiBoot.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>

// The NitroSDK's mb_cache.c: the cache of the file that MB_ReadSegment reads

#pragma optimize_for_size off
#pragma optimization_level 4

extern "C"
{
    void MBi_InitCache(MBiCacheList* pl)
    {
        VectorizedMemset(pl, 0, sizeof(*pl));
    }

    void MBi_AttachCacheBuffer(MBiCacheList* pl, unsigned long src, unsigned long len, void* ptr, unsigned long state)
    {
        int lastState = DisableIRQInterrupts();
        for (MBiCacheInfo* info = pl->list;; ++info)
        {
            if (info >= &pl->list[MB_CACHE_INFO_MAX])
                func_020c9be0();
            if (info->state == 0)
            {
                info->src = src;
                info->len = len;
                info->ptr = (unsigned char*)ptr;
                info->state = state;
                break;
            }
        }
        SetIRQInterruptState(lastState);
    }

    int MBi_ReadFromCache(MBiCacheList* pl, unsigned long src, void* dst, unsigned long len)
    {
        int ret = false;
        int lastState = DisableIRQInterrupts();
        {
            MBiCacheInfo* info = pl->list;
        for (; info < &pl->list[MB_CACHE_INFO_MAX]; ++info)
        {
            if (info->state >= 2)
            {
                const int offset = (int)(src - info->src);
                if (offset >= 0 && offset + len <= info->len)
                {
                    VectorizedInvertedMemcpy(info->ptr + offset, dst, len);
                    pl->lifetime = 0;
                    ret = true;
                    break;
                }
            }
        }
        }
        SetIRQInterruptState(lastState);
        return ret;
    }
}
