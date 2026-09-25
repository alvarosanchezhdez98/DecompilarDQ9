#include "MultiBoot/MultiBoot.h"
#include "Filesystem/FileAccessor.h"
#include "Filesystem/LowNitroHandle.h"
#include "Filesystem/NitroVM.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>

// The NitroSDK's mb_parent.c: the parent's communication with the children, which ask for a game, download it and
// boot it

#pragma optimize_for_size off
#pragma optimization_level 4

// MB_CACHE_STATE_READY and MB_CACHE_STATE_BUSY
#define CACHE_BUSY 1
#define CACHE_READY 2

// WM_ERRCODE_SEND_FAILED
#define SEND_FAILED 0x15
// MB_COMM_PARENT_HEADER_SIZE
#define PARENT_HEADER_SIZE 6

// The types of the blocks that the parent sends (MB_COMM_TYPE_PARENT_*)
enum
{
    TYPE_DUMMY,
    TYPE_SENDSTART,
    TYPE_KICKREQ,
    TYPE_DL_FILEINFO,
    TYPE_DATA,
    TYPE_BOOTREQ,
    TYPE_MEMBER_FULL,
    // The ones that the children send
    TYPE_CHILD_FILEREQ,
    TYPE_CHILD_ACCEPT_FILEINFO,
    TYPE_CHILD_CONTINUE,
    TYPE_CHILD_STOPREQ,
    TYPE_CHILD_BOOTREQ_ACCEPTED,
};

// What the game answers to a child's request (MB_COMM_USER_REQ_*)
enum
{
    USER_REQ_NONE,
    USER_REQ_DL_START,
    USER_REQ_SEND_START,
    USER_REQ_ACCEPT,
    USER_REQ_KICK,
    USER_REQ_BOOT,
};

// A child's request for a game (MBCommRequestData)
struct MBCommRequestData
{
    unsigned long ggid;
    MBUserInfo userinfo;
    unsigned short version;
    unsigned char fileid;
};

// A block of a segment
struct MB_BlockInfo
{
    unsigned long child_address;
    unsigned long size;
    unsigned long offset;
    unsigned char segment_no;
};

// The data that the parent received in an MP exchange (WMMpRecvData)
struct WMMpRecvData
{
    unsigned short length;
    unsigned short rssi;
    unsigned short aid;
    unsigned short noResponse;
    unsigned short timeStamp;
    unsigned char cdata[2];
};

// What the wireless library's callbacks take for a child's connection (WMStartParentCallback)
struct WMStartParentCallback
{
    unsigned short apiid;
    unsigned short errcode;
    char unk_4[0xc];
    unsigned short aid;
};

// The files whose children asked for blocks in this MP exchange
static unsigned long any_recv_bitmap;
// The last file whose information the parent sent
static unsigned char sLastFileInfo = 0xff;

extern "C"
{
    // MIi_CpuClear16
    void func_020ca390(unsigned short value, void* dst, unsigned long size);
    // MIi_CpuClearFast
    void func_020ca458(unsigned long value, void* dst, unsigned long size);
    // WM_ReadMPData
    unsigned short* func_020d49c4(const void* buffer, unsigned short aid);

    unsigned long MBi_GetGgid();
    unsigned short MBi_GetTgid();
    unsigned char MBi_GetAttribute();
    void MB_SendGameInfoBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr);
    void MB_UpdateGameInfoMember(MBGameInfo* gameInfo, const MBUserInfo* member, unsigned short nowPlayerFlag,
                                 unsigned short changePlayerFlag);
    unsigned char* MBi_MakeParentSendBuffer(const MBCommParentBlockHeader* header, unsigned char* sendBuffer);
    void* MBi_SetRecvBufferFromChild(const unsigned char* recvBuffer, MBCommChildBlockHeader* header,
                                     unsigned short aid);
    void MBi_ClearParentPieceBuffer(unsigned short aid);
    int MBi_BlockHeaderEnd(int len, unsigned short pollbmp, void* buffer);
    int MBi_get_blockinfo(MB_BlockInfo* info, const MB_BlockInfoTable* table, unsigned long block,
                          const MBDownloadFileInfo* fileInfo);

    static void MBi_CommChangeParentState(unsigned short child, int state, void* arg);
    static void MBi_CommChangeParentStateCallbackOnly(unsigned short child, int state, void* arg);
    static void MBi_CommParentRecvDataPerChild(void* arg, unsigned short child);
    static void MBi_CommParentRecvData(void* arg);
    static int MBi_CommParentSendMsg(unsigned char type, unsigned short pollbmp);
    static int MBi_CommParentSendDLFileInfo();
    static void MBi_ReloadCache(MBiTaskInfo* task);
    static int MBi_CommParentSendBlock();
    static void MBi_CommParentSendData();
    static void MBi_calc_sendblock(unsigned char fileid);
    static unsigned short MBi_calc_nextsendblock(unsigned short nextBlock, unsigned short nextBlockRequest);
    static int IsChildAidValid(unsigned short child);
    static void MBi_CommCallParentError(unsigned short child, unsigned short errcode);

    void MB_CommSetParentStateCallback(MBCommPStateCallback callback)
    {
        int lastState = DisableIRQInterrupts();
        pPwork->parent_callback = callback;
        SetIRQInterruptState(lastState);
    }

    const MBUserInfo* MB_CommGetChildUser(unsigned short child)
    {
        int lastState = DisableIRQInterrupts();
        if (pPwork != NULL && IsChildAidValid(child))
        {
            VectorizedInvertedMemcpy(&pPwork->childUser[child - 1], &pPwork->childUserBuf, sizeof(MBUserInfo));
            SetIRQInterruptState(lastState);
            return &pPwork->childUserBuf;
        }
        SetIRQInterruptState(lastState);
        return NULL;
    }

    int MB_CommIsBootable(unsigned short child)
    {
        if (pPwork != NULL && IsChildAidValid(child) &&
            pPwork->p_comm_state[child - 1] == MB_COMM_PSTATE_SEND_COMPLETE)
            return true;
        return false;
    }

    int MB_CommResponseRequest(unsigned short child, unsigned long ack)
    {
        unsigned short request;
        int state;
        int lastState = DisableIRQInterrupts();
        switch (ack)
        {
        case 0:
            state = MB_COMM_PSTATE_REQUESTED;
            request = USER_REQ_KICK;
            break;
        case 1:
            state = MB_COMM_PSTATE_REQUESTED;
            request = USER_REQ_ACCEPT;
            break;
        case 2:
            state = MB_COMM_PSTATE_WAIT_TO_SEND;
            request = USER_REQ_SEND_START;
            break;
        case 3:
            state = MB_COMM_PSTATE_SEND_COMPLETE;
            request = USER_REQ_BOOT;
            break;
        default:
            SetIRQInterruptState(lastState);
            return false;
        }
        if (pPwork != NULL && IsChildAidValid(child))
        {
            if (state == pPwork->p_comm_state[child - 1])
            {
                pPwork->req2child[child - 1] = request;
                SetIRQInterruptState(lastState);
                return true;
            }
        }
        SetIRQInterruptState(lastState);
        return false;
    }

    static void MBi_CommChangeParentState(unsigned short child, int state, void* arg)
    {
        if (IsChildAidValid(child))
            pPwork->p_comm_state[child - 1] = state;
        MBi_CommChangeParentStateCallbackOnly(child, state, arg);
    }

    static void MBi_CommChangeParentStateCallbackOnly(unsigned short child, int state, void* arg)
    {
        if (pPwork->parent_callback != NULL)
            pPwork->parent_callback(child, state, arg);
    }

    // NONMATCHING: the C matches 91.9 %: when a child disconnects, the original adds the file's offset to pPwork before
    // the field's, where the compiler adds the field's first and indexes with the file's.
