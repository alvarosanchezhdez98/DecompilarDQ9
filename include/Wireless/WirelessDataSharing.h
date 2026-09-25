#pragma once
#include "Wireless/WirelessManager.h"

// The NitroSDK's data sharing (wm_ds.c): each frame, every console that MP communication connects gets the same data
// set, with a part from each of them. The parent sends the sets, and each child sends its part back.

// WM_DS_DATA_SIZE: the size of a data set's data
#define WM_DS_DATA_SIZE 508
// WM_DS_DATASET_NUM: how many data sets the ring buffer has
#define WM_DS_DATASET_NUM 4

// The state of data sharing (WMDataSharingState)
enum
{
    WM_DS_STATE_READY = 0,
    WM_DS_STATE_START = 1,
    WM_DS_STATE_PAUSING = 2,
    WM_DS_STATE_PAUSED = 3,
    // The data couldn't be sent because the queue was full: WM_StepDataSharing sends it again
    WM_DS_STATE_RETRY_SEND = 4,
    WM_DS_STATE_ERROR = 5,
};

// A data set (WMDataSet)
struct WMDataSet
{
    // The consoles whose data it still waits for
    unsigned short aidBitmap;
    // The consoles whose data it got
    unsigned short receivedBitmap;
    unsigned short data[WM_DS_DATA_SIZE / sizeof(unsigned short)];
};

// The work of data sharing (WMDataSharingInfo)
struct WMDataSharingInfo
{
    WMDataSet ds[WM_DS_DATASET_NUM];
    // The sequence numbers of MP communication that sent the data sets
    unsigned short seqNum[WM_DS_DATASET_NUM];
    // The data set that receives, the one that's being sent, and the one that WM_StepDataSharing reads next
    unsigned short writeIndex;
    unsigned short sendIndex;
    unsigned short readIndex;
    // The consoles that share data
    unsigned short aidBitmap;
    // The data of each console, and how many consoles share it
    unsigned short dataLength;
    unsigned short stationNumber;
    // The size of a data set that MP communication sends: the header and the data of every console
    unsigned short dataSetLength;
    unsigned short port;
    // Whether the parent sends 2 data sets each frame
    unsigned short doubleMode;
    unsigned short currentSeqNum;
    unsigned short state;
    unsigned short reserved[1];
};

extern "C"
{
    // WM_StartDataSharing
    int func_020d5d34(WMDataSharingInfo* dsInfo, unsigned short port, unsigned short aidBitmap,
                      unsigned short dataLength, int doubleMode);
    // WM_EndDataSharing
    int func_020d5f88(WMDataSharingInfo* dsInfo);
    // WM_StepDataSharing
    int func_020d5fd0(WMDataSharingInfo* dsInfo, const unsigned short* sendData, WMDataSet* receiveData);
    // WM_GetSharedDataAddress
    unsigned short* func_020d6830(WMDataSharingInfo* dsInfo, WMDataSet* receiveData, unsigned short aid);
}
