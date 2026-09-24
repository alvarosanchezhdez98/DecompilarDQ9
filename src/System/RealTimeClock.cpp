#include "System/RealTimeClock.h"
#include "System/IPC.h"
#include "System/Interrupts.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's rtc_external.c: gets the date and the time from the ARM7, which reads them from the clock into the
// system's work area. Only the functions that get them are in the ROM, not those that set them, the alarms or
// RTC_GetDateTimeExByTick.

// The IPC command of the real-time clock (the NitroSDK's PXI_FIFO_TAG_RTC), and what the ARM7 sends with it: the
// command that it answers and the result (RTC_PXI_*)
#define IPC_COMMAND_REAL_TIME_CLOCK 5
#define RTC_COMMAND_MASK 0x7f00
#define RTC_COMMAND_SHIFT 8
#define RTC_RESULT_MASK 0xff
#define RTC_COMMAND_INTERRUPT 0x30

#define RTC_PXI_SUCCESS 0
#define RTC_PXI_INVALID_COMMAND 1
#define RTC_PXI_ILLEGAL_STATUS 2
#define RTC_PXI_BUSY 3
#define RTC_PXI_FATAL_ERROR 4

// RTCSequence: what the ARM7 answers to
enum
{
    SEQUENCE_GET_DATE,
    SEQUENCE_GET_TIME,
    SEQUENCE_GET_DATETIME,
    SEQUENCE_SET_DATE,
    SEQUENCE_SET_TIME,
    SEQUENCE_SET_DATETIME,
    SEQUENCE_GET_ALARM1_STATUS,
    SEQUENCE_GET_ALARM2_STATUS,
    SEQUENCE_GET_ALARM_PARAM,
    SEQUENCE_SET_ALARM1_STATUS,
    SEQUENCE_SET_ALARM2_STATUS,
    SEQUENCE_SET_ALARM1_PARAM,
    SEQUENCE_SET_ALARM2_PARAM,
    SEQUENCE_SET_HOUR_FORMAT,
    SEQUENCE_SET_REG_STATUS2,
    SEQUENCE_SET_REG_ADJUST
};

// RTCInterruptMode
#define INTERRUPT_MODE_NONE 0
#define INTERRUPT_MODE_ALARM 4

// RTCAlarmStatus and RTCAlarmEnable
#define ALARM_OFF 0
#define ALARM_ON 1
#define ALARM_ENABLE_WEEK 1
#define ALARM_ENABLE_HOUR 2
#define ALARM_ENABLE_MINUTE 4

// The clock's registers, in BCD (the NitroSDK's RTCRawDate, RTCRawTime, RTCRawStatus2 and RTCRawAlarm)
struct RawDate
{
    unsigned long year : 8;
    unsigned long month : 5;
    unsigned long : 3;
    unsigned long day : 6;
    unsigned long : 2;
    unsigned long dayOfWeek : 3;
    unsigned long : 5;
};

struct RawTime
{
    unsigned long hour : 6;
    unsigned long afternoon : 1;
    unsigned long : 1;
    unsigned long minute : 7;
    unsigned long : 1;
    unsigned long second : 7;
    unsigned long : 9;
};

struct RawStatus2
{
    unsigned short interruptMode : 4;
    unsigned short : 2;
    unsigned short interrupt2Mode : 1;
    unsigned short test : 1;
    unsigned short : 8;
};

struct RawAlarm
{
    unsigned long dayOfWeek : 3;
    unsigned long : 4;
    unsigned long dayOfWeekEnabled : 1;
    unsigned long hour : 6;
    unsigned long afternoon : 1;
    unsigned long hourEnabled : 1;
    unsigned long minute : 7;
    unsigned long minuteEnabled : 1;
    unsigned long : 8;
};

// RTCRawData, which the ARM7 writes in the system's work area (the NitroSDK's OSSystemWork.real_time_clock)
union RawData
{
    struct
    {
        RawDate date;
        RawTime time;
    } t;
    struct
    {
        unsigned short status1;
        RawStatus2 status2;
        RawAlarm alarm;
    } a;
};

#define RAW_DATA ((RawData*)0x027ffde8)

// RTCAlarmParam
struct AlarmParam
{
    unsigned long dayOfWeek;
    unsigned long hour;
    unsigned long minute;
    unsigned long enable;
};

// RTCWork
struct Work
{
    unsigned long lock; // 0
    RealTimeClockCallback callback; // 4
    void* buffers[2]; // 8
    void* callbackArg; // 10
    unsigned long sequence; // 14
    unsigned long index; // 18, a step of the sequence
    void (*interrupt)(); // 1c
    int commonResult; // 20, for the functions that wait for the result
};

