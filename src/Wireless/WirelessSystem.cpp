#include "Wireless/WirelessManager.h"
#include "System/Cache.h"
#include "System/DMA.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include "System/MessageQueue.h"
#include <stdarg.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_system.c: initializes the wireless manager, sends the commands to the ARM7 through the IPC, and
// receives its answers

// The IPC command of the wireless manager (the NitroSDK's PXI_FIFO_TAG_WM)
#define IPC_COMMAND_WM 10
// The size of a command's buffer, and how many there are
#define FIFO_BUFFER_SIZE 0x100
#define FIFO_BUFFER_COUNT 10
// WM_API_REQUEST_ACCEPTED: the ARM9 is done with the buffer of an answer
#define REQUEST_ACCEPTED 0x8000
// WM_SYSTEM_BUF_SIZE
#define SYSTEM_BUFFER_SIZE 0xf00

// WMStateCode: what the answers of the parent and the child say about the connections
#define STATECODE_CONNECTED 7
#define STATECODE_DISCONNECTED 9
#define STATECODE_DISCONNECTED_FROM_MYSELF 26
// And the MP communication's answers that bring data
#define STATECODE_MP_IND 11
#define STATECODE_MPACK_IND 12

// HW_ARM7_FIFO_RECV_FLAG? The flag that the ARM7 sets when it sent an answer
#define FIFO_RECEIVE_FLAG (*(volatile unsigned short*)0x027fff96)

// The answers that ReceiveFifo reads
struct WMStartParentCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short wlCmdID;
    unsigned short wlResult;
    unsigned short state;
    unsigned char macAddress[6];
    unsigned short aid;
    unsigned short reason;
    unsigned char ssid[24];
    unsigned short parentSize;
    unsigned short childSize;
};

struct WMStartConnectCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short wlCmdID;
    unsigned short wlResult;
    unsigned short state;
    unsigned short aid;
    unsigned short reason;
    unsigned short wlStatus;
    unsigned char macAddress[6];
    unsigned short parentSize;
    unsigned short childSize;
};

struct WMStartMPCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short state;
    unsigned char reserved[2];
    void* recvBuf;
};

struct WMPortSendCallback
{
    unsigned short apiid;
    unsigned short errcode;
    char unk_4[0x1c - 0x4];
    WMCallbackFunc callback;
};

// The variables are laid out like the original: the compiler sorts them by size
static unsigned short wmInitialized;
static WMArm9Buf* wm9buf;
static MessageQueue bufMsgQ;
static void* bufMsg[FIFO_BUFFER_COUNT];
static WMPortRecvCallback portRecvCallback;
static unsigned short fifoBuf[FIFO_BUFFER_COUNT][FIFO_BUFFER_SIZE / sizeof(unsigned short)] __attribute__((aligned(32)));

