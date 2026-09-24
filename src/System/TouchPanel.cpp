#include "System/TouchPanel.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include "System/MathCoprocessor.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's tp.c: the touch panel. The ARM7 samples it, once or several times per frame (auto-sampling), and
// sends the results through IPC. TP_RequestSamplingAsync, TP_WaitRawResult, TP_GetCalibratedResult,
// TP_WaitCalibratedResult, TP_RequestSetStabilityAsync, TP_GetUnCalibratedPoint, TP_WaitAllBusy and TP_CheckBusy
// aren't in the ROM.

// The IPC command of the touch panel (the NitroSDK's PXI_FIFO_TAG_TOUCHPANEL)
#define IPC_COMMAND_TOUCH_PANEL 6

// What's sent through IPC (the NitroSDK's SPI_PXI_*): the first and last words of a command, which word it is, and
// the data (the command in the high byte)
#define SPI_START 0x2000000
#define SPI_END 0x1000000
#define SPI_INDEX_SHIFT 16
#define SPI_DATA_MASK 0xffff

// The results that the ARM7 sends (SPI_PXI_RESULT_*)
#define SPI_SUCCESS 0
#define SPI_INVALID_COMMAND 1
#define SPI_INVALID_PARAMETER 2
#define SPI_ILLEGAL_STATUS 3
#define SPI_EXCLUSIVE 4

// TPState
#define STATE_READY 0
#define STATE_AUTO_SAMPLING 2

// The raw values are 12 bits, and the calibration is in fixed point (TP_CALIBRATE_DOT_SCALE_SHIFT and
// TP_CALIBRATE_ORIGIN_SCALE_SHIFT)
#define RAW_MAX 0x1000
#define DOT_SCALE_SHIFT 8
#define ORIGIN_SCALE_SHIFT 2
#define DOT_INVERSE_SCALE_SHIFT (28 - DOT_SCALE_SHIFT)

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

// Where the ARM7 writes the last sample (the NitroSDK's OSSystemWork.touch_panel)
#define SYSTEM_TOUCH_PANEL ((unsigned short*)0x027fffaa)
// The user settings that the system copies from the NVRAM (the NitroSDK's NVRAMConfig)
#define USER_SETTINGS ((UserSettings*)0x027ffc80)

// SPITpData: a sample, as the ARM7 writes it
union SPITouchPanelData
{
    struct
    {
        unsigned long x : 12;
        unsigned long y : 12;
        unsigned long touch : 1;
        unsigned long validity : 2;
        unsigned long unused : 5;
    } e;
    unsigned long raw;
    unsigned short halves[2];
};

struct UserCalibration
{
    unsigned short rawX1; // 0
    unsigned short rawY1; // 2
    unsigned char x1; // 4
    unsigned char y1; // 5
    unsigned short rawX2; // 6
    unsigned short rawY2; // 8
    unsigned char x2; // a
    unsigned char y2; // b
};

struct UserSettings
{
    char unknown_0[0x58];
    UserCalibration touchPanel; // 58, the NitroSDK's NVRAMConfigTpData
};

// TPiCalibrateParam
struct Calibration
{
    long x0;
    long xDotSize;
    long xDotSizeInverse;
    long y0;
    long yDotSize;
    long yDotSizeInverse;
};

// TP_Init's initial
static unsigned short isInitialized;

// tpState
static struct
{
    TouchPanelCallback callback; // 0
    TouchPanelData sample; // 4, for TP_RequestSamplingAsync
    unsigned short index; // c, the last buffer that auto-sampling wrote
    unsigned short frequency; // e, samples per frame
    TouchPanelData* buffers; // 10
    unsigned short bufferCount; // 14
    Calibration calibration; // 18
    unsigned short isCalibrated; // 30
    volatile unsigned short state; // 32
    volatile unsigned short errors; // 34
    volatile unsigned short busy; // 36, the commands waiting for the ARM7
} state;

