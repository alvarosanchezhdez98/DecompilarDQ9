#include "Sound/SoundDriver.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_alarm.c: the handlers of the driver's alarms, which the ARM7 calls through the IPC

// An alarm's handler, and an ID that changes when the alarm is set up again, so that a late call of the old one is
// ignored
struct SoundAlarm
{
    void (*handler)(void* arg);
    void* arg;
    unsigned char id;
};

static SoundAlarm sAlarms[SOUND_ALARM_COUNT];

extern "C"
{
    void func_020d2930()
    {
        for (int i = 0; i < SOUND_ALARM_COUNT; i++)
        {
            sAlarms[i].handler = NULL;
            sAlarms[i].arg = NULL;
            sAlarms[i].id = 0;
        }
    }

    void func_020d2960(int alarmNo)
    {
        SoundAlarm* const alarm = &sAlarms[alarmNo];
        alarm->id++;
    }

    unsigned char func_020d2980(int alarmNo, void (*handler)(void* arg), void* arg)
    {
        SoundAlarm* const alarm = &sAlarms[alarmNo];
        alarm->handler = handler;
        alarm->arg = arg;
        alarm->id++;
        return alarm->id;
    }

    void func_020d29b0(int alarmNo)
    {
        SoundAlarm* const alarm = &sAlarms[alarmNo & 0xff];
        if ((unsigned char)(alarmNo >> 8) != alarm->id)
            return;
        if (alarm->handler == NULL)
            return;
        alarm->handler(alarm->arg);
    }
}
