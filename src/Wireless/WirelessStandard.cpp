#include "Wireless/WirelessManager.h"
#include "System/Cache.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_standard.c: the wireless manager's basic commands, which the ARM7 answers through the callbacks

// WM_SIZE_USER_GAMEINFO
#define USER_GAME_INFO_MAX 0x70
// WM_SIZE_MP_DATA_MAX? The most that MP communication sends at once
#define MP_DATA_MAX 0x200
// The headers of the key sharing's data, which the MP communication also sends
#define KEY_SHARING_PARENT_HEADER 0x2a
#define KEY_SHARING_CHILD_HEADER 6
// WM_SIZE_SCAN_EX_BUF
#define SCAN_EX_BUFFER_MAX 0x400
// WM_SIZE_SSID
#define SSID_MAX 32
// WM_SIZE_CHILD_SSID
#define CHILD_SSID_SIZE 24
// WM_NUM_MAX_CHILD
#define MAX_CHILDREN 15

// The options of WMi_InitializeEx (WM_INST_OPTION_*)
#define OPTION_SCAN_ONLY 1
#define OPTION_NO_INDICATION 2

// The parent's parameters (WMParentParam)
struct WMParentParam
{
    void* userGameInfo;
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
    unsigned short rsv1[4];
    unsigned short rsv2[8];
    unsigned short channel;
    unsigned short parentMaxSize;
    unsigned short childMaxSize;
    unsigned short rsv[4];
};

// The parameters of a scan (WMScanParam and WMScanExParam)
struct WMScanParam
{
    void* scanBuf;
    unsigned short channel;
    unsigned short maxChannelTime;
    unsigned char bssid[6];
};

struct WMScanExParam
{
    void* scanBuf;
    unsigned short scanBufSize;
    unsigned short channelList;
    unsigned short maxChannelTime;
    unsigned char bssid[6];
    unsigned short scanType;
    unsigned short ssidLength;
    unsigned char ssid[SSID_MAX];
    unsigned short ssidMatchLength;
    unsigned short rsv[2];
};

// The scans that look for an SSID (WM_SCANTYPE_ACTIVE_CUSTOM and WM_SCANTYPE_PASSIVE_CUSTOM)
#define SCANTYPE_CUSTOM 2

// The commands that the functions send to the ARM7
struct WMStartScanReq
{
    unsigned short apiid;
    unsigned short channel;
    void* scanBuf;
    unsigned short maxChannelTime;
    unsigned char bssid[6];
};

struct WMStartScanExReq
{
    unsigned short apiid;
    unsigned short channelList;
    void* scanBuf;
    unsigned short scanBufSize;
    unsigned short maxChannelTime;
    unsigned char bssid[6];
    unsigned short scanType;
    unsigned short ssidLength;
    unsigned char ssid[SSID_MAX];
    unsigned short ssidMatchLength;
    unsigned short rsv[2];
};

struct WMStartConnectReq
{
    unsigned short apiid;
    unsigned short reserved;
    const void* pInfo;
    unsigned char ssid[CHILD_SSID_SIZE];
    int powerSave;
    unsigned short reserved2;
    unsigned short authMode;
};

