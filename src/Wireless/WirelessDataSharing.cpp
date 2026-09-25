#include "Wireless/WirelessDataSharing.h"
#include "System/Interrupts.h"
#include "System/Memory.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_ds.c: data sharing. The parent keeps a ring buffer of data sets: it fills the next one with its
// data and the data that the children send it, and sends it to them when every console's data arrived.

// WM_NUM_OF_PORT
#define PORT_COUNT 16
// WM_ERRCODE_NO_DATASET: WM_StepDataSharing has no new data set
#define ERRCODE_NO_DATASET 5

extern "C"
{
    // MIi_CpuClear16, MIi_CpuCopy16 and MIi_CpuClearFast
    void func_020ca390(unsigned short value, void* dst, unsigned long size);
    void func_020ca3b8(const void* src, void* dst, unsigned long size);
    void func_020ca458(unsigned long value, void* dst, unsigned long size);
    // MATH_CountPopulation
    unsigned char func_020d1ae4(unsigned long x);

    static void func_020d6318(void* callback);
    static void func_020d63f0(void* callback);
    static void func_020d651c(void* callback);
    static void func_020d6610(WMDataSharingInfo* dsInfo, unsigned short aid, const unsigned short* data);
    static void func_020d66dc(WMDataSharingInfo* dsInfo, int delayed);
    static unsigned short* func_020d6884(WMDataSharingInfo* dsInfo, unsigned long aidBitmap,
                                         unsigned short* receiveBuf, unsigned long aid);

    // WM_StartDataSharing
    int func_020d5d34(WMDataSharingInfo* dsInfo, unsigned short port, unsigned short aidBitmap,
                      unsigned short dataLength, int doubleMode)
    {
        int result;
        int aid;
        unsigned short connectedAIDs = 1;
        result = func_020d424c(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (dsInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (port >= PORT_COUNT)
            return WM_ERRCODE_INVALID_PARAM;
        if (aidBitmap == 0)
            return WM_ERRCODE_INVALID_PARAM;
        aid = func_020d46cc();
        if (aid == 0)
            connectedAIDs = func_020d46fc();
        func_020ca458(0, dsInfo, sizeof(WMDataSharingInfo));
        dsInfo->writeIndex = 0;
        dsInfo->sendIndex = 0;
        dsInfo->readIndex = 0;
        dsInfo->dataLength = dataLength;
        dsInfo->port = port;
        dsInfo->aidBitmap = 0;
        dsInfo->doubleMode = doubleMode ? true : false;
        // The console shares its own data too
        aidBitmap |= 1 << aid;
        dsInfo->aidBitmap = aidBitmap;
        {
            const unsigned char stationNumber = func_020d1ae4(aidBitmap);
            dsInfo->stationNumber = stationNumber;
            dsInfo->dataSetLength = dataLength * stationNumber;
        }
        if (dsInfo->dataSetLength > WM_DS_DATA_SIZE)
        {
            dsInfo->aidBitmap = 0;
            return WM_ERRCODE_INVALID_PARAM;
        }
        // And the data set's header
        dsInfo->dataSetLength += 4;
        dsInfo->state = WM_DS_STATE_START;
        if (aid == 0)
        {
            int i;
            for (i = 0; i < WM_DS_DATASET_NUM; i++)
                dsInfo->ds[i].aidBitmap = dsInfo->aidBitmap & (connectedAIDs | 1);
            func_020d4770(port, func_020d63f0, dsInfo);
            // The parent sends the first data sets at once
            for (i = 0; i < (dsInfo->doubleMode == true ? 2 : 1); i++)
            {
                int res;
                dsInfo->writeIndex = (dsInfo->writeIndex + 1) & (WM_DS_DATASET_NUM - 1);
                res = func_020d59bc(func_020d6318, dsInfo, (unsigned short*)&dsInfo->ds[i], dsInfo->dataSetLength,
                                    dsInfo->aidBitmap & connectedAIDs, dsInfo->port, WM_PRIORITY_HIGH);
                if (res == WM_ERRCODE_NO_CHILD)
                {
                    dsInfo->seqNum[i] = 0xffff;
                    dsInfo->sendIndex = (dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1);
                }
                else if (res != WM_ERRCODE_SUCCESS && res != WM_ERRCODE_OPERATING)
                {
                    dsInfo->state = WM_DS_STATE_ERROR;
                    return WM_ERRCODE_FAILED;
                }
            }
        }
        else
        {
            dsInfo->sendIndex = WM_DS_DATASET_NUM - 1;
            func_020d4770(port, func_020d651c, dsInfo);
        }
        return WM_ERRCODE_SUCCESS;
    }

    // WM_EndDataSharing
    int func_020d5f88(WMDataSharingInfo* dsInfo)
    {
        if (dsInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (dsInfo->aidBitmap == 0)
            return WM_ERRCODE_ILLEGAL_STATE;
        func_020d4770(dsInfo->port, NULL, NULL);
        dsInfo->aidBitmap = 0;
        dsInfo->state = WM_DS_STATE_READY;
        return WM_ERRCODE_SUCCESS;
    }

    // WM_StepDataSharing: gives the next data set, and sends the console's data for a later one
    int func_020d5fd0(WMDataSharingInfo* dsInfo, const unsigned short* sendData, WMDataSet* receiveData)
    {
        int result;
        unsigned short aid;
        unsigned short connectedAIDs;
        unsigned short state;
        result = func_020d424c(2, WM_STATE_MP_PARENT, WM_STATE_MP_CHILD);
        if (result != WM_ERRCODE_SUCCESS)
            return result;
        if (dsInfo == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (sendData == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        if (receiveData == NULL)
            return WM_ERRCODE_INVALID_PARAM;
        aid = func_020d46cc();
        if (aid == 0)
            connectedAIDs = func_020d46fc();
        state = dsInfo->state;
        if (state == WM_DS_STATE_ERROR)
            return WM_ERRCODE_FAILED;
        if (state != WM_DS_STATE_START && state != WM_DS_STATE_RETRY_SEND)
            return WM_ERRCODE_ILLEGAL_STATE;
        result = ERRCODE_NO_DATASET;
        if (aid == 0)
        {
            int sendFlag = false;
            int delayed = false;
            if (state == WM_DS_STATE_RETRY_SEND)
            {
                // Sends again the data set that the queue didn't take
                int res;
                int oldWI;
                dsInfo->state = WM_DS_STATE_START;
                oldWI = (dsInfo->writeIndex + WM_DS_DATASET_NUM - 1) & (WM_DS_DATASET_NUM - 1);
                res = func_020d59bc(func_020d6318, dsInfo, (unsigned short*)&dsInfo->ds[oldWI],
                                    dsInfo->dataSetLength, dsInfo->aidBitmap & connectedAIDs, dsInfo->port,
                                    WM_PRIORITY_HIGH);
                if (res == WM_ERRCODE_NO_CHILD)
                {
                    dsInfo->seqNum[oldWI] = 0xffff;
                    dsInfo->sendIndex = (dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1);
                }
                else if (res != WM_ERRCODE_SUCCESS && res != WM_ERRCODE_OPERATING)
                {
                    dsInfo->state = WM_DS_STATE_ERROR;
                    return WM_ERRCODE_FAILED;
                }
            }
            if (dsInfo->readIndex != dsInfo->sendIndex)
            {
                dsInfo->ds[dsInfo->readIndex].aidBitmap |= 1;
                func_020ca3b8(&dsInfo->ds[dsInfo->readIndex], receiveData, sizeof(WMDataSet));
                dsInfo->currentSeqNum = dsInfo->seqNum[dsInfo->readIndex];
                dsInfo->readIndex = (dsInfo->readIndex + 1) & (WM_DS_DATASET_NUM - 1);
                sendFlag = true;
                result = WM_ERRCODE_SUCCESS;
                // The next data set only waits for the parent: it's sent after the parent's data
                if (dsInfo->doubleMode == false && connectedAIDs != 0 && dsInfo->ds[dsInfo->writeIndex].aidBitmap == 1)
                    delayed = true;
                else
                    delayed = false;
            }
            func_020d66dc(dsInfo, false);
            if (sendFlag)
            {
                func_020d6610(dsInfo, 0, sendData);
                if (dsInfo->doubleMode == false)
                    func_020d66dc(dsInfo, delayed);
            }
        }
        else
        {
            int sendFlag = false;
            if (state == WM_DS_STATE_RETRY_SEND)
            {
                sendFlag = true;
                dsInfo->state = WM_DS_STATE_START;
            }
            else if (dsInfo->readIndex != dsInfo->writeIndex)
            {
                if (!(dsInfo->ds[dsInfo->readIndex].aidBitmap & 1))
                {
                    dsInfo->ds[dsInfo->readIndex].aidBitmap |= 1;
                }
                else
                {
                    func_020ca3b8(&dsInfo->ds[dsInfo->readIndex], receiveData, sizeof(WMDataSet));
                    dsInfo->currentSeqNum = dsInfo->seqNum[dsInfo->readIndex];
                    dsInfo->readIndex = (dsInfo->readIndex + 1) & (WM_DS_DATASET_NUM - 1);
                    sendFlag = true;
                    result = WM_ERRCODE_SUCCESS;
                }
            }
            if (sendFlag)
            {
                // The child sends its data from a data set that it doesn't read, 32 bytes in to be aligned
                unsigned short* const buf = (unsigned short*)((unsigned char*)&dsInfo->ds[dsInfo->sendIndex] + 32);
                int res;
                func_020ca3b8(sendData, buf, dsInfo->dataLength);
                res = func_020d59bc(func_020d6318, dsInfo, buf, dsInfo->dataLength, dsInfo->aidBitmap, dsInfo->port,
                                    WM_PRIORITY_HIGH);
                dsInfo->sendIndex = (dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1);
                if (res != WM_ERRCODE_OPERATING && res != WM_ERRCODE_SUCCESS)
                {
                    dsInfo->state = WM_DS_STATE_ERROR;
                    result = WM_ERRCODE_FAILED;
                }
            }
        }
        return result;
    }

    // WmDataSharingSetDataCallback: MP communication sent a data set
    static void func_020d6318(void* callback)
    {
        WMArm9Buf* const p = func_020d41d8();
        WMPortSendCallback* const cb = (WMPortSendCallback*)callback;
        const WMCallbackFunc portCallback = p->portCallbackTable[cb->port];
        WMDataSharingInfo* const dsInfo = (WMDataSharingInfo*)p->portCallbackArgument[cb->port];
        unsigned short aid;
        // Data sharing ended
        if (portCallback != func_020d63f0 && portCallback != func_020d651c)
            return;
        if (dsInfo == NULL)
            return;
        if (dsInfo != cb->arg)
            return;
        aid = func_020d46cc();
        if (cb->errcode == WM_ERRCODE_SUCCESS)
        {
            if (aid == 0)
            {
                dsInfo->seqNum[dsInfo->sendIndex] = cb->seqNo >> 1;
                dsInfo->sendIndex = (dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1);
            }
        }
        else if (cb->errcode == WM_ERRCODE_SEND_QUEUE_FULL)
        {
            if (aid != 0)
                dsInfo->sendIndex = (dsInfo->sendIndex + WM_DS_DATASET_NUM - 1) & (WM_DS_DATASET_NUM - 1);
            dsInfo->state = WM_DS_STATE_RETRY_SEND;
        }
        else
        {
            dsInfo->state = WM_DS_STATE_ERROR;
        }
    }

    // WmDataSharingReceiveCallback_Parent
    static void func_020d63f0(void* callback)
    {
        WMPortRecvCallback* const cb = (WMPortRecvCallback*)callback;
        WMDataSharingInfo* const dsInfo = (WMDataSharingInfo*)cb->arg;
        if (dsInfo == NULL)
            return;
        if (cb->errcode == WM_ERRCODE_SUCCESS)
        {
            switch (cb->state)
            {
            case WM_STATECODE_PORT_RECV:
                func_020d6610(dsInfo, cb->aid, (const unsigned short*)cb->data);
                func_020d66dc(dsInfo, false);
                break;
            case WM_STATECODE_CONNECTED:
                func_020d66dc(dsInfo, false);
                break;
            case WM_STATECODE_DISCONNECTED:
            case WM_STATECODE_DISCONNECTED_FROM_MYSELF:
            {
                // The data sets stop waiting for the child
                const unsigned long aidBit = 1 << cb->aid;
                const int lastState = DisableIRQInterrupts();
                const unsigned short wi = dsInfo->writeIndex;
                dsInfo->ds[wi].aidBitmap &= ~aidBit;
                if (dsInfo->doubleMode == true)
                    dsInfo->ds[(unsigned short)((wi + 1) & (WM_DS_DATASET_NUM - 1))].aidBitmap &= ~aidBit;
                SetIRQInterruptState(lastState);
                func_020d66dc(dsInfo, false);
                if (dsInfo->doubleMode == true)
                    func_020d66dc(dsInfo, false);
                break;
            }
            case WM_STATECODE_PORT_INIT:
                break;
            }
        }
        else
        {
            dsInfo->state = WM_DS_STATE_ERROR;
        }
    }

    // WmDataSharingReceiveCallback_Child
    static void func_020d651c(void* callback)
    {
        WMPortRecvCallback* const cb = (WMPortRecvCallback*)callback;
        WMDataSharingInfo* const dsInfo = (WMDataSharingInfo*)cb->arg;
        if (dsInfo == NULL)
            return;
        if (cb->errcode == WM_ERRCODE_SUCCESS)
        {
            switch (cb->state)
            {
            case WM_STATECODE_PORT_RECV:
            {
                // The child gets a data set from the parent
                unsigned short length;
                unsigned short aidBitmap;
                unsigned short aid;
                WMDataSet* dataSet;
                dataSet = (WMDataSet*)cb->data;
                length = cb->length;
                aidBitmap = dataSet->aidBitmap;
                aid = func_020d46cc();
                if (length != dsInfo->dataSetLength)
                {
                    if (length > sizeof(WMDataSet))
                        length = sizeof(WMDataSet);
                }
                if (length < 4)
                    return;
                if (!(aidBitmap & (1 << aid)))
                    return;
                func_020ca3b8(dataSet, &dsInfo->ds[dsInfo->writeIndex], length);
                dsInfo->seqNum[dsInfo->writeIndex] = cb->seqNo >> 1;
                dsInfo->writeIndex = (dsInfo->writeIndex + 1) & (WM_DS_DATASET_NUM - 1);
                break;
            }
            case WM_STATECODE_CONNECTED:
            case WM_STATECODE_DISCONNECTED:
            case WM_STATECODE_PORT_INIT:
            case WM_STATECODE_DISCONNECTED_FROM_MYSELF:
                break;
            }
        }
        else
        {
            dsInfo->state = WM_DS_STATE_ERROR;
        }
    }

    // WmDataSharingReceiveData: puts a console's data in the data set that waits for it
    static void func_020d6610(WMDataSharingInfo* dsInfo, unsigned short aid, const unsigned short* data)
    {
        const unsigned short aidBit = 1 << aid;
        unsigned short wi;
        unsigned short* buf;
        int lastState;
        if (!(dsInfo->aidBitmap & aidBit))
            return;
        wi = dsInfo->writeIndex;
        if (!(dsInfo->ds[wi].aidBitmap & aidBit))
        {
            if (dsInfo->doubleMode != true)
                return;
            wi = (wi + 1) & (WM_DS_DATASET_NUM - 1);
            if (!(dsInfo->ds[wi].aidBitmap & aidBit))
                return;
        }
        buf = func_020d6884(dsInfo, dsInfo->aidBitmap, dsInfo->ds[wi].data, aid);
        if (data != NULL)
            func_020ca3b8(data, buf, dsInfo->dataLength);
        else
            func_020ca390(0, buf, dsInfo->dataLength);
        lastState = DisableIRQInterrupts();
        dsInfo->ds[wi].aidBitmap &= ~aidBit;
        dsInfo->ds[wi].receivedBitmap |= aidBit;
        SetIRQInterruptState(lastState);
    }

    // WmDataSharingSendDataSet: the parent sends the data set when every console's data arrived
    static void func_020d66dc(WMDataSharingInfo* dsInfo, int delayed)
    {
        const int lastState = DisableIRQInterrupts();
        if (dsInfo->ds[dsInfo->writeIndex].aidBitmap == 0)
        {
            unsigned short newWI;
            unsigned short oldWI;
            unsigned short resetWI;
            int res;
            const unsigned short connectedAIDs = func_020d46fc();
            oldWI = dsInfo->writeIndex;
            newWI = (oldWI + 1) & (WM_DS_DATASET_NUM - 1);
            if (dsInfo->doubleMode == true)
                resetWI = (newWI + 1) & (WM_DS_DATASET_NUM - 1);
            else
                resetWI = newWI;
            func_020ca390(0, &dsInfo->ds[resetWI], sizeof(WMDataSet));
            dsInfo->ds[resetWI].aidBitmap = dsInfo->aidBitmap & (connectedAIDs | 1);
            dsInfo->writeIndex = newWI;
            dsInfo->ds[oldWI].aidBitmap = dsInfo->aidBitmap;
            // The parent's data isn't in the data set yet
            if (delayed == true)
                dsInfo->ds[oldWI].aidBitmap &= ~1;
            SetIRQInterruptState(lastState);
            res = func_020d59bc(func_020d6318, dsInfo, (unsigned short*)&dsInfo->ds[oldWI], dsInfo->dataSetLength,
                                dsInfo->aidBitmap & connectedAIDs, dsInfo->port, WM_PRIORITY_HIGH);
            if (res == WM_ERRCODE_NO_CHILD)
            {
                dsInfo->seqNum[oldWI] = 0xffff;
                dsInfo->sendIndex = (dsInfo->sendIndex + 1) & (WM_DS_DATASET_NUM - 1);
            }
            else if (res != WM_ERRCODE_SUCCESS && res != WM_ERRCODE_OPERATING)
            {
                dsInfo->state = WM_DS_STATE_ERROR;
            }
        }
        else
        {
            SetIRQInterruptState(lastState);
        }
    }

    // WM_GetSharedDataAddress: where a console's data is in a data set
    unsigned short* func_020d6830(WMDataSharingInfo* dsInfo, WMDataSet* receiveData, unsigned short aid)
    {
        const unsigned short aidBitmap = receiveData->aidBitmap;
        const unsigned short receivedBitmap = receiveData->receivedBitmap;
        const unsigned long aidBit = 1 << aid;
        if (dsInfo == NULL)
            return NULL;
        if (receiveData == NULL)
            return NULL;
        if (!(aidBitmap & aidBit))
            return NULL;
        if (!(receivedBitmap & aidBit))
            return NULL;
        return func_020d6884(dsInfo, aidBitmap, receiveData->data, aid);
    }

    // WmGetSharedDataAddress: the consoles' data are in the order of their AIDs
    static unsigned short* func_020d6884(WMDataSharingInfo* dsInfo, unsigned long aidBitmap,
                                         unsigned short* receiveBuf, unsigned long aid)
    {
        const unsigned long mask = (1 << aid) - 1;
        const unsigned long count = func_020d1ae4(aidBitmap & mask);
        return (unsigned short*)((unsigned char*)receiveBuf + dsInfo->dataLength * count);
    }
}