// TPi_AutoSamplingOn
static inline int SendAutoSamplingOn(unsigned short line, unsigned char frequency)
{
    if (0 > SendCommandToArm7(IPC_COMMAND_TOUCH_PANEL,
            SPI_START | (0 << SPI_INDEX_SHIFT) | (TOUCH_PANEL_AUTO_ON << 8) | (unsigned long)frequency, false))
    {
        return false;
    }
    if (0 > SendCommandToArm7(IPC_COMMAND_TOUCH_PANEL, SPI_END | (1 << SPI_INDEX_SHIFT) | (unsigned long)line, false))
    {
        return false;
    }
    return true;
}

// TPi_AutoSamplingOff
static inline int SendAutoSamplingOff()
{
    if (0 > SendCommandToArm7(IPC_COMMAND_TOUCH_PANEL,
            SPI_START | SPI_END | (0 << SPI_INDEX_SHIFT) | (TOUCH_PANEL_AUTO_OFF << 8), false))
    {
        return false;
    }
    return true;
}

// NitroSDK's C copies a structure as a block, and C++ member by member
struct SampleCopy
{
    unsigned short data[4];
};

static inline void CopySample(TouchPanelData* dst, const TouchPanelData* src)
{
    *(SampleCopy*)dst = *(const SampleCopy*)src;
}

// TPi_CopyTpFromSystemWork
static inline void CopySystemSample(TouchPanelData* result)
{
    SPITouchPanelData sample;

    sample.halves[0] = SYSTEM_TOUCH_PANEL[0];
    sample.halves[1] = SYSTEM_TOUCH_PANEL[1];
    result->x = (unsigned short)sample.e.x;
    result->y = (unsigned short)sample.e.y;
    result->touch = (unsigned char)sample.e.touch;
    result->validity = (unsigned char)sample.e.validity;
}

// TPi_ErrorAtPxi
static inline void OnSendError(int command)
{
    state.errors |= 1 << command;
    if (state.callback)
    {
        state.callback(command, TOUCH_PANEL_PXI_BUSY, 0);
    }
}

