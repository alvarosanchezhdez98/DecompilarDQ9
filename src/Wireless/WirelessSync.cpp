#include "Wireless/WirelessManager.h"
#include "System/Cache.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include "System/RealTimeClock.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_sync.c: the wireless manager's functions that answer at once, without the ARM7

// WM_STATECODE_PORT_INIT: what a port's callback gets when it's set
#define STATECODE_PORT_INIT 25
// WM_NUM_MAX_CHILD
#define MAX_CHILDREN 15
// WM_SCAN_OTHER_ELEMENT_MAX
#define OTHER_ELEMENT_MAX 16
// WM_LINK_LEVEL_0
#define LINK_LEVEL_0 0
// OS_GetAllowedChannel? The channels that the console can use
#define ALLOWED_CHANNELS (*(unsigned short*)0x027ffcfa)
// OS_GetVBlankCount
#define VBLANK_COUNT (*(volatile unsigned long*)0x027ffc3c)
// The TGID before WM_GetNextTgid initializes it from the time
#define TGID_DEFAULT 0x10000

// The data that MP communication received from a child (WMMpRecvData), and their header (WMMpRecvHeader)
struct WMMpRecvData
{
    unsigned short length;
    unsigned short rssi;
    unsigned short aid;
    unsigned short noResponse;
    unsigned short timeStamp;
    unsigned char cdata[2];
};

struct WMMpRecvHeader
{
    unsigned short bitmap;
    unsigned short errBitmap;
    unsigned short count;
    unsigned short length;
    unsigned short txCount;
    WMMpRecvData data[1];
};

// The elements of a parent's beacon that aren't the game's information (WMOtherElements)
struct WMOtherElements
{
    unsigned char count;
    unsigned char padding[3];
    struct
    {
        unsigned char id;
        unsigned char length;
        unsigned char rsv[2];
        unsigned char* body;
    } element[OTHER_ELEMENT_MAX];
};

// A parent that a scan found (WMBssDesc): the length is in halfwords
struct WMBssDesc
{
    unsigned short length;
    char unk_2[0x3c - 0x2];
    unsigned short gameInfoLength;
    unsigned short otherElementCount;
    unsigned char elements[1];
};

// The last TGID (WM_GetNextTgid)
static unsigned long sTgid = TGID_DEFAULT;