#ifdef NONMATCHING
    void MBi_CommParentCallback(unsigned short type, void* arg)
    {
        switch (type)
        {
        case 0x15:
            MBi_CommChangeParentState(0, MB_COMM_PSTATE_INIT_COMPLETE, arg);
            break;
        case 0:
        {
            const unsigned short child = ((WMStartParentCallback*)arg)->aid;
            if (child != 0 && child < 16)
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_CONNECTED, arg);
            break;
        }
        case 1:
        {
            const unsigned short child = ((WMStartParentCallback*)arg)->aid;
            if (child != 0 && child < 16)
            {
                pPwork->childversion[child - 1] = 0;
                VectorizedMemset(&pPwork->childggid[((WMStartParentCallback*)arg)->aid - 1], 0, sizeof(unsigned long));
                VectorizedMemset(&pPwork->childUser[((WMStartParentCallback*)arg)->aid - 1], 0, sizeof(MBUserInfo));
                MBi_ClearParentPieceBuffer(((WMStartParentCallback*)arg)->aid);
                pPwork->req2child[((WMStartParentCallback*)arg)->aid - 1] = USER_REQ_NONE;
                {
                    const unsigned short aid = ((WMStartParentCallback*)arg)->aid;
                    if (pPwork->fileid_of_child[aid - 1] != -1)
                    {
                        const unsigned char fileid = pPwork->fileid_of_child[aid - 1];
                        pPwork->fileinfo[fileid].gameinfo_child_bmp &= ~(1 << aid);
                        pPwork->fileinfo[fileid].gameinfo_changed_bmp |= 1 << aid;
                        pPwork->fileid_of_child[aid - 1] = -1;
                        pPwork->fileinfo[fileid].pollbmp &= ~(1 << aid);
                    }
                }
                if (pPwork->child_entry_bmp & (1 << ((WMStartParentCallback*)arg)->aid))
                {
                    pPwork->child_num--;
                    pPwork->child_entry_bmp &= ~(1 << ((WMStartParentCallback*)arg)->aid);
                }
                if (pPwork->p_comm_state[((WMStartParentCallback*)arg)->aid - 1] == MB_COMM_PSTATE_BOOT_REQUEST)
                    MBi_CommChangeParentState(((WMStartParentCallback*)arg)->aid, MB_COMM_PSTATE_BOOT_STARTABLE, NULL);
                MBi_CommChangeParentState(((WMStartParentCallback*)arg)->aid, MB_COMM_PSTATE_DISCONNECTED, arg);
                pPwork->p_comm_state[((WMStartParentCallback*)arg)->aid - 1] = MB_COMM_PSTATE_NONE;
            }
            break;
        }
        case 3:
            MBi_CommParentRecvData(arg);
            break;
        case 0x19:
            MBi_CommParentSendData();
            break;
        case 0x1c:
            for (unsigned char i = 0; i < MB_MAX_FILE; i++)
            {
                if (pPwork->fileinfo[i].active && pPwork->fileinfo[i].gameinfo_changed_bmp)
                {
                    MB_UpdateGameInfoMember(&pPwork->fileinfo[i].game_info, pPwork->childUser,
                                            pPwork->fileinfo[i].gameinfo_child_bmp,
                                            pPwork->fileinfo[i].gameinfo_changed_bmp);
                    pPwork->fileinfo[i].gameinfo_changed_bmp = 0;
                }
            }
            MB_SendGameInfoBeacon(MBi_GetGgid(), MBi_GetTgid(), MBi_GetAttribute());
            break;
        case 0xff:
            switch (((WMStartParentCallback*)arg)->errcode)
            {
            case 1:
            case 4:
            case 5:
            case 6:
            case 8:
            case 9:
                MBi_CommCallParentError(0, 9);
                break;
            case 0:
            case 2:
            case 3:
            case 7:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            default:
                MBi_CommCallParentError(0, 8);
                break;
            }
            break;
        case 0x100:
            switch (*(unsigned short*)arg)
            {
            case 0:
            case 7:
            case 8:
            case 13:
            case 14:
            case 15:
            case 17:
            case 18:
            case 21:
            case 25:
            case 29:
                MBi_CommCallParentError(0, 9);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 9:
            case 10:
            case 11:
            case 12:
            case 16:
            case 19:
            case 20:
            case 22:
            case 23:
            case 24:
            case 26:
            case 27:
            case 28:
            default:
                MBi_CommCallParentError(0, 8);
                break;
            }
            break;
        case 0x11:
            break;
        }
        if (type == 0x11)
        {
            MBCommPStateCallback callback = pPwork->parent_callback;
            func_020ca458(0, pPwork, sizeof(MB_CommPWork));
            pPwork = NULL;
            if (callback != NULL)
                callback(0, MB_COMM_PSTATE_END, NULL);
        }
    }