// rtcInitialized
static unsigned short isInitialized;
// rtcWork
static Work rtcWork;
// rtcInitialTotalTicks and rtcTickInitialized, for RTC_GetDateTimeExByTick, which isn't in the ROM
static unsigned long long initialTotalTicks;
static unsigned short isTickInitialized;

extern "C"
{
    void func_020cf294(unsigned int command, unsigned int data, unsigned int error);
    unsigned long func_020cf7e4(unsigned long bcd);
    void func_020cf854(int result, void* arg);
    void func_020cf864();

    // usa: func_020cf020
    // RTC_Init
    void func_020cf020()
    {
        if (isInitialized)
        {
            return;
        }
        isInitialized = true;

        rtcWork.lock = false;
        rtcWork.callback = NULL;
        rtcWork.interrupt = NULL;
        rtcWork.buffers[0] = NULL;
        rtcWork.buffers[1] = NULL;

        InitializeInterProcessorCommunication();
        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_REAL_TIME_CLOCK, IPCSide_Arm7))
        {
        }
        SetArm9IPCCommandHandler(IPC_COMMAND_REAL_TIME_CLOCK, func_020cf294);
    }

    // usa: func_020cf08c
    // RTC_GetDateAsync
    int func_020cf08c(RealTimeClockDate* date, RealTimeClockCallback callback, void* arg)
    {
        int priorState = DisableIRQInterrupts();

        if (rtcWork.lock != false)
        {
            SetIRQInterruptState(priorState);
            return REAL_TIME_CLOCK_BUSY;
        }
        rtcWork.lock = true;
        SetIRQInterruptState(priorState);

        rtcWork.sequence = SEQUENCE_GET_DATE;
        rtcWork.index = 0;
        rtcWork.buffers[0] = date;
        rtcWork.callback = callback;
        rtcWork.callbackArg = arg;

        if (func_020cf88c())
        {
            return REAL_TIME_CLOCK_SUCCESS;
        }
        else
        {
            return REAL_TIME_CLOCK_SEND_ERROR;
        }
    }

    // usa: func_020cf0fc
    // RTC_GetDate
    int func_020cf0fc(RealTimeClockDate* date)
    {
        rtcWork.commonResult = func_020cf08c(date, func_020cf854, NULL);
        if (rtcWork.commonResult == REAL_TIME_CLOCK_SUCCESS)
        {
            func_020cf864();
        }
        return rtcWork.commonResult;
    }

    // usa: func_020cf134
    // RTC_GetTimeAsync
    int func_020cf134(RealTimeClockTime* time, RealTimeClockCallback callback, void* arg)
    {
        int priorState = DisableIRQInterrupts();

        if (rtcWork.lock != false)
        {
            SetIRQInterruptState(priorState);
            return REAL_TIME_CLOCK_BUSY;
        }
        rtcWork.lock = true;
        SetIRQInterruptState(priorState);

        rtcWork.sequence = SEQUENCE_GET_TIME;
        rtcWork.index = 0;
        rtcWork.buffers[0] = time;
        rtcWork.callback = callback;
        rtcWork.callbackArg = arg;

        if (func_020cf89c())
        {
            return REAL_TIME_CLOCK_SUCCESS;
        }
        else
        {
            return REAL_TIME_CLOCK_SEND_ERROR;
        }
    }

    // usa: func_020cf1a8
    // RTC_GetTime
    int func_020cf1a8(RealTimeClockTime* time)
    {
        rtcWork.commonResult = func_020cf134(time, func_020cf854, NULL);
        if (rtcWork.commonResult == REAL_TIME_CLOCK_SUCCESS)
        {
            func_020cf864();
        }
        return rtcWork.commonResult;
    }

    // usa: func_020cf1e0
    // RTC_GetDateTimeAsync
    int func_020cf1e0(RealTimeClockDate* date, RealTimeClockTime* time, RealTimeClockCallback callback, void* arg)
    {
        int priorState = DisableIRQInterrupts();

        if (rtcWork.lock != false)
        {
            SetIRQInterruptState(priorState);
            return REAL_TIME_CLOCK_BUSY;
        }
        rtcWork.lock = true;
        SetIRQInterruptState(priorState);

        rtcWork.sequence = SEQUENCE_GET_DATETIME;
        rtcWork.index = 0;
        rtcWork.buffers[0] = date;
        rtcWork.buffers[1] = time;
        rtcWork.callback = callback;
        rtcWork.callbackArg = arg;

        if (func_020cf87c())
        {
            return REAL_TIME_CLOCK_SUCCESS;
        }
        else
        {
            return REAL_TIME_CLOCK_SEND_ERROR;
        }
    }

    // usa: func_020cf25c
    // RTC_GetDateTime
    int func_020cf25c(RealTimeClockDate* date, RealTimeClockTime* time)
    {
        rtcWork.commonResult = func_020cf1e0(date, time, func_020cf854, NULL);
        if (rtcWork.commonResult == REAL_TIME_CLOCK_SUCCESS)
        {
            func_020cf864();
        }
        return rtcWork.commonResult;
    }

    // usa: func_020cf294
    // RtcCommonCallback: receives the ARM7's results, and converts the date and the time that it wrote
    void func_020cf294(unsigned int command, unsigned int data, unsigned int error)
    {
        int result;
        int pxiResult;
        unsigned char rtcCommand;
        RealTimeClockCallback callback;

        if (error)
        {
            if (rtcWork.index)
            {
                rtcWork.index = 0;
            }
            if (rtcWork.lock != false)
            {
                rtcWork.lock = false;
            }
            if (rtcWork.callback)
            {
                callback = rtcWork.callback;
                rtcWork.callback = NULL;
                callback(REAL_TIME_CLOCK_FATAL_ERROR, rtcWork.callbackArg);
            }
            return;
        }

        rtcCommand = (unsigned char)((data & RTC_COMMAND_MASK) >> RTC_COMMAND_SHIFT);
        pxiResult = data & RTC_RESULT_MASK;

        if (rtcCommand == RTC_COMMAND_INTERRUPT)
        {
            if (rtcWork.interrupt)
            {
                rtcWork.interrupt();
            }
            return;
        }

        if (pxiResult == RTC_PXI_SUCCESS)
        {
            result = REAL_TIME_CLOCK_SUCCESS;
            switch (rtcWork.sequence)
            {
            case SEQUENCE_GET_DATE:
            {
                RealTimeClockDate* dst = (RealTimeClockDate*)rtcWork.buffers[0];
                RawDate* src = &RAW_DATA->t.date;

                dst->year = func_020cf7e4(src->year);
                dst->month = func_020cf7e4(src->month);
                dst->day = func_020cf7e4(src->day);
                dst->dayOfWeek = func_020cfc00(dst);
            }
            break;

            case SEQUENCE_GET_TIME:
            {
                RealTimeClockTime* dst = (RealTimeClockTime*)rtcWork.buffers[0];
                RawTime* src = &RAW_DATA->t.time;

                dst->hour = func_020cf7e4(src->hour);
                dst->minute = func_020cf7e4(src->minute);
                dst->second = func_020cf7e4(src->second);
            }
            break;

            case SEQUENCE_GET_DATETIME:
            {
                RealTimeClockDate* dst = (RealTimeClockDate*)rtcWork.buffers[0];
                RawDate* src = &RAW_DATA->t.date;

                dst->year = func_020cf7e4(*(unsigned long*)src & 0xff);
                dst->month = func_020cf7e4(src->month);
                dst->day = func_020cf7e4(src->day);
                dst->dayOfWeek = func_020cfc00(dst);
            }
                {
                    RealTimeClockTime* dst = (RealTimeClockTime*)rtcWork.buffers[1];
                    RawTime* src = &RAW_DATA->t.time;

                    dst->hour = func_020cf7e4(src->hour);
                    dst->minute = func_020cf7e4(src->minute);
                    dst->second = func_020cf7e4(src->second);
                }
                break;

            case SEQUENCE_SET_DATE:
            case SEQUENCE_SET_TIME:
            case SEQUENCE_SET_DATETIME:
                break;

            case SEQUENCE_GET_ALARM1_STATUS:
            {
                unsigned long* dst = (unsigned long*)rtcWork.buffers[0];
                RawStatus2* src = &RAW_DATA->a.status2;

                switch (src->interruptMode)
                {
                case INTERRUPT_MODE_ALARM:
                    *dst = ALARM_ON;
                    break;
                default:
                    *dst = ALARM_OFF;
                }
            }
            break;

            case SEQUENCE_GET_ALARM2_STATUS:
            {
                unsigned long* dst = (unsigned long*)rtcWork.buffers[0];
                RawStatus2* src = &RAW_DATA->a.status2;

                if (src->interrupt2Mode)
                {
                    *dst = ALARM_ON;
                }
                else
                {
                    *dst = ALARM_OFF;
                }
            }
            break;

            case SEQUENCE_GET_ALARM_PARAM:
            {
                AlarmParam* dst = (AlarmParam*)rtcWork.buffers[0];
                RawAlarm* src = &RAW_DATA->a.alarm;

                dst->dayOfWeek = src->dayOfWeek;
                dst->hour = func_020cf7e4(src->hour);
                dst->minute = func_020cf7e4(src->minute);
                dst->enable = 0;
                if (src->dayOfWeekEnabled)
                {
                    dst->enable += ALARM_ENABLE_WEEK;
                }
                if (src->hourEnabled)
                {
                    dst->enable += ALARM_ENABLE_HOUR;
                }
                if (src->minuteEnabled)
                {
                    dst->enable += ALARM_ENABLE_MINUTE;
                }
            }
            break;

            case SEQUENCE_SET_ALARM1_STATUS:
                if (rtcWork.index == 0)
                {
                    RawStatus2* src = &RAW_DATA->a.status2;

                    if (*(unsigned long*)rtcWork.buffers[0] == ALARM_ON)
                    {
                        if (src->interruptMode != INTERRUPT_MODE_ALARM)
                        {
                            rtcWork.index++;
                            src->interruptMode = INTERRUPT_MODE_ALARM;
                            if (!func_020cf8ac())
                            {
                                rtcWork.index = 0;
                                result = REAL_TIME_CLOCK_SEND_ERROR;
                            }
                        }
                    }
                    else
                    {
                        if (src->interruptMode != INTERRUPT_MODE_NONE)
                        {
                            rtcWork.index++;
                            src->interruptMode = INTERRUPT_MODE_NONE;
                            if (!func_020cf8ac())
                            {
                                rtcWork.index = 0;
                                result = REAL_TIME_CLOCK_SEND_ERROR;
                            }
                        }
                    }
                }
                else
                {
                    rtcWork.index = 0;
                }
                break;

            case SEQUENCE_SET_ALARM2_STATUS:
                if (rtcWork.index == 0)
                {
                    RawStatus2* src = &RAW_DATA->a.status2;

                    if (*(unsigned long*)rtcWork.buffers[0] == ALARM_ON)
                    {
                        if (!src->interrupt2Mode)
                        {
                            rtcWork.index++;
                            src->interrupt2Mode = 1;
                            if (!func_020cf8ac())
                            {
                                rtcWork.index = 0;
                                result = REAL_TIME_CLOCK_SEND_ERROR;
                            }
                        }
                    }
                    else
                    {
                        if (src->interrupt2Mode)
                        {
                            rtcWork.index++;
                            src->interrupt2Mode = 0;
                            if (!func_020cf8ac())
                            {
                                rtcWork.index = 0;
                                result = REAL_TIME_CLOCK_SEND_ERROR;
                            }
                        }
                    }
                }
                else
                {
                    rtcWork.index = 0;
                }
                break;

            case SEQUENCE_SET_ALARM1_PARAM:
            case SEQUENCE_SET_ALARM2_PARAM:
            case SEQUENCE_SET_HOUR_FORMAT:
            case SEQUENCE_SET_REG_STATUS2:
            case SEQUENCE_SET_REG_ADJUST:
                break;

            default:
                result = REAL_TIME_CLOCK_INVALID_COMMAND;
                rtcWork.index = 0;
            }
        }
        else
        {
            rtcWork.index = 0;

            switch (pxiResult)
            {
            case RTC_PXI_INVALID_COMMAND:
                result = REAL_TIME_CLOCK_INVALID_COMMAND;
                break;
            case RTC_PXI_ILLEGAL_STATUS:
                result = REAL_TIME_CLOCK_ILLEGAL_STATUS;
                break;
            case RTC_PXI_BUSY:
                result = REAL_TIME_CLOCK_BUSY;
                break;
            case RTC_PXI_FATAL_ERROR:
            default:
                result = REAL_TIME_CLOCK_FATAL_ERROR;
            }
        }

        if (rtcWork.index == 0)
        {
            if (rtcWork.lock != false)
            {
                rtcWork.lock = false;
            }
            if (rtcWork.callback)
            {
                callback = rtcWork.callback;
                rtcWork.callback = NULL;
                callback(result, rtcWork.callbackArg);
            }
        }
    }

    // usa: func_020cf7e4
    // RtcBCD2HEX: converts from BCD, or returns 0 if it's not valid
    unsigned long func_020cf7e4(unsigned long bcd)
    {
        unsigned long hex = 0;
        long i;
        long weight;

        for (i = 0; i < 8; i++)
        {
            if (((bcd >> (i * 4)) & 0xf) >= 10)
            {
                return hex;
            }
        }

        for (i = 0, weight = 1; i < 8; i++, weight *= 10)
        {
            hex += ((bcd >> (i * 4)) & 0xf) * weight;
        }
        return hex;
    }

    // usa: func_020cf854
    // RtcGetResultCallback
    void func_020cf854(int result, void* arg)
    {
        rtcWork.commonResult = result;
    }

    // usa: func_020cf864
    // RtcWaitBusy: waits for the ARM7's answer
    asm void func_020cf864()
    {
        ldr r12, =rtcWork
    loop:
        ldr r0, [r12, #0]
        cmp r0, #1
        beq loop
        bx lr
    }
}
