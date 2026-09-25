#include "MultiBoot/MultiBoot.h"
#include "Filesystem/FileAccessor.h"
#include "Filesystem/LowNitroHandle.h"
#include "Filesystem/NitroVM.h"
#include "System/Cache.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>

// The NitroSDK's mb_fileinfo.c: reads the program that the parent sends, and registers it

#pragma optimize_for_size off
#pragma optimization_level 4

// MB_SEGMENT_BUFFER_MIN
#define SEGMENT_BUFFER_MIN 0x164
// The secure area, which MB_ReadSegment takes from the memory when the file is the game's own
#define SECURE_AREA_START 0x4000
#define SECURE_AREA_END 0x8000

// The MB library's area of the main memory
#define MAIN_MEMORY 0x02000000
#define MAIN_MEMORY_END 0x022c0000
#define MAIN_MEMORY_EXTENDED_END 0x02300000
#define MAIN_MEMORY_SUB_END 0x023fe800
#define WRAM_START 0x037f8000
#define WRAM_END 0x0380f000

// A block of a segment
struct MB_BlockInfo
{
    unsigned long child_address;
    unsigned long size;
    unsigned long offset;
    unsigned char segment_no;
};

// Where the segments of the file are, in MB_ReadSegment's buffer
struct MbRomOffsets
{
    unsigned long unk_0;
    unsigned long main_offset;
    unsigned long sub_offset;
    unsigned long unk_c;
};

// What MBi_ReadSegmentHeader copies or clears
struct MbSegmentHeaderArea
{
    unsigned long top;
    unsigned char* source;
    unsigned char* destination;
    unsigned long len;
};

// Something that the parent's code doesn't use. Defined first, the variables get the original's layout (see
// tools/data_order.py)
static unsigned long sUnknown[6];

// The segments of a program, and the ranges of the secure area that are copied
static const int sSegmentTypes[3] = {2, 0, 1};
static const unsigned long sSecureAreaRanges[][2] = {
    {0x4000, 0x1000},
    {0x7000, 0x1000},
    {0, 0},
};
static const unsigned long (*sSecureAreaRangesPointer)[2] = sSecureAreaRanges;
static char sRomArchive[] = "rom";

static unsigned char sSeqNo;

