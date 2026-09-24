#pragma once

// The NitroSDK's touch panel library (TP), which asks the ARM7 for the touch panel's samples

// TPData: a sample
struct TouchPanelData
{
    unsigned short x; // 0
    unsigned short y; // 2
    unsigned short touch; // 4
    unsigned short validity; // 6, TOUCH_PANEL_INVALID_X and TOUCH_PANEL_INVALID_Y
};

#define TOUCH_PANEL_INVALID_X 1
#define TOUCH_PANEL_INVALID_Y 2

// TPCalibrateParam: how the samples translate to pixels
struct TouchPanelCalibration
{
    short x0; // 0
    short y0; // 2
    short xDotSize; // 4
    short yDotSize; // 6
};

// TPRequestCommand, and the bits of each one in the flags (TPRequestCommandFlag)
#define TOUCH_PANEL_SAMPLING 0
#define TOUCH_PANEL_AUTO_ON 1
#define TOUCH_PANEL_AUTO_OFF 2
#define TOUCH_PANEL_SET_STABILITY 3
#define TOUCH_PANEL_AUTO_SAMPLING 0x10

// TPRequestResult
#define TOUCH_PANEL_SUCCESS 0
#define TOUCH_PANEL_INVALID_PARAMETER 1
#define TOUCH_PANEL_ILLEGAL_STATUS 2
#define TOUCH_PANEL_EXCLUSIVE 3
#define TOUCH_PANEL_PXI_BUSY 4

// TPRecvCallback
typedef void (*TouchPanelCallback)(int command, int result, unsigned short index);

extern "C"
{
    // usa: func_020cd890
    // TP_Init
    void func_020cd890();
    // usa: func_020cd908
    // TP_GetUserInfo: the calibration in the user settings
    int func_020cd908(TouchPanelCalibration* calibration);
    // usa: func_020cd99c
    // TP_SetCalibrateParam
    void func_020cd99c(const TouchPanelCalibration* calibration);
    // usa: func_020cdac4
    // TP_SetCallback
    void func_020cdac4(TouchPanelCallback callback);
    // usa: func_020cdae4
    // TP_RequestAutoSamplingStartAsync
    void func_020cdae4(unsigned short line, unsigned short frequency, TouchPanelData* buffers, unsigned short count);
    // usa: func_020cdbe4
    // TP_RequestAutoSamplingStopAsync
    void func_020cdbe4();
    // usa: func_020cdc7c
    // TP_GetLatestRawPointInAuto
    void func_020cdc7c(TouchPanelData* result);
    // usa: func_020cddc0
    // TP_GetLatestCalibratedPointInAuto
    void func_020cddc0(TouchPanelData* result);
    // usa: func_020cdddc
    // TP_GetLatestIndexInAuto
    unsigned short func_020cdddc();
    // usa: func_020cddec
    // TP_CalcCalibrateParam
    unsigned long func_020cddec(TouchPanelCalibration* calibration, unsigned short rawX1, unsigned short rawY1,
        unsigned short x1, unsigned short y1, unsigned short rawX2, unsigned short rawY2, unsigned short x2,
        unsigned short y2);
    // usa: func_020cdfd8
    // TP_GetCalibratedPoint
    void func_020cdfd8(TouchPanelData* result, const TouchPanelData* raw);
    // usa: func_020ce0fc
    // TP_WaitBusy
    void func_020ce0fc(unsigned long commands);
    // usa: func_020ce114
    // TP_CheckError
    unsigned long func_020ce114(unsigned long commands);
}
