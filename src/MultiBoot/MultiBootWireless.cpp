#include "MultiBoot/MultiBoot.h"
#include "System/Cache.h"
#include "System/DMA.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>

// The NitroSDK's mb_wm_base.c: MB_Init and MB_End, and the wireless library's calls and callbacks for the parent and
// the child

#pragma optimize_for_size off
#pragma optimization_level 4

// The wireless library's API (WM_APIID_*)
enum
{
    APIID_INITIALIZE = 0x00,
    APIID_RESET = 0x01,
    APIID_END = 0x02,
    APIID_SET_P_PARAM = 0x07,
    APIID_START_PARENT = 0x08,
    APIID_START_SCAN = 0x0a,
    APIID_END_SCAN = 0x0b,
    APIID_START_CONNECT = 0x0c,
    APIID_START_MP = 0x0e,
    APIID_SET_MP_DATA = 0x0f,
    APIID_DISCONNECT = 0x0d,
    APIID_SET_BEACON_IND = 0x19,
    APIID_SET_LIFETIME = 0x1d,
    APIID_INDICATION = 0x80,
};

// The wireless library's errors (WM_ERRCODE_*)
#define ERRCODE_SUCCESS 0
#define ERRCODE_FAILED 1
#define ERRCODE_OPERATING 2
#define ERRCODE_INVALID_PARAM 4

// What the MB library tells the game (MB_CALLBACK_*)
enum
{
    CALLBACK_CHILD_CONNECTED = 0x00,
    CALLBACK_CHILD_DISCONNECTED = 0x01,
    CALLBACK_MP_PARENT_SENT = 0x02,
    CALLBACK_MP_PARENT_RECV = 0x03,
    CALLBACK_PARENT_FOUND = 0x04,
    CALLBACK_PARENT_NOT_FOUND = 0x05,
    CALLBACK_CONNECTED_TO_PARENT = 0x06,
    CALLBACK_DISCONNECTED = 0x07,
    CALLBACK_MP_CHILD_SENT = 0x08,
    CALLBACK_MP_CHILD_RECV = 0x09,
    CALLBACK_DISCONNECTED_FROM_PARENT = 0x0a,
    CALLBACK_CONNECT_FAILED = 0x0b,
    CALLBACK_END_COMPLETE = 0x11,
    CALLBACK_MP_CHILD_SENT_ERR = 0x12,
    CALLBACK_MP_PARENT_SENT_ERR = 0x13,
    CALLBACK_INIT_COMPLETE = 0x15,
    CALLBACK_SEND_READY = 0x19,
    CALLBACK_BEACON_SENT = 0x1c,
    CALLBACK_API_ERROR = 0xff,
    CALLBACK_ERROR = 0x100,
};

// The MB library's modes
#define MODE_PARENT 1
#define MODE_CHILD 2

// The size of MB_CommPWork's part that MB_Init clears (MB_CommCommonWork)
#define COMMON_WORK_SIZE 0x1340

typedef void (*WMCallbackFunc)(void* arg);
typedef void (*MBCallbackFunc)(unsigned short type, void* arg);

// WMParentParam
struct WMParentParam
{
    unsigned short* userGameInfo;
    unsigned short userGameInfoLength;
    unsigned short padding;
    unsigned long ggid;
    unsigned short tgid;
    unsigned short entryFlag;
    unsigned short maxEntry;
    unsigned short multiBootFlag;
    unsigned short KS_Flag;
    unsigned short CS_Flag;
    unsigned short beaconPeriod;
    char unk_1a[0x32 - 0x1a];
    unsigned short channel;
    unsigned short parentMaxSize;
    unsigned short childMaxSize;
    char unk_38[8];
};

// The game information in a parent's beacon (WMGameInfo)
struct WMGameInfo
{
    char data[0x80];
};

// What the wireless library's callback gets for a parent that it found (WMStartScanCallback)
struct WMStartScanCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short wlCmdID;
    unsigned short wlResult;
    unsigned short state;
    unsigned char macAddress[6];
    char unk_10[0x36 - 0x10];
    unsigned short gameInfoLength;
    WMGameInfo gameInfo;
};

// A parent that the child found
struct MBiParentInfo
{
    // The parent's WMBssDesc
    char bssDesc[0xc0];
    WMStartScanCallback scan;
    char unk_178[8];
};

// The MB library's parameters (MBiParam)
struct MBiParam
{
    WMParentParam parentParam;
    // The wireless library's buffer of the data that the parent sends
    unsigned char sendBuf[0x400];
    // The wireless library's buffer of the parents that it found
    char scanBuf[0xc0];
    unsigned short parentMaxSize;
    unsigned short childMaxSize;
    void* recvBuf;
    WMCallbackFunc callback_ptr;
    unsigned char mpBusy;
    unsigned char mbIsStarted;
    char unk_50e[0x518 - 0x50e];
    unsigned short sendBufSize;
    unsigned short recvBufSize;
    MBCallbackFunc callback;
    // The parent that the child connects to
    const void* pInfo;
    unsigned short mode;
    unsigned short endReq;
    unsigned short mpStarted;
    unsigned short child_bitmap;
    unsigned short contSend;
    char unk_52e[2];
    unsigned short uname[4];
    unsigned short ssid[8];
    unsigned short unk_548;
    char unk_54a[0x5e0 - 0x54a];
    unsigned short found_parent_count;
    unsigned short my_aid;
    int scanning_flag;
    int scan_channel_flag;
    int last_found_parent_no;
    char unk_5f0[0x10];
    MBiParentInfo parent_info[16];
};

// The variables are defined in this order so that the compiler lays them out like the original

// The DMA channel of the wireless library
static unsigned short WM_DMA_NO;
// The wireless library's lifetimes
static unsigned short mbi_life_camera = 0x28;
static WMScanParam mbi_scan_param;
MB_CommPWork* pPwork;
static unsigned short mbi_life_frame = 5;
// The wireless library's buffer
static void* wmBuf;
static unsigned short mbi_ssid[18] = {'m', 'u', 'l', 't', 'i', 'b', 'o', 'o', 't'};
static unsigned short mbi_life_mp = 0x28;
static int mbi_power_save_mode = true;
static MBiParam* p_mbi_param;
static const unsigned short* mbi_ssid_ptr = mbi_ssid;
static unsigned short mbi_life_table = 0xffff;