extern "C"
{
    // AutoloadCallback, which MB_ReadSegment replaces with a return in the program that it sends
    void AutoloadCallback();

    int MBi_IsStarted();
    int MBi_SendMP(const void* buffer, int len, int pollbmp);
    void MBi_MakeGameInfo(MBGameInfo* gameInfo, const MBGameRegistry* gameReg, const unsigned short* user);
    void MB_AddGameInfo(MBGameInfo* gameInfo);

    static void MBi_ReadSegmentHeader(const MbSegmentHeaderArea* area, unsigned long top, unsigned long bottom,
                                      int clear);
    static void MBi_MakeDownloadFileInfo(MBDownloadFileInfo* info, const void* buffer);
    static void MBi_SetSegmentInfo(const MBRomHeader* header, const int* type, MbSegmentInfo* seg,
                                   unsigned long* extraOffset);
    static int MBi_MakeBlockInfoTable(MB_BlockInfoTable* table, const MBDownloadFileInfo* info);
    int MBi_IsAbleToRecv(unsigned char segment, unsigned long address, unsigned long size);
    static int IsAbleToLoad(unsigned char segment, unsigned long address, unsigned long size);

    unsigned long MB_GetSegmentLength(NitroVM* file)
    {
        const MBRomHeader* header = NULL;
        unsigned long length = 0;
        unsigned char buffer[0x60];
        if (file != NULL)
        {
            const int position = file->fileInfo.cursorPos - file->fileInfo.startOffset;
            if (NitroVM_ReadSync(file, buffer, sizeof(buffer)) >= sizeof(buffer))
                header = (const MBRomHeader*)buffer;
            NitroVM_Seek(file, position, 0);
        }
        else
        {
            header = ROM_HEADER;
        }
        if (header != NULL)
        {
            length = 0x268 + header->main_size + header->sub_size;
            if (length < 0x10000)
                length = 0x10000;
        }
        return length;
    }

    // NONMATCHING: the C matches 74.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
    // The compiler gives other registers to the remaining length and the cache, and it loads ROM_HEADER->rom_size from
    // one constant, where the original adds 0x80 to the header's address.
#ifdef NONMATCHING
    int MB_ReadSegment(NitroVM* file, void* buffer, unsigned long len)
    {
        int ret = false;
        if (len >= SEGMENT_BUFFER_MIN)
        {
            int isOwnFile = false;
            MBiCacheList* cache = NULL;
            MbRomOffsets* seg = NULL;
            MBRomHeader* header = (MBRomHeader*)buffer;
            unsigned char* p = (unsigned char*)buffer + sizeof(MBRomHeader);
            unsigned long rest = len - sizeof(MBRomHeader);
            int top;
            unsigned long authOffset;
            NitroVM ownFile;

            if (file != NULL)
            {
                top = file->fileInfo.cursorPos - file->fileInfo.startOffset;
                if (NitroVM_ReadSync(file, header, sizeof(MBRomHeader)) < (int)sizeof(MBRomHeader))
                    rest = 0;
                authOffset = header->rom_size;
                if (authOffset == 0)
                    authOffset = 0x01000000;
            }
            else
            {
                authOffset = ROM_HEADER->rom_size;
                if (authOffset == 0)
                    authOffset = 0x01000000;
                isOwnFile = true;
                NitroVM_Initialize(&ownFile);
                NitroVM_PrepareRead(&ownFile, NitroHandle_FindBySignature(sRomArchive, 3), 0, authOffset + 0x88,
                                    (unsigned int)-1);
                top = ownFile.fileInfo.cursorPos - ownFile.fileInfo.startOffset;
                file = &ownFile;
                VectorizedInvertedMemcpy(ROM_HEADER, header, sizeof(MBRomHeader));
                header->rom_ctrl |= 0x406000;
            }

            if (rest >= 0x88)
            {
                NitroVM_Seek(file, top + authOffset, 0);
                NitroVM_ReadSync(file, p, 0x88);
                p += 0x88;
                rest -= 0x88;
            }
            else
            {
                rest = 0;
            }

            if (rest >= sizeof(MBiCacheList))
            {
                cache = (MBiCacheList*)p;
                MBi_InitCache(cache);
                p += sizeof(MBiCacheList);
                rest -= sizeof(MBiCacheList);
                MBi_AttachCacheBuffer(cache, 0, sizeof(MBRomHeader), header, 3);
                {
                    const char* name = (const char*)file->linkedHandle;
                    int length;
                    for (length = 0; length < 3 && name[length] != '\0'; ++length)
                    {
                    }
                    VectorizedInvertedMemcpy(name, cache->arc_name, length);
                    cache->arc_name_len = length;
                    cache->arc_pointer = (void*)name;
                }
            }
            else
            {
                rest = 0;
            }

            if (rest >= 0x10)
            {
                seg = (MbRomOffsets*)p;
                seg->unk_0 = 0;
                seg->main_offset = header->main_rom_offset + (top + file->fileInfo.startOffset);
                seg->sub_offset = header->sub_rom_offset + (top + file->fileInfo.startOffset);
                p += 0x10;
                rest -= 0x10;
            }
            else
            {
                rest = 0;
            }

            if (rest >= header->main_size + header->sub_size)
            {
                const int base = file->fileInfo.startOffset;
                NitroVM_Seek(file, seg->main_offset - base, 0);
                NitroVM_ReadSync(file, p, header->main_size);
                MBi_AttachCacheBuffer(cache, seg->main_offset, header->main_size, p, 3);
                const unsigned long mainSize = header->main_size;
                NitroVM_Seek(file, seg->sub_offset - base, 0);
                NitroVM_ReadSync(file, p + mainSize, header->sub_size);
                MBi_AttachCacheBuffer(cache, seg->sub_offset, header->sub_size, p + mainSize, 3);
                ret = true;
            }
            else if (rest >= 0xcc00)
            {
                const int base = file->fileInfo.startOffset;
                const unsigned long offset = seg->main_offset;
                NitroVM_Seek(file, offset - base, 0);
                NitroVM_ReadSync(file, p, 0x4400);
                MBi_AttachCacheBuffer(cache, offset, 0x4400, p, 3);
                NitroVM_Seek(file, offset + 0x4400 - base, 0);
                NitroVM_ReadSync(file, p + 0x4400, 0x4400);
                MBi_AttachCacheBuffer(cache, offset + 0x4400, 0x4400, p + 0x4400, 2);
                NitroVM_Seek(file, offset + 0x8800 - base, 0);
                NitroVM_ReadSync(file, p + 0x8800, 0x4400);
                MBi_AttachCacheBuffer(cache, offset + 0x8800, 0x4400, p + 0x8800, 2);
                ret = true;
            }

            NitroVM_Seek(file, top, 0);

            if (isOwnFile)
            {
                NitroVM_FinishRead(&ownFile);
                if (ret)
                {
                    MbSegmentHeaderArea area;
                    const unsigned long(*range)[2] = sSecureAreaRangesPointer;
                    area.top = header->main_rom_offset;
                    area.source = (unsigned char*)(header->main_ram_address - header->main_rom_offset);
                    area.destination = cache->list[1].ptr - header->main_rom_offset;
                    area.len = len;
                    MBi_ReadSegmentHeader(&area, SECURE_AREA_START, SECURE_AREA_END, true);
                    for (; (*range)[1] != 0; ++range)
                        MBi_ReadSegmentHeader(&area, (*range)[0], (*range)[0] + (*range)[1], false);
                    *(unsigned long*)(cache->list[1].ptr + ((unsigned long)AutoloadCallback - header->main_ram_address)) =
                        0xe12fff1e;
                }
            }
            if (ret)
                CleanInvalidateCacheRange(buffer, len);
        }
        return ret;
    }
#else
    asm int MB_ReadSegment(NitroVM* file, void* buffer, unsigned long len)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
        sub sp, sp, #0x6c
        str r2, [sp, #0x4]
        cmp r2, #0x164
        mov r2, #0x0
        mov r10, r0
        mov r9, r1
        str r2, [sp, #0x10]
        blo @L021da2f4
        ldr r4, [sp, #0x4]
        mov r5, r9
        str r2, [sp, #0xc]
        mov r6, r2
        mov r11, r2
        cmp r10, #0x0
        add r5, r5, #0x160
        sub r4, r4, #0x160
        beq @L021d9f14
        ldr r7, [r10, #0x2c]
        ldr r3, [r10, #0x24]
        mov r2, #0x160
        sub r3, r7, r3
        str r3, [sp, #0x8]
        bl NitroVM_ReadSync
        cmp r0, #0x160
        ldr r7, [r9, #0x80]
        movlt r4, r11
        cmp r7, #0x0
        moveq r7, #0x1000000
        b @L021d9f90
    @L021d9f14:
        ldr r0, =0x27ffe00
        mov r1, #0x1
        ldr r7, [r0, #0x80]
        add r0, sp, #0x24
        cmp r7, #0x0
        moveq r7, #0x1000000
        str r1, [sp, #0xc]
        bl NitroVM_Initialize
        ldr r0, =sRomArchive
        mov r1, #0x3
        bl NitroHandle_FindBySignature
        mov r1, r0
        mvn r0, #0x0
        str r0, [sp, #0x0]
        add r0, sp, #0x24
        mov r2, #0x0
        add r3, r7, #0x88
        bl NitroVM_PrepareRead
        ldr r2, [sp, #0x50]
        ldr r1, [sp, #0x48]
        ldr r0, =0x27ffe00
        sub r1, r2, r1
        str r1, [sp, #0x8]
        mov r1, r9
        mov r2, #0x160
        add r10, sp, #0x24
        bl VectorizedInvertedMemcpy
        ldr r0, [r9, #0x60]
        orr r0, r0, #0x6000
        orr r0, r0, #0x400000
        str r0, [r9, #0x60]
    @L021d9f90:
        cmp r4, #0x88
        movlo r4, #0x0
        blo @L021d9fc8
        ldr r1, [sp, #0x8]
        mov r0, r10
        add r1, r1, r7
        mov r2, #0x0
        bl NitroVM_Seek
        mov r0, r10
        mov r1, r5
        mov r2, #0x88
        bl NitroVM_ReadSync
        add r5, r5, #0x88
        sub r4, r4, #0x88
    @L021d9fc8:
        cmp r4, #0x70
        blo @L021da040
        mov r0, r5
        mov r6, r5
        bl MBi_InitCache
        mov r0, #0x3
        str r0, [sp, #0x0]
        mov r0, r6
        mov r1, #0x0
        mov r2, #0x160
        mov r3, r9
        add r5, r5, #0x70
        sub r4, r4, #0x70
        bl MBi_AttachCacheBuffer
        ldr r8, [r10, #0x8]
        mov r7, #0x0
        b @L021da010
    @L021da00c:
        add r7, r7, #0x1
    @L021da010:
        cmp r7, #0x3
        bge @L021da024
        ldrsb r0, [r8, r7]
        cmp r0, #0x0
        bne @L021da00c
    @L021da024:
        mov r0, r8
        mov r2, r7
        add r1, r6, #0x10
        bl VectorizedInvertedMemcpy
        str r7, [r6, #0x14]
        str r8, [r6, #0x18]
        b @L021da044
    @L021da040:
        mov r4, #0x0
    @L021da044:
        cmp r4, #0x10
        movlo r4, #0x0
        blo @L021da094
        mov r0, #0x0
        str r0, [r5, #0x0]
        ldr r1, [r10, #0x24]
        ldr r0, [sp, #0x8]
        ldr r2, [r9, #0x20]
        add r0, r0, r1
        add r0, r2, r0
        str r0, [r5, #0x4]
        ldr r1, [r10, #0x24]
        ldr r0, [sp, #0x8]
        ldr r2, [r9, #0x30]
        add r0, r0, r1
        add r0, r2, r0
        mov r11, r5
        str r0, [r5, #0x8]
        add r5, r5, #0x10
        sub r4, r4, #0x10
    @L021da094:
        ldr r1, [r9, #0x2c]
        ldr r0, [r9, #0x3c]
        add r0, r1, r0
        cmp r4, r0
        blo @L021da13c
        ldr r7, [r10, #0x24]
        ldr r1, [r11, #0x4]
        mov r0, r10
        sub r1, r1, r7
        mov r2, #0x0
        bl NitroVM_Seek
        ldr r2, [r9, #0x2c]
        mov r0, r10
        mov r1, r5
        bl NitroVM_ReadSync
        mov r0, #0x3
        str r0, [sp, #0x0]
        ldr r1, [r11, #0x4]
        ldr r2, [r9, #0x2c]
        mov r0, r6
        mov r3, r5
        bl MBi_AttachCacheBuffer
        ldr r1, [r11, #0x8]
        ldr r4, [r9, #0x2c]
        mov r0, r10
        mov r2, #0x0
        sub r1, r1, r7
        bl NitroVM_Seek
        ldr r2, [r9, #0x3c]
        mov r0, r10
        add r1, r5, r4
        bl NitroVM_ReadSync
        mov r0, #0x3
        str r0, [sp, #0x0]
        ldr r1, [r11, #0x8]
        ldr r2, [r9, #0x3c]
        add r3, r5, r4
        mov r0, r6
        bl MBi_AttachCacheBuffer
        mov r0, #0x1
        str r0, [sp, #0x10]
        b @L021da210
    @L021da13c:
        cmp r4, #0xcc00
        blo @L021da210
        ldr r7, [r10, #0x24]
        ldr r4, [r11, #0x4]
        mov r0, r10
        sub r1, r4, r7
        mov r2, #0x0
        bl NitroVM_Seek
        mov r0, r10
        mov r1, r5
        mov r2, #0x4400
        bl NitroVM_ReadSync
        mov r0, #0x3
        str r0, [sp, #0x0]
        mov r0, r6
        mov r1, r4
        mov r2, #0x4400
        mov r3, r5
        bl MBi_AttachCacheBuffer
        add r1, r4, #0x4400
        mov r0, r10
        sub r1, r1, r7
        mov r2, #0x0
        bl NitroVM_Seek
        mov r0, r10
        add r1, r5, #0x4400
        mov r2, #0x4400
        bl NitroVM_ReadSync
        mov r0, #0x2
        str r0, [sp, #0x0]
        mov r0, r6
        add r1, r4, #0x4400
        mov r2, #0x4400
        add r3, r5, #0x4400
        bl MBi_AttachCacheBuffer
        add r1, r4, #0x8800
        mov r0, r10
        sub r1, r1, r7
        mov r2, #0x0
        bl NitroVM_Seek
        mov r0, r10
        add r1, r5, #0x8800
        mov r2, #0x4400
        bl NitroVM_ReadSync
        mov r0, #0x2
        str r0, [sp, #0x0]
        add r1, r4, #0x8800
        add r3, r5, #0x8800
        mov r0, r6
        mov r2, #0x4400
        bl MBi_AttachCacheBuffer
        mov r0, #0x1
        str r0, [sp, #0x10]
    @L021da210:
        ldr r1, [sp, #0x8]
        mov r0, r10
        mov r2, #0x0
        bl NitroVM_Seek
        ldr r0, [sp, #0xc]
        cmp r0, #0x0
        beq @L021da2dc
        add r0, sp, #0x24
        bl NitroVM_FinishRead
        ldr r0, [sp, #0x10]
        cmp r0, #0x0
        beq @L021da2dc
        ldr r1, [r9, #0x20]
        ldr r0, =sSecureAreaRangesPointer
        str r1, [sp, #0x14]
        ldr r2, [r9, #0x28]
        ldr r1, [r9, #0x20]
        ldr r4, [r0, #0x0]
        sub r0, r2, r1
        str r0, [sp, #0x18]
        ldr r2, [r6, #0x48]
        ldr r1, [r9, #0x20]
        add r0, sp, #0x14
        sub r1, r2, r1
        str r1, [sp, #0x1c]
        ldr r1, [sp, #0x4]
        mov r2, #0x8000
        str r1, [sp, #0x20]
        mov r1, #0x4000
        mov r3, #0x1
        bl MBi_ReadSegmentHeader
        ldr r0, [r4, #0x4]
        cmp r0, #0x0
        beq @L021da2c4
        add r7, sp, #0x14
        mov r5, #0x0
    @L021da2a0:
        ldmia r4, {r1, r2}
        mov r0, r7
        mov r3, r5
        add r2, r1, r2
        bl MBi_ReadSegmentHeader
        add r4, r4, #0x8
        ldr r0, [r4, #0x4]
        cmp r0, #0x0
        bne @L021da2a0
    @L021da2c4:
        ldr r1, [r9, #0x28]
        ldr r2, =AutoloadCallback
        ldr r3, [r6, #0x48]
        ldr r0, =0xe12fff1e
        sub r1, r2, r1
        str r0, [r3, r1]
    @L021da2dc:
        ldr r0, [sp, #0x10]
        cmp r0, #0x0
        beq @L021da2f4
        ldr r1, [sp, #0x4]
        mov r0, r9
        bl CleanInvalidateCacheRange
    @L021da2f4:
        ldr r0, [sp, #0x10]
        add sp, sp, #0x6c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    }
#endif

    static void MBi_ReadSegmentHeader(const MbSegmentHeaderArea* area, unsigned long top, unsigned long bottom,
                                      int clear)
    {
        if (top < SECURE_AREA_START)
            top = SECURE_AREA_START;
        if (bottom > SECURE_AREA_END)
            bottom = SECURE_AREA_END;
        if (top < area->top)
            top = area->top;
        if (bottom > area->top + area->len)
            bottom = area->top + area->len;
        if (top < bottom)
        {
            if (clear)
                VectorizedMemset(area->destination + top, 0, bottom - top);
            else
                VectorizedInvertedMemcpy(area->source + top, area->destination + top, bottom - top);
        }
    }

    // NONMATCHING: the C matches 80.5 %: the original doesn't read sSeqNo again for its increment after the stores to
    // the file's information, and schedules the stores of the cache's and the task's pointers otherwise.
#ifdef NONMATCHING
    int MB_RegisterFile(const MBGameRegistry* gameReg, const void* buffer)
    {
        unsigned char entry = 0xff;
        int lastState = DisableIRQInterrupts();
        if (!MBi_IsStarted())
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        if (pPwork->file_num + 1 > MB_MAX_FILE)
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        unsigned char i;
        for (i = 0; i < MB_MAX_FILE; i++)
        {
            if (pPwork->fileinfo[i].game_reg == gameReg)
            {
                SetIRQInterruptState(lastState);
                return false;
            }
            if (!pPwork->fileinfo[i].active)
            {
                entry = i;
                break;
            }
        }
        if (i == MB_MAX_FILE)
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        pPwork->fileinfo[entry].game_reg = gameReg;
        MBDownloadFileInfo* info = &pPwork->fileinfo[entry].dl_fileinfo;
        MBi_MakeDownloadFileInfo(info, buffer);
        VectorizedInvertedMemcpy(gameReg->auth_code, info->auth_code, sizeof(info->auth_code));
        if (!MBi_MakeBlockInfoTable(&pPwork->fileinfo[entry].blockinfo_table, info))
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        MBi_MakeGameInfo(&pPwork->fileinfo[entry].game_info, gameReg, (const unsigned short*)&pPwork->user);
        pPwork->fileinfo[entry].game_info.fileNo = entry;
        MB_AddGameInfo(&pPwork->fileinfo[entry].game_info);
        pPwork->fileinfo[entry].game_info.seqNoFixed = sSeqNo++;
        pPwork->fileinfo[entry].gameinfo_child_bmp = 1;
        pPwork->fileinfo[entry].src_adr = buffer;
        pPwork->fileinfo[entry].cache_list = &((MBSegmentBuffer*)buffer)->cache;
        pPwork->fileinfo[entry].card_mapping = &((MBSegmentBuffer*)buffer)->unk_258;
        if (pPwork->fileinfo[entry].cache_list->list[3].state != 0 && !MBi_IsTaskAvailable())
        {
            MBi_InitTaskInfo(&pPwork->cur_task);
            MBi_InitTaskThread((MBiTaskWork*)pPwork->task_work, sizeof(pPwork->task_work));
        }
        pPwork->fileinfo[entry].active = true;
        pPwork->file_num++;
        SetIRQInterruptState(lastState);
        return true;
    }
#else
    asm int MB_RegisterFile(const MBGameRegistry* gameReg, const void* buffer)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
        mov r8, r0
        mov r7, r1
        mov r4, #0xff
        bl DisableIRQInterrupts
        mov r5, r0
        bl MBi_IsStarted
        cmp r0, #0x0
        bne @L021da3c0
        mov r0, r5
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    @L021da3c0:
        ldr r0, =pPwork
        ldr r0, [r0, #0x0]
        add r1, r0, #0x1000
        ldrb r1, [r1, #0x524]
        add r1, r1, #0x1
        cmp r1, #0x10
        ble @L021da3ec
        mov r0, r5
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    @L021da3ec:
        ldr r1, =0x5d4
        mov r6, #0x0
    @L021da3f4:
        mla r2, r6, r1, r0
        add r2, r2, #0x1000
        ldr r3, [r2, #0xd40]
        cmp r3, r8
        bne @L021da418
        mov r0, r5
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    @L021da418:
        ldrb r2, [r2, #0xd52]
        cmp r2, #0x0
        moveq r4, r6
        beq @L021da438
        add r2, r6, #0x1
        and r6, r2, #0xff
        cmp r6, #0x10
        blo @L021da3f4
    @L021da438:
        cmp r6, #0x10
        bne @L021da450
        mov r0, r5
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    @L021da450:
        ldr r1, =0x5d4
        ldr r2, =pPwork
        mul r6, r4, r1
        add r0, r0, r6
        add r0, r0, #0x1000
        str r8, [r0, #0xd40]
        ldr r0, [r2, #0x0]
        mov r1, r7
        add r0, r0, #0x388
        add r0, r0, #0x1400
        add r9, r0, r6
        mov r0, r9
        bl MBi_MakeDownloadFileInfo
        add r0, r8, #0x1c
        add r1, r9, #0xc4
        mov r2, #0x20
        bl VectorizedInvertedMemcpy
        ldr r0, =pPwork
        mov r1, r9
        ldr r0, [r0, #0x0]
        add r0, r0, #0x12c
        add r0, r0, #0x1c00
        add r0, r0, r6
        bl MBi_MakeBlockInfoTable
        cmp r0, #0x0
        bne @L021da4c8
        mov r0, r5
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    @L021da4c8:
        ldr r0, =pPwork
        mov r1, r8
        ldr r2, [r0, #0x0]
        add r0, r2, #0x6c
        add r0, r0, #0x1800
        add r0, r0, r6
        add r2, r2, #0x1300
        bl MBi_MakeGameInfo
        ldr r1, =pPwork
        ldr r0, [r1, #0x0]
        add r0, r0, r6
        add r0, r0, #0x1000
        strb r4, [r0, #0xd21]
        ldr r0, [r1, #0x0]
        add r0, r0, #0x6c
        add r0, r0, #0x1800
        add r0, r0, r6
        bl MB_AddGameInfo
        ldr r2, =pPwork
        ldr r3, =sSeqNo
        ldr r1, [r2, #0x0]
        ldrb r0, [r3, #0x0]
        add r1, r1, r6
        add r1, r1, #0x1000
        strb r0, [r1, #0xd1f]
        ldr r1, [r2, #0x0]
        mov r4, #0x1
        add r1, r1, r6
        add r1, r1, #0x1d00
        strh r4, [r1, #0x4e]
        ldr r1, [r2, #0x0]
        add r8, r7, #0x1e8
        add r1, r1, r6
        add r1, r1, #0x1000
        str r7, [r1, #0xd44]
        ldr r1, [r2, #0x0]
        add r4, r7, #0x258
        add r1, r1, r6
        add r1, r1, #0x1000
        str r8, [r1, #0xd54]
        ldr r1, [r2, #0x0]
        add r7, r0, #0x1
        add r0, r1, r6
        add r0, r0, #0x1000
        str r4, [r0, #0xd58]
        ldr r0, [r2, #0x0]
        strb r7, [r3, #0x0]
        add r0, r0, r6
        add r0, r0, #0x1000
        ldr r0, [r0, #0xd54]
        ldr r0, [r0, #0x6c]
        cmp r0, #0x0
        beq @L021da5d4
        bl MBi_IsTaskAvailable
        cmp r0, #0x0
        bne @L021da5d4
        ldr r0, =pPwork
        ldr r0, [r0, #0x0]
        add r0, r0, #0xce0
        add r0, r0, #0x7000
        bl MBi_InitTaskInfo
        ldr r0, =pPwork
        mov r1, #0x800
        ldr r0, [r0, #0x0]
        add r0, r0, #0x4e0
        add r0, r0, #0x7000
        bl MBi_InitTaskThread
    @L021da5d4:
        ldr r2, =pPwork
        mov r3, #0x1
        ldr r1, [r2, #0x0]
        mov r0, r5
        add r1, r1, r6
        add r1, r1, #0x1000
        strb r3, [r1, #0xd52]
        ldr r1, [r2, #0x0]
        add r1, r1, #0x1000
        ldrb r2, [r1, #0x524]
        add r2, r2, #0x1
        strb r2, [r1, #0x524]
        bl SetIRQInterruptState
        mov r0, #0x1
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    }
#endif

    static void MBi_MakeDownloadFileInfo(MBDownloadFileInfo* info, const void* buffer)
    {
        const MBRomHeader* header = (const MBRomHeader*)buffer;
        unsigned long extraOffset = MAIN_MEMORY_END;
        const int* type = sSegmentTypes;
        info->arm9_entry = header->main_entry_address;
        MbSegmentInfo* seg = info->seg;
        info->arm7_entry = header->sub_entry_address;
        for (int i = 0; i < 3; i++, seg++, type++)
            MBi_SetSegmentInfo(header, type, seg, &extraOffset);
        VectorizedInvertedMemcpy(((MBSegmentBuffer*)buffer)->auth_code, info->header, sizeof(info->header));
    }

    // NONMATCHING: the C matches 82.1 %: the ARM7 segment's address and end get each other's registers, and the ROM
    // header's segment stores its address and size with one stmib in the original.
#ifdef NONMATCHING
    static void MBi_SetSegmentInfo(const MBRomHeader* header, const int* type, MbSegmentInfo* seg,
                                   unsigned long* extraOffset)
    {
        switch (*type)
        {
        case 0:
        {
            unsigned long address = header->main_ram_address;
            if (address >= MAIN_MEMORY && address < MAIN_MEMORY_END && address + header->main_size <= MAIN_MEMORY_END)
            {
                seg->size = header->main_size;
                seg->recv_addr = seg->load_addr = header->main_ram_address;
                seg->target = 0;
            }
            else
            {
                func_020c9be0();
            }
            break;
        }
        case 1:
        {
            int error = false;
            int extra = false;
            unsigned long address = header->sub_ram_address;
            unsigned long size = header->sub_size;
            unsigned long end = address + size;
            if (address >= MAIN_MEMORY && address < MAIN_MEMORY_SUB_END)
            {
                if (end > MAIN_MEMORY_EXTENDED_END)
                {
                    if (end < MAIN_MEMORY_SUB_END && size <= 0x40000)
                        extra = true;
                    else
                        error = true;
                }
            }
            else if (address >= WRAM_START && address < WRAM_END)
            {
                if (end <= WRAM_END)
                    extra = true;
                else
                    error = true;
            }
            else
            {
                error = true;
            }
            if (error == true)
                func_020c9be0();
            seg->size = header->sub_size;
            seg->load_addr = header->sub_ram_address;
            if (!extra)
            {
                seg->recv_addr = seg->load_addr;
            }
            else
            {
                seg->recv_addr = *extraOffset;
                *extraOffset += seg->size;
            }
            seg->target = 1;
            break;
        }
        case 2:
            seg->load_addr = (unsigned long)ROM_HEADER;
            seg->size = sizeof(MBRomHeader);
            seg->recv_addr = (unsigned long)ROM_HEADER;
            seg->target = 0;
            break;
        }
    }
#else
    asm static void MBi_SetSegmentInfo(const MBRomHeader* header, const int* type, MbSegmentInfo* seg,
                                   unsigned long* extraOffset)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, lr}
        ldr r1, [r1, #0x0]
        mov r7, r0
        mov r6, r2
        mov r5, r3
        cmp r1, #0x0
        beq @L021da6c0
        cmp r1, #0x1
        beq @L021da70c
        cmp r1, #0x2
        beq @L021da7dc
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    @L021da6c0:
        ldr r0, [r7, #0x28]
        cmp r0, #0x2000000
        blo @L021da704
        cmp r0, #0x22c0000
        bhs @L021da704
        ldr r1, [r7, #0x2c]
        add r0, r0, r1
        cmp r0, #0x22c0000
        bhi @L021da704
        str r1, [r6, #0x8]
        ldr r0, [r7, #0x28]
        str r0, [r6, #0x4]
        str r0, [r6, #0x0]
        ldr r0, [r6, #0xc]
        bic r0, r0, #0x1
        str r0, [r6, #0xc]
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    @L021da704:
        bl func_020c9be0
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    @L021da70c:
        ldr r12, [r7, #0x38]
        ldr r1, [r7, #0x3c]
        mov r2, #0x0
        mov r4, r2
        cmp r12, #0x2000000
        add r3, r12, r1
        blo @L021da758
        ldr r0, =0x23fe800
        cmp r12, r0
        bhs @L021da758
        cmp r3, #0x2300000
        bls @L021da784
        cmp r3, r0
        bhs @L021da750
        cmp r1, #0x40000
        movls r4, #0x1
        bls @L021da784
    @L021da750:
        mov r2, #0x1
        b @L021da784
    @L021da758:
        ldr r1, =0x37f8000
        cmp r12, r1
        blo @L021da780
        add r0, r1, #0x17000
        cmp r12, r0
        bhs @L021da780
        cmp r3, r0
        movls r4, #0x1
        movhi r2, #0x1
        b @L021da784
    @L021da780:
        mov r2, #0x1
    @L021da784:
        cmp r2, #0x1
        bne @L021da790
        bl func_020c9be0
    @L021da790:
        ldr r0, [r7, #0x3c]
        cmp r4, #0x0
        str r0, [r6, #0x8]
        ldr r0, [r7, #0x38]
        str r0, [r6, #0x4]
        ldreq r0, [r6, #0x4]
        streq r0, [r6, #0x0]
        beq @L021da7c8
        ldr r0, [r5, #0x0]
        str r0, [r6, #0x0]
        ldr r1, [r5, #0x0]
        ldr r0, [r6, #0x8]
        add r0, r1, r0
        str r0, [r5, #0x0]
    @L021da7c8:
        ldr r0, [r6, #0xc]
        bic r0, r0, #0x1
        orr r0, r0, #0x1
        str r0, [r6, #0xc]
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    @L021da7dc:
        ldr r0, =0x27ffe00
        mov r1, #0x160
        stmib r6, {r0, r1}
        str r0, [r6, #0x0]
        ldr r0, [r6, #0xc]
        bic r0, r0, #0x1
        str r0, [r6, #0xc]
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    }
#endif

    static int MBi_MakeBlockInfoTable(MB_BlockInfoTable* table, const MBDownloadFileInfo* info)
    {
        unsigned short* blockNo = table->seg_head_blockno;
        unsigned long offset = 0;
        unsigned char i;
        if (info == NULL)
            return false;
        for (i = 0; i < 3; i++)
        {
            table->seg_src_offset[i] = offset;
            offset += info->seg[i].size;
        }
        blockNo[0] = 0;
        for (i = 0; i < 3; i++)
        {
            const MbSegmentInfo* seg = &info->seg[i];
            unsigned short next = blockNo[i] + (unsigned short)((seg->size + pPwork->block_size - 1) / pPwork->block_size);
            if (!IsAbleToLoad(i, seg->load_addr, seg->size))
                return false;
            if (i < 2)
                blockNo[i + 1] = next;
            else
                table->block_num = next;
        }
        return true;
    }

    int MBi_get_blockinfo(MB_BlockInfo* info, const MB_BlockInfoTable* table, unsigned long block,
                          const MBDownloadFileInfo* fileInfo)
    {
        signed char i;
        if (block >= table->block_num)
            return false;
        for (i = 2; i >= 0; i--)
        {
            if (block >= table->seg_head_blockno[i])
                break;
        }
        if (i < 0)
            return false;
        {
            unsigned long offset = block - table->seg_head_blockno[i];
            offset *= pPwork->block_size;
            const MbSegmentInfo* seg = &fileInfo->seg[i];
            info->size = seg->size - offset;
            if (info->size > pPwork->block_size)
                info->size = pPwork->block_size;
            info->offset = offset + table->seg_src_offset[i];
            info->child_address = offset + seg->recv_addr;
            info->segment_no = i;
        }
        return true;
    }

    int MBi_IsAbleToRecv(unsigned char segment, unsigned long address, unsigned long size)
    {
        switch (sSegmentTypes[segment])
        {
        case 2:
            if (address >= (unsigned long)ROM_HEADER && address + size <= (unsigned long)ROM_HEADER + sizeof(MBRomHeader))
                return true;
            break;
        case 0:
            if (address >= MAIN_MEMORY && address + size <= MAIN_MEMORY_END)
                return true;
            break;
        case 1:
            if (address >= MAIN_MEMORY_END && address + size <= MAIN_MEMORY_EXTENDED_END)
                return true;
            else if (address >= MAIN_MEMORY && address + size <= MAIN_MEMORY_EXTENDED_END)
                return true;
            break;
        default:
            return false;
        }
        return false;
    }

    static int IsAbleToLoad(unsigned char segment, unsigned long address, unsigned long size)
    {
        switch (sSegmentTypes[segment])
        {
        case 0:
        case 2:
            return MBi_IsAbleToRecv(segment, address, size);
        case 1:
            if (address >= MAIN_MEMORY && address < MAIN_MEMORY_SUB_END)
            {
                const unsigned long end = address + size;
                if (address < MAIN_MEMORY_EXTENDED_END && end > MAIN_MEMORY_EXTENDED_END)
                    return false;
                if (end <= MAIN_MEMORY_EXTENDED_END)
                    return true;
                if (end < MAIN_MEMORY_SUB_END && size <= 0x40000)
                    return true;
                return false;
            }
            if (address >= WRAM_START && address < WRAM_END)
                return address + size <= WRAM_END ? true : false;
            break;
        default:
            return false;
        }
        return false;
    }

    int MBi_BlockHeaderEnd(int len, unsigned short pollbmp, void* buffer)
    {
        CleanInvalidateCacheRange(buffer, (len + 31) & ~31);
        DrainWriteBuffer();
        return MBi_SendMP(buffer, len, pollbmp);
    }

    unsigned short MBi_calc_cksum(const unsigned short* buffer, int length)
    {
        unsigned long sum = 0;
        int words;
        for (words = length >> 1; words > 0; words--)
            sum += *buffer++;
        sum = (sum >> 16) + (sum & 0xffff);
        sum += sum >> 16;
        return (unsigned short)(sum ^ 0xffff);
    }
}
