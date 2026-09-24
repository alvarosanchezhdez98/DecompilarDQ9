#pragma once

// The NitroSDK's real-time clock library (RTC), which asks the ARM7 for the date and the time

// RTCDate
struct RealTimeClockDate
{
    unsigned long year; // 0, from 2000
    unsigned long month; // 4, 1 to 12
    unsigned long day; // 8, 1 to 31
    int dayOfWeek; // c, 0 on Sunday (the NitroSDK's RTCWeek)
};

// RTCTime
struct RealTimeClockTime
{
    unsigned long hour; // 0
    unsigned long minute; // 4
    unsigned long second; // 8
};

// RTCResult
#define REAL_TIME_CLOCK_SUCCESS 0
#define REAL_TIME_CLOCK_BUSY 1
#define REAL_TIME_CLOCK_ILLEGAL_PARAMETER 2
#define REAL_TIME_CLOCK_SEND_ERROR 3
#define REAL_TIME_CLOCK_INVALID_COMMAND 4
#define REAL_TIME_CLOCK_ILLEGAL_STATUS 5
#define REAL_TIME_CLOCK_FATAL_ERROR 6

// RTCCallback
typedef void (*RealTimeClockCallback)(int result, void* arg);

extern "C"
{
    // usa: func_020cf020
    // RTC_Init
    void func_020cf020();
    // usa: func_020cf08c
    // RTC_GetDateAsync
    int func_020cf08c(RealTimeClockDate* date, RealTimeClockCallback callback, void* arg);
    // usa: func_020cf0fc
    // RTC_GetDate
    int func_020cf0fc(RealTimeClockDate* date);
    // usa: func_020cf134
    // RTC_GetTimeAsync
    int func_020cf134(RealTimeClockTime* time, RealTimeClockCallback callback, void* arg);
    // usa: func_020cf1a8
    // RTC_GetTime
    int func_020cf1a8(RealTimeClockTime* time);
    // usa: func_020cf1e0
    // RTC_GetDateTimeAsync
    int func_020cf1e0(RealTimeClockDate* date, RealTimeClockTime* time, RealTimeClockCallback callback, void* arg);
    // usa: func_020cf25c
    // RTC_GetDateTime
    int func_020cf25c(RealTimeClockDate* date, RealTimeClockTime* time);

    // usa: func_020cf87c
    // RTCi_ReadRawDateTimeAsync
    int func_020cf87c();
    // usa: func_020cf88c
    // RTCi_ReadRawDateAsync
    int func_020cf88c();
    // usa: func_020cf89c
    // RTCi_ReadRawTimeAsync
    int func_020cf89c();
    // usa: func_020cf8ac
    // RTCi_WriteRawStatus2Async
    int func_020cf8ac();

    // usa: func_020cf8e4
    // RTC_ConvertDateToDay: the days since January 1, 2000, or -1 if the date isn't valid
    long func_020cf8e4(const RealTimeClockDate* date);
    // usa: func_020cf978
    // RTCi_ConvertTimeToSecond
    long func_020cf978(const RealTimeClockTime* time);
    // usa: func_020cf990
    // RTC_ConvertDateTimeToSecond: the seconds since January 1, 2000, or -1 if the date isn't valid
    long long func_020cf990(const RealTimeClockDate* date, const RealTimeClockTime* time);
    // usa: func_020cf9f4
    // RTC_ConvertDayToDate
    void func_020cf9f4(RealTimeClockDate* date, long day);
    // usa: func_020cfaf4
    // RTCi_ConvertSecondToTime
    void func_020cfaf4(RealTimeClockTime* time, long second);
    // usa: func_020cfb74
    // RTC_ConvertSecondToDateTime
    void func_020cfb74(RealTimeClockDate* date, RealTimeClockTime* time, long long second);
    // usa: func_020cfc00
    // RTC_GetDayOfWeek
    int func_020cfc00(RealTimeClockDate* date);
}
