#include "Sound/Sound.h"
#include "System/Cache.h"
#include "System/Interrupts.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's sndarc_loader.c: loads the sequences, banks and wave archives of the sound archive to a sound heap.
// The wave archives marked for single load only load the waves that their banks use. NNS_SndArcLoadSeqArc,
// NNS_SndArcLoadBank, NNS_SndArcLoadWaveArc and NNS_SndArcLoadBankEx aren't in the ROM.

// Room after each file
#define RESERVED_AREA_SIZE 32

// NitroSystem's NNSSndArcSndType
enum ArchiveSoundType
{
    ArchiveSoundType_Sequence,
    ArchiveSoundType_Bank,
    ArchiveSoundType_WaveArchive,
    ArchiveSoundType_SequenceArchive,
};

// NitroSystem's NNS_SND_ARC_LOAD_*: what to load
#define LOAD_SEQUENCE (1 << 0)
#define LOAD_BANK (1 << 1)
#define LOAD_WAVE (1 << 2)
#define LOAD_SEQUENCE_ARCHIVE (1 << 3)
#define LOAD_ALL 0xff

// NitroSystem's NNSSndArcLoadResult
enum LoadResult
{
    LoadResult_Success,
    LoadResult_InvalidGroupNo,
    LoadResult_InvalidSequenceNo,
    LoadResult_InvalidSequenceArchiveNo,
    LoadResult_InvalidBankNo,
    LoadResult_InvalidWaveArchiveNo,
    LoadResult_FailedLoadSequence,
    LoadResult_FailedLoadSequenceArchive,
    LoadResult_FailedLoadBank,
    LoadResult_FailedLoadWave,
};

// The header of the wave archive that LoadWaveArcTable reads. In NitroSystem, it's a static variable of the function.
static SoundWaveArchive waveArcHeader;

