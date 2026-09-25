#pragma once

#include "System/ProcessorContext.h"

// The NitroSDK's MB library (DS Download Play's parent side), which is all of overlay 27. The functions keep their
// official names, and so do the types (the SDK's u32 is unsigned long)

struct MBiTaskInfo;

typedef void (*MBTaskFunc)(MBiTaskInfo* info);

// A task of the MB library's thread (mb_task.c)
struct MBiTaskInfo
{
    MBiTaskInfo* next;
    unsigned long busy : 1;
    unsigned long priority : 31;
    MBTaskFunc task;
    MBTaskFunc callback;
    unsigned long param[4];
};

// The MB library's thread, with its stack after it
struct MBiTaskWork
{
    ProcessorContext thread;
    MBiTaskInfo* volatile list;
    MBiTaskInfo endTask;
};

// A buffer of MB_ReadSegment's cache (mb_cache.c)
struct MBiCacheInfo
{
    unsigned long src;
    unsigned long len;
    unsigned char* ptr;
    unsigned long state;
};

#define MB_CACHE_INFO_MAX 4

struct MBiCacheList
{
    unsigned long lifetime;
    char unk_4[0xc];
    // The name of the archive of the file
    char arc_name[4];
    unsigned long arc_name_len;
    void* arc_pointer;
    char unk_1c[0x14];
    MBiCacheInfo list[MB_CACHE_INFO_MAX];
};

// The ROM's header (HW_ROM_HEADER_BUF)
struct MBRomHeader
{
    char unk_0[0x20];
    unsigned long main_rom_offset;
    unsigned long main_entry_address;
    unsigned long main_ram_address;
    unsigned long main_size;
    unsigned long sub_rom_offset;
    unsigned long sub_entry_address;
    unsigned long sub_ram_address;
    unsigned long sub_size;
    char unk_40[0x20];
    unsigned long rom_ctrl;
    char unk_64[0x1c];
    unsigned long rom_size;
    char unk_84[0x160 - 0x84];
};

#define ROM_HEADER ((MBRomHeader*)0x027ffe00)

// A segment of a program that the parent sends
struct MbSegmentInfo
{
    // Where the child receives it, and where it goes
    unsigned long recv_addr;
    unsigned long load_addr;
    unsigned long size;
    unsigned long target : 1;
    unsigned long unk_c_1 : 31;
};

// MBDownloadFileInfo
struct MBDownloadFileInfo
{
    unsigned long arm9_entry;
    unsigned long arm7_entry;
    char unk_8[4];
    MbSegmentInfo seg[3];
    unsigned char header[0x88];
    unsigned char auth_code[0x20];
};

// Where the blocks of each segment start
struct MB_BlockInfoTable
{
    unsigned long seg_src_offset[3];
    unsigned short seg_head_blockno[3];
    unsigned short block_num;
};

// A game that the parent sends
struct MBGameRegistry
{
    const char* romFilePathp;
    const unsigned short* gameNamep;
    const unsigned short* gameIntroductionp;
    const char* iconCharPathp;
    const char* iconPalettePathp;
    unsigned long ggid;
    unsigned char maxPlayerNum;
    char unk_19[3];
    unsigned char auth_code[0x20];
};

// MB_ReadSegment's buffer: the ROM's header, the authentication, the cache and the segments' offsets
struct MBSegmentBuffer
{
    MBRomHeader header;
    unsigned char auth_code[0x88];
    MBiCacheList cache;
    unsigned long unk_258;
    unsigned long main_offset;
    unsigned long sub_offset;
    unsigned long unk_264;
};

// The information of a game, which the parent sends in beacons
struct MBGameInfo
{
    unsigned short iconPalette[0x10];
    unsigned char iconChar[0x200];
    unsigned short parent[0xb];
    unsigned char maxPlayerNum;
    char unk_237;
    unsigned short gameName[0x30];
    unsigned short gameIntroduction[0x60];
    unsigned char nowPlayerNum;
    char unk_359;
    unsigned short nowPlayerFlag;
    unsigned short changePlayerFlag;
    unsigned short member[15][0xb];
    unsigned char userVolatData[8];
    unsigned short sentPlayerFlag;
    unsigned char dataAttr;
    unsigned char seqNoFixed;
    unsigned char seqNoVolat;
    unsigned char fileNo;
    char unk_4b6[2];
    unsigned long ggid;
    MBGameInfo* next;
};

// A file that the parent sends
struct MbParentFile
{
    MBDownloadFileInfo dl_fileinfo;
    MBGameInfo game_info;
    MB_BlockInfoTable blockinfo_table;
    const MBGameRegistry* game_reg;
    const void* src_adr;
    // The next block to send, and the next one that a child asked for
    unsigned short currentb;
    unsigned short nextb;
    // The children that are downloading it
    unsigned short pollbmp;
    // The children that chose it, and the ones that changed
    unsigned short gameinfo_child_bmp;
    unsigned short gameinfo_changed_bmp;
    unsigned char active;
    char unk_5cb;
    MBiCacheList* cache_list;
    // Where each segment is in the file
    unsigned long* card_mapping;
};

