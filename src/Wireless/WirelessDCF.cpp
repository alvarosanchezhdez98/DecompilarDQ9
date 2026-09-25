#include "Wireless/WirelessManager.h"
#include "System/Cache.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_dcf.c: DCF communication, where a child that connected to an access point sends and receives
// ordinary wireless LAN frames

// WM_DCF_MAX_SIZE: the most that DCF communication sends at once
#define DCF_DATA_MAX 0x5e4
// The smallest buffer that WM_StartDCF takes (the header of WMDcfRecvBuf)
#define DCF_RECV_BUFFER_MIN 0x10

extern "C"
{
    // WM_StartDCF
    int func_020d5b5c(WMCallbackFunc callback, void* recvBuf, unsigned short recvBufSize)
    {
        int result;
        WMArm9Buf* const p = func_020d41d8();
        result = func_020d424c(1, WM_STATE_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&p->status->dcf_flag, 4);
        if (p->status->dcf_flag == true)
            return WM_ERRCODE_ILLEGAL_STATE;
        if (recvBufSize < DCF_RECV_BUFFER_MIN)
            return WM_ERRCODE_INVALID_PARAM;
        if (recvBuf == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        CleanCacheRange(recvBuf, recvBufSize);
        func_020d404c(WM_APIID_START_DCF, callback);
        result = func_020d40bc(WM_APIID_START_DCF, 2, recvBuf, recvBufSize);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_SetDCFData
    int func_020d5bfc(WMCallbackFunc callback, const unsigned char* destAdr, const unsigned short* sendData,
                      unsigned short sendDataSize)
    {
        int result;
        unsigned long wMac[2];
        WMArm9Buf* const p = func_020d41d8();
        result = func_020d424c(1, WM_STATE_DCF_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&p->status->dcf_flag, 4);
        if (p->status->dcf_flag == false)
            return WM_ERRCODE_ILLEGAL_STATE;
        if (sendDataSize > DCF_DATA_MAX)
            return WM_ERRCODE_INVALID_PARAM;
        CleanCacheRange(sendData, sendDataSize);
        func_020d404c(WM_APIID_SET_DCF_DATA, callback);
        // The MAC address is copied to be aligned to 4 bytes
        VectorizedInvertedMemcpy(destAdr, wMac, 6);
        result = func_020d40bc(WM_APIID_SET_DCF_DATA, 4, wMac[0], wMac[1], sendData, sendDataSize);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }

    // WM_EndDCF
    int func_020d5cc8(WMCallbackFunc callback)
    {
        int result;
        WMArm9Buf* const p = func_020d41d8();
        result = func_020d424c(1, WM_STATE_DCF_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&p->status->dcf_flag, 4);
        if (p->status->dcf_flag == false)
            return WM_ERRCODE_ILLEGAL_STATE;
        func_020d404c(WM_APIID_END_DCF, callback);
        result = func_020d40bc(WM_APIID_END_DCF, 0);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        return WM_ERRCODE_OPERATING;
    }
}