extern "C"
{
    // OS_GetMacAddress
    void func_020c99ac(unsigned char* mac);
    // MIi_CpuCopyFast
    void func_020ca4b4(const void* src, void* dst, unsigned long size);
    // WMi_GetStatusAddress, WM_GetAID and WM_GetConnectedAIDs
    unsigned short func_020d46cc();
    unsigned short func_020d46fc();

    // WM_SetIndCallback
    int func_020d472c(WMCallbackFunc callback)
    {
        int result;
        int lastState = DisableIRQInterrupts();
        result = func_020d41e8();
        if (result != WM_ERRCODE_SUCCESS)
        {
            SetIRQInterruptState(lastState);
            return result;
        }
        func_020d41d8()->indCallback = callback;
        SetIRQInterruptState(lastState);
        return WM_ERRCODE_SUCCESS;
    }

    // WM_SetPortCallback
    int func_020d4770(unsigned short port, WMCallbackFunc callback, void* arg)
    {
        int result;
        int lastState;
        WMPortRecvCallback cb;
        if (callback != NULL)
        {
            VectorizedMemset(&cb, 0, sizeof(WMPortRecvCallback));
            cb.apiid = WM_APIID_PORT_RECV;
            cb.errcode = WM_ERRCODE_SUCCESS;
            cb.state = STATECODE_PORT_INIT;
            cb.port = port;
            cb.recvBuf = NULL;
            cb.data = NULL;
            cb.length = 0;
            cb.seqNo = 0xffff;
            cb.arg = arg;
            cb.aid = 0;
            func_020c99ac(cb.macAddress);
        }
        lastState = DisableIRQInterrupts();
        result = func_020d41e8();
        if (result != WM_ERRCODE_SUCCESS)
        {
            SetIRQInterruptState(lastState);
            return result;
        }
        {
            WMArm9Buf* const w9b = func_020d41d8();
            w9b->portCallbackTable[port] = callback;
            w9b->portCallbackArgument[port] = arg;
        }
        if (callback != NULL)
        {
            cb.connectedAidBitmap = func_020d46fc();
            cb.myAid = func_020d46cc();
            callback(&cb);
        }
        SetIRQInterruptState(lastState);
        return WM_ERRCODE_SUCCESS;
    }

    // WM_ReadStatus
    int func_020d4848(WMStatus* statusBuf)
    {
        WMArm9Buf* const w9b = func_020d41d8();
        const int result = func_020d41e8();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (statusBuf == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        InvalidateDataCacheRange(w9b->status, 0x7d0);
        func_020ca4b4(w9b->status, statusBuf, 0x7d0);
        return WM_ERRCODE_SUCCESS;
    }

    // WM_GetMPSendBufferSize
    unsigned long func_020d4894()
    {
        WMArm9Buf* const w9b = func_020d41d8();
        if (func_020d424c(2, WM_STATE_PARENT, WM_STATE_CHILD) != WM_ERRCODE_SUCCESS)
            return 0;
        InvalidateDataCacheRange(&w9b->status->mp_flag, 4);
        if (w9b->status->mp_flag == true)
            return 0;
        InvalidateDataCacheRange(&w9b->status->mp_sendSize, 4);
        return (w9b->status->mp_sendSize + 0x1f) & ~0x1f;
    }

    // WM_GetMPReceiveBufferSize
    unsigned long func_020d4900()
    {
        WMArm9Buf* const w9b = func_020d41d8();
        int isParent;
        unsigned short recvSize;
        if (func_020d424c(2, WM_STATE_PARENT, WM_STATE_CHILD) != WM_ERRCODE_SUCCESS)
            return 0;
        InvalidateDataCacheRange(&w9b->status->mp_flag, 4);
        if (w9b->status->mp_flag == true)
            return 0;
        InvalidateDataCacheRange(&w9b->status->aid, 2);
        isParent = w9b->status->aid == 0 ? true : false;
        InvalidateDataCacheRange(&w9b->status->mp_recvSize, 2);
        recvSize = w9b->status->mp_recvSize;
        if (isParent == true)
        {
            InvalidateDataCacheRange(&w9b->status->pparam_maxEntry, 2);
            return (((recvSize + 0xc) * w9b->status->pparam_maxEntry + 0x29) & ~0x1f) * 2;
        }
        return ((recvSize + 0x51) & ~0x1f) * 2;
    }

    // WM_ReadMPData
    const WMMpRecvData* func_020d49c4(const void* header, unsigned short aid)
    {
        const WMMpRecvHeader* const recvHeader = (const WMMpRecvHeader*)header;
        WMMpRecvData* recvData[MAX_CHILDREN];
        WMArm9Buf* const w9b = func_020d41d8();
        if (func_020d41e8() != WM_ERRCODE_SUCCESS)
            return NULL;
        if (aid < 1 || aid > MAX_CHILDREN)
            return NULL;
        InvalidateDataCacheRange(&w9b->status->child_bitmap, 2);
        if (!(w9b->status->child_bitmap & (1 << aid)))
            return NULL;
        if (recvHeader->count == 0)
            return NULL;
        recvData[0] = (WMMpRecvData*)recvHeader->data;
        int i = 0;
        do
        {
            if (recvData[i]->aid == aid)
                return recvData[i];
            i++;
            recvData[i] = (WMMpRecvData*)((unsigned long)recvData[i - 1] + recvHeader->length);
        } while (i < recvHeader->count);
        return NULL;
    }

    // WM_GetAllowedChannel
    unsigned short func_020d4aa8()
    {
        if (func_020d41e8() != WM_ERRCODE_SUCCESS)
            return 0x8000;
        return ALLOWED_CHANNELS;
    }

    // WM_GetLinkLevel
    int func_020d4ac8()
    {
        WMArm9Buf* const w9b = func_020d41d8();
        if (func_020d41e8() != WM_ERRCODE_SUCCESS)
            return LINK_LEVEL_0;
        InvalidateDataCacheRange(&w9b->status->state, 2);
        switch (w9b->status->state)
        {
        case WM_STATE_MP_PARENT:
            InvalidateDataCacheRange(&w9b->status->child_bitmap, 2);
            if (w9b->status->child_bitmap == 0)
                return LINK_LEVEL_0;
        case WM_STATE_MP_CHILD:
        case WM_STATE_DCF_CHILD:
            InvalidateDataCacheRange(&w9b->status->linkLevel, 2);
            return w9b->status->linkLevel;
        }
        return LINK_LEVEL_0;
    }

    // WM_GetDispersionBeaconPeriod
    unsigned short func_020d4b58()
    {
        unsigned char mac[6];
        unsigned short ret;
        int i;
        func_020c99ac(mac);
        for (i = 0, ret = 0; i < 6; i++)
            ret += mac[i];
        ret += VBLANK_COUNT;
        ret *= 7;
        return 200 + ret % 20;
    }

    // WM_GetDispersionScanPeriod
    unsigned short func_020d4be8()
    {
        unsigned char mac[6];
        unsigned short ret;
        int i;
        func_020c99ac(mac);
        for (i = 0, ret = 0; i < 6; i++)
            ret += mac[i];
        ret += VBLANK_COUNT;
        ret *= 13;
        return 30 + ret % 10;
    }

    // WM_GetOtherElements
    WMOtherElements func_020d4c7c(const WMBssDesc* bssDesc)
    {
        WMOtherElements elements;
        const unsigned char* element;
        int i;
        unsigned char length;
        unsigned char maxLength;
        if (bssDesc->gameInfoLength != 0)
        {
            elements.count = 0;
            return elements;
        }
        elements.count = bssDesc->otherElementCount;
        if (elements.count == 0)
            return elements;
        if (elements.count > OTHER_ELEMENT_MAX)
            elements.count = OTHER_ELEMENT_MAX;
        element = bssDesc->elements;
        maxLength = bssDesc->length * 2 - 64;
        length = 0;
        for (i = 0; i < elements.count; i++)
        {
            unsigned char elementLength;
            elements.element[i].id = element[0];
            elements.element[i].length = element[1];
            elements.element[i].body = (unsigned char*)&element[2];
            elementLength = elements.element[i].length + 2;
            length += elementLength;
            if (length > maxLength)
            {
                elements.count = 0;
                return elements;
            }
            element += elementLength;
        }
        return elements;
    }

    // WM_GetNextTgid
    unsigned short func_020d4dd4()
    {
        if (sTgid == TGID_DEFAULT)
        {
            RealTimeClockTime time;
            func_020cf020();
            if (func_020cf1a8(&time) == REAL_TIME_CLOCK_SUCCESS)
                sTgid = (unsigned short)(time.second + (time.minute << 8));
        }
        sTgid++;
        sTgid = (unsigned short)sTgid;
        return sTgid;
    }
}
