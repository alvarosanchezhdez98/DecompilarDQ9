#pragma once
#include <globaldefs.h>

// The NitroSDK's wireless manager (WM), the ARM9's side: it sends the API's commands to the ARM7, which runs the
// wireless hardware, and calls the callbacks with its answers

// The API's commands (WMApiid)
enum
{
    WM_APIID_INITIALIZE = 0x00,
    WM_APIID_RESET = 0x01,
    WM_APIID_END = 0x02,
    WM_APIID_ENABLE = 0x03,
    WM_APIID_DISABLE = 0x04,
    WM_APIID_POWER_ON = 0x05,
    WM_APIID_POWER_OFF = 0x06,
    WM_APIID_SET_P_PARAM = 0x07,
    WM_APIID_START_PARENT = 0x08,
    WM_APIID_END_PARENT = 0x09,
    WM_APIID_START_SCAN = 0x0a,
    WM_APIID_END_SCAN = 0x0b,
    WM_APIID_START_CONNECT = 0x0c,
    WM_APIID_DISCONNECT = 0x0d,
    WM_APIID_START_MP = 0x0e,
    WM_APIID_SET_MP_DATA = 0x0f,
    WM_APIID_END_MP = 0x10,
    WM_APIID_START_DCF = 0x11,
    WM_APIID_SET_DCF_DATA = 0x12,
    WM_APIID_END_DCF = 0x13,
    WM_APIID_SET_WEPKEY = 0x14,
    WM_APIID_START_KS = 0x15,
    WM_APIID_END_KS = 0x16,
    WM_APIID_GET_KEYSET = 0x17,
    WM_APIID_SET_GAMEINFO = 0x18,
    WM_APIID_SET_BEACON_IND = 0x19,
    WM_APIID_START_TESTMODE = 0x1a,
    WM_APIID_STOP_TESTMODE = 0x1b,
    WM_APIID_VALARM_MP = 0x1c,
    WM_APIID_SET_LIFETIME = 0x1d,
    WM_APIID_MEASURE_CHANNEL = 0x1e,
    WM_APIID_INIT_W_COUNTER = 0x1f,
    WM_APIID_GET_W_COUNTER = 0x20,
    WM_APIID_SET_ENTRY = 0x21,
    WM_APIID_AUTO_DEAUTH = 0x22,
    WM_APIID_SET_MP_PARAMETER = 0x23,
    WM_APIID_SET_BEACON_PERIOD = 0x24,
    WM_APIID_AUTO_DISCONNECT = 0x25,
    WM_APIID_START_SCAN_EX = 0x26,
    WM_APIID_SET_WEPKEY_EX = 0x27,
    WM_APIID_SET_PS_MODE = 0x28,
    WM_APIID_START_TESTRXMODE = 0x29,
    WM_APIID_STOP_TESTRXMODE = 0x2a,
    WM_APIID_KICK_MP_PARENT = 0x2b,
    // WM_NUM_OF_CALLBACK: the commands that have a callback in WMArm9Buf's table
    WM_NUM_OF_CALLBACK = 0x2c,
    WM_APIID_INDICATION = 0x80,
    WM_APIID_PORT_SEND = 0x81,
    WM_APIID_PORT_RECV = 0x82,
};

// WMErrCode
enum
{
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_ILLEGAL_STATE = 3,
    WM_ERRCODE_WM_DISABLE = 4,
    WM_ERRCODE_NO_KEYSET = 5,
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7,
    WM_ERRCODE_FIFO_ERROR = 8,
    WM_ERRCODE_TIMEOUT = 9,
    WM_ERRCODE_SEND_QUEUE_FULL = 10,
    WM_ERRCODE_NO_ENTRY = 11,
    WM_ERRCODE_OVER_MAX_ENTRY = 12,
    WM_ERRCODE_INVALID_POLLBITMAP = 13,
    WM_ERRCODE_NO_DATA = 14,
    WM_ERRCODE_SEND_FAILED = 15,
    WM_ERRCODE_DCF_TEST = 16,
    WM_ERRCODE_WL_INVALID_PARAM = 17,
    WM_ERRCODE_WL_LENGTH_ERR = 18,
    WM_ERRCODE_FLASH_ERROR = 19,
};

// WMState: the ARM7's state
enum
{
    WM_STATE_READY = 0,
    WM_STATE_STOP = 1,
    WM_STATE_IDLE = 2,
    WM_STATE_CLASS1 = 3,
    WM_STATE_TESTMODE = 4,
    WM_STATE_SCAN = 5,
    WM_STATE_CONNECT = 6,
    WM_STATE_PARENT = 7,
    WM_STATE_CHILD = 8,
    WM_STATE_MP_PARENT = 9,
    WM_STATE_MP_CHILD = 10,
    WM_STATE_DCF_CHILD = 11,
    WM_STATE_TESTMODE_RX = 12,
};

// WMStateCode: what the callbacks' state says
enum
{
    WM_STATECODE_CONNECTED = 7,
    WM_STATECODE_DISCONNECTED = 9,
    // The MP communication's answers that bring data
    WM_STATECODE_MP_IND = 11,
    WM_STATECODE_MPACK_IND = 12,
    // A port received data
    WM_STATECODE_PORT_RECV = 21,
    // What a port's callback gets when it's set
    WM_STATECODE_PORT_INIT = 25,
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26,
};