extern "C"
{
    // OS_Terminate
    void func_020c9be0();
    // MIi_CpuClear16
    void func_020ca390(unsigned short value, void* dst, unsigned long size);
    // MI_CpuCopy16
    void func_020ca3b8(const void* src, void* dst, unsigned long size);

    int func_020d3df8(void* sysBuf, unsigned short dmaNo, unsigned long bufSize);
    static void* func_020d4064();
    static void func_020d42e0(unsigned int command, unsigned int data, unsigned int error);
    static void func_020d468c();

    // WM_Init
    int func_020d3dcc(void* sysBuf, unsigned short dmaNo)
    {
        const int result = func_020d3df8(sysBuf, dmaNo, SYSTEM_BUFFER_SIZE);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        wm9buf->scanOnlyFlag = false;
        return result;
    }

    // WmInitCore
    int func_020d3df8(void* sysBuf, unsigned short dmaNo, unsigned long bufSize)
    {
        int lastState = DisableIRQInterrupts();
        if (wmInitialized)
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_ILLEGAL_STATE;
        }
        if (sysBuf == NULL)
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_INVALID_PARAM;
        }
        if (dmaNo > 3)
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_INVALID_PARAM;
        }
        if ((unsigned long)sysBuf & 0x1f)
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_INVALID_PARAM;
        }
        InitializeInterProcessorCommunication();
        if (!IsIPCCommandHandlerRegistered(IPC_COMMAND_WM, IPCSide_Arm7))
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_WM_DISABLE;
        }
        InvalidateDataCacheRange(sysBuf, bufSize);
        DMAMemsetSynchronous(dmaNo, (unsigned int)sysBuf, 0, bufSize);
        wm9buf = (WMArm9Buf*)sysBuf;
        wm9buf->WM7 = (unsigned char*)sysBuf + 0x200;
        wm9buf->status = (WMStatus*)((unsigned char*)wm9buf->WM7 + 0x300);
        wm9buf->fifo9to7 = (unsigned long*)((unsigned char*)wm9buf->status + 0x800);
        wm9buf->fifo7to9 = (unsigned long*)((unsigned char*)wm9buf->fifo9to7 + FIFO_BUFFER_SIZE);
        func_020d468c();
        wm9buf->dmaNo = dmaNo;
        wm9buf->connectedAidBitmap = 0;
        wm9buf->myAid = 0;
        for (int i = 0; i < 16; i++)
        {
            wm9buf->portCallbackTable[i] = NULL;
            wm9buf->portCallbackArgument[i] = NULL;
        }
        func_020c7de4(&bufMsgQ, bufMsg, FIFO_BUFFER_COUNT);
        for (int i = 0; i < FIFO_BUFFER_COUNT; i++)
        {
            fifoBuf[i][0] = REQUEST_ACCEPTED;
            CleanCacheRange(fifoBuf[i], sizeof(unsigned short));
            func_020c7e0c(&bufMsgQ, fifoBuf[i], MESSAGE_QUEUE_BLOCK);
        }
        SetArm9IPCCommandHandler(IPC_COMMAND_WM, func_020d42e0);
        wmInitialized = true;
        SetIRQInterruptState(lastState);
        return WM_ERRCODE_SUCCESS;
    }

    int func_020d3fdc()
    {
        int result;
        int lastState = DisableIRQInterrupts();
        if (func_020d41e8() != WM_ERRCODE_SUCCESS)
        {
            SetIRQInterruptState(lastState);
            return WM_ERRCODE_ILLEGAL_STATE;
        }
        result = func_020d424c(1, WM_STATE_READY);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        func_020d468c();
        SetArm9IPCCommandHandler(IPC_COMMAND_WM, NULL);
        wm9buf = NULL;
        wmInitialized = false;
        SetIRQInterruptState(lastState);
        return WM_ERRCODE_SUCCESS;
    }

    void func_020d404c(int id, WMCallbackFunc callback)
    {
        wm9buf->CallbackTable[id] = callback;
    }

    // WmGetCommandBuffer4Arm7
    static void* func_020d4064()
    {
        void* buffer;
        if (!func_020c7ea0(&bufMsgQ, &buffer, 0))
            return NULL;
        InvalidateDataCacheRange(buffer, sizeof(unsigned short));
        if (*(unsigned short*)buffer & REQUEST_ACCEPTED)
            return buffer;
        func_020c7f44(&bufMsgQ, buffer, MESSAGE_QUEUE_BLOCK);
        return NULL;
    }

    int func_020d40bc(int id, unsigned short paramNum, ...)
    {
        va_list args;
        int i;
        int result;
        unsigned long* buffer;
        buffer = (unsigned long*)func_020d4064();
        if (buffer == NULL)
            return WM_ERRCODE_FIFO_ERROR;
        *(unsigned short*)buffer = id;
        va_start(args, paramNum);
        for (i = 0; i < paramNum; i++)
            buffer[i + 1] = va_arg(args, unsigned long);
        va_end(args);
        CleanCacheRange(buffer, FIFO_BUFFER_SIZE);
        result = SendCommandToArm7(IPC_COMMAND_WM, (int)buffer, false);
        func_020c7e0c(&bufMsgQ, buffer, MESSAGE_QUEUE_BLOCK);
        if (result < 0)
            return WM_ERRCODE_FIFO_ERROR;
        return WM_ERRCODE_OPERATING;
    }

    int func_020d4168(const void* data, unsigned long length)
    {
        void* const buffer = func_020d4064();
        int result;
        if (buffer == NULL)
            return WM_ERRCODE_FIFO_ERROR;
        VectorizedInvertedMemcpy(data, buffer, length);
        CleanCacheRange(buffer, length);
        result = SendCommandToArm7(IPC_COMMAND_WM, (int)buffer, false);
        func_020c7e0c(&bufMsgQ, buffer, MESSAGE_QUEUE_BLOCK);
        if (result < 0)
            return WM_ERRCODE_FIFO_ERROR;
        return WM_ERRCODE_OPERATING;
    }

    WMArm9Buf* func_020d41d8()
    {
        return wm9buf;
    }

    int func_020d41e8()
    {
        if (wmInitialized)
            return WM_ERRCODE_SUCCESS;
        return WM_ERRCODE_ILLEGAL_STATE;
    }

    int func_020d4204()
    {
        const int result = func_020d41e8();
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&wm9buf->status->state, sizeof(unsigned short));
        if (wm9buf->status->state == WM_STATE_READY || wm9buf->status->state == WM_STATE_STOP)
            return WM_ERRCODE_ILLEGAL_STATE;
        return WM_ERRCODE_SUCCESS;
    }

    int func_020d424c(int paramNum, ...)
    {
        int result = func_020d41e8();
        unsigned short state;
        va_list args;
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        InvalidateDataCacheRange(&wm9buf->status->state, sizeof(unsigned short));
        state = wm9buf->status->state;
        va_start(args, paramNum);
        result = WM_ERRCODE_ILLEGAL_STATE;
        while (paramNum != 0)
        {
            if (va_arg(args, unsigned long) == state)
                result = WM_ERRCODE_SUCCESS;
            paramNum--;
        }
        va_end(args);
        return result;
    }

    // WmReceiveFifo
    static void func_020d42e0(unsigned int command, unsigned int data, unsigned int error)
    {
        WMCallback* const callback = (WMCallback*)data;
        WMArm9Buf* const w9b = wm9buf;
        if (error)
            return;
        InvalidateDataCacheRange(w9b->fifo7to9, FIFO_BUFFER_SIZE);
        if (!w9b->scanOnlyFlag)
            InvalidateDataCacheRange(w9b->status, sizeof(WMStatus));
        if ((unsigned long)callback != (unsigned long)w9b->fifo7to9)
            InvalidateDataCacheRange(callback, FIFO_BUFFER_SIZE);
        if (callback->apiid >= WM_NUM_OF_CALLBACK)
        {
            if (callback->apiid == WM_APIID_INDICATION)
            {
                if (callback->errcode == WM_ERRCODE_FLASH_ERROR)
                    func_020c9be0();
                if (w9b->indCallback != NULL)
                    w9b->indCallback(callback);
            }
            else if (callback->apiid == WM_APIID_PORT_RECV)
            {
                WMPortRecvCallback* const port = (WMPortRecvCallback*)callback;
                if (w9b->portCallbackTable[port->port] != NULL)
                {
                    port->arg = w9b->portCallbackArgument[port->port];
                    port->connectedAidBitmap = w9b->connectedAidBitmap;
                    InvalidateDataCacheRange(port->recvBuf, w9b->status->mp_recvBufSize);
                    w9b->portCallbackTable[port->port](port);
                }
            }
            else if (callback->apiid == WM_APIID_PORT_SEND)
            {
                WMPortSendCallback* const port = (WMPortSendCallback*)callback;
                callback->apiid = WM_APIID_SET_MP_DATA;
                if (port->callback != NULL)
                    port->callback(port);
            }
        }
        else
        {
            if (callback->apiid == WM_APIID_START_MP)
            {
                WMStartMPCallback* const mp = (WMStartMPCallback*)callback;
                if ((mp->state == STATECODE_MP_IND || mp->state == STATECODE_MPACK_IND) &&
                    mp->errcode == WM_ERRCODE_SUCCESS)
                    InvalidateDataCacheRange(mp->recvBuf, w9b->status->mp_recvBufSize);
            }
            if (callback->apiid == WM_APIID_END && callback->errcode == WM_ERRCODE_SUCCESS)
            {
                const WMCallbackFunc func = w9b->CallbackTable[callback->apiid];
                func_020d3fdc();
                if (func != NULL)
                    func(callback);
                return;
            }
            if (w9b->CallbackTable[callback->apiid] != NULL)
            {
                w9b->CallbackTable[callback->apiid](callback);
                if (!wmInitialized)
                    return;
            }
            if (callback->apiid == WM_APIID_START_PARENT || callback->apiid == WM_APIID_START_CONNECT)
            {
                unsigned short state;
                unsigned short aid;
                unsigned short myAid;
                unsigned short reason;
                const unsigned char* macAddress;
                const unsigned char* ssid;
                unsigned short parentSize;
                unsigned short childSize;
                if (callback->apiid == WM_APIID_START_PARENT)
                {
                    WMStartParentCallback* const parent = (WMStartParentCallback*)callback;
                    state = parent->state;
                    aid = parent->aid;
                    myAid = 0;
                    macAddress = parent->macAddress;
                    ssid = parent->ssid;
                    reason = parent->reason;
                    parentSize = parent->parentSize;
                    childSize = parent->childSize;
                }
                else if (callback->apiid == WM_APIID_START_CONNECT)
                {
                    WMStartConnectCallback* const connect = (WMStartConnectCallback*)callback;
                    state = connect->state;
                    aid = 0;
                    myAid = connect->aid;
                    macAddress = connect->macAddress;
                    ssid = NULL;
                    reason = connect->reason;
                    parentSize = connect->parentSize;
                    childSize = connect->childSize;
                }
                if (state == STATECODE_CONNECTED || state == STATECODE_DISCONNECTED ||
                    state == STATECODE_DISCONNECTED_FROM_MYSELF)
                {
                    if (state == STATECODE_CONNECTED)
                        w9b->connectedAidBitmap |= 1 << aid;
                    else
                        w9b->connectedAidBitmap &= ~(1 << aid);
                    w9b->myAid = myAid;
                    VectorizedMemset(&portRecvCallback, 0, sizeof(WMPortRecvCallback));
                    portRecvCallback.apiid = WM_APIID_PORT_RECV;
                    portRecvCallback.errcode = WM_ERRCODE_SUCCESS;
                    portRecvCallback.state = state;
                    portRecvCallback.recvBuf = NULL;
                    portRecvCallback.data = NULL;
                    portRecvCallback.length = 0;
                    portRecvCallback.aid = aid;
                    portRecvCallback.myAid = myAid;
                    portRecvCallback.connectedAidBitmap = w9b->connectedAidBitmap;
                    portRecvCallback.seqNo = 0xffff;
                    portRecvCallback.reason = reason;
                    VectorizedInvertedMemcpy(macAddress, portRecvCallback.macAddress, sizeof(portRecvCallback.macAddress));
                    if (ssid != NULL)
                        func_020ca3b8(ssid, portRecvCallback.ssid, sizeof(portRecvCallback.ssid));
                    else
                        func_020ca390(0, portRecvCallback.ssid, sizeof(portRecvCallback.ssid));
                    portRecvCallback.maxSendDataSize = myAid == 0 ? parentSize : childSize;
                    portRecvCallback.maxRecvDataSize = myAid == 0 ? childSize : parentSize;
                    for (unsigned short i = 0; i < 16; i++)
                    {
                        portRecvCallback.port = i;
                        if (w9b->portCallbackTable[i] != NULL)
                        {
                            portRecvCallback.arg = w9b->portCallbackArgument[i];
                            w9b->portCallbackTable[i](&portRecvCallback);
                        }
                    }
                }
            }
        }
        InvalidateDataCacheRange(w9b->fifo7to9, FIFO_BUFFER_SIZE);
        func_020d468c();
        if ((unsigned long)callback != (unsigned long)w9b->fifo7to9)
        {
            callback->apiid |= REQUEST_ACCEPTED;
            CleanCacheRange(callback, FIFO_BUFFER_SIZE);
        }
    }

    // WmClearFifoRecvFlag
    static void func_020d468c()
    {
        const unsigned short flag = FIFO_RECEIVE_FLAG;
        if (flag & 1)
            FIFO_RECEIVE_FLAG = flag & ~1;
    }

    // WMi_GetStatusAddress
    WMStatus* func_020d46a8()
    {
        if (func_020d41e8() != WM_ERRCODE_SUCCESS)
            return NULL;
        return wm9buf->status;
    }

    // WM_GetAID
    unsigned short func_020d46cc()
    {
        unsigned short aid;
        int lastState = DisableIRQInterrupts();
        if (wm9buf != NULL)
            aid = wm9buf->myAid;
        else
            aid = 0;
        SetIRQInterruptState(lastState);
        return aid;
    }

    // WM_GetConnectedAIDs
    unsigned short func_020d46fc()
    {
        unsigned long bitmap;
        int lastState = DisableIRQInterrupts();
        if (wm9buf != NULL)
            bitmap = wm9buf->connectedAidBitmap;
        else
            bitmap = 0;
        SetIRQInterruptState(lastState);
        return bitmap;
    }
}
