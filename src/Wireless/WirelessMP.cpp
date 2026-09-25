#include "Wireless/WirelessManager.h"
#include "System/Cache.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_mp.c: starts and ends MP communication, where the parent polls the children each frame, and
// sets the data that it sends

// WM_SIZE_MP_DATA_MAX: the most that MP communication sends at once
#define MP_DATA_MAX 0x200

// Which members of WMMPParam and WMMPTmpParam are set (WM_MP_PARAM_*)
#define MP_PARAM_MIN_FREQUENCY 0x1
#define MP_PARAM_FREQUENCY 0x2
#define MP_PARAM_MAX_FREQUENCY 0x4
#define MP_PARAM_PARENT_VCOUNT 0x80
#define MP_PARAM_CHILD_VCOUNT 0x100
#define MP_PARAM_DEFAULT_RETRY_COUNT 0x200
#define MP_PARAM_MIN_POLL_BMP_MODE 0x400
#define MP_PARAM_SINGLE_PACKET_MODE 0x800
#define MP_PARAM_IGNORE_FATAL_ERROR_MODE 0x1000

// The parameters of MP communication (WMMPParam)
struct WMMPParam
{
    unsigned long mask;
    unsigned short minFrequency;
    unsigned short frequency;
    unsigned short maxFrequency;
    unsigned short parentSize;
    unsigned short childSize;
    unsigned short parentInterval;
    unsigned short childInterval;
    unsigned short parentVCount;
    unsigned short childVCount;
    unsigned short defaultRetryCount;
    unsigned char minPollBmpMode;
    unsigned char singlePacketMode;
    unsigned char ignoreFatalErrorMode;
    unsigned char ignoreSizePrecheckMode;
};

// The parameters that last until MP communication ends (WMMPTmpParam)
struct WMMPTmpParam
{
    unsigned long mask;
    unsigned short minFrequency;
    unsigned short frequency;
    unsigned short maxFrequency;
    unsigned short defaultRetryCount;
    unsigned char minPollBmpMode;
    unsigned char singlePacketMode;
    unsigned char ignoreFatalErrorMode;
    unsigned char reserved[1];
};

// The commands that the functions send to the ARM7
struct WMStartMPReq
{
    unsigned short apiid;
    unsigned short reserved;
    unsigned long* recvBuf;
    unsigned long recvBufSize;
    unsigned long* sendBuf;
    unsigned long sendBufSize;
    WMMPParam param;
    WMMPTmpParam tmpParam;
};

struct WMSetMPParameterReq
{
    unsigned short apiid;
    unsigned short reserved;
    WMMPParam param;
};