extern "C"
{
    // WM_Init
    int func_020d3dcc(void* sysBuf, unsigned short dmaNo);
    // WM_GetMPReceiveBufferSize and WM_GetMPSendBufferSize
    int func_020d4900();
    int func_020d4894();

    int func_020d4e58(WMCallbackFunc callback, unsigned long miscFlags);
    int func_020d4fa4(void* wmSysBuf, WMCallbackFunc callback, unsigned short dmaNo, unsigned long miscFlags);
    static int func_020d5158(const WMParentParam* param);
    int func_020d51a8(WMCallbackFunc callback, int powerSave);

    // WM_Enable
    int func_020d4e48(WMCallbackFunc callback)
    {
        return func_020d4e58(callback, 0);
    }

    // WMi_EnableEx
    int func_020d4e58(WMCallbackFunc callback, unsigned long miscFlags)
    {
        int result = func_020d424c(1, WM_STATE_READY);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_ENABLE, callback);
        {
            WMArm9Buf* const w9b = func_020d41d8();
            result = func_020d40bc(WM_APIID_ENABLE, 4, w9b->WM7, w9b->status, w9b->fifo7to9, miscFlags);
        }
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_Disable
    int func_020d4ebc(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_STOP);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_DISABLE, callback);
        result = func_020d40bc(WM_APIID_DISABLE, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_PowerOn
    int func_020d4efc(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_STOP);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_POWER_ON, callback);
        result = func_020d40bc(WM_APIID_POWER_ON, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_PowerOff
    int func_020d4f3c(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_POWER_OFF, callback);
        result = func_020d40bc(WM_APIID_POWER_OFF, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_Initialize
    int func_020d4f7c(void* wmSysBuf, WMCallbackFunc callback, unsigned short dmaNo)
    {
        return func_020d4fa4(wmSysBuf, callback, dmaNo, 0);
    }

    // WM_InitializeForListening
    int func_020d4f8c(void* wmSysBuf, WMCallbackFunc callback, unsigned short dmaNo, int indicateFlag)
    {
        unsigned long miscFlags = OPTION_SCAN_ONLY;
        if (!indicateFlag)
            miscFlags |= OPTION_NO_INDICATION;
        return func_020d4fa4(wmSysBuf, callback, dmaNo, miscFlags);
    }

    // WMi_InitializeEx
    int func_020d4fa4(void* wmSysBuf, WMCallbackFunc callback, unsigned short dmaNo, unsigned long miscFlags)
    {
        int result = func_020d3dcc(wmSysBuf, dmaNo);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_INITIALIZE, callback);
        {
            WMArm9Buf* const w9b = func_020d41d8();
            result = func_020d40bc(WM_APIID_INITIALIZE, 4, w9b->WM7, w9b->status, w9b->fifo7to9, miscFlags);
        }
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_Reset
    int func_020d5004(WMCallbackFunc callback)
    {
        int result = func_020d4204();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_RESET, callback);
        result = func_020d40bc(WM_APIID_RESET, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_End
    int func_020d503c(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_END, callback);
        result = func_020d40bc(WM_APIID_END, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetParentParameter
    int func_020d507c(WMCallbackFunc callback, const WMParentParam* param)
    {
        int result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (param == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->userGameInfoLength > 0 && param->userGameInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->parentMaxSize + (param->KS_Flag ? KEY_SHARING_PARENT_HEADER : 0) > MP_DATA_MAX ||
            param->childMaxSize + (param->KS_Flag ? KEY_SHARING_CHILD_HEADER : 0) > MP_DATA_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        func_020d5158(param);
        func_020d404c(WM_APIID_SET_P_PARAM, callback);
        CleanCacheRange(param, sizeof(WMParentParam));
        if (param->userGameInfoLength > 0)
            CleanCacheRange(param->userGameInfo, param->userGameInfoLength);
        result = func_020d40bc(WM_APIID_SET_P_PARAM, 1, param);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WmCheckParentParameter
    static int func_020d5158(const WMParentParam* param)
    {
        if (param->userGameInfoLength > USER_GAME_INFO_MAX)
            return false;
        if (param->beaconPeriod < 10 || param->beaconPeriod > 1000)
            return false;
        if (param->channel < 1 || param->channel > 14)
            return false;
        return true;
    }

    // WMi_StartParentEx
    int func_020d51a8(WMCallbackFunc callback, int powerSave)
    {
        int result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        {
            WMArm9Buf* const w9b = func_020d41d8();
            w9b->myAid = 0;
            w9b->connectedAidBitmap = 0;
        }
        func_020d404c(WM_APIID_START_PARENT, callback);
        result = func_020d40bc(WM_APIID_START_PARENT, 1, powerSave);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_StartParent
    int func_020d5204(WMCallbackFunc callback)
    {
        return func_020d51a8(callback, true);
    }

    // WM_EndParent
    int func_020d5214(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_PARENT);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_END_PARENT, callback);
        result = func_020d40bc(WM_APIID_END_PARENT, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_StartScan
    int func_020d5254(WMCallbackFunc callback, const WMScanParam* param)
    {
        WMStartScanReq req;
        int result = func_020d424c(3, WM_STATE_IDLE, WM_STATE_CLASS1, WM_STATE_SCAN);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (param == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->scanBuf == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->channel < 1 || param->channel > 14)
            return WM_ERRCODE_INVALID_PARAM;
        func_020d404c(WM_APIID_START_SCAN, callback);
        req.apiid = WM_APIID_START_SCAN;
        req.channel = param->channel;
        req.scanBuf = param->scanBuf;
        req.maxChannelTime = param->maxChannelTime;
        req.bssid[0] = param->bssid[0];
        req.bssid[1] = param->bssid[1];
        req.bssid[2] = param->bssid[2];
        req.bssid[3] = param->bssid[3];
        req.bssid[4] = param->bssid[4];
        req.bssid[5] = param->bssid[5];
        result = func_020d4168(&req, sizeof(WMStartScanReq));
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_StartScanEx
    int func_020d5340(WMCallbackFunc callback, const WMScanExParam* param)
    {
        WMStartScanExReq req;
        int result = func_020d424c(3, WM_STATE_IDLE, WM_STATE_CLASS1, WM_STATE_SCAN);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (param == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->scanBuf == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->scanBufSize > SCAN_EX_BUFFER_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->ssidLength > SSID_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        if (param->scanType != 0 && param->scanType != 1 && param->scanType != 2 && param->scanType != 3)
            return WM_ERRCODE_INVALID_PARAM;
        if ((param->scanType == SCANTYPE_CUSTOM || param->scanType == SCANTYPE_CUSTOM + 1) &&
            param->ssidMatchLength > SSID_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        func_020d404c(WM_APIID_START_SCAN_EX, callback);
        req.apiid = WM_APIID_START_SCAN_EX;
        req.channelList = param->channelList;
        req.scanBuf = param->scanBuf;
        req.scanBufSize = param->scanBufSize;
        req.maxChannelTime = param->maxChannelTime;
        VectorizedInvertedMemcpy(param->bssid, req.bssid, sizeof(req.bssid));
        req.scanType = param->scanType;
        req.ssidMatchLength = param->ssidMatchLength;
        req.ssidLength = param->ssidLength;
        VectorizedInvertedMemcpy(param->ssid, req.ssid, sizeof(req.ssid));
        result = func_020d4168(&req, sizeof(WMStartScanExReq));
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_EndScan
    int func_020d5490(WMCallbackFunc callback)
    {
        int result = func_020d424c(1, WM_STATE_SCAN);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_END_SCAN, callback);
        result = func_020d40bc(WM_APIID_END_SCAN, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_StartConnectEx
    int func_020d54d0(WMCallbackFunc callback, const void* pInfo, const unsigned char* ssid, int powerSave,
                      unsigned short authMode)
    {
        WMStartConnectReq req;
        int result = func_020d424c(1, WM_STATE_IDLE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (pInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        CleanCacheRange(pInfo, *(const unsigned short*)pInfo * 2);
        {
            WMArm9Buf* const w9b = func_020d41d8();
            w9b->myAid = 0;
            w9b->connectedAidBitmap = 0;
        }
        func_020d404c(WM_APIID_START_CONNECT, callback);
        req.apiid = WM_APIID_START_CONNECT;
        req.pInfo = pInfo;
        if (ssid != NULL)
            VectorizedInvertedMemcpy(ssid, req.ssid, CHILD_SSID_SIZE);
        else
            VectorizedMemset(req.ssid, 0, CHILD_SSID_SIZE);
        req.powerSave = powerSave;
        req.authMode = authMode;
        result = func_020d4168(&req, sizeof(WMStartConnectReq));
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_Disconnect
    int func_020d559c(WMCallbackFunc callback, unsigned short aid)
    {
        WMArm9Buf* const w9b = func_020d41d8();
        int result = func_020d424c(5, WM_STATE_PARENT, WM_STATE_MP_PARENT, WM_STATE_CHILD, WM_STATE_MP_CHILD,
                                   WM_STATE_DCF_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (w9b->status->state == WM_STATE_PARENT || w9b->status->state == WM_STATE_MP_PARENT)
        {
            if (aid < 1 || aid > MAX_CHILDREN)
                return WM_ERRCODE_INVALID_PARAM;
            InvalidateDataCacheRange(&w9b->status->child_bitmap, 2);
            if (!(w9b->status->child_bitmap & (1 << aid)))
                return WM_ERRCODE_NO_CHILD;
        }
        else if (aid != 0)
        {
            return WM_ERRCODE_INVALID_PARAM;
        }
        func_020d404c(WM_APIID_DISCONNECT, callback);
        result = func_020d40bc(WM_APIID_DISCONNECT, 1, 1 << aid);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }
}