// WMPriorityLevel: the priority of the data that MP communication sends
enum
{
    WM_PRIORITY_URGENT = 0,
    WM_PRIORITY_HIGH = 1,
    WM_PRIORITY_NORMAL = 2,
    WM_PRIORITY_LOW = 3,
};

typedef void (*WMCallbackFunc)(void* arg);

// WMStatus: the state that the ARM7 shares. Only the members that the ARM9 reads are named.
struct WMStatus
{
    unsigned short state;
    char unk_2[0xc - 0x2];
    // Whether MP communication and DCF communication are running
    unsigned long mp_flag;
    unsigned long dcf_flag;
    char unk_14[0x3c - 0x14];
    // The sizes of the data that MP communication sends and receives
    unsigned short mp_sendSize;
    unsigned short mp_recvSize;
    char unk_40[0x72 - 0x40];
    // The size of the buffer of the data that MP communication receives
    unsigned short mp_recvBufSize;
    char unk_74[0x7c - 0x74];
    // The buffer of the data that MP communication is sending
    unsigned long* mp_sendBuf;
    char unk_80[0x86 - 0x80];
    // Probably the children that are ready for MP communication: WM_SetMPDataToPortEx invalidates it but doesn't read it
    unsigned short mp_readyBitmap;
    char unk_88[0x9c - 0x88];
    // Whether WM_StartMP doesn't check the sizes of the buffers
    unsigned short mp_ignoreSizePrecheckMode;
    char unk_9e[0xbc - 0x9e];
    unsigned short linkLevel;
    char unk_be[0xc6 - 0xbe];
    // The child's power management: 1 while it's always awake, which MP communication needs
    unsigned short pwrMgtMode;
    char unk_c8[0xf8 - 0xc8];
    // The parent's parameters (WMParentParam): maxEntry
    unsigned short pparam_maxEntry;
    char unk_fa[0x182 - 0xfa];
    // The children that are connected
    unsigned short child_bitmap;
    char unk_184[0x188 - 0x184];
    unsigned short aid;
    char unk_18a[0x800 - 0x18a];
};

// WMArm9Buf: the wireless manager's work, in the buffer that WM_Init takes
struct WMArm9Buf
{
    void* WM7;
    WMStatus* status;
    unsigned long* indbuf;
    unsigned long* fifo9to7;
    unsigned long* fifo7to9;
    unsigned short dmaNo;
    // Whether WM_InitializeForListening initialized it, to scan only
    unsigned short scanOnlyFlag;
    WMCallbackFunc CallbackTable[WM_NUM_OF_CALLBACK];
    WMCallbackFunc indCallback;
    WMCallbackFunc portCallbackTable[16];
    void* portCallbackArgument[16];
    unsigned long connectedAidBitmap;
    unsigned short myAid;
};

// The first members of the ARM7's answers (WMCallback)
struct WMCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short wlCmdID;
    unsigned short wlResult;
};

// What the callbacks of the data that a port sent get (WMPortSendCallback)
struct WMPortSendCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short wlCmdID;
    unsigned short wlResult;
    unsigned short state;
    unsigned short port;
    unsigned short destBitmap;
    unsigned short restBitmap;
    unsigned short sentBitmap;
    unsigned short rsv;
    const unsigned short* data;
    unsigned short length;
    unsigned short seqNo;
    WMCallbackFunc callback;
    void* arg;
    unsigned short maxSendDataSize;
    unsigned short maxRecvDataSize;
};

// What the ports' callbacks get (WMPortRecvCallback)
struct WMPortRecvCallback
{
    unsigned short apiid;
    unsigned short errcode;
    unsigned short state;
    unsigned short port;
    void* recvBuf;
    void* data;
    unsigned short length;
    unsigned short aid;
    unsigned char macAddress[6];
    unsigned short seqNo;
    void* arg;
    unsigned short myAid;
    unsigned short connectedAidBitmap;
    unsigned char ssid[24];
    unsigned short reason;
    unsigned short rssi;
    unsigned short maxSendDataSize;
    unsigned short maxRecvDataSize;
};

extern "C"
{
    // WMi_SetCallbackTable
    void func_020d404c(int id, WMCallbackFunc callback);
    // WMi_SendCommand
    int func_020d40bc(int id, unsigned short paramNum, ...);
    // WMi_SendCommandDirect
    int func_020d4168(const void* data, unsigned long length);
    // WMi_GetSystemWork
    WMArm9Buf* func_020d41d8();
    // WMi_CheckInitialized
    int func_020d41e8();
    // WMi_CheckIdle
    int func_020d4204();
    // WMi_CheckStateEx
    int func_020d424c(int paramNum, ...);
    // WM_Finish
    int func_020d3fdc();
    // WM_GetAID and WM_GetConnectedAIDs
    unsigned short func_020d46cc();
    unsigned short func_020d46fc();
    // WM_SetPortCallback
    int func_020d4770(unsigned short port, WMCallbackFunc callback, void* arg);
    // WM_SetMPDataToPortEx
    int func_020d59bc(WMCallbackFunc callback, void* arg, const unsigned short* sendData, unsigned short sendDataSize,
                      unsigned short destBitmap, unsigned short port, unsigned short prio);
}