extern "C"
{
    // usa: func_020c9be0
    // OS_Terminate
    void func_020c9be0();

    // usa: func_020cd610
    // TPi_TpCallback: receives the ARM7's results
    void func_020cd610(unsigned int command, unsigned int data, unsigned int error)
    {
        unsigned short result;
        unsigned short tpCommand;

        result = (unsigned short)(data & SPI_DATA_MASK);
        tpCommand = (unsigned short)((result & 0x7f00) >> 8);

        if (error)
        {
            OnSendError(tpCommand);
            return;
        }

        if (tpCommand == TOUCH_PANEL_AUTO_SAMPLING)
        {
            state.index++;
            if (state.index >= state.bufferCount)
            {
                state.index = 0;
            }

            CopySystemSample(&state.buffers[state.index]);

            if (state.callback)
            {
                state.callback(tpCommand, TOUCH_PANEL_SUCCESS, (unsigned char)state.index);
            }
            return;
        }

        if (!(data & SPI_END))
        {
            return;
        }

        switch ((unsigned char)(result & 0xff))
        {
        case SPI_SUCCESS:
            switch (tpCommand)
            {
            case TOUCH_PANEL_SAMPLING:
                CopySystemSample(&state.sample);
                state.state = STATE_READY;
                break;
            case TOUCH_PANEL_AUTO_ON:
                state.state = STATE_AUTO_SAMPLING;
                break;
            case TOUCH_PANEL_AUTO_OFF:
                state.state = STATE_READY;
                break;
            }

            state.busy &= ~(1 << tpCommand);

            if (state.callback)
            {
                state.callback(tpCommand, TOUCH_PANEL_SUCCESS, 0);
            }
            break;

        case SPI_EXCLUSIVE:
            result = TOUCH_PANEL_EXCLUSIVE;
            goto common;

        case SPI_INVALID_PARAMETER:
            result = TOUCH_PANEL_INVALID_PARAMETER;
            goto common;

        case SPI_ILLEGAL_STATUS:
            result = TOUCH_PANEL_ILLEGAL_STATUS;

        common:
            state.errors |= 1 << tpCommand;
            state.busy &= ~(1 << tpCommand);

            if (state.callback)
            {
                state.callback(tpCommand, result & 0xff, 0);
            }
            break;

        case SPI_INVALID_COMMAND:
        default:
            func_020c9be0();
            return;
        }
    }

    // usa: func_020cd890
    // TP_Init
    void func_020cd890()
    {
        if (isInitialized)
        {
            return;
        }
        isInitialized = true;

        InitializeInterProcessorCommunication();

        state.index = 0;
        state.callback = NULL;
        state.buffers = NULL;
        state.state = STATE_READY;
        state.isCalibrated = false;
        state.busy = 0;
        state.errors = 0;

        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_TOUCH_PANEL, IPCSide_Arm7))
        {
        }
        SetArm9IPCCommandHandler(IPC_COMMAND_TOUCH_PANEL, func_020cd610);
    }

    // usa: func_020cd908
    // TP_GetUserInfo: the calibration in the user settings, or none if it's not valid. Always returns true.
    int func_020cd908(TouchPanelCalibration* calibration)
    {
        UserSettings* settings = USER_SETTINGS;
        unsigned short rawX1, rawY1, rawX2, rawY2, x1, y1, x2, y2;

        rawX1 = settings->touchPanel.rawX1;
        rawY1 = settings->touchPanel.rawY1;
        x1 = (unsigned short)settings->touchPanel.x1;
        y1 = (unsigned short)settings->touchPanel.y1;
        rawX2 = settings->touchPanel.rawX2;
        rawY2 = settings->touchPanel.rawY2;
        x2 = (unsigned short)settings->touchPanel.x2;
        y2 = (unsigned short)settings->touchPanel.y2;

        if (rawX1 == 0 && rawX2 == 0 && rawY1 == 0 && rawY2 == 0 ||
            func_020cddec(calibration, rawX1, rawY1, x1, y1, rawX2, rawY2, x2, y2) != 0)
        {
            calibration->x0 = 0;
            calibration->y0 = 0;
            calibration->xDotSize = 0;
            calibration->yDotSize = 0;
            return true;
        }
        return true;
    }

    // usa: func_020cd99c
    // TP_SetCalibrateParam: sets the calibration, or none if it's NULL
    void func_020cd99c(const TouchPanelCalibration* calibration)
    {
        int priorState;

        if (calibration == NULL)
        {
            state.isCalibrated = false;
            return;
        }

        priorState = DisableIRQInterrupts();

        if (calibration->xDotSize != 0)
        {
            StartDivision32_32(0x10000000, (unsigned long)calibration->xDotSize);
            state.calibration.x0 = calibration->x0;
            state.calibration.xDotSize = calibration->xDotSize;
            state.calibration.xDotSizeInverse = GetDivisionResult32();
        }
        else
        {
            state.calibration.x0 = 0;
            state.calibration.xDotSize = 0;
            state.calibration.xDotSizeInverse = 0;
        }

        if (calibration->yDotSize != 0)
        {
            StartDivision32_32(0x10000000, (unsigned long)calibration->yDotSize);
            state.calibration.y0 = calibration->y0;
            state.calibration.yDotSize = calibration->yDotSize;
            state.calibration.yDotSizeInverse = GetDivisionResult32();
        }
        else
        {
            state.calibration.y0 = 0;
            state.calibration.yDotSize = 0;
            state.calibration.yDotSizeInverse = 0;
        }

        SetIRQInterruptState(priorState);

        state.isCalibrated = true;
    }

    // usa: func_020cdac4
    // TP_SetCallback
    void func_020cdac4(TouchPanelCallback callback)
    {
        int priorState = DisableIRQInterrupts();
        state.callback = callback;
        SetIRQInterruptState(priorState);
    }

    // usa: func_020cdae4
    // TP_RequestAutoSamplingStartAsync: samples frequency times per frame, starting at a line, into a ring of buffers
    void func_020cdae4(unsigned short line, unsigned short frequency, TouchPanelData* buffers, unsigned short count)
    {
        unsigned long i;
        int priorState;

        state.buffers = buffers;
        state.index = 0;
        state.frequency = frequency;
        state.bufferCount = count;

        for (i = 0; i < count; i++)
        {
            state.buffers[i].touch = false;
        }

        priorState = DisableIRQInterrupts();

        if ((unsigned char)SendAutoSamplingOn(line, (unsigned char)frequency) == false)
        {
            SetIRQInterruptState(priorState);
            OnSendError(TOUCH_PANEL_AUTO_ON);
            return;
        }
        state.busy |= 1 << TOUCH_PANEL_AUTO_ON;
        state.errors &= ~(1 << TOUCH_PANEL_AUTO_ON);

        SetIRQInterruptState(priorState);
    }

    // usa: func_020cdbe4
    // TP_RequestAutoSamplingStopAsync
    void func_020cdbe4()
    {
        int priorState = DisableIRQInterrupts();

        if (SendAutoSamplingOff() == false)
        {
            SetIRQInterruptState(priorState);
            OnSendError(TOUCH_PANEL_AUTO_OFF);
            return;
        }
        state.busy |= 1 << TOUCH_PANEL_AUTO_OFF;
        state.errors &= ~(1 << TOUCH_PANEL_AUTO_OFF);

        SetIRQInterruptState(priorState);
    }

    // usa: func_020cdc7c
    // TP_GetLatestRawPointInAuto: the last sample, with the coordinates of the previous samples of the frame if they
    // aren't valid
    void func_020cdc7c(TouchPanelData* result)
    {
        long i, current;
        TouchPanelData* sample;

        result->validity = TOUCH_PANEL_INVALID_X | TOUCH_PANEL_INVALID_Y;

        current = state.index;

        if (state.frequency == 1 || state.bufferCount == 1)
        {
            CopySample(result, &state.buffers[current]);
            return;
        }

        for (i = 0; i < state.frequency && i < state.bufferCount - 1; i++)
        {
            long index;

            index = current - i;
            if (index < 0)
            {
                index += state.bufferCount;
            }

            sample = &state.buffers[index];

            if (!sample->touch)
            {
                CopySample(result, sample);
                return;
            }

            if (result->validity & TOUCH_PANEL_INVALID_X)
            {
                if (!(sample->validity & TOUCH_PANEL_INVALID_X))
                {
                    result->x = sample->x;
                    if (i != 0)
                    {
                        result->validity &= ~TOUCH_PANEL_INVALID_X;
                    }
                }
            }

            if (result->validity & TOUCH_PANEL_INVALID_Y)
            {
                if (!(sample->validity & TOUCH_PANEL_INVALID_Y))
                {
                    result->y = sample->y;
                    if (i != 0)
                    {
                        result->validity &= ~TOUCH_PANEL_INVALID_Y;
                    }
                }
            }

            if (result->validity == 0)
            {
                result->touch = true;
                return;
            }
        }

        result->touch = true;
        return;
    }

    // usa: func_020cddc0
    // TP_GetLatestCalibratedPointInAuto
    void func_020cddc0(TouchPanelData* result)
    {
        func_020cdc7c(result);
        func_020cdfd8(result, result);
    }

    // usa: func_020cdddc
    // TP_GetLatestIndexInAuto
    unsigned short func_020cdddc()
    {
        return state.index;
    }