#define MB_MAX_FILE 16

#define MB_MAX_CHILD 15

// A player (MBUserInfo)
struct MBUserInfo
{
    unsigned char favoriteColour : 4;
    unsigned char playerNo : 4;
    unsigned char nameLength;
    unsigned short name[10];
};

// The state of a child, for the parent (MBCommPState)
enum
{
    MB_COMM_PSTATE_NONE,
    MB_COMM_PSTATE_INIT_COMPLETE,
    MB_COMM_PSTATE_CONNECTED,
    MB_COMM_PSTATE_DISCONNECTED,
    MB_COMM_PSTATE_KICKED,
    MB_COMM_PSTATE_REQ_ACCEPTED,
    MB_COMM_PSTATE_SEND_PROCEED,
    MB_COMM_PSTATE_SEND_COMPLETE,
    MB_COMM_PSTATE_BOOT_REQUEST,
    MB_COMM_PSTATE_BOOT_STARTABLE,
    MB_COMM_PSTATE_REQUESTED,
    MB_COMM_PSTATE_MEMBER_FULL,
    MB_COMM_PSTATE_END,
    MB_COMM_PSTATE_ERROR,
    MB_COMM_PSTATE_WAIT_TO_SEND,
};

typedef void (*MBCommPStateCallback)(unsigned short child, unsigned long state, void* arg);

// The header of a block that the parent sends
struct MBCommParentBlockHeader
{
    unsigned char type;
    unsigned short fid;
    unsigned short seqno;
};

// MB_COMM_REQ_DATA_SIZE, the size of a child's request
#define MB_COMM_REQ_DATA_SIZE 0x1e

// The header of a block that a child sends
struct MBCommChildBlockHeader
{
    unsigned char type;
    union
    {
        struct
        {
            unsigned char piece;
            // A piece of the request (MB_COMM_CALC_REQ_DATA_PIECE_SIZE)
            unsigned char data[0x10];
            char pad[1];
        } req_data;
        struct
        {
            unsigned short req;
            unsigned char data[0x10];
        } data;
    };
};

// The parent's work (MB_CommPWork)
struct MB_CommPWork
{
    // The buffer of the data that the parent sends
    unsigned char sendbuf[0x400];
    // The wireless library's buffer of the data that the parent receives
    unsigned char recvbuf[0xf00];
    // The parent's user
    MBUserInfo user;
    // Whether MB_Init was called
    unsigned short isMbInitialized;
    unsigned long block_size;
    // Whether MP communication is being started
    unsigned long start_mp_busy;
    // Whether the wireless library was already initialized (MB_StartParentFromIdle)
    unsigned long is_started_ex;
    char unk_1324[0x1340 - 0x1324];
    // The children's users
    MBUserInfo childUser[MB_MAX_CHILD];
    unsigned short childversion[MB_MAX_CHILD];
    unsigned long childggid[MB_MAX_CHILD];
    MBCommPStateCallback parent_callback;
    int p_comm_state[MB_MAX_CHILD];
    unsigned char file_num;
    unsigned char cur_fileid;
    signed char fileid_of_child[MB_MAX_CHILD];
    unsigned char child_num;
    unsigned short child_entry_bmp;
    // The children's requests (see MultiBootRequest.cpp)
    unsigned char req_data_buf[0x21c];
    unsigned short req2child[MB_MAX_CHILD];
    // What MB_CommGetChildUser returns
    MBUserInfo childUserBuf;
    MbParentFile fileinfo[MB_MAX_FILE];
    // Whether the ARM7 is ready for the wireless library's commands
    unsigned long useWvrFlag;
    char unk_74cc[0x74e0 - 0x74cc];
    unsigned char task_work[0x800];
    MBiTaskInfo cur_task;
};

extern "C" MB_CommPWork* pPwork;

// The parameters of a scan for parents (WMScanParam)
struct WMScanParam
{
    void* scanBuf;
    unsigned short channel;
    unsigned short maxChannelTime;
    unsigned char bssid[6];
} __attribute__((aligned(32)));

extern "C"
{
    // OS_Terminate
    void func_020c9be0();

    void MBi_InitCache(MBiCacheList* pl);
    void MBi_AttachCacheBuffer(MBiCacheList* pl, unsigned long src, unsigned long len, void* ptr, unsigned long state);
    int MBi_ReadFromCache(MBiCacheList* pl, unsigned long src, void* dst, unsigned long len);

    void MBi_InitTaskThread(MBiTaskWork* work, unsigned long size);
    int MBi_IsTaskAvailable();
    void MBi_InitTaskInfo(MBiTaskInfo* info);
    int MBi_IsTaskBusy(volatile const MBiTaskInfo* info);
    void MBi_SetTask(MBiTaskInfo* info, MBTaskFunc task, MBTaskFunc callback, unsigned long priority);
    void MBi_EndTaskThread(MBTaskFunc callback);
}
