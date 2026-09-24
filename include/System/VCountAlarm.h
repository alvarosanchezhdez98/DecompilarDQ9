#pragma once

// The NitroSDK's V-count alarms (OSVAlarm): a handler that's called when the display reaches a line

typedef void (*VCountAlarmHandler)(void* arg);

struct VCountAlarm
{
    VCountAlarmHandler handler; // 0, NULL when the alarm isn't set
    void* arg; // 4
    unsigned long tag; // 8
    unsigned long frame; // c, the frame in which it fires
    short line; // 10, the line at which it fires
    short delay; // 12, how many lines late it can still fire
    VCountAlarm* prev; // 14
    VCountAlarm* next; // 18
    int periodic; // 1c, fires again in the next frame
    int finished; // 20
    int canceled; // 24
};

extern "C"
{
    // usa: func_020c9288
    // OS_InitVAlarm
    void func_020c9288();
    // usa: func_020c93bc
    // OS_CreateVAlarm
    void func_020c93bc(VCountAlarm* alarm);
    // usa: func_020c93d0
    // OS_SetPeriodicVAlarm
    void func_020c93d0(VCountAlarm* alarm, short line, short delay, VCountAlarmHandler handler, void* arg);
    // usa: func_020c949c
    // OS_CancelVAlarm
    void func_020c949c(VCountAlarm* alarm);
}