extern "C"
{
    // usa: func_020d2084
    // The NitroSDK's SND_InvalidateSeqData
    void func_020d2084(const void* start, const void* end);
    // usa: func_020d20a4
    // The NitroSDK's SND_InvalidateBankData
    void func_020d20a4(const void* start, const void* end);
    // usa: func_020d20c4
    // The NitroSDK's SND_InvalidateWaveData
    void func_020d20c4(const void* start, const void* end);
    // usa: func_020d2b34
    // The NitroSDK's SND_AssignWaveArc
    void func_020d2b34(SoundBank* bank, int index, SoundWaveArchive* waveArc);
    // usa: func_020d2c00
    // The NitroSDK's SND_DestroyBank
    void func_020d2c00(SoundBank* bank);
    // usa: func_020d2c98
    // The NitroSDK's SND_DestroyWaveArc
    void func_020d2c98(SoundWaveArchive* waveArc);
    // usa: func_020d2ce0
    // The NitroSDK's SND_GetFirstInstDataPos
    InstrumentPosition func_020d2ce0(const SoundBank* bank);
    // usa: func_020d2d00
    // The NitroSDK's SND_GetNextInstData
    int func_020d2d00(const SoundBank* bank, InstrumentData* inst, InstrumentPosition* pos);
    // usa: func_020d2eb0
    // The NitroSDK's SND_GetWaveDataCount
    unsigned long func_020d2eb0(const SoundWaveArchive* waveArc);
    // usa: func_020d2eb8
    // The NitroSDK's SND_SetWaveDataAddress
    void func_020d2eb8(SoundWaveArchive* waveArc, int index, const void* address);
    // usa: func_020d2eec
    // The NitroSDK's SND_GetWaveDataAddress
    const void* func_020d2eec(const SoundWaveArchive* waveArc, int index);

    int func_020bdce8(int groupNo, SoundHeap* heap);
    int func_020bde70(int seqArcNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SequenceArchive** data);
    int func_020be010(int waveArcNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundWaveArchive** data);
    SoundSequence* func_020be13c(unsigned long fileId, SoundHeap* heap, int setAddress);
    SequenceArchive* func_020be1a8(unsigned long fileId, SoundHeap* heap, int setAddress);
    SoundBank* func_020be214(unsigned long fileId, SoundHeap* heap, int setAddress);
    SoundWaveArchive* func_020be280(unsigned long fileId, SoundHeap* heap, int setAddress);
    SoundWaveArchive* func_020be2ec(unsigned long fileId, SoundHeap* heap, int setAddress);
    void func_020be3f4(void* memory, SoundArchive* arc, unsigned long fileId);
    void func_020be44c(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020be474(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020be4a4(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020be4d4(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020be4f4(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    int func_020be53c(SoundWaveArchive* waveArc, int waveNo, unsigned long fileId, SoundHeap* heap);
    int func_020be604(SoundWaveArchive* waveArc, const SoundBank* bank, int waveArcNo, unsigned long fileId,
        SoundHeap* heap);

    // usa: func_020bdc80
    // NNS_SndArcLoadGroup
    int func_020bdc80(int groupNo, SoundHeap* heap)
    {
        int result;

        result = func_020bdce8(groupNo, heap);
        return result == LoadResult_Success ? 1 : 0;
    }

    // usa: func_020bdc98
    // NNS_SndArcLoadSeq
    int func_020bdc98(int seqNo, SoundHeap* heap)
    {
        int result;

        result = func_020bddec(seqNo, LOAD_ALL, heap, 1, NULL);
        return result == LoadResult_Success ? 1 : 0;
    }

    // usa: func_020bdcc4
    // NNS_SndArcLoadSeqEx
    int func_020bdcc4(int seqNo, unsigned long loadFlag, SoundHeap* heap)
    {
        int result;

        result = func_020bddec(seqNo, loadFlag, heap, 1, NULL);
        return result == LoadResult_Success ? 1 : 0;
    }

    // usa: func_020bdce8
    // NNSi_SndArcLoadGroup
    int func_020bdce8(int groupNo, SoundHeap* heap)
    {
        const ArchiveGroupInfo* info;
        const ArchiveGroupItem* item;
        int result;
        int itemNo;

        info = func_020bd710(groupNo);
        if (info == NULL)
            return LoadResult_InvalidGroupNo;

        for (itemNo = 0; itemNo < info->count; itemNo++)
        {
            item = &info->item[itemNo];
            switch (item->type)
            {
                case ArchiveSoundType_Sequence:
                    result = func_020bddec((int)item->index, item->loadFlag, heap, 1, NULL);
                    if (result != LoadResult_Success)
                        return result;
                    break;
                case ArchiveSoundType_SequenceArchive:
                    result = func_020bde70((int)item->index, item->loadFlag, heap, 1, NULL);
                    if (result != LoadResult_Success)
                        return result;
                    break;
                case ArchiveSoundType_Bank:
                    result = func_020bded0((int)item->index, item->loadFlag, heap, 1, NULL);
                    if (result != LoadResult_Success)
                        return result;
                    break;
                case ArchiveSoundType_WaveArchive:
                    result = func_020be010((int)item->index, item->loadFlag, heap, 1, NULL);
                    if (result != LoadResult_Success)
                        return result;
                    break;
                default:
                    break;
            }
        }
        return LoadResult_Success;
    }

    // usa: func_020bddec
    // NNSi_SndArcLoadSeq: loads a sequence and its bank
    int func_020bddec(int seqNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundSequence** data)
    {
        const ArchiveSequenceInfo* seqInfo;
        SoundSequence* seqData = NULL;
        SoundBank* bank = NULL;
        int result;

        seqInfo = func_020bd454(seqNo);
        if (seqInfo == NULL)
            return LoadResult_InvalidSequenceNo;

        result = func_020bded0(seqInfo->param.bankNo, loadFlag, heap, setAddress, NULL);
        if (result != LoadResult_Success)
            return result;

        if (loadFlag & LOAD_SEQUENCE)
        {
            seqData = func_020be13c(seqInfo->fileId, heap, setAddress);
            if (seqData == NULL)
                return LoadResult_FailedLoadSequence;
        }
        else
        {
            seqData = (SoundSequence*)func_020bd8ac(seqInfo->fileId);
        }

        if (data != NULL)
            *data = seqData;
        return LoadResult_Success;
    }

    // usa: func_020bde70
    // NNSi_SndArcLoadSeqArc
    int func_020bde70(int seqArcNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SequenceArchive** data)
    {
        const ArchiveSequenceArchiveInfo* seqArcInfo;
        SequenceArchive* seqArc = NULL;

        seqArcInfo = func_020bd4b8(seqArcNo);
        if (seqArcInfo == NULL)
            return LoadResult_InvalidSequenceArchiveNo;

        if (loadFlag & LOAD_SEQUENCE_ARCHIVE)
        {
            seqArc = func_020be1a8(seqArcInfo->fileId, heap, setAddress);
            if (seqArc == NULL)
                return LoadResult_FailedLoadSequenceArchive;
        }
        else
        {
            seqArc = (SequenceArchive*)func_020bd8ac(seqArcInfo->fileId);
        }

        if (data != NULL)
            *data = seqArc;
        return LoadResult_Success;
    }

    // usa: func_020bded0
    // NNSi_SndArcLoadBank: loads a bank and its wave archives
    int func_020bded0(int bankNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundBank** data)
    {
        const ArchiveBankInfo* bankInfo;
        const ArchiveWaveArchiveInfo* waveArcInfo;
        SoundBank* bank = NULL;
        SoundWaveArchive* waveArc;
        int result;
        int i;

        bankInfo = func_020bd51c(bankNo);
        if (bankInfo == NULL)
            return LoadResult_InvalidBankNo;

        if (loadFlag & LOAD_BANK)
        {
            bank = func_020be214(bankInfo->fileId, heap, setAddress);
            if (bank == NULL)
                return LoadResult_FailedLoadBank;
        }
        else
        {
            bank = (SoundBank*)func_020bd8ac(bankInfo->fileId);
        }

        for (i = 0; i < BANK_WAVE_ARCHIVE_COUNT; i++)
        {
            if (bankInfo->waveArcNo[i] == INVALID_WAVE_ARCHIVE)
                continue;

            waveArcInfo = func_020bd580(bankInfo->waveArcNo[i]);
            if (waveArcInfo == NULL)
                return LoadResult_InvalidWaveArchiveNo;

            result = func_020be010(bankInfo->waveArcNo[i], loadFlag, heap, setAddress, &waveArc);
            if (result != LoadResult_Success)
                return result;

            if (waveArcInfo->flags & WAVE_ARCHIVE_SINGLE_LOAD)
            {
                if (loadFlag & LOAD_WAVE)
                {
                    if (!func_020be604(waveArc, bank, i, waveArcInfo->fileId, heap))
                        return LoadResult_FailedLoadWave;
                }
            }

            if (bank != NULL && waveArc != NULL)
                func_020d2b34(bank, i, waveArc);
        }

        if (data != NULL)
            *data = bank;
        return LoadResult_Success;
    }

    // usa: func_020be010
    // NNSi_SndArcLoadWaveArc
    int func_020be010(int waveArcNo, unsigned long loadFlag, SoundHeap* heap, int setAddress, SoundWaveArchive** data)
    {
        const ArchiveWaveArchiveInfo* waveArcInfo;
        SoundWaveArchive* waveArc = NULL;

        waveArcInfo = func_020bd580(waveArcNo);
        if (waveArcInfo == NULL)
            return LoadResult_InvalidWaveArchiveNo;

        if (loadFlag & LOAD_WAVE)
        {
            if (waveArcInfo->flags & WAVE_ARCHIVE_SINGLE_LOAD)
                waveArc = func_020be2ec(waveArcInfo->fileId, heap, setAddress);
            else
                waveArc = func_020be280(waveArcInfo->fileId, heap, setAddress);

            if (waveArc == NULL)
                return LoadResult_FailedLoadWave;
        }
        else
        {
            waveArc = (SoundWaveArchive*)func_020bd8ac(waveArcInfo->fileId);
        }

        if (data != NULL)
            *data = waveArc;
        return LoadResult_Success;
    }

    // usa: func_020be09c
    // NNSi_SndArcLoadFile: loads a file of the sound archive to the heap
    void* func_020be09c(unsigned long fileId, SoundHeapDisposeCallback callback, unsigned long data1,
        unsigned long data2, SoundHeap* heap)
    {
        void* buffer;
        unsigned long length;

        length = func_020bd79c(fileId);
        if (length == 0)
            return NULL;

        if (heap == NULL)
            return NULL;

        buffer = func_020bda58(heap, length + RESERVED_AREA_SIZE, callback, data1, data2);
        if (buffer == NULL)
            return NULL;

        if (func_020bd7c4(fileId, buffer, (long)length, 0) != length)
            return NULL;

        CleanCacheRange(buffer, length);
        return buffer;
    }

    // usa: func_020be13c
    // LoadSeq
    SoundSequence* func_020be13c(unsigned long fileId, SoundHeap* heap, int setAddress)
    {
        void* buffer;

        buffer = func_020bd8ac(fileId);
        if (buffer == NULL)
        {
            buffer = func_020be09c(fileId, func_020be44c, setAddress ? (unsigned long)func_020bd444() : 0, fileId,
                heap);
            if (setAddress && buffer != NULL)
                func_020bd8d4(fileId, buffer);
        }
        return (SoundSequence*)buffer;
    }

    // usa: func_020be1a8
    // LoadSeqArc
    SequenceArchive* func_020be1a8(unsigned long fileId, SoundHeap* heap, int setAddress)
    {
        void* buffer;

        buffer = func_020bd8ac(fileId);
        if (buffer == NULL)
        {
            buffer = func_020be09c(fileId, func_020be44c, setAddress ? (unsigned long)func_020bd444() : 0, fileId,
                heap);
            if (setAddress && buffer != NULL)
                func_020bd8d4(fileId, buffer);
        }
        return (SequenceArchive*)buffer;
    }

    // usa: func_020be214
    // LoadBank
    SoundBank* func_020be214(unsigned long fileId, SoundHeap* heap, int setAddress)
    {
        void* buffer;

        buffer = func_020bd8ac(fileId);
        if (buffer == NULL)
        {
            buffer = func_020be09c(fileId, func_020be474, setAddress ? (unsigned long)func_020bd444() : 0, fileId,
                heap);
            if (setAddress && buffer != NULL)
                func_020bd8d4(fileId, buffer);
        }
        return (SoundBank*)buffer;
    }

    // usa: func_020be280
    // LoadWaveArc
    SoundWaveArchive* func_020be280(unsigned long fileId, SoundHeap* heap, int setAddress)
    {
        void* buffer;

        buffer = func_020bd8ac(fileId);
        if (buffer == NULL)
        {
            buffer = func_020be09c(fileId, func_020be4a4, setAddress ? (unsigned long)func_020bd444() : 0, fileId,
                heap);
            if (setAddress && buffer != NULL)
                func_020bd8d4(fileId, buffer);
        }
        return (SoundWaveArchive*)buffer;
    }

    // usa: func_020be2ec
    // LoadWaveArcTable: loads a wave archive's header and the offsets of its waves, which are moved after room for
    // the waves' addresses
    SoundWaveArchive* func_020be2ec(unsigned long fileId, SoundHeap* heap, int setAddress)
    {
        SoundWaveArchive* waveArc;
        unsigned long length;
        unsigned long tableSize;
        long readSize;

        waveArc = (SoundWaveArchive*)func_020bd8ac(fileId);
        if (waveArc == NULL)
        {
            readSize = func_020bd7c4(fileId, &waveArcHeader, sizeof(waveArcHeader), 0);
            if (readSize != sizeof(waveArcHeader))
                return NULL;

            tableSize = sizeof(unsigned long) * waveArcHeader.waveCount;
            length = sizeof(waveArcHeader) + tableSize * 2;

            if (heap == NULL)
                return NULL;

            waveArc = (SoundWaveArchive*)func_020bda58(heap, length + RESERVED_AREA_SIZE, func_020be4d4,
                setAddress ? (unsigned long)func_020bd444() : 0, fileId);
            if (waveArc == NULL)
                return NULL;

            readSize = func_020bd7c4(fileId, waveArc, (long)(sizeof(waveArcHeader) + tableSize), 0);
            if (readSize != sizeof(waveArcHeader) + tableSize)
                return NULL;

            VectorizedInvertedMemcpy(waveArc->waveOffset, &waveArc->waveOffset[waveArc->waveCount], tableSize);
            VectorizedMemset(waveArc->waveOffset, 0, tableSize);
            CleanCacheRange(waveArc, length);

            if (setAddress)
                func_020bd8d4(fileId, waveArc);
        }
        return waveArc;
    }

    // usa: func_020be3f4
    // DisposeCallback: forgets the file's address in its sound archive
    void func_020be3f4(void* memory, SoundArchive* arc, unsigned long fileId)
    {
        SoundArchive* oldArc;
        int oldState;

        if (arc == NULL)
            return;

        oldState = DisableIRQInterrupts();
        oldArc = func_020bd42c(arc);

        if (memory == func_020bd8ac(fileId))
            func_020bd8d4(fileId, NULL);

        func_020bd42c(oldArc);
        SetIRQInterruptState(oldState);
    }

    // usa: func_020be44c
    // SeqDisposeCallback
    void func_020be44c(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundArchive* arc = (SoundArchive*)data1;
        unsigned long fileId = data2;

        func_020be3f4(memory, arc, fileId);
        func_020d2084(memory, (unsigned char*)memory + size);
    }

    // usa: func_020be474
    // BankDisposeCallback
    void func_020be474(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundBank* bank = (SoundBank*)memory;
        SoundArchive* arc = (SoundArchive*)data1;
        unsigned long fileId = data2;

        func_020be3f4(memory, arc, fileId);
        func_020d20a4(memory, (unsigned char*)memory + size);
        func_020d2c00(bank);
    }

    // usa: func_020be4a4
    // WaveArcDisposeCallback
    void func_020be4a4(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundWaveArchive* waveArc = (SoundWaveArchive*)memory;
        SoundArchive* arc = (SoundArchive*)data1;
        unsigned long fileId = data2;

        func_020be3f4(memory, arc, fileId);
        func_020d20c4(memory, (unsigned char*)memory + size);
        func_020d2c98(waveArc);
    }

    // usa: func_020be4d4
    // WaveArcTableDisposeCallback
    void func_020be4d4(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundWaveArchive* waveArc = (SoundWaveArchive*)memory;
        SoundArchive* arc = (SoundArchive*)data1;
        unsigned long fileId = data2;

        func_020be3f4(memory, arc, fileId);
        func_020d2c98(waveArc);
    }

    // usa: func_020be4f4
    // SingleWaveDisposeCallback
    void func_020be4f4(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundWaveArchive* waveArc = (SoundWaveArchive*)data1;
        unsigned long waveNo = data2;

        if (memory == func_020d2eec(waveArc, (int)waveNo))
            func_020d2eb8(waveArc, (int)waveNo, NULL);

        func_020d20c4(memory, (unsigned char*)memory + size);
    }

    // usa: func_020be53c
    // LoadSingleWave
    int func_020be53c(SoundWaveArchive* waveArc, int waveNo, unsigned long fileId, SoundHeap* heap)
    {
        void* buffer;
        unsigned long length;
        unsigned long begin;
        unsigned long end;
        unsigned long waveCount;

        if (func_020d2eec(waveArc, waveNo) != NULL)
            return 1;

        waveCount = func_020d2eb0(waveArc);
        begin = waveArc->waveOffset[waveArc->waveCount + waveNo];
        if (waveNo < waveCount - 1)
            end = waveArc->waveOffset[waveArc->waveCount + waveNo + 1];
        else
            end = waveArc->fileHeader.fileSize;
        length = end - begin;

        if (heap == NULL)
            return 0;

        buffer = func_020bda58(heap, length + RESERVED_AREA_SIZE, func_020be4f4, (unsigned long)waveArc,
            (unsigned long)waveNo);
        if (buffer == NULL)
            return 0;

        if (func_020bd7c4(fileId, buffer, (long)length, (long)begin) != length)
            return 0;

        CleanCacheRange(buffer, length);
        func_020d2eb8(waveArc, waveNo, buffer);
        return 1;
    }

    // usa: func_020be604
    // LoadSingleWaves: loads the waves of a wave archive that a bank uses
    int func_020be604(SoundWaveArchive* waveArc, const SoundBank* bank, int waveArcNo, unsigned long fileId,
        SoundHeap* heap)
    {
        InstrumentPosition pos = func_020d2ce0(bank);
        InstrumentData inst;

        if (bank == NULL)
            return 0;

        while (func_020d2d00(bank, &inst, &pos))
        {
            if (inst.type == INSTRUMENT_PCM && waveArcNo == inst.param.wave[1])
            {
                if (!func_020be53c(waveArc, inst.param.wave[0], fileId, heap))
                    return 0;
            }
        }
        return 1;
    }
}