extern "C"
{
    // MIi_CpuClear32 and MIi_CpuCopy32
    void func_020ca3ec(unsigned long value, void* dst, unsigned long size);
    void func_020ca408(const void* src, void* dst, unsigned long size);
    // WM_GetMPReceiveBufferSize and WM_GetMPSendBufferSize
    int func_020d4900();
    int func_020d4894();

    int func_020d5900(WMCallbackFunc callback, const WMMPParam* param);

    // WMi_StartMP
    static int func_020d5684(WMCallbackFunc callback, unsigned short* recvBuf, unsigned short recvBufSize,
                             unsigned short* sendBuf, unsigned short sendBufSize, const WMMPTmpParam* tmpParam)
    {
        int result;
        WMArm9Buf* const p = func_020d41d8();
        WMStatus* const status = p->status;
        result = func_020d424c(2, WM_STATE_PARENT, WM_STATE_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        // A child must stay awake
        InvalidateDataCacheRange(&status->aid, 2);
        InvalidateDataCacheRange(&status->pwrMgtMode, 2);
        if (status->aid != 0 && status->pwrMgtMode != 1)
            return WM_ERRCODE_ILLEGAL_STATE;
        InvalidateDataCacheRange(&status->mp_flag, 4);
        if (status->mp_flag == true)
            return WM_ERRCODE_ILLEGAL_STATE;
        if ((recvBufSize & 0x3f) != 0)
            return WM_ERRCODE_INVALID_PARAM;
        if ((sendBufSize & 0x1f) != 0)
            return WM_ERRCODE_INVALID_PARAM;
        InvalidateDataCacheRange(&status->mp_ignoreSizePrecheckMode, 2);
        if (status->mp_ignoreSizePrecheckMode == false)
        {
            if (recvBufSize < func_020d4900())
                return WM_ERRCODE_INVALID_PARAM;
            if (sendBufSize < func_020d4894())
                return WM_ERRCODE_INVALID_PARAM;
        }
        func_020d404c(WM_APIID_START_MP, callback);
        {
            WMStartMPReq req;
            func_020ca3ec(0, &req, sizeof(WMStartMPReq));
            req.apiid = WM_APIID_START_MP;
            req.recvBuf = (unsigned long*)recvBuf;
            // The ARM7 counts in halfwords
            req.recvBufSize = recvBufSize / 2;
            req.sendBuf = (unsigned long*)sendBuf;
            req.sendBufSize = sendBufSize;
            func_020ca3ec(0, &req.param, sizeof(WMMPParam));
            func_020ca408(tmpParam, &req.tmpParam, sizeof(WMMPTmpParam));
            result = func_020d4168(&req, sizeof(WMStartMPReq));
        }
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_StartMPEx
    int func_020d57f4(WMCallbackFunc callback, unsigned short* recvBuf, unsigned short recvBufSize,
                      unsigned short* sendBuf, unsigned short sendBufSize, unsigned short mpFreq,
                      unsigned short defaultRetryCount, int minPollBmpMode, int singlePacketMode, int fixFreqMode,
                      int ignoreFatalError)
    {
        WMMPTmpParam tmpParam;
        func_020ca3ec(0, &tmpParam, sizeof(WMMPTmpParam));
        tmpParam.mask = MP_PARAM_MIN_FREQUENCY | MP_PARAM_FREQUENCY | MP_PARAM_DEFAULT_RETRY_COUNT |
                        MP_PARAM_MIN_POLL_BMP_MODE | MP_PARAM_SINGLE_PACKET_MODE | MP_PARAM_IGNORE_FATAL_ERROR_MODE;
        tmpParam.minFrequency = mpFreq;
        tmpParam.frequency = mpFreq;
        tmpParam.defaultRetryCount = defaultRetryCount;
        tmpParam.minPollBmpMode = minPollBmpMode;
        tmpParam.singlePacketMode = singlePacketMode;
        tmpParam.ignoreFatalErrorMode = ignoreFatalError;
        if (fixFreqMode != false && mpFreq != 0)
        {
            tmpParam.mask |= MP_PARAM_MAX_FREQUENCY;
            tmpParam.maxFrequency = mpFreq;
        }
        return func_020d5684(callback, recvBuf, recvBufSize, sendBuf, sendBufSize, &tmpParam);
    }

    // WM_StartMP
    int func_020d5898(WMCallbackFunc callback, unsigned short* recvBuf, unsigned short recvBufSize,
                      unsigned short* sendBuf, unsigned short sendBufSize, unsigned short mpFreq)
    {
        WMMPTmpParam tmpParam;
        func_020ca3ec(0, &tmpParam, sizeof(WMMPTmpParam));
        tmpParam.mask = MP_PARAM_MIN_FREQUENCY | MP_PARAM_FREQUENCY;
        tmpParam.minFrequency = mpFreq;
        tmpParam.frequency = mpFreq;
        return func_020d5684(callback, recvBuf, recvBufSize, sendBuf, sendBufSize, &tmpParam);
    }

    // WM_SetMPParameter
    int func_020d5900(WMCallbackFunc callback, const WMMPParam* param)
    {
        int result;
        func_020d41d8();
        result = func_020d41e8();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d404c(WM_APIID_SET_MP_PARAMETER, callback);
        {
            WMSetMPParameterReq req;
            func_020ca3ec(0, &req, sizeof(WMSetMPParameterReq));
            req.apiid = WM_APIID_SET_MP_PARAMETER;
            func_020ca408(param, &req.param, sizeof(WMMPParam));
            result = func_020d4168(&req, sizeof(WMSetMPParameterReq));
        }
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetMPTiming: the V-counts where the parent and the children start MP communication
    int func_020d5974(WMCallbackFunc callback, unsigned short parentVCount, unsigned short childVCount)
    {
        WMMPParam param;
        func_020ca3ec(0, &param, sizeof(WMMPParam));
        param.mask = MP_PARAM_PARENT_VCOUNT | MP_PARAM_CHILD_VCOUNT;
        param.parentVCount = parentVCount;
        param.childVCount = childVCount;
        return func_020d5900(callback, &param);
    }

    // WM_SetMPDataToPortEx
    int func_020d59bc(WMCallbackFunc callback, void* arg, const unsigned short* sendData, unsigned short sendDataSize,
                      unsigned short destBitmap, unsigned short port, unsigned short prio)
    {
        int result;
        unsigned short childBitmap = 1;
        WMArm9Buf* const p = func_020d41d8();
        WMStatus* const status = p->status;
        result = func_020d424c(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&status->aid, 2);
        if (status->aid == 0)
        {
            InvalidateDataCacheRange(&status->child_bitmap, 2);
            childBitmap = status->child_bitmap;
            InvalidateDataCacheRange(&status->mp_readyBitmap, 2);
        }
        if (sendData == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (childBitmap == 0)
            return WM_ERRCODE_NO_CHILD;
        // The buffer mustn't be the one that MP communication is sending
        InvalidateDataCacheRange(&status->mp_sendBuf, 2);
        if ((unsigned long*)sendData == status->mp_sendBuf)
            return WM_ERRCODE_INVALID_PARAM;
        if (sendDataSize > MP_DATA_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        if (sendDataSize == 0)
            return WM_ERRCODE_INVALID_PARAM;
        CleanCacheRange(sendData, sendDataSize);
        result = func_020d40bc(WM_APIID_SET_MP_DATA, 7, sendData, sendDataSize, destBitmap, port, prio, callback, arg);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_EndMP
    int func_020d5aec(WMCallbackFunc callback)
    {
        int result;
        WMArm9Buf* const p = func_020d41d8();
        result = func_020d424c(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&p->status->mp_flag, 4);
        if (p->status->mp_flag == false)
            return WM_ERRCODE_ILLEGAL_STATE;
        func_020d404c(WM_APIID_END_MP, callback);
        result = func_020d40bc(WM_APIID_END_MP, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }
}