extern "C"
{
    // OS_SpinWait
    void func_020c976c(unsigned long cycles);
    // OS_GetMacAddress
    void func_020c99ac(unsigned char* mac);
    // MIi_CpuClear16
    void func_020ca390(unsigned short value, void* dst, unsigned long size);
    // MI_CpuCopy16
    void func_020ca3b8(const void* src, void* dst, unsigned long size);
    // MIi_CpuClear32
    void func_020ca3ec(unsigned long value, void* dst, unsigned long size);
    // WM_SetIndCallback
    int func_020d472c(WMCallbackFunc callback);
    // WM_SetPortCallback
    int func_020d4770(unsigned short port, WMCallbackFunc callback, void* arg);
    // WM_GetNextTgid
    unsigned short func_020d4dd4();
    // WM_Initialize
    int func_020d4f7c(void* wmSysBuf, WMCallbackFunc callback, unsigned short dmaNo);
    // WM_Reset
    int func_020d5004(WMCallbackFunc callback);
    // WM_End
    int func_020d503c(WMCallbackFunc callback);
    // WM_SetParentParameter
    int func_020d507c(WMCallbackFunc callback, const WMParentParam* param);
    // WMi_StartParentEx
    int func_020d51a8(WMCallbackFunc callback, int powerSave);
    // WM_StartScan
    int func_020d5254(WMCallbackFunc callback, const WMScanParam* param);
    // WM_StartConnectEx
    int func_020d54d0(WMCallbackFunc callback, const void* pInfo, const unsigned char* ssid, int powerSave,
                      unsigned short authMode);
    // WM_Disconnect
    int func_020d559c(WMCallbackFunc callback, unsigned short aid);
    // WM_StartMPEx
    int func_020d57f4(WMCallbackFunc callback, void* recvBuf, unsigned short recvBufSize, void* sendBuf,
                      unsigned short sendBufSize, unsigned short mpFreq, unsigned short defaultRetryCount,
                      int minPollBmpMode, int singlePacketMode, int fixFreqMode, int ignoreFatalError);
    // WM_SetMPDataToPortEx
    int func_020d59bc(WMCallbackFunc callback, void* arg, const void* sendData, unsigned short sendDataSize,
                      unsigned short destBitmap, unsigned short port, unsigned short prio);
    // WM_SetBeaconIndication
    int func_020d6a84(WMCallbackFunc callback, unsigned short flag);
    // WM_SetLifeTime
    int func_020d6ad4(WMCallbackFunc callback, unsigned short tableNumber, unsigned short camLifeTime,
                      unsigned short frameLifeTime, unsigned short mpLifeTime);

    int changeScanChannel(WMScanParam* param);
    void MB_InitSendGameInfoStatus();
    void MB_CommSetParentStateCallback(MBCommPStateCallback callback);
    void MBi_CommParentCallback(unsigned short type, void* arg);
    void MBi_SetChildMPMaxSize(unsigned short childSize);
    void MBi_SetParentPieceBuffer(void* buffer);
    void MBi_ClearParentPieceBuffer(unsigned short aid);

    static int MBi_IsSendEnabled();
    static void MBi_OnInitializeDone();
    static void MBi_EndCommon(void* arg);
    static void MBi_ParentCallback(void* arg);
    static void MBi_ChildPortCallback(void* arg);
    static void MBi_ChildCallback(void* arg);
    static unsigned long MBi_GetBeaconPeriodDispersion();
    static int MBi_IsCommSizeValid(unsigned short sendSize, unsigned short recvSize, unsigned short entry_num);
    static int MBi_StartCommon();
    static int MBi_StartParentCore(int channel);
    static int MBi_CallReset();
    static void MBi_OnReset(MBiTaskInfo* task);
    static int MBi_CommEnd();
    void MBi_SetMaxScanTime(unsigned short time);
    static int MBi_SetMPData(WMCallbackFunc callback, const void* sendData, unsigned short sendDataSize,
                             unsigned short tmptt, unsigned short pollbmp);
    int MBi_SendMP(const void* buf, int len, int pollbmp);
    unsigned long MBi_GetGgid();
    unsigned short MBi_GetTgid();
    unsigned char MBi_GetAttribute();
    int MBi_IsStarted();
    static void MBi_CheckWmErrcode(unsigned short apiid, int errcode);

    // WM_IsBssidEqual
    static inline int WM_IsBssidEqual(const unsigned char* idp1, const unsigned char* idp2)
    {
        return *idp1 == *idp2 && *(idp1 + 1) == *(idp2 + 1) && *(idp1 + 2) == *(idp2 + 2) &&
               *(idp1 + 3) == *(idp2 + 3) && *(idp1 + 4) == *(idp2 + 4) && *(idp1 + 5) == *(idp2 + 5);
    }

    static int MBi_IsSendEnabled()
    {
        return p_mbi_param->mpStarted == 1 && p_mbi_param->mpBusy == 0 && p_mbi_param->endReq == 0 &&
               p_mbi_param->child_bitmap != 0;
    }

    static void MBi_OnInitializeDone()
    {
        MBi_CheckWmErrcode(APIID_INDICATION, func_020d472c(MBi_ParentCallback));
        MBi_CheckWmErrcode(APIID_SET_LIFETIME, func_020d6ad4(MBi_ParentCallback, mbi_life_table, mbi_life_camera,
                                                             mbi_life_frame, mbi_life_mp));
    }

    static void MBi_EndCommon(void* arg)
    {
        p_mbi_param->mbIsStarted = 0;
        pPwork->isMbInitialized = 0;
        if (p_mbi_param->callback != NULL)
            p_mbi_param->callback(CALLBACK_END_COMPLETE, arg);
    }

    // NONMATCHING: the C matches 96.6 %: the original reads pPwork->start_mp_busy and sets it through the same
    // register, where the compiler computes its address again.
#ifdef NONMATCHING
    static void MBi_ParentCallback(void* arg)
    {
        unsigned short* const cb = (unsigned short*)arg;
        switch (cb[0])
        {
        case APIID_INITIALIZE:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            MBi_OnInitializeDone();
            break;
        case APIID_SET_LIFETIME:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            MBi_CheckWmErrcode(APIID_SET_P_PARAM, func_020d507c(MBi_ParentCallback, &p_mbi_param->parentParam));
            break;
        case APIID_SET_P_PARAM:
            p_mbi_param->callback(CALLBACK_INIT_COMPLETE, arg);
            MBi_CheckWmErrcode(APIID_SET_BEACON_IND, func_020d6a84(MBi_ParentCallback, 1));
            break;
        case APIID_SET_BEACON_IND:
            if (!p_mbi_param->endReq)
            {
                if (cb[1] != ERRCODE_SUCCESS)
                {
                    p_mbi_param->callback(CALLBACK_ERROR, arg);
                    return;
                }
                MBi_CheckWmErrcode(APIID_START_PARENT, func_020d51a8(MBi_ParentCallback, mbi_power_save_mode));
            }
            else
            {
                if (cb[1] != ERRCODE_SUCCESS)
                {
                    p_mbi_param->endReq = 0;
                    p_mbi_param->callback(CALLBACK_ERROR, arg);
                    return;
                }
                MBi_EndCommon(arg);
            }
            break;
        case APIID_START_PARENT:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            switch (cb[4])
            {
            case 0:
                p_mbi_param->child_bitmap = 0;
                p_mbi_param->mpStarted = 0;
                break;
            case 7:
                if (p_mbi_param->endReq == 1)
                    break;
                p_mbi_param->child_bitmap |= 1 << cb[8];
                p_mbi_param->callback(CALLBACK_CHILD_CONNECTED, arg);
                if (p_mbi_param->mpStarted == 0 && !pPwork->start_mp_busy)
                {
                    pPwork->start_mp_busy = true;
                    MBi_CheckWmErrcode(APIID_START_MP,
                                       func_020d57f4(MBi_ParentCallback, p_mbi_param->recvBuf,
                                                     p_mbi_param->recvBufSize, p_mbi_param->sendBuf,
                                                     p_mbi_param->sendBufSize, p_mbi_param->contSend ? 0 : 1, 0,
                                                     false, false, true, true));
                }
                else if (MBi_IsSendEnabled())
                {
                    p_mbi_param->callback(CALLBACK_SEND_READY, NULL);
                }
                break;
            case 9:
                p_mbi_param->child_bitmap &= ~(1 << cb[8]);
                p_mbi_param->callback(CALLBACK_CHILD_DISCONNECTED, arg);
                break;
            case 2:
                if (p_mbi_param->endReq == 1)
                    break;
                p_mbi_param->callback(CALLBACK_BEACON_SENT, arg);
                break;
            case 0x1a:
                return;
            default:
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                break;
            }
            break;
        case APIID_START_MP:
            pPwork->start_mp_busy = false;
            switch (cb[2])
            {
            case 10:
                p_mbi_param->mpStarted = 1;
                if (p_mbi_param->endReq)
                    break;
                p_mbi_param->callback(CALLBACK_SEND_READY, NULL);
                break;
            case 11:
                p_mbi_param->callback(CALLBACK_MP_PARENT_RECV, *(void**)&cb[4]);
                break;
            default:
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                break;
            }
            break;
        case APIID_SET_MP_DATA:
            if (pPwork->useWvrFlag)
            {
                unsigned long i;
                unsigned long children = 0;
                for (i = 0; i < MB_MAX_CHILD; i++)
                {
                    if (pPwork->p_comm_state[i] != MB_COMM_PSTATE_NONE && ++children >= 2)
                        break;
                }
                if (children == 1)
                    func_020c976c(13000);
            }
            p_mbi_param->mpBusy = 0;
            if (cb[1] == ERRCODE_SUCCESS)
            {
                p_mbi_param->callback(CALLBACK_MP_PARENT_SENT, arg);
                if (!p_mbi_param->endReq)
                    p_mbi_param->callback(CALLBACK_SEND_READY, NULL);
            }
            else if (cb[1] == 10)
            {
                p_mbi_param->callback(0x2a, arg);
            }
            else
            {
                p_mbi_param->callback(CALLBACK_MP_PARENT_SENT_ERR, arg);
                if (!p_mbi_param->endReq)
                    p_mbi_param->callback(CALLBACK_SEND_READY, NULL);
            }
            break;
        case APIID_RESET:
            if (!pPwork->is_started_ex)
            {
                if (cb[1] != ERRCODE_SUCCESS)
                {
                    p_mbi_param->endReq = 0;
                    p_mbi_param->callback(CALLBACK_ERROR, arg);
                    return;
                }
                p_mbi_param->child_bitmap = 0;
                p_mbi_param->mpStarted = 0;
                MBi_CheckWmErrcode(APIID_END, func_020d503c(MBi_ParentCallback));
            }
            else
            {
                func_020d4770(1, NULL, NULL);
                func_020d472c(NULL);
                if (cb[1] != ERRCODE_SUCCESS)
                {
                    p_mbi_param->endReq = 0;
                    p_mbi_param->callback(CALLBACK_ERROR, arg);
                    return;
                }
                MBi_CheckWmErrcode(APIID_SET_BEACON_IND, func_020d6a84(MBi_ParentCallback, 0));
            }
            break;
        case APIID_END:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_mbi_param->endReq = 0;
                p_mbi_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            MBi_EndCommon(arg);
            break;
        case APIID_DISCONNECT:
            if (cb[1] != ERRCODE_SUCCESS)
                return;
            p_mbi_param->child_bitmap &= ~cb[5];
            break;
        case APIID_INDICATION:
            switch (cb[2])
            {
            case 0x10:
                p_mbi_param->callback(0x1d, arg);
                break;
            case 0x11:
                p_mbi_param->callback(0x1f, arg);
                break;
            case 0x12:
                p_mbi_param->callback(0x20, arg);
                break;
            case 0x13:
                p_mbi_param->callback(0x21, arg);
                break;
            case 0x16:
                func_020c9be0();
                break;
            case 0x17:
                break;
            }
            break;
        default:
            p_mbi_param->callback(CALLBACK_ERROR, arg);
            break;
        }
    }
#else
    asm static void MBi_ParentCallback(void* arg)
    {
        stmdb sp!, {r3, r4, lr}
        sub sp, sp, #0x1c
        mov r4, r0
        ldrh r1, [r4, #0x0]
        cmp r1, #0x19
        bgt @L021db58c
        bge @L021db668
        cmp r1, #0xf
        addls pc, pc, r1, lsl #0x2
        b @L021dbd4c
    @L021db54c:
        b @L021db5a8
        b @L021dbb1c
        b @L021dbc0c
        b @L021dbd4c
        b @L021dbd4c
        b @L021dbd4c
        b @L021dbd4c
        b @L021db630
        b @L021db704
        b @L021dbd4c
        b @L021dbd4c
        b @L021dbd4c
        b @L021dbd4c
        b @L021dbc54
        b @L021db958
        b @L021db9f8
    @L021db58c:
        cmp r1, #0x1d
        bgt @L021db59c
        beq @L021db5e0
        b @L021dbd4c
    @L021db59c:
        cmp r1, #0x80
        beq @L021dbc8c
        b @L021dbd4c
    @L021db5a8:
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        beq @L021db5d4
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db5d4:
        bl MBi_OnInitializeDone
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db5e0:
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        beq @L021db60c
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db60c:
        ldr r1, =WM_DMA_NO
        ldr r0, =MBi_ParentCallback
        ldr r1, [r1, #0x8]
        bl func_020d507c
        mov r1, r0
        mov r0, #0x7
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db630:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x15
        ldr r2, [r2, #0x51c]
        blx r2
        ldr r0, =MBi_ParentCallback
        mov r1, #0x1
        bl func_020d6a84
        mov r1, r0
        mov r0, #0x19
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db668:
        ldr r2, =WM_DMA_NO
        ldr r12, [r2, #0x8]
        add r1, r12, #0x500
        ldrh r3, [r1, #0x26]
        cmp r3, #0x0
        bne @L021db6c8
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        beq @L021db6a4
        ldr r2, [r12, #0x51c]
        mov r1, r4
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db6a4:
        ldr r1, =mbi_life_frame
        ldr r0, =MBi_ParentCallback
        ldr r1, [r1, #0xc]
        bl func_020d51a8
        mov r1, r0
        mov r0, #0x8
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db6c8:
        ldrh r3, [r4, #0x2]
        cmp r3, #0x0
        beq @L021db6f8
        mov r0, #0x0
        strh r0, [r1, #0x26]
        ldr r0, [r2, #0x8]
        mov r1, r4
        ldr r2, [r0, #0x51c]
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db6f8:
        bl MBi_EndCommon
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db704:
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        beq @L021db730
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db730:
        ldrh r0, [r4, #0x8]
        cmp r0, #0x7
        bgt @L021db760
        bge @L021db7a8
        cmp r0, #0x2
        bgt @L021db938
        cmp r0, #0x0
        blt @L021db938
        beq @L021db780
        cmp r0, #0x2
        beq @L021db904
        b @L021db938
    @L021db760:
        cmp r0, #0x9
        bgt @L021db770
        beq @L021db8c8
        b @L021db938
    @L021db770:
        cmp r0, #0x1a
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r3, r4, pc}
        b @L021db938
    @L021db780:
        ldr r1, =WM_DMA_NO
        mov r2, #0x0
        ldr r0, [r1, #0x8]
        add sp, sp, #0x1c
        add r0, r0, #0x500
        strh r2, [r0, #0x2a]
        ldr r0, [r1, #0x8]
        add r0, r0, #0x500
        strh r2, [r0, #0x28]
        ldmia sp!, {r3, r4, pc}
    @L021db7a8:
        ldr r2, =WM_DMA_NO
        ldr r0, [r2, #0x8]
        add r0, r0, #0x500
        ldrh r1, [r0, #0x26]
        cmp r1, #0x1
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r3, r4, pc}
        ldrh lr, [r0, #0x2a]
        ldrh r3, [r4, #0x10]
        mov r12, #0x1
        mov r1, r4
        orr r3, lr, r12, lsl r3
        strh r3, [r0, #0x2a]
        ldr r2, [r2, #0x8]
        mov r0, #0x0
        ldr r2, [r2, #0x51c]
        blx r2
        ldr r1, =WM_DMA_NO
        ldr r0, [r1, #0x8]
        add r0, r0, #0x500
        ldrh r0, [r0, #0x28]
        cmp r0, #0x0
        bne @L021db898
        ldr r0, [r1, #0xc]
        add r0, r0, #0x1000
        ldr r2, [r0, #0x31c]
        cmp r2, #0x0
        bne @L021db898
        mov r2, #0x1
        str r2, [r0, #0x31c]
        ldr r0, [r1, #0x8]
        ldr r1, =WM_DMA_NO
        add r0, r0, #0x500
        ldrh r0, [r0, #0x2c]
        ldr r12, [r1, #0x8]
        mov r1, #0x1
        cmp r0, #0x0
        movne r2, #0x0
        mov r0, r2, lsl #0x10
        mov r3, r0, lsr #0x10
        add r0, r12, #0x500
        ldrh r4, [r0, #0x18]
        mov r2, #0x0
        str r4, [sp, #0x0]
        str r3, [sp, #0x4]
        str r2, [sp, #0x8]
        str r2, [sp, #0xc]
        str r2, [sp, #0x10]
        str r1, [sp, #0x14]
        str r1, [sp, #0x18]
        ldrh r2, [r0, #0x1a]
        ldr r1, [r12, #0x504]
        ldr r0, =MBi_ParentCallback
        add r3, r12, #0x40
        bl func_020d57f4
        mov r1, r0
        mov r0, #0xe
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db898:
        bl MBi_IsSendEnabled
        cmp r0, #0x0
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r3, r4, pc}
        ldr r1, =WM_DMA_NO
        mov r0, #0x19
        ldr r2, [r1, #0x8]
        mov r1, #0x0
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db8c8:
        ldr r2, =WM_DMA_NO
        ldrh r3, [r4, #0x10]
        ldr r1, [r2, #0x8]
        mov r0, #0x1
        add r1, r1, #0x500
        ldrh r12, [r1, #0x2a]
        mvn r3, r0, lsl r3
        and r3, r12, r3
        strh r3, [r1, #0x2a]
        ldr r2, [r2, #0x8]
        mov r1, r4
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db904:
        ldr r0, =WM_DMA_NO
        ldr r1, [r0, #0x8]
        add r0, r1, #0x500
        ldrh r0, [r0, #0x26]
        cmp r0, #0x1
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r3, r4, pc}
        ldr r2, [r1, #0x51c]
        mov r1, r4
        mov r0, #0x1c
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db938:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db958:
        ldr r2, =WM_DMA_NO
        mov r1, #0x0
        ldr r0, [r2, #0xc]
        add r0, r0, #0x1000
        str r1, [r0, #0x31c]
        ldrh r0, [r4, #0x4]
        cmp r0, #0xa
        beq @L021db984
        cmp r0, #0xb
        beq @L021db9c0
        b @L021db9dc
    @L021db984:
        ldr r0, [r2, #0x8]
        mov r3, #0x1
        add r0, r0, #0x500
        strh r3, [r0, #0x28]
        ldr r2, [r2, #0x8]
        add r0, r2, #0x500
        ldrh r0, [r0, #0x26]
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r3, r4, pc}
        ldr r2, [r2, #0x51c]
        mov r0, #0x19
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db9c0:
        ldr r0, [r2, #0x8]
        ldr r1, [r4, #0x8]
        ldr r2, [r0, #0x51c]
        mov r0, #0x3
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db9dc:
        ldr r0, [r2, #0x8]
        mov r1, r4
        ldr r2, [r0, #0x51c]
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021db9f8:
        ldr r0, =WM_DMA_NO
        ldr r3, [r0, #0xc]
        add r0, r3, #0x7000
        ldr r0, [r0, #0x4c8]
        cmp r0, #0x0
        beq @L021dba54
        mov r2, #0x0
        mov r1, r2
    @L021dba18:
        add r0, r3, r1, lsl #0x2
        add r0, r0, #0x1000
        ldr r0, [r0, #0x4e8]
        cmp r0, #0x0
        beq @L021dba38
        add r2, r2, #0x1
        cmp r2, #0x2
        bhs @L021dba44
    @L021dba38:
        add r1, r1, #0x1
        cmp r1, #0xf
        blo @L021dba18
    @L021dba44:
        cmp r2, #0x1
        bne @L021dba54
        ldr r0, =0x32c8
        bl func_020c976c
    @L021dba54:
        ldr r0, =WM_DMA_NO
        mov r2, #0x0
        ldr r1, [r0, #0x8]
        strb r2, [r1, #0x50c]
        ldrh r1, [r4, #0x2]
        cmp r1, #0x0
        bne @L021dbab8
        ldr r0, [r0, #0x8]
        mov r1, r4
        ldr r2, [r0, #0x51c]
        mov r0, #0x2
        blx r2
        ldr r0, =WM_DMA_NO
        ldr r1, [r0, #0x8]
        add r0, r1, #0x500
        ldrh r0, [r0, #0x26]
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r3, r4, pc}
        ldr r2, [r1, #0x51c]
        mov r0, #0x19
        mov r1, #0x0
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbab8:
        cmp r1, #0xa
        ldr r0, [r0, #0x8]
        mov r1, r4
        bne @L021dbadc
        ldr r2, [r0, #0x51c]
        mov r0, #0x2a
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbadc:
        ldr r2, [r0, #0x51c]
        mov r0, #0x13
        blx r2
        ldr r0, =WM_DMA_NO
        ldr r1, [r0, #0x8]
        add r0, r1, #0x500
        ldrh r0, [r0, #0x26]
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r3, r4, pc}
        ldr r2, [r1, #0x51c]
        mov r0, #0x19
        mov r1, #0x0
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbb1c:
        ldr r1, =WM_DMA_NO
        ldr r0, [r1, #0xc]
        add r0, r0, #0x1000
        ldr r0, [r0, #0x320]
        cmp r0, #0x0
        bne @L021dbb98
        ldrh r0, [r4, #0x2]
        mov r2, #0x0
        cmp r0, #0x0
        ldr r0, [r1, #0x8]
        add r0, r0, #0x500
        beq @L021dbb6c
        strh r2, [r0, #0x26]
        ldr r0, [r1, #0x8]
        mov r1, r4
        ldr r2, [r0, #0x51c]
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbb6c:
        strh r2, [r0, #0x2a]
        ldr r1, [r1, #0x8]
        ldr r0, =MBi_ParentCallback
        add r1, r1, #0x500
        strh r2, [r1, #0x28]
        bl func_020d503c
        mov r1, r0
        mov r0, #0x2
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbb98:
        mov r1, #0x0
        mov r2, r1
        mov r0, #0x1
        bl func_020d4770
        mov r0, #0x0
        bl func_020d472c
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        beq @L021dbbec
        ldr r2, =WM_DMA_NO
        mov r3, #0x0
        ldr r0, [r2, #0x8]
        mov r1, r4
        add r0, r0, #0x500
        strh r3, [r0, #0x26]
        ldr r2, [r2, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbbec:
        ldr r0, =MBi_ParentCallback
        mov r1, #0x0
        bl func_020d6a84
        mov r1, r0
        mov r0, #0x19
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbc0c:
        ldrh r1, [r4, #0x2]
        cmp r1, #0x0
        beq @L021dbc48
        ldr r2, =WM_DMA_NO
        mov r3, #0x0
        ldr r0, [r2, #0x8]
        mov r1, r4
        add r0, r0, #0x500
        strh r3, [r0, #0x26]
        ldr r2, [r2, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbc48:
        bl MBi_EndCommon
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbc54:
        ldrh r0, [r4, #0x2]
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r3, r4, pc}
        ldr r0, =WM_DMA_NO
        ldrh r1, [r4, #0xa]
        ldr r0, [r0, #0x8]
        add sp, sp, #0x1c
        add r0, r0, #0x500
        ldrh r2, [r0, #0x2a]
        mvn r1, r1
        and r1, r2, r1
        strh r1, [r0, #0x2a]
        ldmia sp!, {r3, r4, pc}
    @L021dbc8c:
        ldrh r0, [r4, #0x4]
        sub r0, r0, #0x10
        cmp r0, #0x7
        addls pc, pc, r0, lsl #0x2
        b @L021dbd64
    @L021dbca0:
        b @L021dbcc0
        b @L021dbce0
        b @L021dbd00
        b @L021dbd20
        b @L021dbd64
        b @L021dbd64
        b @L021dbd40
        b @L021dbd64
    @L021dbcc0:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x1d
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbce0:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x1f
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbd00:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x20
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbd20:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x21
        ldr r2, [r2, #0x51c]
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbd40:
        bl func_020c9be0
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    @L021dbd4c:
        ldr r0, =WM_DMA_NO
        mov r1, r4
        ldr r2, [r0, #0x8]
        mov r0, #0x100
        ldr r2, [r2, #0x51c]
        blx r2
    @L021dbd64:
        add sp, sp, #0x1c
        ldmia sp!, {r3, r4, pc}
    }
#endif

    static void MBi_ChildPortCallback(void* arg)
    {
        unsigned short* const cb = (unsigned short*)arg;
        if (cb[1] != ERRCODE_SUCCESS)
            return;
        switch (cb[2])
        {
        case 0x15:
            p_mbi_param->callback(CALLBACK_MP_CHILD_RECV, arg);
            break;
        case 7:
        case 9:
        case 0x19:
        case 0x1a:
            break;
        }
    }

    // NONMATCHING: the C matches 52 %: the original keeps WM_IsBssidEqual's comparisons as flags and computes each
    // parent's address again in each turn of the loop, where the compiler folds the comparisons and walks the parents with
    // a pointer (#pragma opt_common_subs off gets it to 69.8 %).
#ifdef NONMATCHING
    static void MBi_ChildCallback(void* arg)
    {
        unsigned short* const cb = (unsigned short*)arg;
        MBiParam* const p_param = p_mbi_param;
        switch (cb[0])
        {
        case APIID_INITIALIZE:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            p_param->callback(CALLBACK_INIT_COMPLETE, arg);
            MBi_CheckWmErrcode(APIID_SET_LIFETIME, func_020d6ad4(MBi_ChildCallback, mbi_life_table, mbi_life_camera,
                                                                 mbi_life_frame, mbi_life_mp));
            break;
        case APIID_SET_LIFETIME:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            mbi_scan_param.scanBuf = p_param->scanBuf;
            if (mbi_scan_param.channel == 0)
                mbi_scan_param.channel = 1;
            if (mbi_scan_param.maxChannelTime == 0)
                mbi_scan_param.maxChannelTime = 200;
            mbi_scan_param.bssid[0] = 0xff;
            mbi_scan_param.bssid[1] = 0xff;
            mbi_scan_param.bssid[2] = 0xff;
            mbi_scan_param.bssid[3] = 0xff;
            mbi_scan_param.bssid[4] = 0xff;
            mbi_scan_param.bssid[5] = 0xff;
            p_param->scanning_flag = true;
            p_param->scan_channel_flag = true;
            MBi_CheckWmErrcode(APIID_START_SCAN, func_020d5254(MBi_ChildCallback, &mbi_scan_param));
            break;
        case APIID_START_SCAN:
        {
            WMStartScanCallback* const scan = (WMStartScanCallback*)arg;
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            switch (scan->state)
            {
            case 3:
                return;
            case 5:
            {
                int i;
                for (i = 0; i < p_param->found_parent_count; i++)
                {
                    if (WM_IsBssidEqual(scan->macAddress, p_param->parent_info[i].scan.macAddress))
                    {
                        p_param->parent_info[i].scan.gameInfoLength = scan->gameInfoLength;
                        p_param->parent_info[i].scan.gameInfo = scan->gameInfo;
                        InvalidateDataCacheRange(&p_param->parent_info[i], sizeof(p_param->parent_info[i].bssDesc));
                        DMAMemcpySynchronous16Bit(WM_DMA_NO, (unsigned int)p_param->scanBuf,
                                                  (unsigned int)&p_param->parent_info[i],
                                                  sizeof(p_param->parent_info[i].bssDesc));
                        p_param->last_found_parent_no = i;
                        goto found;
                    }
                }
                if (i < 16)
                {
                    p_param->found_parent_count = i + 1;
                    func_020ca3b8(arg, &p_param->parent_info[i].scan, sizeof(WMStartScanCallback));
                    InvalidateDataCacheRange(&p_param->parent_info[i], sizeof(p_param->parent_info[i].bssDesc));
                    DMAMemcpySynchronous16Bit(WM_DMA_NO, (unsigned int)p_param->scanBuf,
                                              (unsigned int)&p_param->parent_info[i],
                                              sizeof(p_param->parent_info[i].bssDesc));
                    p_param->last_found_parent_no = i;
                }
            found:
                p_param->callback(CALLBACK_PARENT_FOUND, arg);
                if (!p_param->scanning_flag)
                    return;
                if (p_param->scan_channel_flag && !changeScanChannel(&mbi_scan_param))
                    MBi_CommEnd();
                MBi_CheckWmErrcode(APIID_START_SCAN, func_020d5254(MBi_ChildCallback, &mbi_scan_param));
                break;
            }
            case 4:
                p_param->callback(CALLBACK_PARENT_NOT_FOUND, arg);
                if (!p_param->scanning_flag)
                    return;
                if (p_param->scan_channel_flag && !changeScanChannel(&mbi_scan_param))
                    MBi_CommEnd();
                MBi_CheckWmErrcode(APIID_START_SCAN, func_020d5254(MBi_ChildCallback, &mbi_scan_param));
                break;
            default:
                p_param->callback(CALLBACK_ERROR, arg);
                break;
            }
            break;
        }
        case APIID_END_SCAN:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            MBi_CheckWmErrcode(APIID_START_CONNECT, func_020d54d0(MBi_ChildCallback, p_param->pInfo, NULL, true, 0));
            break;
        case APIID_START_CONNECT:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->found_parent_count = 0;
                p_param->callback(CALLBACK_CONNECT_FAILED, arg);
                return;
            }
            switch (cb[4])
            {
            case 0x1a:
                return;
            case 6:
                p_param->child_bitmap = 0;
                p_param->mpStarted = 1;
                break;
            case 7:
                p_param->my_aid = cb[5];
                p_param->callback(CALLBACK_CONNECTED_TO_PARENT, arg);
                p_param->child_bitmap = 1;
                if (func_020d4770(1, MBi_ChildPortCallback, NULL) != ERRCODE_SUCCESS)
                    return;
                MBi_CheckWmErrcode(APIID_START_MP,
                                   func_020d57f4(MBi_ChildCallback, p_param->recvBuf, p_param->recvBufSize,
                                                 p_param->sendBuf, p_param->sendBufSize, p_param->contSend ? 0 : 1,
                                                 0, false, false, true, true));
                break;
            case 9:
                p_param->callback(CALLBACK_DISCONNECTED_FROM_PARENT, arg);
                p_param->child_bitmap = 0;
                p_param->mpStarted = 0;
                break;
            default:
                p_param->callback(CALLBACK_ERROR, arg);
                break;
            }
            break;
        case APIID_START_MP:
            switch (cb[2])
            {
            case 12:
            case 13:
                return;
            case 10:
                p_param->mpStarted = 1;
                if (MBi_IsSendEnabled())
                    p_param->callback(CALLBACK_SEND_READY, NULL);
                break;
            default:
                p_param->callback(CALLBACK_ERROR, arg);
                break;
            }
            break;
        case APIID_SET_MP_DATA:
            p_param->mpBusy = 0;
            if (cb[1] == ERRCODE_SUCCESS)
                p_param->callback(CALLBACK_MP_CHILD_SENT, arg);
            else if (cb[1] == 9)
                p_param->callback(0x29, arg);
            else
                p_param->callback(CALLBACK_MP_CHILD_SENT_ERR, arg);
            if (!p_mbi_param->endReq)
                p_param->callback(CALLBACK_SEND_READY, NULL);
            break;
        case APIID_RESET:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->endReq = 0;
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            p_param->child_bitmap = 0;
            p_mbi_param->mpStarted = 0;
            MBi_CheckWmErrcode(APIID_END, func_020d503c(MBi_ChildCallback));
            break;
        case APIID_END:
            if (cb[1] != ERRCODE_SUCCESS)
            {
                p_param->endReq = 0;
                p_param->callback(CALLBACK_ERROR, arg);
                return;
            }
            MBi_EndCommon(arg);
            break;
        case 0x15:
            if (MBi_IsSendEnabled())
                p_param->callback(CALLBACK_SEND_READY, NULL);
            break;
        case APIID_INDICATION:
            if (cb[2] == 0x16)
                func_020c9be0();
            break;
        default:
            p_param->callback(CALLBACK_ERROR, arg);
            break;
        }
    }
#else
    asm static void MBi_ChildCallback(void* arg)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
        sub sp, sp, #0x1c
        mov r6, r0
        ldrh r2, [r6, #0x0]
        ldr r1, =WM_DMA_NO
        cmp r2, #0x1d
        ldr r4, [r1, #0x8]
        bgt @L021dbe78
        cmp r2, #0x1d
        bge @L021dbee4
        cmp r2, #0x15
        addls pc, pc, r2, lsl #0x2
        b @L021dc5ec
    @L021dbe20:
        b @L021dbe84
        b @L021dc504
        b @L021dc564
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dbf80
        b @L021dc248
        b @L021dc298
        b @L021dc5ec
        b @L021dc410
        b @L021dc484
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5ec
        b @L021dc5a0
    @L021dbe78:
        cmp r2, #0x80
        beq @L021dc5c8
        b @L021dc5ec
    @L021dbe84:
        ldrh r0, [r6, #0x2]
        ldr r2, [r4, #0x51c]
        mov r1, r6
        cmp r0, #0x0
        beq @L021dbea8
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dbea8:
        mov r0, #0x15
        blx r2
        ldr r3, =mbi_life_frame
        ldr r0, =MBi_ChildCallback
        ldrh r1, [r3, #0x4]
        str r1, [sp, #0x0]
        ldrh r1, [r3, #0x6]
        ldrh r2, [r3, #0x2]
        ldrh r3, [r3, #0x0]
        bl func_020d6ad4
        mov r1, r0
        mov r0, #0x1d
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dbee4:
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        beq @L021dbf08
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dbf08:
        add r0, r4, #0x440
        str r0, [r1, #0x20]
        ldrh r0, [r1, #0x24]
        mov r2, #0x1
        cmp r0, #0x0
        moveq r0, #0x1
        streqh r0, [r1, #0x24]
        ldr r0, =WM_DMA_NO
        ldrh r1, [r0, #0x26]
        cmp r1, #0x0
        moveq r1, #0xc8
        streqh r1, [r0, #0x26]
        ldr r0, =WM_DMA_NO
        mov r1, #0xff
        strb r1, [r0, #0x28]
        strb r1, [r0, #0x29]
        strb r1, [r0, #0x2a]
        strb r1, [r0, #0x2b]
        strb r1, [r0, #0x2c]
        strb r1, [r0, #0x2d]
        str r2, [r4, #0x5e4]
        ldr r0, =MBi_ChildCallback
        ldr r1, =mbi_scan_param
        str r2, [r4, #0x5e8]
        bl func_020d5254
        mov r1, r0
        mov r0, #0xa
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dbf80:
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        beq @L021dbfa4
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dbfa4:
        ldrh r0, [r6, #0x8]
        cmp r0, #0x3
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        cmp r0, #0x4
        beq @L021dc1d0
        cmp r0, #0x5
        bne @L021dc230
        add r12, r4, #0x600
        mov r5, #0x0
        add r0, r4, #0x500
        mov r11, #0x180
        b @L021dc100
    @L021dbfd8:
        mla r2, r5, r11, r12
        ldrb r3, [r6, #0xa]
        ldrb r1, [r2, #0xca]
        mov lr, #0x0
        mov r10, lr
        cmp r3, r1
        ldreqb r1, [r2, #0xcb]
        ldreqb r2, [r6, #0xb]
        mov r7, lr
        mov r8, lr
        cmpeq r2, r1
        moveq r10, #0x1
        mov r9, lr
        cmp r10, #0x0
        beq @L021dc02c
        mov r2, #0x180
        mla r2, r5, r2, r12
        ldrb r1, [r6, #0xc]
        ldrb r2, [r2, #0xcc]
        cmp r1, r2
        moveq r9, #0x1
    @L021dc02c:
        cmp r9, #0x0
        beq @L021dc04c
        mov r1, #0x180
        mla r1, r5, r1, r12
        ldrb r2, [r6, #0xd]
        ldrb r1, [r1, #0xcd]
        cmp r2, r1
        moveq r8, #0x1
    @L021dc04c:
        cmp r8, #0x0
        beq @L021dc06c
        mov r1, #0x180
        mla r1, r5, r1, r12
        ldrb r2, [r6, #0xe]
        ldrb r1, [r1, #0xce]
        cmp r2, r1
        moveq r7, #0x1
    @L021dc06c:
        cmp r7, #0x0
        beq @L021dc08c
        mov r1, #0x180
        mla r1, r5, r1, r12
        ldrb r2, [r6, #0xf]
        ldrb r1, [r1, #0xcf]
        cmp r2, r1
        moveq lr, #0x1
    @L021dc08c:
        cmp lr, #0x0
        beq @L021dc0fc
        mov r0, #0x180
        mla r0, r5, r0, r12
        ldrh r1, [r6, #0x36]
        add r9, r6, #0x38
        add r8, r0, #0xf8
        strh r1, [r0, #0xf6]
        mov r7, #0x8
    @L021dc0b0:
        ldmia r9!, {r0, r1, r2, r3}
        stmia r8!, {r0, r1, r2, r3}
        subs r7, r7, #0x1
        bne @L021dc0b0
        add r1, r4, #0x600
        mov r0, #0x180
        mla r0, r5, r0, r1
        mov r1, #0xc0
        bl InvalidateDataCacheRange
        ldr r1, =WM_DMA_NO
        add r2, r4, #0x600
        mov r0, #0x180
        mla r2, r5, r0, r2
        ldrh r0, [r1, #0x0]
        add r1, r4, #0x440
        mov r3, #0xc0
        bl DMAMemcpySynchronous16Bit
        str r5, [r4, #0x5ec]
        b @L021dc170
    @L021dc0fc:
        add r5, r5, #0x1
    @L021dc100:
        ldrh r1, [r0, #0xe0]
        cmp r5, r1
        blt @L021dbfd8
        cmp r5, #0x10
        bge @L021dc170
        mov r0, #0x180
        mla r1, r5, r0, r12
        mov r0, r6
        add r7, r5, #0x1
        add r3, r4, #0x500
        add r1, r1, #0xc0
        mov r2, #0xb8
        strh r7, [r3, #0xe0]
        bl func_020ca3b8
        add r1, r4, #0x600
        mov r0, #0x180
        mla r0, r5, r0, r1
        mov r1, #0xc0
        bl InvalidateDataCacheRange
        ldr r1, =WM_DMA_NO
        add r2, r4, #0x600
        mov r0, #0x180
        mla r2, r5, r0, r2
        ldrh r0, [r1, #0x0]
        add r1, r4, #0x440
        mov r3, #0xc0
        bl DMAMemcpySynchronous16Bit
        str r5, [r4, #0x5ec]
    @L021dc170:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x4
        blx r2
        ldr r0, [r4, #0x5e4]
        cmp r0, #0x0
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r0, [r4, #0x5e8]
        cmp r0, #0x0
        beq @L021dc1b0
        ldr r0, =mbi_scan_param
        bl changeScanChannel
        cmp r0, #0x0
        bne @L021dc1b0
        bl MBi_CommEnd
    @L021dc1b0:
        ldr r0, =MBi_ChildCallback
        ldr r1, =mbi_scan_param
        bl func_020d5254
        mov r1, r0
        mov r0, #0xa
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc1d0:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x5
        blx r2
        ldr r0, [r4, #0x5e4]
        cmp r0, #0x0
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r0, [r4, #0x5e8]
        cmp r0, #0x0
        beq @L021dc210
        ldr r0, =mbi_scan_param
        bl changeScanChannel
        cmp r0, #0x0
        bne @L021dc210
        bl MBi_CommEnd
    @L021dc210:
        ldr r0, =MBi_ChildCallback
        ldr r1, =mbi_scan_param
        bl func_020d5254
        mov r1, r0
        mov r0, #0xa
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc230:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc248:
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        beq @L021dc26c
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc26c:
        ldr r1, [r4, #0x520]
        mov r2, #0x0
        ldr r0, =MBi_ChildCallback
        mov r3, #0x1
        str r2, [sp, #0x0]
        bl func_020d54d0
        mov r1, r0
        mov r0, #0xc
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc298:
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        beq @L021dc2c8
        add r0, r4, #0x500
        mov r1, #0x0
        strh r1, [r0, #0xe0]
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0xb
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc2c8:
        ldrh r0, [r6, #0x8]
        cmp r0, #0x9
        bgt @L021dc2f4
        cmp r0, #0x6
        blt @L021dc3f8
        beq @L021dc304
        cmp r0, #0x7
        beq @L021dc320
        cmp r0, #0x9
        beq @L021dc3d0
        b @L021dc3f8
    @L021dc2f4:
        cmp r0, #0x1a
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        b @L021dc3f8
    @L021dc304:
        add r0, r4, #0x500
        mov r1, #0x0
        strh r1, [r0, #0x2a]
        mov r1, #0x1
        strh r1, [r0, #0x28]
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc320:
        ldrh r2, [r6, #0xa]
        add r0, r4, #0x500
        mov r1, r6
        strh r2, [r0, #0xe2]
        ldr r2, [r4, #0x51c]
        mov r0, #0x6
        blx r2
        ldr r1, =MBi_ChildPortCallback
        add r3, r4, #0x500
        mov r0, #0x1
        mov r2, #0x0
        strh r0, [r3, #0x2a]
        bl func_020d4770
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        add r0, r4, #0x500
        ldrh r0, [r0, #0x2c]
        add r1, r4, #0x500
        ldrh r2, [r1, #0x18]
        cmp r0, #0x0
        movne r0, #0x0
        moveq r0, #0x1
        mov r0, r0, lsl #0x10
        mov r0, r0, lsr #0x10
        str r2, [sp, #0x0]
        str r0, [sp, #0x4]
        mov r0, #0x0
        str r0, [sp, #0x8]
        str r0, [sp, #0xc]
        str r0, [sp, #0x10]
        mov r0, #0x1
        str r0, [sp, #0x14]
        str r0, [sp, #0x18]
        ldrh r2, [r1, #0x1a]
        ldr r1, [r4, #0x504]
        ldr r0, =MBi_ChildCallback
        add r3, r4, #0x40
        bl func_020d57f4
        mov r1, r0
        mov r0, #0xe
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc3d0:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0xa
        blx r2
        add r0, r4, #0x500
        mov r1, #0x0
        strh r1, [r0, #0x2a]
        strh r1, [r0, #0x28]
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc3f8:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc410:
        ldrh r0, [r6, #0x4]
        cmp r0, #0xa
        beq @L021dc438
        cmp r0, #0xc
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        cmp r0, #0xd
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        b @L021dc46c
    @L021dc438:
        add r0, r4, #0x500
        mov r1, #0x1
        strh r1, [r0, #0x28]
        bl MBi_IsSendEnabled
        cmp r0, #0x0
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r2, [r4, #0x51c]
        mov r0, #0x19
        mov r1, #0x0
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc46c:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc484:
        mov r0, #0x0
        strb r0, [r4, #0x50c]
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        bne @L021dc4ac
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x8
        blx r2
        b @L021dc4d0
    @L021dc4ac:
        cmp r0, #0x9
        ldr r2, [r4, #0x51c]
        mov r1, r6
        bne @L021dc4c8
        mov r0, #0x29
        blx r2
        b @L021dc4d0
    @L021dc4c8:
        mov r0, #0x12
        blx r2
    @L021dc4d0:
        ldr r0, =WM_DMA_NO
        ldr r0, [r0, #0x8]
        add r0, r0, #0x500
        ldrh r0, [r0, #0x26]
        cmp r0, #0x0
        addne sp, sp, #0x1c
        ldmneia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r2, [r4, #0x51c]
        mov r0, #0x19
        mov r1, #0x0
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc504:
        ldrh r0, [r6, #0x2]
        cmp r0, #0x0
        add r0, r4, #0x500
        beq @L021dc534
        mov r1, #0x0
        strh r1, [r0, #0x26]
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc534:
        mov r2, #0x0
        strh r2, [r0, #0x2a]
        ldr r1, [r1, #0x8]
        ldr r0, =MBi_ChildCallback
        add r1, r1, #0x500
        strh r2, [r1, #0x28]
        bl func_020d503c
        mov r1, r0
        mov r0, #0x2
        bl MBi_CheckWmErrcode
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc564:
        ldrh r1, [r6, #0x2]
        cmp r1, #0x0
        beq @L021dc594
        add r0, r4, #0x500
        mov r1, #0x0
        strh r1, [r0, #0x26]
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc594:
        bl MBi_EndCommon
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc5a0:
        bl MBi_IsSendEnabled
        cmp r0, #0x0
        addeq sp, sp, #0x1c
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r2, [r4, #0x51c]
        mov r0, #0x19
        mov r1, #0x0
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc5c8:
        ldrh r0, [r6, #0x4]
        cmp r0, #0x16
        beq @L021dc5e0
        add sp, sp, #0x1c
        cmp r0, #0x17
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc5e0:
        bl func_020c9be0
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    @L021dc5ec:
        ldr r2, [r4, #0x51c]
        mov r1, r6
        mov r0, #0x100
        blx r2
        add sp, sp, #0x1c
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    }
#endif

    static unsigned long MBi_GetBeaconPeriodDispersion()
    {
        unsigned char mac[6];
        unsigned long ret;
        int i;
        func_020c99ac(mac);
        for (i = 0, ret = 0; i < 6; i++)
            ret += mac[i];
        ret += *(volatile unsigned long*)0x027ffc3c;
        ret *= 7;
        return ret % 20;
    }

    // NONMATCHING: the C matches 97.5 %: in the loop that copies "multiboot", the original counts before it saves the
    // pointer.
#ifdef NONMATCHING
    int MB_Init(void* work, const MBUserInfo* user, unsigned long ggid, unsigned long tgid, unsigned long dma)
    {
        if (pPwork != NULL && pPwork->isMbInitialized)
            return 2;
        MBiParam* const param = (MBiParam*)(((unsigned long)work + 31) & ~31);
        MB_CommPWork* const pwork = (MB_CommPWork*)(((unsigned long)param + sizeof(MBiParam) + 31) & ~31);
        if (tgid == 0x10000)
            tgid = func_020d4dd4();
        {
            int lastState = DisableIRQInterrupts();
            mbi_life_table = 0xffff;
            mbi_life_frame = 5;
            mbi_life_camera = 0x28;
            mbi_life_mp = 0x28;
            mbi_power_save_mode = true;
            WM_DMA_NO = dma;
            p_mbi_param = param;
            pPwork = pwork;
            func_020ca3ec(0, param, sizeof(MBiParam));
            func_020ca390(0, pwork, COMMON_WORK_SIZE);
            {
                int i;
                unsigned short* dst = param->uname;
                for (i = 0; i < user->nameLength; i++)
                    *dst++ = user->name[i];
                dst = param->ssid;
                for (i = 0; i < 16; i++)
                {
                    unsigned short c = *mbi_ssid_ptr;
                    if (c == 0)
                        break;
                    mbi_ssid_ptr++;
                    *dst++ = c;
                }
            }
            VectorizedInvertedMemcpy(user, &pwork->user, sizeof(MBUserInfo));
            if (user->nameLength < 10)
                pwork->user.name[user->nameLength] = 0;
            param->parentMaxSize = 0x100;
            param->childMaxSize = 8;
            param->sendBufSize = 0;
            param->recvBufSize = 0;
            param->contSend = 1;
            param->recvBuf = pwork->recvbuf;
            param->parentParam.entryFlag = 0;
            param->parentParam.multiBootFlag = 0;
            param->parentParam.CS_Flag = 1;
            param->parentParam.KS_Flag = 0;
            param->parentParam.ggid = ggid;
            param->parentParam.tgid = tgid;
            param->parentParam.beaconPeriod = MBi_GetBeaconPeriodDispersion() + 200;
            param->parentParam.maxEntry = 15;
            param->mpBusy = 0;
            param->mbIsStarted = 0;
            pwork->isMbInitialized = 1;
            pwork->start_mp_busy = 0;
            SetIRQInterruptState(lastState);
        }
        return 0;
    }
#else
    asm int MB_Init(void* work, const MBUserInfo* user, unsigned long ggid, unsigned long tgid, unsigned long dma)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
        ldr r4, =WM_DMA_NO
        mov r9, r1
        ldr r1, [r4, #0xc]
        mov r8, r2
        cmp r1, #0x0
        addne r1, r1, #0x1300
        ldrneh r1, [r1, #0x16]
        mov r7, r3
        cmpne r1, #0x0
        movne r0, #0x2
        ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
        add r0, r0, #0x1f
        bic r4, r0, #0x1f
        add r0, r4, #0x1f
        add r0, r0, #0x1e00
        cmp r7, #0x10000
        bic r5, r0, #0x1f
        bne @L021dc6d4
        bl func_020d4dd4
        mov r7, r0
    @L021dc6d4:
        bl DisableIRQInterrupts
        ldr r3, =0xffff
        ldr r1, =mbi_life_frame
        mov r2, #0x5
        strh r3, [r1, #0x6]
        strh r2, [r1, #0x0]
        mov r2, #0x28
        strh r2, [r1, #0x2]
        mov r6, r0
        strh r2, [r1, #0x4]
        mov r2, #0x1
        ldr r0, [sp, #0x20]
        ldr r3, =WM_DMA_NO
        str r2, [r1, #0xc]
        strh r0, [r3, #0x0]
        str r4, [r3, #0x8]
        mov r1, r4
        mov r0, #0x0
        mov r2, #0x1e00
        str r5, [r3, #0xc]
        bl func_020ca3ec
        mov r1, r5
        mov r0, #0x0
        mov r2, #0x1340
        bl func_020ca390
        ldrb r0, [r9, #0x1]
        add r2, r4, #0x530
        mov r1, #0x0
        cmp r0, #0x0
        ble @L021dc768
    @L021dc74c:
        add r0, r9, r1, lsl #0x1
        ldrh r0, [r0, #0x2]
        add r1, r1, #0x1
        strh r0, [r2], #0x2
        ldrb r0, [r9, #0x1]
        cmp r1, r0
        blt @L021dc74c
    @L021dc768:
        add r0, r4, #0x138
        add r3, r0, #0x400
        ldr r0, =mbi_life_frame
        mov r12, #0x0
        ldr r1, [r0, #0x8]
    @L021dc77c:
        ldrh r2, [r1, #0x0]
        cmp r2, #0x0
        beq @L021dc7a0
        add r1, r1, #0x2
        add r12, r12, #0x1
        str r1, [r0, #0x8]
        cmp r12, #0x10
        strh r2, [r3], #0x2
        blt @L021dc77c
    @L021dc7a0:
        mov r0, r9
        add r1, r5, #0x1300
        mov r2, #0x16
        bl VectorizedInvertedMemcpy
        ldrb r0, [r9, #0x1]
        cmp r0, #0xa
        bhs @L021dc7cc
        add r0, r5, r0, lsl #0x1
        add r0, r0, #0x1300
        mov r1, #0x0
        strh r1, [r0, #0x2]
    @L021dc7cc:
        add r0, r4, #0x500
        mov r1, #0x100
        strh r1, [r0, #0x0]
        mov r1, #0x8
        strh r1, [r0, #0x2]
        mov r2, #0x0
        strh r2, [r0, #0x18]
        strh r2, [r0, #0x1a]
        mov r1, #0x1
        strh r1, [r0, #0x2c]
        add r0, r5, #0x400
        str r0, [r4, #0x504]
        strh r2, [r4, #0xe]
        strh r2, [r4, #0x12]
        strh r1, [r4, #0x16]
        strh r2, [r4, #0x14]
        str r8, [r4, #0x8]
        strh r7, [r4, #0xc]
        bl MBi_GetBeaconPeriodDispersion
        add r0, r0, #0xc8
        strh r0, [r4, #0x18]
        mov r0, #0xf
        strh r0, [r4, #0x10]
        mov r3, #0x0
        strb r3, [r4, #0x50c]
        strb r3, [r4, #0x50d]
        add r1, r5, #0x1300
        mov r2, #0x1
        mov r0, r6
        strh r2, [r1, #0x16]
        add r1, r5, #0x1000
        str r3, [r1, #0x31c]
        bl SetIRQInterruptState
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    }
#endif

    static int MBi_IsCommSizeValid(unsigned short sendSize, unsigned short recvSize, unsigned short entry_num)
    {
        if (sendSize > 0x1fe || sendSize < 0xe4)
            return false;
        if (recvSize > 0x10 || recvSize < 8)
            return false;
        return (sendSize + 38) * 4 + 330 + entry_num * ((recvSize + 32) * 4 + 112) < 5600;
    }

    int MB_SetParentCommParam(unsigned short sendSize, unsigned short maxChildren)
    {
        int lastState = DisableIRQInterrupts();
        if (p_mbi_param->mbIsStarted)
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        if (!MBi_IsCommSizeValid(sendSize, 8, maxChildren))
        {
            SetIRQInterruptState(lastState);
            return false;
        }
        p_mbi_param->parentParam.maxEntry = maxChildren;
        p_mbi_param->parentMaxSize = sendSize;
        p_mbi_param->childMaxSize = 8;
        SetIRQInterruptState(lastState);
        return true;
    }

    static int MBi_StartCommon()
    {
        int ret;
        p_mbi_param->mpStarted = 0;
        p_mbi_param->child_bitmap = 0;
        p_mbi_param->endReq = 0;
        p_mbi_param->unk_548 = 0;
        MBi_SetMaxScanTime(10);
        if (!pPwork->is_started_ex)
        {
            do
            {
                ret = func_020d4f7c(wmBuf, p_mbi_param->callback_ptr, WM_DMA_NO);
            } while (ret == ERRCODE_INVALID_PARAM);
            if (ret != ERRCODE_OPERATING)
                return 8;
            func_020d472c(p_mbi_param->callback_ptr);
            p_mbi_param->mbIsStarted = 1;
            return 0;
        }
        else
        {
            func_020d472c(p_mbi_param->callback_ptr);
            p_mbi_param->mbIsStarted = 1;
            MBi_OnInitializeDone();
        }
        return 0;
    }

    static int MBi_StartParentCore(int channel)
    {
        int i;
        int ret;
        int lastState = DisableIRQInterrupts();
        p_mbi_param->parentParam.channel = channel;
        wmBuf = (void*)(((unsigned long)pPwork + sizeof(MB_CommPWork) + 31) & ~31);
        {
            MBCommPStateCallback callback = pPwork->parent_callback;
            func_020ca390(0, (unsigned char*)pPwork + COMMON_WORK_SIZE, sizeof(MB_CommPWork) - COMMON_WORK_SIZE);
            MB_CommSetParentStateCallback(callback);
        }
        pPwork->block_size = p_mbi_param->parentMaxSize - 6;
        MBi_SetChildMPMaxSize(p_mbi_param->childMaxSize);
        MBi_SetParentPieceBuffer(pPwork->req_data_buf);
        for (i = 0; i < MB_MAX_CHILD; i++)
        {
            pPwork->p_comm_state[i] = MB_COMM_PSTATE_NONE;
            pPwork->fileid_of_child[i] = -1;
        }
        pPwork->file_num = 0;
        func_020ca390(0, pPwork->fileinfo, sizeof(pPwork->fileinfo));
        VectorizedMemset(pPwork->req2child, 0, sizeof(pPwork->req2child));
        p_mbi_param->mode = MODE_PARENT;
        p_mbi_param->callback = MBi_CommParentCallback;
        p_mbi_param->callback_ptr = MBi_ParentCallback;
        p_mbi_param->parentParam.parentMaxSize = p_mbi_param->parentMaxSize;
        p_mbi_param->sendBufSize = (p_mbi_param->parentParam.parentMaxSize + 0x23) & ~0x1f;
        p_mbi_param->parentParam.childMaxSize = p_mbi_param->childMaxSize;
        p_mbi_param->recvBufSize = (((p_mbi_param->parentParam.childMaxSize + 0xe) * 15 + 0x29) & ~0x1f) * 2;
        MB_InitSendGameInfoStatus();
        ret = MBi_StartCommon();
        SetIRQInterruptState(lastState);
        pPwork->useWvrFlag = IsIPCCommandHandlerRegistered(0xf, IPCSide_Arm7);
        return ret;
    }

    int MB_StartParentFromIdle(int channel)
    {
        pPwork->is_started_ex = true;
        return MBi_StartParentCore(channel);
    }

    static int MBi_CallReset()
    {
        int ret = func_020d5004(p_mbi_param->callback_ptr);
        MBi_CheckWmErrcode(APIID_RESET, ret);
        if (ret == ERRCODE_OPERATING)
            ret = ERRCODE_SUCCESS;
        return ret;
    }

    static void MBi_OnReset(MBiTaskInfo* task)
    {
        MBi_CallReset();
    }

    static int MBi_CommEnd()
    {
        int ret = ERRCODE_FAILED;
        int lastState = DisableIRQInterrupts();
        if (!p_mbi_param->mbIsStarted)
        {
            MBi_EndCommon(NULL);
        }
        else if (!p_mbi_param->endReq)
        {
            p_mbi_param->scanning_flag = false;
            p_mbi_param->endReq = 1;
            if (MBi_IsTaskAvailable())
            {
                MBi_EndTaskThread(MBi_OnReset);
                ret = ERRCODE_SUCCESS;
            }
            else
            {
                ret = MBi_CallReset();
            }
        }
        SetIRQInterruptState(lastState);
        return ret;
    }

    void MB_End()
    {
        int lastState = DisableIRQInterrupts();
        if (!pPwork->is_started_ex)
            func_020c9be0();
        MBi_CommEnd();
        SetIRQInterruptState(lastState);
    }

    // NONMATCHING: the C matches 82.8 %: the original adds the file's offset to pPwork before the fields', where the
    // compiler adds the fields' first and indexes with the file's offset.
#ifdef NONMATCHING
    void MB_DisconnectChild(unsigned short aid)
    {
        func_020d559c(MBi_ParentCallback, aid);
        if (aid == 0 || aid >= 16)
            return;
        pPwork->childversion[aid - 1] = 0;
        VectorizedMemset(&pPwork->childggid[aid - 1], 0, sizeof(unsigned long));
        VectorizedMemset(&pPwork->childUser[aid - 1], 0, sizeof(MBUserInfo));
        MBi_ClearParentPieceBuffer(aid);
        pPwork->req2child[aid - 1] = 0;
        if (pPwork->fileid_of_child[aid - 1] != -1)
        {
            const unsigned char fileid = pPwork->fileid_of_child[aid - 1];
            pPwork->fileinfo[fileid].gameinfo_child_bmp &= ~(1 << aid);
            pPwork->fileinfo[fileid].gameinfo_changed_bmp |= 1 << aid;
            pPwork->fileid_of_child[aid - 1] = -1;
            pPwork->fileinfo[fileid].pollbmp &= ~(1 << aid);
        }
        if (pPwork->child_entry_bmp & (1 << aid))
        {
            pPwork->child_num--;
            pPwork->child_entry_bmp &= ~(1 << aid);
        }
        pPwork->p_comm_state[aid - 1] = MB_COMM_PSTATE_NONE;
    }
#else
    asm void MB_DisconnectChild(unsigned short aid)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, lr}
        mov r5, r0
        ldr r0, =MBi_ParentCallback
        mov r1, r5
        bl func_020d559c
        cmp r5, #0x0
        ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
        cmp r5, #0x10
        ldmhsia sp!, {r3, r4, r5, r6, r7, pc}
        ldr r2, =WM_DMA_NO
        sub r4, r5, #0x1
        ldr r0, [r2, #0xc]
        mov r1, #0x0
        add r0, r0, r4, lsl #0x1
        add r0, r0, #0x1400
        strh r1, [r0, #0x8a]
        ldr r0, [r2, #0xc]
        mov r2, #0x4
        add r0, r0, #0xa8
        add r0, r0, #0x1400
        add r0, r0, r4, lsl #0x2
        bl VectorizedMemset
        ldr r0, =WM_DMA_NO
        mov r2, #0x16
        ldr r0, [r0, #0xc]
        mov r1, #0x0
        add r0, r0, #0x1340
        mla r0, r4, r2, r0
        bl VectorizedMemset
        mov r0, r5
        bl MBi_ClearParentPieceBuffer
        ldr r12, =WM_DMA_NO
        mov r2, #0x0
        ldr r0, [r12, #0xc]
        sub r1, r2, #0x1
        add r0, r0, r4, lsl #0x1
        add r0, r0, #0x1700
        strh r2, [r0, #0x54]
        ldr r3, [r12, #0xc]
        add r0, r3, r4
        add r0, r0, #0x1500
        ldrsb r2, [r0, #0x26]
        cmp r2, r1
        beq @L021dce7c
        ldr r0, =0x5d4
        and r1, r2, #0xff
        mul r0, r1, r0
        add r1, r3, r0
        add r3, r1, #0x1d00
        mov r2, #0x1
        ldrh r6, [r3, #0x4e]
        mvn r1, r2, lsl r5
        and r6, r6, r1
        strh r6, [r3, #0x4e]
        ldr r3, [r12, #0xc]
        sub r6, r2, #0x2
        add r3, r3, r0
        add r3, r3, #0x1d00
        ldrh r7, [r3, #0x50]
        mov lr, r4
        orr r2, r7, r2, lsl r5
        strh r2, [r3, #0x50]
        ldr r2, [r12, #0xc]
        add r2, r2, lr
        add r2, r2, #0x1000
        strb r6, [r2, #0x526]
        ldr r2, [r12, #0xc]
        add r0, r2, r0
        add r0, r0, #0x1d00
        ldrh r2, [r0, #0x4c]
        and r1, r2, r1
        strh r1, [r0, #0x4c]
    @L021dce7c:
        ldr r1, =WM_DMA_NO
        mov r12, #0x1
        ldr r2, [r1, #0xc]
        add r0, r2, #0x1500
        ldrh r0, [r0, #0x36]
        tst r0, r12, lsl r5
        beq @L021dcec0
        add r0, r2, #0x1000
        ldrb r3, [r0, #0x535]
        mvn r2, r12, lsl r5
        sub r3, r3, #0x1
        strb r3, [r0, #0x535]
        ldr r0, [r1, #0xc]
        add r0, r0, #0x1500
        ldrh r1, [r0, #0x36]
        and r1, r1, r2
        strh r1, [r0, #0x36]
    @L021dcec0:
        ldr r0, =WM_DMA_NO
        mov r1, #0x0
        ldr r0, [r0, #0xc]
        add r0, r0, r4, lsl #0x2
        add r0, r0, #0x1000
        str r1, [r0, #0x4e8]
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    }
#endif

    void MBi_SetMaxScanTime(unsigned short time)
    {
        mbi_scan_param.maxChannelTime = time;
    }

    static int MBi_SetMPData(WMCallbackFunc callback, const void* sendData, unsigned short sendDataSize,
                             unsigned short tmptt, unsigned short pollbmp)
    {
        int ret = func_020d59bc(callback, NULL, sendData, sendDataSize, pollbmp, 1, 3);
        MBi_CheckWmErrcode(APIID_SET_MP_DATA, ret);
        return ret;
    }

    int MBi_SendMP(const void* buf, int len, int pollbmp)
    {
        int ret;
        const unsigned short size = len;
        const unsigned short bitmap = pollbmp;
        if (!p_mbi_param->mpStarted || p_mbi_param->endReq == 1)
            return ERRCODE_FAILED;
        switch (p_mbi_param->mode)
        {
        case MODE_PARENT:
            ret = MBi_SetMPData(p_mbi_param->callback_ptr, buf, size, !p_mbi_param->contSend ? 1000 : 0, bitmap);
            if (ret == ERRCODE_OPERATING)
                p_mbi_param->mpBusy = 1;
            if (ret == ERRCODE_OPERATING)
                ret = ERRCODE_SUCCESS;
            return ret;
        case MODE_CHILD:
            ret = MBi_SetMPData(MBi_ChildCallback, buf, size, 0, bitmap);
            if (ret == ERRCODE_OPERATING)
                p_mbi_param->mpBusy = 1;
            if (ret == ERRCODE_OPERATING)
                ret = ERRCODE_SUCCESS;
            return ret;
        default:
            return ERRCODE_FAILED;
        }
    }

    unsigned long MBi_GetGgid()
    {
        return p_mbi_param->parentParam.ggid;
    }

    unsigned short MBi_GetTgid()
    {
        return p_mbi_param->parentParam.tgid;
    }

    unsigned char MBi_GetAttribute()
    {
        return (p_mbi_param->parentParam.entryFlag ? 1 : 0) | (p_mbi_param->parentParam.multiBootFlag ? 2 : 0) |
               (p_mbi_param->parentParam.KS_Flag ? 4 : 0) | (p_mbi_param->parentParam.CS_Flag ? 8 : 0);
    }

    int MBi_IsStarted()
    {
        return p_mbi_param->mbIsStarted == 1 ? true : false;
    }

    static void MBi_CheckWmErrcode(unsigned short apiid, int errcode)
    {
        unsigned short arg[2];
        if (errcode != ERRCODE_OPERATING && errcode != ERRCODE_SUCCESS)
        {
            arg[0] = apiid;
            arg[1] = errcode;
            p_mbi_param->callback(CALLBACK_API_ERROR, arg);
        }
    }
}
