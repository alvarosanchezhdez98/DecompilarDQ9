#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's seqdata.c: reads sequence archives. NNSi_SndSeqArcGetSeqCount isn't in the ROM.

extern "C"
{
    // usa: func_020c01ac
    // NNSi_SndSeqArcGetSeqInfo
    const SequenceArchiveEntry* func_020c01ac(const SequenceArchive* seqArc, int index)
    {
        if (index < 0)
            return NULL;
        if (index >= seqArc->count)
            return NULL;
        if (seqArc->info[index].offset == SEQUENCE_ARCHIVE_INVALID_OFFSET)
            return NULL;
        return &seqArc->info[index];
    }
}