#else
    asm void MBi_CommParentCallback(unsigned short type, void* arg)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
        mov r5, r0
        mov r4, r1
        cmp r5, #0x19
        bgt @L021d8cec
        bge @L021d8f30
        cmp r5, #0x11
        bgt @L021d8ce0
        bge @L021d90e4
        cmp r5, #0x3
        bgt @L021d90e4
        cmp r5, #0x0
        blt @L021d90e4
        beq @L021d8d24
        cmp r5, #0x1
        beq @L021d8d48
        cmp r5, #0x3
        beq @L021d8f24
        b @L021d90e4
    @L021d8ce0:
        cmp r5, #0x15
        beq @L021d8d10
        b @L021d90e4
    @L021d8cec:
        cmp r5, #0xff
        bgt @L021d8d04
        bge @L021d8fd0
        cmp r5, #0x1c
        beq @L021d8f38
        b @L021d90e4
    @L021d8d04:
        cmp r5, #0x100
        beq @L021d9040
        b @L021d90e4
    @L021d8d10:
        mov r2, r4
        mov r0, #0x0
        mov r1, #0x1
        bl MBi_CommChangeParentState
        b @L021d90e4
    @L021d8d24:
        ldrh r0, [r4, #0x10]
        cmp r0, #0x0
        beq @L021d90e4
        cmp r0, #0x10
        bhs @L021d90e4
        mov r2, r4
        mov r1, #0x2
        bl MBi_CommChangeParentState
        b @L021d90e4
    @L021d8d48:
        ldrh r0, [r4, #0x10]
        cmp r0, #0x0
        beq @L021d90e4
        cmp r0, #0x10
        bhs @L021d90e4
        ldr r2, =pPwork
        sub r0, r0, #0x1
        ldr r3, [r2, #0x0]
        mov r1, #0x0
        add r0, r3, r0, lsl #0x1
        add r0, r0, #0x1400
        strh r1, [r0, #0x8a]
        ldr r0, [r2, #0x0]
        ldrh r2, [r4, #0x10]
        add r0, r0, #0xa8
        add r3, r0, #0x1400
        sub r0, r2, #0x1
        add r0, r3, r0, lsl #0x2
        mov r2, #0x4
        bl VectorizedMemset
        ldr r0, =pPwork
        ldrh r1, [r4, #0x10]
        ldr r0, [r0, #0x0]
        mov r2, #0x16
        add r0, r0, #0x1340
        sub r1, r1, #0x1
        mla r0, r1, r2, r0
        mov r1, #0x0
        bl VectorizedMemset
        ldrh r0, [r4, #0x10]
        bl MBi_ClearParentPieceBuffer
        ldrh r1, [r4, #0x10]
        ldr r0, =pPwork
        mov r3, #0x0
        ldr r2, [r0, #0x0]
        sub r1, r1, #0x1
        add r1, r2, r1, lsl #0x1
        add r1, r1, #0x1700
        strh r3, [r1, #0x54]
        ldrh r7, [r4, #0x10]
        ldr r8, [r0, #0x0]
        sub r2, r3, #0x1
        sub r6, r7, #0x1
        add r1, r8, r6
        add r1, r1, #0x1500
        ldrsb r3, [r1, #0x26]
        cmp r3, r2
        beq @L021d8e74
        ldr r1, =0x5d4
        and r2, r3, #0xff
        mul r1, r2, r1
        add r2, r8, r1
        add r8, r2, #0x1d00
        mov r3, #0x1
        ldrh r9, [r8, #0x4e]
        mvn r2, r3, lsl r7
        and r9, r9, r2
        strh r9, [r8, #0x4e]
        ldr r8, [r0, #0x0]
        sub r9, r3, #0x2
        add r8, r8, r1
        add r8, r8, #0x1d00
        ldrh r12, [r8, #0x50]
        orr r3, r12, r3, lsl r7
        strh r3, [r8, #0x50]
        ldr r3, [r0, #0x0]
        add r3, r3, r6
        add r3, r3, #0x1000
        strb r9, [r3, #0x526]
        ldr r0, [r0, #0x0]
        add r0, r0, r1
        add r0, r0, #0x1d00
        ldrh r1, [r0, #0x4c]
        and r1, r1, r2
        strh r1, [r0, #0x4c]
    @L021d8e74:
        ldr r1, =pPwork
        ldrh r2, [r4, #0x10]
        ldr r6, [r1, #0x0]
        mov r3, #0x1
        add r0, r6, #0x1500
        ldrh r0, [r0, #0x36]
        tst r0, r3, lsl r2
        beq @L021d8ec0
        add r0, r6, #0x1000
        ldrb r2, [r0, #0x535]
        sub r2, r2, #0x1
        strb r2, [r0, #0x535]
        ldr r0, [r1, #0x0]
        ldrh r1, [r4, #0x10]
        add r0, r0, #0x1500
        ldrh r2, [r0, #0x36]
        mvn r1, r3, lsl r1
        and r1, r2, r1
        strh r1, [r0, #0x36]
    @L021d8ec0:
        ldrh r0, [r4, #0x10]
        ldr r1, =pPwork
        ldr r2, [r1, #0x0]
        sub r1, r0, #0x1
        add r1, r2, r1, lsl #0x2
        add r1, r1, #0x1000
        ldr r1, [r1, #0x4e8]
        cmp r1, #0x8
        bne @L021d8ef0
        mov r1, #0x9
        mov r2, #0x0
        bl MBi_CommChangeParentState
    @L021d8ef0:
        ldrh r0, [r4, #0x10]
        mov r2, r4
        mov r1, #0x3
        bl MBi_CommChangeParentState
        ldrh r1, [r4, #0x10]
        ldr r0, =pPwork
        mov r3, #0x0
        ldr r2, [r0, #0x0]
        sub r0, r1, #0x1
        add r0, r2, r0, lsl #0x2
        add r0, r0, #0x1000
        str r3, [r0, #0x4e8]
        b @L021d90e4
    @L021d8f24:
        mov r0, r4
        bl MBi_CommParentRecvData
        b @L021d90e4
    @L021d8f30:
        bl MBi_CommParentSendData
        b @L021d90e4
    @L021d8f38:
        mov r8, #0x0
        ldr r6, =pPwork
        ldr r4, =0x5d4
        mov r7, r8
    @L021d8f48:
        mul r9, r8, r4
        ldr r1, [r6, #0x0]
        add r2, r1, r9
        add r0, r2, #0x1000
        ldrb r0, [r0, #0xd52]
        cmp r0, #0x0
        addne r2, r2, #0x1d00
        ldrneh r3, [r2, #0x50]
        cmpne r3, #0x0
        beq @L021d8f98
        add r0, r1, #0x6c
        add r0, r0, #0x1800
        ldrh r2, [r2, #0x4e]
        add r0, r0, r9
        add r1, r1, #0x1340
        bl MB_UpdateGameInfoMember
        ldr r0, [r6, #0x0]
        add r0, r0, r9
        add r0, r0, #0x1d00
        strh r7, [r0, #0x50]
    @L021d8f98:
        add r0, r8, #0x1
        and r8, r0, #0xff
        cmp r8, #0x10
        blo @L021d8f48
        bl MBi_GetGgid
        mov r6, r0
        bl MBi_GetTgid
        mov r4, r0
        bl MBi_GetAttribute
        mov r2, r0
        mov r0, r6
        mov r1, r4
        bl MB_SendGameInfoBeacon
        b @L021d90e4
    @L021d8fd0:
        ldrh r0, [r4, #0x2]
        cmp r0, #0xf
        addls pc, pc, r0, lsl #0x2
        b @L021d9030
    @L021d8fe0:
        b @L021d9030
        b @L021d9020
        b @L021d9030
        b @L021d9030
        b @L021d9020
        b @L021d9020
        b @L021d9020
        b @L021d9030
        b @L021d9020
        b @L021d9020
        b @L021d9030
        b @L021d9030
        b @L021d9030
        b @L021d9030
        b @L021d9030
        b @L021d9030
    @L021d9020:
        mov r0, #0x0
        mov r1, #0x9
        bl MBi_CommCallParentError
        b @L021d90e4
    @L021d9030:
        mov r0, #0x0
        mov r1, #0x8
        bl MBi_CommCallParentError
        b @L021d90e4
    @L021d9040:
        ldrh r0, [r4, #0x0]
        cmp r0, #0x1d
        addls pc, pc, r0, lsl #0x2
        b @L021d90d8
    @L021d9050:
        b @L021d90c8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90c8
        b @L021d90c8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90c8
        b @L021d90c8
        b @L021d90c8
        b @L021d90d8
        b @L021d90c8
        b @L021d90c8
        b @L021d90d8
        b @L021d90d8
        b @L021d90c8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90c8
        b @L021d90d8
        b @L021d90d8
        b @L021d90d8
        b @L021d90c8
    @L021d90c8:
        mov r0, #0x0
        mov r1, #0x9
        bl MBi_CommCallParentError
        b @L021d90e4
    @L021d90d8:
        mov r0, #0x0
        mov r1, #0x8
        bl MBi_CommCallParentError
    @L021d90e4:
        cmp r5, #0x11
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
        ldr r1, =pPwork
        mov r0, #0x0
        ldr r1, [r1, #0x0]
        mov r2, #0x7d00
        add r3, r1, #0x1000
        ldr r4, [r3, #0x4e4]
        bl func_020ca458
        ldr r1, =pPwork
        mov r0, #0x0
        str r0, [r1, #0x0]
        cmp r4, #0x0
        ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
        mov r2, r0
        mov r1, #0xc
        blx r4
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    }
#endif

    // NONMATCHING: the C matches 45.7 %: the original computes child - 1 again after each call and reads the file's
    // children in each turn of the loop, where the compiler keeps both (#pragma opt_common_subs off and
    // opt_loop_invariants off get it to 96.5 %).
#ifdef NONMATCHING
    static void MBi_CommParentRecvDataPerChild(void* arg, unsigned short child)
    {
        MBCommChildBlockHeader header;
        MBCommRequestData request;
        int state;
        void* data;
        if (child == 0 || child > MB_MAX_CHILD)
            return;
        data = MBi_SetRecvBufferFromChild(((WMMpRecvData*)arg)->cdata, &header, child);
        state = pPwork->p_comm_state[child - 1];
        switch (header.type)
        {
        case TYPE_CHILD_FILEREQ:
            if (state == MB_COMM_PSTATE_CONNECTED)
            {
                if (data == NULL)
                    return;
                VectorizedInvertedMemcpy(data, &request, MB_COMM_REQ_DATA_SIZE - 1);
                pPwork->childggid[child - 1] = request.ggid;
                pPwork->childversion[child - 1] = request.version;
                VectorizedInvertedMemcpy(&request.userinfo, &pPwork->childUser[child - 1], sizeof(MBUserInfo));
                pPwork->childUser[child - 1].playerNo = child;
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_REQUESTED, &request.userinfo);
            }
            if (state != MB_COMM_PSTATE_REQUESTED)
                return;
            {
                const unsigned char fileid = ((MBCommRequestData*)data)->fileid;
                unsigned char num = 0;
                if (fileid >= MB_MAX_FILE || !pPwork->fileinfo[fileid].active ||
                    pPwork->childggid[child - 1] != pPwork->fileinfo[fileid].game_reg->ggid)
                {
                    pPwork->req2child[child - 1] = USER_REQ_KICK;
                }
                else
                {
                    for (unsigned char i = 0; i < 16; i++)
                    {
                        if (pPwork->fileinfo[fileid].gameinfo_child_bmp & (1 << i))
                            num++;
                    }
                    if (num >= pPwork->fileinfo[fileid].game_reg->maxPlayerNum)
                    {
                        pPwork->req2child[child - 1] = USER_REQ_NONE;
                        MBi_CommChangeParentState(child, MB_COMM_PSTATE_MEMBER_FULL, NULL);
                        return;
                    }
                }
                switch (pPwork->req2child[child - 1])
                {
                case USER_REQ_ACCEPT:
                    if (pPwork->child_entry_bmp & (1 << child))
                        return;
                    pPwork->child_num++;
                    pPwork->child_entry_bmp |= 1 << child;
                    pPwork->fileid_of_child[child - 1] = fileid;
                    pPwork->fileinfo[fileid].gameinfo_child_bmp |= 1 << child;
                    pPwork->fileinfo[fileid].gameinfo_changed_bmp |= 1 << child;
                    pPwork->req2child[child - 1] = USER_REQ_NONE;
                    MBi_CommChangeParentState(child, MB_COMM_PSTATE_REQ_ACCEPTED, NULL);
                    break;
                case USER_REQ_KICK:
                    pPwork->req2child[child - 1] = USER_REQ_NONE;
                    MBi_CommChangeParentState(child, MB_COMM_PSTATE_KICKED, NULL);
                    break;
                }
            }
            break;
        case TYPE_CHILD_ACCEPT_FILEINFO:
            if (state == MB_COMM_PSTATE_REQ_ACCEPTED)
            {
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_WAIT_TO_SEND, NULL);
            }
            else if (state == MB_COMM_PSTATE_WAIT_TO_SEND)
            {
                if (pPwork->req2child[child - 1] != USER_REQ_SEND_START)
                    return;
                const unsigned char fileid = pPwork->fileid_of_child[child - 1];
                pPwork->fileinfo[fileid].pollbmp |= 1 << child;
                pPwork->fileinfo[fileid].currentb = 0;
                pPwork->req2child[child - 1] = USER_REQ_NONE;
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_SEND_PROCEED, NULL);
            }
            break;
        case TYPE_CHILD_CONTINUE:
            if (state == MB_COMM_PSTATE_SEND_PROCEED)
            {
                const unsigned char fileid = pPwork->fileid_of_child[child - 1];
                if (fileid == 0xff)
                    return;
                pPwork->fileinfo[fileid].nextb = MBi_calc_nextsendblock(pPwork->fileinfo[fileid].nextb, header.data.req);
                any_recv_bitmap |= 1 << fileid;
            }
            break;
        case TYPE_CHILD_STOPREQ:
            if (state == MB_COMM_PSTATE_SEND_PROCEED)
            {
                const unsigned char fileid = pPwork->fileid_of_child[child - 1];
                if (fileid == 0xff)
                    return;
                pPwork->fileinfo[fileid].pollbmp &= ~(1 << child);
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_SEND_COMPLETE, NULL);
            }
            else if (state == MB_COMM_PSTATE_SEND_COMPLETE)
            {
                if (pPwork->req2child[child - 1] != USER_REQ_BOOT)
                    return;
                pPwork->req2child[child - 1] = USER_REQ_NONE;
                MBi_CommChangeParentState(child, MB_COMM_PSTATE_BOOT_REQUEST, NULL);
            }
            break;
        case TYPE_CHILD_BOOTREQ_ACCEPTED:
            break;
        }
    }
#else
    asm static void MBi_CommParentRecvDataPerChild(void* arg, unsigned short child)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
        sub sp, sp, #0x34
        movs r6, r1
        addeq sp, sp, #0x34
        ldmeqia sp!, {r3, r4, r5, r6, r7, r8, pc}
        cmp r6, #0xf
        addhi sp, sp, #0x34
        ldmhiia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r1, sp, #0x20
        mov r2, r6
        add r0, r0, #0xa
        bl MBi_SetRecvBufferFromChild
        ldr r1, =pPwork
        ldrb r7, [sp, #0x20]
        ldr r2, [r1, #0x0]
        sub r3, r6, #0x1
        add r4, r2, r3, lsl #0x2
        add r4, r4, #0x1000
        ldr r4, [r4, #0x4e8]
        mov r5, r0
        cmp r7, #0xb
        addls pc, pc, r7, lsl #0x2
        b @L021d9604
    @L021d9190:
        b @L021d9604
        b @L021d9604
        b @L021d9604
        b @L021d9604
        b @L021d9604
        b @L021d9604
        b @L021d9604
        b @L021d91c0
        b @L021d9458
        b @L021d9500
        b @L021d9570
        b @L021d9604
    @L021d91c0:
        cmp r4, #0x2
        bne @L021d9268
        cmp r5, #0x0
        addeq sp, sp, #0x34
        ldmeqia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r1, sp, #0x0
        mov r2, #0x1d
        bl VectorizedInvertedMemcpy
        ldr r2, =pPwork
        sub r0, r6, #0x1
        ldr r1, [r2, #0x0]
        ldr r3, [sp, #0x0]
        add r1, r1, r0, lsl #0x2
        add r1, r1, #0x1000
        str r3, [r1, #0x4a8]
        ldr r1, [r2, #0x0]
        ldrh r3, [sp, #0x1a]
        add r1, r1, r0, lsl #0x1
        add r1, r1, #0x1400
        strh r3, [r1, #0x8a]
        ldr r1, [r2, #0x0]
        mov r2, #0x16
        add r1, r1, #0x1340
        mla r1, r0, r2, r1
        add r0, sp, #0x4
        bl VectorizedInvertedMemcpy
        ldr r0, =pPwork
        sub r2, r6, #0x1
        ldr r3, [r0, #0x0]
        mov r0, #0x16
        mul r7, r2, r0
        add r8, r3, #0x1340
        and r1, r6, #0xff
        ldrb r3, [r8, r7]
        mov r0, r1, lsl #0x1c
        add r2, sp, #0x4
        bic r1, r3, #0xf0
        orr r1, r1, r0, lsr #0x18
        strb r1, [r8, r7]
        mov r0, r6
        mov r1, #0xa
        bl MBi_CommChangeParentState
    @L021d9268:
        cmp r4, #0xa
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        ldrb lr, [r5, #0x1c]
        mov r0, #0x0
        cmp lr, #0x10
        bhs @L021d92c4
        ldr r2, =pPwork
        ldr r1, =0x5d4
        ldr r3, [r2, #0x0]
        mla r4, lr, r1, r3
        add r1, r4, #0x1000
        ldrb r2, [r1, #0xd52]
        cmp r2, #0x0
        beq @L021d92c4
        sub r2, r6, #0x1
        add r3, r3, r2, lsl #0x2
        ldr r2, [r1, #0xd40]
        add r1, r3, #0x1000
        ldr r3, [r1, #0x4a8]
        ldr r1, [r2, #0x14]
        cmp r3, r1
        beq @L021d92e4
    @L021d92c4:
        ldr r0, =pPwork
        sub r1, r6, #0x1
        ldr r0, [r0, #0x0]
        mov r2, #0x4
        add r0, r0, r1, lsl #0x1
        add r0, r0, #0x1700
        strh r2, [r0, #0x54]
        b @L021d9360
    @L021d92e4:
        mov r5, r0
        add r1, r4, #0x1d00
        mov r3, #0x1
        b @L021d930c
    @L021d92f4:
        ldrh r2, [r1, #0x4e]
        tst r2, r3, lsl r5
        addne r0, r0, #0x1
        add r2, r5, #0x1
        andne r0, r0, #0xff
        and r5, r2, #0xff
    @L021d930c:
        cmp r5, #0x10
        blo @L021d92f4
        ldr r2, =pPwork
        ldr r1, =0x5d4
        ldr r2, [r2, #0x0]
        mla r1, lr, r1, r2
        add r1, r1, #0x1000
        ldr r1, [r1, #0xd40]
        ldrb r1, [r1, #0x18]
        cmp r0, r1
        blo @L021d9360
        sub r0, r6, #0x1
        add r1, r2, r0, lsl #0x1
        add r3, r1, #0x1700
        mov r2, #0x0
        mov r0, r6
        mov r1, #0xb
        strh r2, [r3, #0x54]
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9360:
        ldr r3, =pPwork
        sub r12, r6, #0x1
        ldr r1, [r3, #0x0]
        add r0, r1, r12, lsl #0x1
        add r4, r0, #0x1700
        ldrh r0, [r4, #0x54]
        cmp r0, #0x3
        beq @L021d9390
        cmp r0, #0x4
        beq @L021d943c
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9390:
        add r0, r1, #0x1500
        ldrh r0, [r0, #0x36]
        mov r5, #0x1
        tst r0, r5, lsl r6
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r1, r1, #0x1000
        ldrb r4, [r1, #0x535]
        ldr r2, =0x5d4
        mov r0, r6
        add r4, r4, #0x1
        strb r4, [r1, #0x535]
        ldr r1, [r3, #0x0]
        mul r4, lr, r2
        add r7, r1, #0x1500
        ldrh r8, [r7, #0x36]
        mov r2, #0x0
        mov r1, #0x5
        orr r8, r8, r5, lsl r6
        strh r8, [r7, #0x36]
        ldr r7, [r3, #0x0]
        add r7, r7, r12
        add r7, r7, #0x1000
        strb lr, [r7, #0x526]
        ldr r7, [r3, #0x0]
        add r7, r7, #0x4e
        add lr, r7, #0x1d00
        ldrh r7, [lr, r4]
        orr r7, r7, r5, lsl r6
        strh r7, [lr, r4]
        ldr r7, [r3, #0x0]
        add r7, r7, #0xd50
        add lr, r7, #0x1000
        ldrh r7, [lr, r4]
        orr r5, r7, r5, lsl r6
        strh r5, [lr, r4]
        ldr r3, [r3, #0x0]
        add r3, r3, r12, lsl #0x1
        add r3, r3, #0x1700
        strh r2, [r3, #0x54]
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d943c:
        mov r2, #0x0
        mov r0, r6
        mov r1, #0x4
        strh r2, [r4, #0x54]
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9458:
        cmp r4, #0x5
        bne @L021d9478
        mov r0, r6
        mov r1, #0xe
        mov r2, #0x0
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9478:
        cmp r4, #0xe
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r0, r2, r3, lsl #0x1
        add r0, r0, #0x1700
        ldrh r0, [r0, #0x54]
        cmp r0, #0x2
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r0, r2, r3
        add r0, r0, #0x1000
        ldrb r7, [r0, #0x526]
        ldr r4, =0x5d4
        add r0, r2, #0x14c
        mul r5, r7, r4
        add r7, r0, #0x1c00
        ldrh r4, [r7, r5]
        mov r0, #0x1
        mov r2, #0x0
        orr r0, r4, r0, lsl r6
        strh r0, [r7, r5]
        ldr r4, [r1, #0x0]
        mov r0, r6
        add r4, r4, r5
        add r4, r4, #0x1d00
        strh r2, [r4, #0x48]
        ldr r4, [r1, #0x0]
        mov r1, #0x6
        add r3, r4, r3, lsl #0x1
        add r3, r3, #0x1700
        strh r2, [r3, #0x54]
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9500:
        cmp r4, #0x6
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r0, r2, r3
        add r0, r0, #0x1000
        ldrb r4, [r0, #0x526]
        cmp r4, #0xff
        addeq sp, sp, #0x34
        ldmeqia sp!, {r3, r4, r5, r6, r7, r8, pc}
        ldr r0, =0x5d4
        ldrh r1, [sp, #0x22]
        mla r0, r4, r0, r2
        add r0, r0, #0x1d00
        ldrh r0, [r0, #0x4a]
        bl MBi_calc_nextsendblock
        ldr r2, =pPwork
        ldr r1, =0x5d4
        ldr r3, [r2, #0x0]
        ldr r2, =any_recv_bitmap
        mla r1, r4, r1, r3
        add r1, r1, #0x1d00
        strh r0, [r1, #0x4a]
        ldr r1, [r2, #0x0]
        mov r0, #0x1
        orr r0, r1, r0, lsl r4
        str r0, [r2, #0x0]
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d9570:
        cmp r4, #0x6
        bne @L021d95cc
        add r0, r2, r3
        add r0, r0, #0x1000
        ldrb r3, [r0, #0x526]
        cmp r3, #0xff
        addeq sp, sp, #0x34
        ldmeqia sp!, {r3, r4, r5, r6, r7, r8, pc}
        ldr r1, =0x5d4
        add r0, r2, #0x14c
        mul r4, r3, r1
        add r5, r0, #0x1c00
        mov r0, #0x1
        ldrh r1, [r5, r4]
        mvn r0, r0, lsl r6
        and r3, r1, r0
        mov r0, r6
        mov r1, #0x7
        mov r2, #0x0
        strh r3, [r5, r4]
        bl MBi_CommChangeParentState
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    @L021d95cc:
        cmp r4, #0x7
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        add r0, r2, r3, lsl #0x1
        add r3, r0, #0x1700
        ldrh r0, [r3, #0x54]
        cmp r0, #0x5
        addne sp, sp, #0x34
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, pc}
        mov r2, #0x0
        mov r0, r6
        mov r1, #0x8
        strh r2, [r3, #0x54]
        bl MBi_CommChangeParentState
    @L021d9604:
        add sp, sp, #0x34
        ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
    }
#endif

    static void MBi_CommParentRecvData(void* arg)
    {
        for (unsigned short i = 0; i < MB_MAX_FILE; i++)
        {
            if (pPwork->fileinfo[i].active)
                pPwork->fileinfo[i].nextb = 0;
        }
        any_recv_bitmap = 0;
        for (unsigned short child = 1; child <= MB_MAX_CHILD; child++)
        {
            unsigned short* data = func_020d49c4(arg, child);
            if (data != NULL && *data != 0xffff && *data != 0)
                MBi_CommParentRecvDataPerChild(data, child);
        }
    }

    static int MBi_CommParentSendMsg(unsigned char type, unsigned short pollbmp)
    {
        MBCommParentBlockHeader header;
        header.type = type;
        MBi_MakeParentSendBuffer(&header, pPwork->sendbuf);
        return MBi_BlockHeaderEnd(PARENT_HEADER_SIZE, pollbmp, pPwork->sendbuf);
    }

    static int MBi_CommParentSendDLFileInfo()
    {
        MBCommParentBlockHeader header;
        unsigned char childNum[MB_MAX_FILE];
        signed char candidate = -1;
        unsigned short pollbmp = 0;
        unsigned char* data;
        VectorizedMemset(childNum, 0, sizeof(childNum));
        for (unsigned short child = 1; child <= MB_MAX_CHILD; child++)
        {
            if (pPwork->p_comm_state[child - 1] == MB_COMM_PSTATE_REQ_ACCEPTED)
                childNum[pPwork->fileid_of_child[child - 1]]++;
        }
        {
            unsigned char next = sLastFileInfo;
            for (unsigned char i = 0; i < MB_MAX_FILE; i++)
            {
                next = (next + 1) % MB_MAX_FILE;
                if (pPwork->fileinfo[next].active && childNum[next] != 0)
                {
                    candidate = next;
                    break;
                }
            }
        }
        if (candidate == -1)
            return SEND_FAILED;
        sLastFileInfo = candidate;
        for (unsigned short child = 1; child <= MB_MAX_CHILD; child++)
        {
            if (pPwork->p_comm_state[child - 1] == MB_COMM_PSTATE_REQ_ACCEPTED &&
                candidate == pPwork->fileid_of_child[child - 1])
                pollbmp |= 1 << child;
        }
        header.type = TYPE_DL_FILEINFO;
        header.fid = candidate;
        data = MBi_MakeParentSendBuffer(&header, pPwork->sendbuf);
        if (data != NULL)
            VectorizedInvertedMemcpy(&pPwork->fileinfo[candidate].dl_fileinfo, data, sizeof(MBDownloadFileInfo));
        return MBi_BlockHeaderEnd(sizeof(MBDownloadFileInfo) + PARENT_HEADER_SIZE, pollbmp, pPwork->sendbuf);
    }

    static void MBi_ReloadCache(MBiTaskInfo* task)
    {
        MBiCacheInfo* const info = (MBiCacheInfo*)task->param[0];
        MBiCacheList* const list = (MBiCacheList*)task->param[1];
        NitroHandle* archive = NitroHandle_FindBySignature(list->arc_name, list->arc_name_len);
        if (archive == NULL)
            archive = (NitroHandle*)list->arc_pointer;
        {
            NitroVM file;
            NitroVM_Initialize(&file);
            if (NitroVM_PrepareRead(&file, archive, info->src, info->src + info->len, (unsigned int)-1))
            {
                if (info->len == NitroVM_ReadSync(&file, info->ptr, info->len))
                    info->state = CACHE_READY;
                NitroVM_FinishRead(&file);
            }
        }
        if (info->state != CACHE_READY)
        {
            info->src = 0;
            info->state = CACHE_READY;
        }
    }

    // NONMATCHING: the C matches 88 %: the original reads pPwork again at the start of the loop, and gives the block's
    // address other registers (optimization level 3 gets it to 93.4 %).
#ifdef NONMATCHING
    static int MBi_CommParentSendBlock()
    {
        MBCommParentBlockHeader header;
        MB_BlockInfo block;
        unsigned char* data;
        if (pPwork->file_num == 0)
            return SEND_FAILED;
        {
            unsigned char i;
            for (i = 0; i < MB_MAX_FILE; i++)
            {
                pPwork->cur_fileid = (pPwork->cur_fileid + 1) % MB_MAX_FILE;
                if (pPwork->fileinfo[pPwork->cur_fileid].active && pPwork->fileinfo[pPwork->cur_fileid].pollbmp)
                    break;
            }
            if (i == MB_MAX_FILE)
                return SEND_FAILED;
        }
        MBi_calc_sendblock(pPwork->cur_fileid);
        if (!MBi_get_blockinfo(&block, &pPwork->fileinfo[pPwork->cur_fileid].blockinfo_table,
                               pPwork->fileinfo[pPwork->cur_fileid].currentb,
                               &pPwork->fileinfo[pPwork->cur_fileid].dl_fileinfo))
            return SEND_FAILED;
        header.type = TYPE_DATA;
        header.fid = pPwork->cur_fileid;
        header.seqno = pPwork->fileinfo[pPwork->cur_fileid].currentb;
        data = MBi_MakeParentSendBuffer(&header, pPwork->sendbuf);
        {
            const unsigned long src =
                block.offset - pPwork->fileinfo[pPwork->cur_fileid].blockinfo_table.seg_src_offset[block.segment_no] +
                pPwork->fileinfo[pPwork->cur_fileid].card_mapping[block.segment_no];
            MBiCacheList* const list = pPwork->fileinfo[pPwork->cur_fileid].cache_list;
            if (!MBi_ReadFromCache(list, src, data, block.size))
            {
                MBiTaskInfo* const task = &pPwork->cur_task;
                if (!MBi_IsTaskBusy(task))
                {
                    if (list->lifetime != 0)
                    {
                        list->lifetime--;
                    }
                    else
                    {
                        MBiCacheInfo* info = list->list;
                        MBiCacheInfo* target = NULL;
                        for (int i = 0; i < MB_CACHE_INFO_MAX; i++)
                        {
                            if (info[i].state == CACHE_READY)
                            {
                                if (target == NULL || target->src > info[i].src)
                                    target = &info[i];
                            }
                        }
                        if (target == NULL)
                            func_020c9be0();
                        list->lifetime = 2;
                        target->state = CACHE_BUSY;
                        target->src = src & ~31;
                        task->param[0] = (unsigned long)target;
                        task->param[1] = (unsigned long)list;
                        MBi_SetTask(task, MBi_ReloadCache, NULL, 4);
                    }
                }
                return SEND_FAILED;
            }
        }
        return MBi_BlockHeaderEnd(block.size + PARENT_HEADER_SIZE, pPwork->fileinfo[pPwork->cur_fileid].pollbmp,
                                  pPwork->sendbuf);
    }
#else
    asm static int MBi_CommParentSendBlock()
    {
        stmdb sp!, {r3, r4, r5, r6, r7, lr}
        sub sp, sp, #0x18
        ldr r5, =pPwork
        ldr r0, [r5, #0x0]
        add r0, r0, #0x1000
        ldrb r0, [r0, #0x524]
        cmp r0, #0x0
        addeq sp, sp, #0x18
        moveq r0, #0x15
        ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
        ldr r4, =0x5d4
        mov r1, #0x0
    @L021d9970:
        ldr r0, [r5, #0x0]
        add r3, r0, #0x1000
        ldrb r0, [r3, #0x525]
        add r0, r0, #0x1
        mov r2, r0, lsr #0x1f
        rsb r0, r2, r0, lsl #0x1c
        add r0, r2, r0, ror #0x1c
        strb r0, [r3, #0x525]
        ldr r2, [r5, #0x0]
        add r0, r2, #0x1000
        ldrb r0, [r0, #0x525]
        mla r3, r0, r4, r2
        add r2, r3, #0x1000
        ldrb r2, [r2, #0xd52]
        cmp r2, #0x0
        addne r2, r3, #0x1d00
        ldrneh r2, [r2, #0x4c]
        cmpne r2, #0x0
        bne @L021d99cc
        add r1, r1, #0x1
        and r1, r1, #0xff
        cmp r1, #0x10
        blo @L021d9970
    @L021d99cc:
        cmp r1, #0x10
        addeq sp, sp, #0x18
        moveq r0, #0x15
        ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
        bl MBi_calc_sendblock
        ldr r0, =pPwork
        ldr r2, =0x5d4
        ldr r6, [r0, #0x0]
        add r0, sp, #0x8
        add r1, r6, #0x1000
        ldrb r4, [r1, #0x525]
        add r1, r6, #0x12c
        add r3, r6, #0x388
        mul r5, r4, r2
        add r2, r6, r5
        add r2, r2, #0x1d00
        add r1, r1, #0x1c00
        add r3, r3, #0x1400
        ldrh r2, [r2, #0x48]
        add r1, r1, r5
        add r3, r3, r5
        bl MBi_get_blockinfo
        cmp r0, #0x0
        addeq sp, sp, #0x18
        moveq r0, #0x15
        ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
        ldr r0, =pPwork
        mov r3, #0x4
        ldr r1, [r0, #0x0]
        strb r3, [sp, #0x0]
        add r2, r1, #0x1000
        ldrb r4, [r2, #0x525]
        add r3, r3, #0x5d0
        add r0, sp, #0x0
        strh r4, [sp, #0x2]
        ldrb r4, [r2, #0x525]
        mla r2, r4, r3, r1
        add r2, r2, #0x1d00
        ldrh r2, [r2, #0x48]
        strh r2, [sp, #0x4]
        bl MBi_MakeParentSendBuffer
        ldr r1, =pPwork
        ldr r4, =0x5d4
        ldr r5, [r1, #0x0]
        ldrb r1, [sp, #0x14]
        add r2, r5, #0x1000
        ldrb r2, [r2, #0x525]
        ldr r6, [sp, #0x10]
        ldr r3, [sp, #0xc]
        mla r4, r2, r4, r5
        add r2, r4, r1, lsl #0x2
        add r5, r4, #0x1000
        ldr r4, [r5, #0xd58]
        add r2, r2, #0x1000
        ldr r2, [r2, #0xd2c]
        ldr r1, [r4, r1, lsl #0x2]
        sub r2, r6, r2
        add r4, r2, r1
        ldr r5, [r5, #0xd54]
        mov r2, r0
        mov r0, r5
        mov r1, r4
        bl MBi_ReadFromCache
        cmp r0, #0x0
        bne @L021d9b9c
        ldr r0, =pPwork
        ldr r0, [r0, #0x0]
        add r0, r0, #0xce0
        add r6, r0, #0x7000
        mov r0, r6
        bl MBi_IsTaskBusy
        cmp r0, #0x0
        bne @L021d9b90
        ldr r0, [r5, #0x0]
        cmp r0, #0x0
        subne r0, r0, #0x1
        strne r0, [r5, #0x0]
        bne @L021d9b90
        add r2, r5, #0x30
        mov r7, #0x0
        mov r3, r7
        mov r12, r2
    @L021d9b14:
        add r0, r2, r3, lsl #0x4
        ldr r0, [r0, #0xc]
        cmp r0, #0x2
        bne @L021d9b40
        cmp r7, #0x0
        beq @L021d9b3c
        ldr r1, [r7, #0x0]
        ldr r0, [r2, r3, lsl #0x4]
        cmp r1, r0
        bls @L021d9b40
    @L021d9b3c:
        mov r7, r12
    @L021d9b40:
        add r3, r3, #0x1
        cmp r3, #0x4
        add r12, r12, #0x10
        blt @L021d9b14
        cmp r7, #0x0
        bne @L021d9b5c
        bl func_020c9be0
    @L021d9b5c:
        mov r0, #0x2
        str r0, [r5, #0x0]
        mov r0, #0x1
        str r0, [r7, #0xc]
        bic r0, r4, #0x1f
        str r0, [r7, #0x0]
        str r7, [r6, #0x10]
        ldr r1, =MBi_ReloadCache
        mov r0, r6
        mov r2, #0x0
        mov r3, #0x4
        str r5, [r6, #0x14]
        bl MBi_SetTask
    @L021d9b90:
        add sp, sp, #0x18
        mov r0, #0x15
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    @L021d9b9c:
        ldr r0, =pPwork
        ldr r4, [sp, #0xc]
        ldr r2, [r0, #0x0]
        ldr r1, =0x5d4
        add r0, r2, #0x1000
        ldrb r3, [r0, #0x525]
        add r0, r4, #0x6
        mla r1, r3, r1, r2
        add r1, r1, #0x1d00
        ldrh r1, [r1, #0x4c]
        bl MBi_BlockHeaderEnd
        add sp, sp, #0x18
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    }
#endif

    static void MBi_CommParentSendData()
    {
        struct
        {
            unsigned short connected;
            unsigned short accepted;
            unsigned short kicked;
            unsigned short boot;
            unsigned short full;
        } bitmaps;
        int errcode;
        func_020ca390(0, &bitmaps, sizeof(bitmaps));
        for (unsigned short child = 1; child <= MB_MAX_CHILD; child++)
        {
            switch (pPwork->p_comm_state[child - 1])
            {
            case MB_COMM_PSTATE_CONNECTED:
                bitmaps.connected |= 1 << child;
                break;
            case MB_COMM_PSTATE_REQ_ACCEPTED:
                bitmaps.accepted |= 1 << child;
                break;
            case MB_COMM_PSTATE_KICKED:
                bitmaps.kicked |= 1 << child;
                break;
            case MB_COMM_PSTATE_BOOT_REQUEST:
                bitmaps.boot |= 1 << child;
                break;
            case MB_COMM_PSTATE_MEMBER_FULL:
                bitmaps.full |= 1 << child;
                break;
            }
        }
        if (bitmaps.boot)
            errcode = MBi_CommParentSendMsg(TYPE_BOOTREQ, bitmaps.boot);
        else if (bitmaps.connected)
            errcode = MBi_CommParentSendMsg(TYPE_SENDSTART, bitmaps.connected);
        else if (bitmaps.full)
            errcode = MBi_CommParentSendMsg(TYPE_MEMBER_FULL, bitmaps.full);
        else if (bitmaps.kicked)
            errcode = MBi_CommParentSendMsg(TYPE_KICKREQ, bitmaps.kicked);
        else if (bitmaps.accepted)
            errcode = MBi_CommParentSendDLFileInfo();
        else
            errcode = MBi_CommParentSendBlock();
        if (errcode == SEND_FAILED)
            MBi_CommParentSendMsg(TYPE_DUMMY, 0xffff);
    }

    // NONMATCHING: the C matches 40.6 %: the original adds the file's offset to pPwork before the fields', where the
    // compiler indexes each field with the file's offset.
#ifdef NONMATCHING
    static void MBi_calc_sendblock(unsigned char fileid)
    {
        if (!(any_recv_bitmap & (1 << fileid)))
            return;
        MbParentFile* file = &pPwork->fileinfo[fileid];
        if (file->active && file->pollbmp)
        {
            const unsigned short current = file->currentb;
            const unsigned short next = file->nextb;
            if (current >= next && current <= next + 2)
                file->currentb = current + 1;
            else
                file->currentb = next;
        }
    }
#else
    asm static void MBi_calc_sendblock(unsigned char fileid)
    {
        ldr r1, =any_recv_bitmap
        mov r2, #0x1
        ldr r1, [r1, #0x0]
        tst r1, r2, lsl r0
        bxeq lr
        ldr r2, =pPwork
        ldr r1, =0x5d4
        ldr r2, [r2, #0x0]
        mla r12, r0, r1, r2
        add r0, r12, #0x1000
        ldrb r0, [r0, #0xd52]
        cmp r0, #0x0
        addne r0, r12, #0x1d00
        ldrneh r1, [r0, #0x4c]
        cmpne r1, #0x0
        bxeq lr
        ldrh r2, [r0, #0x48]
        ldrh r3, [r0, #0x4a]
        cmp r3, r2
        bhi @L021d9dc0
        add r1, r3, #0x2
        cmp r2, r1
        addle r1, r2, #0x1
        strleh r1, [r0, #0x48]
        bxle lr
    @L021d9dc0:
        add r0, r12, #0x1d00
        strh r3, [r0, #0x48]
        bx lr
    }
#endif

    static unsigned short MBi_calc_nextsendblock(unsigned short nextBlock, unsigned short nextBlockRequest)
    {
        return nextBlockRequest > nextBlock ? nextBlockRequest : nextBlock;
    }

    static int IsChildAidValid(unsigned short child)
    {
        return child >= 1 && child <= MB_MAX_CHILD ? true : false;
    }

    static void MBi_CommCallParentError(unsigned short child, unsigned short errcode)
    {
        unsigned short error = errcode;
        MBi_CommChangeParentStateCallbackOnly(child, MB_COMM_PSTATE_ERROR, &error);
    }
}
