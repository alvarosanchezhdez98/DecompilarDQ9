#include "Sound/Sound.h"
#include "Filesystem/FileAccessor.h"
#include "Filesystem/LowNitroHandle.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's sndarc.c: reads the sound archive's tables. NNS_SndArcInitWithResult, NNS_SndArcGetSeqParam,
// NNS_SndArcGetSeqArcParam, the functions that count the sounds and the functions that read the symbols aren't in
// the ROM.

// The NitroSDK's FS_SEEK_SET
#define SEEK_SET 0

static SoundArchive* currentArchive = NULL;

// NitroSystem's GetPtr and GetPtrConst: offsets of 0 are NULL
static inline void* GetPointer(void* base, unsigned long offset)
{
    if (offset == 0)
        return NULL;
    return (unsigned char*)base + offset;
}

static inline const void* GetConstPointer(const void* base, unsigned long offset)
{
    if (offset == 0)
        return NULL;
    return (const unsigned char*)base + offset;
}

// NitroSystem's GetOffsetTable
static inline const ArchiveOffsetTable* GetOffsetTable(const ArchiveInfo* info, unsigned long offset)
{
    return (const ArchiveOffsetTable*)GetConstPointer(info, offset);
}

extern "C"
{
    // usa: func_020ca408
    // The NitroSDK's MI_CpuCopy32
    void func_020ca408(const void* src, void* dst, unsigned int numBytes);

    void func_020bd8f0(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020bd8fc(void* memory, unsigned long size, unsigned long data1, unsigned long data2);
    void func_020bd908(void* memory, unsigned long size, unsigned long data1, unsigned long data2);

    // usa: func_020bd110
    // NNS_SndArcInit: opens the sound archive's file and reads its tables
    void func_020bd110(SoundArchive* arc, const char* filePath, SoundHeap* heap, int symbolLoadFlag)
    {
        int result;

        arc->info = NULL;
        arc->fat = NULL;
        arc->symbol = NULL;
        arc->loadBlockSize = 0;

        result = CreateFileAccessor(&arc->fileId, filePath);
        if (!result)
            return;

        NitroVM_Initialize(&arc->file);
        result = NitroVM_PrepareReadFileByID(&arc->file, arc->fileId);
        if (!result)
            return;
        arc->fileOpen = 1;

        result = func_020bd190(arc, heap, symbolLoadFlag);
        if (!result)
            return;

        currentArchive = arc;
    }

    // usa: func_020bd190
    // NNS_SndArcSetup: reads the header, and the tables to the heap
    int func_020bd190(SoundArchive* arc, SoundHeap* heap, int symbolLoadFlag)
    {
        int result;
        long readSize;

        result = NitroVM_Seek(&arc->file, 0, SEEK_SET);
        if (!result)
            return 0;

        readSize = NitroVM_ReadSync(&arc->file, &arc->header, sizeof(arc->header));
        if (readSize != sizeof(arc->header))
            return 0;

        if (heap != NULL)
        {
            arc->info = (ArchiveInfo*)func_020bda58(heap, arc->header.infoSize, func_020bd8f0, (unsigned long)arc, 0);
            if (arc->info == NULL)
                return 0;

            result = NitroVM_Seek(&arc->file, (long)arc->header.infoOffset, SEEK_SET);
            if (!result)
                return 0;

            readSize = NitroVM_ReadSync(&arc->file, arc->info, (long)arc->header.infoSize);
            if (readSize != arc->header.infoSize)
                return 0;

            arc->fat = (ArchiveFat*)func_020bda58(heap, arc->header.fatSize, func_020bd8fc, (unsigned long)arc, 0);
            if (arc->fat == NULL)
                return 0;

            result = NitroVM_Seek(&arc->file, (long)arc->header.fatOffset, SEEK_SET);
            if (!result)
                return 0;

            readSize = NitroVM_ReadSync(&arc->file, arc->fat, (long)arc->header.fatSize);
            if (readSize != arc->header.fatSize)
                return 0;

            if (symbolLoadFlag && arc->header.symbolDataSize > 0)
            {
                arc->symbol = (ArchiveSymbols*)func_020bda58(heap, arc->header.symbolDataSize, func_020bd908,
                    (unsigned long)arc, 0);
                if (arc->symbol == NULL)
                    return 0;

                result = NitroVM_Seek(&arc->file, (long)arc->header.symbolDataOffset, SEEK_SET);
                if (!result)
                    return 0;

                readSize = NitroVM_ReadSync(&arc->file, arc->symbol, (long)arc->header.symbolDataSize);
                if (readSize != arc->header.symbolDataSize)
                    return 0;
            }
        }
        return 1;
    }

    // usa: func_020bd368
    // NNS_SndArcInitOnMemory: uses a sound archive that's all in memory
    void func_020bd368(SoundArchive* arc, void* data)
    {
        ArchiveHeader* header = (ArchiveHeader*)data;
        ArchiveFileInfo* file;
        int fileId;

        func_020ca408(header, &arc->header, sizeof(arc->header));

        arc->info = (ArchiveInfo*)GetPointer(header, arc->header.infoOffset);
        arc->fat = (ArchiveFat*)GetPointer(header, arc->header.fatOffset);
        arc->symbol = (ArchiveSymbols*)GetPointer(header, arc->header.symbolDataOffset);
        arc->loadBlockSize = 0;

        for (fileId = 0; fileId < arc->fat->count; fileId++)
        {
            file = &arc->fat->files[fileId];
            file->mem = GetPointer(header, file->offset);
        }

        arc->fileOpen = 0;
        currentArchive = arc;
    }

    // usa: func_020bd42c
    // NNS_SndArcSetCurrent
    SoundArchive* func_020bd42c(SoundArchive* arc)
    {
        SoundArchive* oldArc = currentArchive;
        currentArchive = arc;
        return oldArc;
    }

    // usa: func_020bd444
    // NNS_SndArcGetCurrent
    SoundArchive* func_020bd444()
    {
        return currentArchive;
    }

    // usa: func_020bd454
    // NNS_SndArcGetSeqInfo
    const ArchiveSequenceInfo* func_020bd454(int seqNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->seqOffset);
        if (table == NULL)
            return NULL;
        if (seqNo < 0)
            return NULL;
        if (seqNo >= table->count)
            return NULL;
        return (const ArchiveSequenceInfo*)GetConstPointer(arc->info, table->offset[seqNo]);
    }

    // usa: func_020bd4b8
    // NNS_SndArcGetSeqArcInfo
    const ArchiveSequenceArchiveInfo* func_020bd4b8(int seqArcNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->seqArcOffset);
        if (table == NULL)
            return NULL;
        if (seqArcNo < 0)
            return NULL;
        if (seqArcNo >= table->count)
            return NULL;
        return (const ArchiveSequenceArchiveInfo*)GetConstPointer(arc->info, table->offset[seqArcNo]);
    }

    // usa: func_020bd51c
    // NNS_SndArcGetBankInfo
    const ArchiveBankInfo* func_020bd51c(int bankNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->bankOffset);
        if (table == NULL)
            return NULL;
        if (bankNo < 0)
            return NULL;
        if (bankNo >= table->count)
            return NULL;
        return (const ArchiveBankInfo*)GetConstPointer(arc->info, table->offset[bankNo]);
    }

    // usa: func_020bd580
    // NNS_SndArcGetWaveArcInfo
    const ArchiveWaveArchiveInfo* func_020bd580(int waveArcNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->waveArcOffset);
        if (table == NULL)
            return NULL;
        if (waveArcNo < 0)
            return NULL;
        if (waveArcNo >= table->count)
            return NULL;
        return (const ArchiveWaveArchiveInfo*)GetConstPointer(arc->info, table->offset[waveArcNo]);
    }

    // usa: func_020bd5e4
    // NNS_SndArcGetStrmInfo
    const ArchiveStreamInfo* func_020bd5e4(int strmNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->strmOffset);
        if (table == NULL)
            return NULL;
        if (strmNo < 0)
            return NULL;
        if (strmNo >= table->count)
            return NULL;
        return (const ArchiveStreamInfo*)GetConstPointer(arc->info, table->offset[strmNo]);
    }

    // usa: func_020bd648
    // NNS_SndArcGetPlayerInfo
    const ArchivePlayerInfo* func_020bd648(int playerNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->playerInfoOffset);
        if (table == NULL)
            return NULL;
        if (playerNo < 0)
            return NULL;
        if (playerNo >= table->count)
            return NULL;
        return (const ArchivePlayerInfo*)GetConstPointer(arc->info, table->offset[playerNo]);
    }

    // usa: func_020bd6ac
    // NNS_SndArcGetStrmPlayerInfo
    const ArchiveStreamPlayerInfo* func_020bd6ac(int playerNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->strmPlayerInfoOffset);
        if (table == NULL)
            return NULL;
        if (playerNo < 0)
            return NULL;
        if (playerNo >= table->count)
            return NULL;
        return (const ArchiveStreamPlayerInfo*)GetConstPointer(arc->info, table->offset[playerNo]);
    }

    // usa: func_020bd710
    // NNS_SndArcGetGroupInfo
    const ArchiveGroupInfo* func_020bd710(int groupNo)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveOffsetTable* table;

        table = GetOffsetTable(arc->info, arc->info->groupInfoOffset);
        if (table == NULL)
            return NULL;
        if (groupNo < 0)
            return NULL;
        if (groupNo >= table->count)
            return NULL;
        return (const ArchiveGroupInfo*)GetConstPointer(arc->info, table->offset[groupNo]);
    }

    // usa: func_020bd774
    // NNS_SndArcGetFileOffset
    unsigned long func_020bd774(unsigned long fileId)
    {
        SoundArchive* arc = currentArchive;

        if (fileId >= arc->fat->count)
            return 0;
        return arc->fat->files[fileId].offset;
    }

    // usa: func_020bd79c
    // NNS_SndArcGetFileSize
    unsigned long func_020bd79c(unsigned long fileId)
    {
        SoundArchive* arc = currentArchive;

        if (fileId >= arc->fat->count)
            return 0;
        return arc->fat->files[fileId].size;
    }

    // usa: func_020bd7c4
    // NNS_SndArcReadFile: reads part of a file, loadBlockSize bytes at a time
    long func_020bd7c4(unsigned long fileId, void* buffer, long size, long offset)
    {
        SoundArchive* arc = currentArchive;
        const ArchiveFileInfo* file;
        long result;
        long total;
        long blockSize;
        long readSize;

        if (fileId >= arc->fat->count)
            return -1;

        file = &arc->fat->files[fileId];

        blockSize = arc->loadBlockSize;
        if (blockSize == 0)
            blockSize = size;

        total = 0;
        while (total < size)
        {
            readSize = size - total;
            if (readSize > blockSize)
                readSize = blockSize;
            if (readSize > file->size - offset)
                readSize = (long)(file->size - offset);
            if (readSize == 0)
                break;

            if (!NitroVM_Seek(&arc->file, (long)(file->offset + offset), SEEK_SET))
                return -1;

            result = NitroVM_ReadSync(&arc->file, buffer, readSize);
            if (result < 0)
                return result;

            total += result;
            offset += result;
            buffer = (unsigned char*)buffer + result;
        }
        return total;
    }

    // usa: func_020bd88c
    // NNS_SndArcGetFileID
    NitroFileAccessor func_020bd88c()
    {
        SoundArchive* arc = currentArchive;
        return arc->fileId;
    }

    // usa: func_020bd8ac
    // NNS_SndArcGetFileAddress: where the file is loaded, or NULL
    void* func_020bd8ac(unsigned long fileId)
    {
        SoundArchive* arc = currentArchive;

        if (fileId >= arc->fat->count)
            return NULL;
        return arc->fat->files[fileId].mem;
    }

    // usa: func_020bd8d4
    // NNS_SndArcSetFileAddress
    void func_020bd8d4(unsigned long fileId, void* address)
    {
        SoundArchive* arc = currentArchive;
        arc->fat->files[fileId].mem = address;
    }

    // usa: func_020bd8f0
    // InfoDisposeCallback
    void func_020bd8f0(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundArchive* arc = (SoundArchive*)data1;
        arc->info = NULL;
    }

    // usa: func_020bd8fc
    // FatDisposeCallback
    void func_020bd8fc(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundArchive* arc = (SoundArchive*)data1;
        arc->fat = NULL;
    }

    // usa: func_020bd908
    // SymbolDisposeCallback
    void func_020bd908(void* memory, unsigned long size, unsigned long data1, unsigned long data2)
    {
        SoundArchive* arc = (SoundArchive*)data1;
        arc->symbol = NULL;
    }
}
