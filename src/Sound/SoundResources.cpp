#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's resource_mgr.c: locks the sound driver's channels, captures and alarms for NitroSystem.
// NNS_SndLockCapture and NNSi_GetLockedChannel aren't in the ROM.

// The NitroSDK's SND_ALARM_NUM
#define ALARM_COUNT 8

// The compiler places these in reverse order: captureLock, alarmLock, channelLock
static unsigned long alarmLock;
static unsigned long captureLock;
static unsigned long channelLock;

extern "C"
{
    // usa: func_020d1fb0
    // The NitroSDK's SND_LockChannel
    void func_020d1fb0(unsigned long channelMask, unsigned long flags);
    // usa: func_020d1fd0
    // The NitroSDK's SND_UnlockChannel
    void func_020d1fd0(unsigned long channelMask, unsigned long flags);

    // usa: func_020bbe1c
    // NNS_SndLockChannel
    int func_020bbe1c(unsigned long channelMask)
    {
        if (channelMask == 0)
            return 1;

        if (channelMask & channelLock)
            return 0;

        func_020d1fb0(channelMask, 0);
        channelLock |= channelMask;
        return 1;
    }

    // usa: func_020bbe64
    // NNS_SndUnlockChannel
    void func_020bbe64(unsigned long channelMask)
    {
        if (channelMask == 0)
            return;

        func_020d1fd0(channelMask, 0);
        channelLock &= ~channelMask;
    }

    // usa: func_020bbe94
    // NNS_SndUnlockCapture
    void func_020bbe94(unsigned long captureMask)
    {
        captureLock &= ~captureMask;
    }

    // usa: func_020bbeb0
    // NNS_SndAllocAlarm
    int func_020bbeb0()
    {
        int alarmNo;
        unsigned long mask = 1;

        for (alarmNo = 0; alarmNo < ALARM_COUNT; alarmNo++, mask <<= 1)
        {
            if ((alarmLock & mask) == 0)
            {
                alarmLock |= mask;
                return alarmNo;
            }
        }
        return -1;
    }

    // usa: func_020bbef8
    // NNS_SndFreeAlarm
    void func_020bbef8(int alarmNo)
    {
        alarmLock &= ~(1 << alarmNo);
    }

    // usa: func_020bbf18
    // NNSi_SndInitResourceMgr
    void func_020bbf18()
    {
        channelLock = 0;
        captureLock = 0;
        alarmLock = 0;
    }
}