// The calibration's values are 16-bit
#define IN_SHORT_RANGE(x) ((x) < 0x8000 && (x) >= -0x8000)

    // usa: func_020cddec
    // TP_CalcCalibrateParam: the calibration from two points and their raw values. Returns 0 if it's valid.
    unsigned long func_020cddec(TouchPanelCalibration* calibration, unsigned short rawX1, unsigned short rawY1,
        unsigned short x1, unsigned short y1, unsigned short rawX2, unsigned short rawY2, unsigned short x2,
        unsigned short y2)
    {
        long rawWidth, width, rawHeight, height;
        long value;
        int priorState;

        if (rawX1 >= RAW_MAX || rawY1 >= RAW_MAX || rawX2 >= RAW_MAX || rawY2 >= RAW_MAX)
        {
            return 1;
        }
        if (x1 >= SCREEN_WIDTH || x2 >= SCREEN_WIDTH || y1 >= SCREEN_HEIGHT || y2 >= SCREEN_HEIGHT)
        {
            return 1;
        }
        if (x1 == x2 || y1 == y2 || rawX1 == rawX2 || rawY1 == rawY2)
        {
            return 1;
        }

        rawWidth = rawX1 - rawX2;
        width = x1 - x2;

        priorState = DisableIRQInterrupts();

        StartDivision32_32((unsigned long)rawWidth << DOT_SCALE_SHIFT, (unsigned long)width);

        rawHeight = rawY1 - rawY2;
        height = y1 - y2;

        value = GetDivisionResult32();
        StartDivision32_32((unsigned long)rawHeight << DOT_SCALE_SHIFT, (unsigned long)height);

        if (!IN_SHORT_RANGE(value))
        {
            SetIRQInterruptState(priorState);
            return 1;
        }
        calibration->xDotSize = (short)value;
        value = (short)((((long)(rawX1 + rawX2) << DOT_SCALE_SHIFT) - ((long)(x1 + x2) * calibration->xDotSize)) >>
            (DOT_SCALE_SHIFT - ORIGIN_SCALE_SHIFT + 1));
        if (!IN_SHORT_RANGE(value))
        {
            SetIRQInterruptState(priorState);
            return 1;
        }
        calibration->x0 = (short)value;

        value = GetDivisionResult32();
        SetIRQInterruptState(priorState);

        if (!IN_SHORT_RANGE(value))
        {
            return 1;
        }
        calibration->yDotSize = (short)value;
        value = (short)((((long)(rawY1 + rawY2) << DOT_SCALE_SHIFT) - ((long)(y1 + y2) * calibration->yDotSize)) >>
            (DOT_SCALE_SHIFT - ORIGIN_SCALE_SHIFT + 1));
        if (!IN_SHORT_RANGE(value))
        {
            return 1;
        }
        calibration->y0 = (short)value;

        return 0;
    }

    // usa: func_020cdfd8
    // TP_GetCalibratedPoint: translates a raw sample to pixels
    void func_020cdfd8(TouchPanelData* result, const TouchPanelData* raw)
    {
        Calibration* calibration;

        if (!state.isCalibrated)
        {
            CopySample(result, raw);
            return;
        }

        calibration = &state.calibration;

        result->touch = raw->touch;
        result->validity = raw->validity;

        if (raw->touch == 0)
        {
            result->x = 0;
            result->y = 0;
            return;
        }

        result->x = (unsigned short)((((unsigned long long)(raw->x << ORIGIN_SCALE_SHIFT) - calibration->x0) *
            calibration->xDotSizeInverse) >> (DOT_INVERSE_SCALE_SHIFT + ORIGIN_SCALE_SHIFT));
        if ((short)result->x < 0)
        {
            result->x = 0;
        }
        else if ((short)result->x > SCREEN_WIDTH - 1)
        {
            result->x = SCREEN_WIDTH - 1;
        }

        result->y = (unsigned short)((((unsigned long long)(raw->y << ORIGIN_SCALE_SHIFT) - calibration->y0) *
            calibration->yDotSizeInverse) >> (DOT_INVERSE_SCALE_SHIFT + ORIGIN_SCALE_SHIFT));
        if ((short)result->y < 0)
        {
            result->y = 0;
        }
        else if ((short)result->y > SCREEN_HEIGHT - 1)
        {
            result->y = SCREEN_HEIGHT - 1;
        }
    }

    // usa: func_020ce0fc
    // TP_WaitBusy: waits for the ARM7 to finish the commands
    void func_020ce0fc(unsigned long commands)
    {
        while (state.busy & commands)
        {
        }
        return;
    }

    // usa: func_020ce114
    // TP_CheckError
    unsigned long func_020ce114(unsigned long commands)
    {
        return (unsigned long)(state.errors & commands);
    }
}
