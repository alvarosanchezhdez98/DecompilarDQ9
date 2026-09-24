#include "System/VCountAlarm.h"
#include "System/DTCM.h"
#include "System/Graphics.h"
#include "System/Interrupts.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_valarm.c: alarms that fire when the display reaches a line (the V-count). The alarms wait in a
// queue sorted by frame and line, and the V-count match interrupt is set for the first one. OS_IsVAlarmAvailable,
// OS_SetVAlarm, OS_SetVAlarmTag and OS_CancelVAlarms aren't in the ROM.

// The number of lines of the display, including those of the V-blank (the NitroSDK's HW_LCD_LINES)
#define DISPLAY_LINES 263

// What CompareVCount returns: the alarm fires later, now, or it's too late
#define ALARM_LATER 0
#define ALARM_NOW 1
#define ALARM_TIMEOUT 2

// OSi_UseVAlarm
static unsigned short isInitialized;
// OSi_PreviousVCount
static long previousVCount;
// OSi_VFrameCount: the number of frames since the initialization
static long frameCount;
// OSi_VAlarmQueue
static struct
{
    VCountAlarm* head;
    VCountAlarm* tail;
} queue;

// GX_GetVCount
static inline long GetVCount()
{
    return VCOUNT;
}

// GX_GetVCountEqVal: the line of the V-count match interrupt
static inline long GetVCountMatchLine()
{
    unsigned short status = DISPSTAT;
    return ((status >> 8) & 0xff) | ((status << 1) & 0x100);
}

extern "C"
{
    // usa: func_020c383c
    // GX_SetVCountEqVal
    void func_020c383c(long line);
    // usa: func_020c9be0
    // OS_Terminate
    void func_020c9be0();

    void func_020c934c(VCountAlarm* alarm);
    void func_020c945c(VCountAlarm* alarm);
    void func_020c94e4();
    long func_020c96a8(long line);

    // usa: func_020c9288
    // OS_InitVAlarm
    void func_020c9288()
    {
        if (!isInitialized)
        {
            isInitialized = true;
            queue.head = NULL;
            queue.tail = NULL;
            DisableSpecificInterrupts(IRQ_MASK_LCD_VCOUNTER_MATCH);
            frameCount = 0;
            previousVCount = 0;
        }
    }

    // usa: func_020c92d0
    // OSi_InsertVAlarm: adds an alarm to the queue, after those that fire before it or at the same time
    void func_020c92d0(VCountAlarm* alarm)
    {
        VCountAlarm* prev;
        VCountAlarm* next;

        for (next = queue.head; next; next = next->next)
        {
            if (next->frame < alarm->frame || next->frame == alarm->frame && next->line <= alarm->line)
            {
                continue;
            }

            prev = next->prev;
            alarm->prev = prev;
            alarm->next = next;
            next->prev = alarm;
            if (prev)
            {
                prev->next = alarm;
            }
            else
            {
                queue.head = alarm;
                func_020c945c(alarm);
            }
            return;
        }

        func_020c934c(alarm);
    }

    // usa: func_020c934c
    // OSi_AppendVAlarm
    void func_020c934c(VCountAlarm* alarm)
    {
        VCountAlarm* prev = queue.tail;

        alarm->prev = prev;
        alarm->next = NULL;
        queue.tail = alarm;
        if (prev)
        {
            prev->next = alarm;
        }
        else
        {
            queue.head = alarm;
            func_020c945c(alarm);
        }
    }

    // usa: func_020c9384
    // OSi_DetachVAlarm: removes an alarm from the queue
    void func_020c9384(VCountAlarm* alarm)
    {
        VCountAlarm* prev;
        VCountAlarm* next;

        if (alarm == NULL)
        {
            return;
        }

        prev = alarm->prev;
        next = alarm->next;
        if (next)
        {
            next->prev = prev;
        }
        else
        {
            queue.tail = prev;
        }
        if (prev)
        {
            prev->next = next;
        }
        else
        {
            queue.head = next;
        }
    }

    // usa: func_020c93bc
    // OS_CreateVAlarm
    void func_020c93bc(VCountAlarm* alarm)
    {
        alarm->handler = NULL;
        alarm->tag = 0;
        alarm->finished = false;
    }

    // usa: func_020c93d0
    // OS_SetPeriodicVAlarm: sets an alarm that fires at a line in every frame, up to delay lines late
    void func_020c93d0(VCountAlarm* alarm, short line, short delay, VCountAlarmHandler handler, void* arg)
    {
        int priorState = DisableIRQInterrupts();
        long currentLine;
        long currentFrame;

        if (!alarm || alarm->handler)
        {
            func_020c9be0();
        }

        currentLine = GetVCount();
        currentFrame = func_020c96a8(currentLine);

        alarm->periodic = true;
        alarm->line = line;
        alarm->frame = line > currentLine ? currentFrame : currentFrame + 1;
        alarm->delay = delay;
        alarm->handler = handler;
        alarm->arg = arg;
        alarm->canceled = false;
        func_020c92d0(alarm);

        SetIRQInterruptState(priorState);
    }

    // usa: func_020c945c
    // OSi_SetNextVAlarm: sets the V-count match interrupt for an alarm
    void func_020c945c(VCountAlarm* alarm)
    {
        SetInterruptHandler(IRQ_MASK_LCD_VCOUNTER_MATCH, (const void*)func_020c94e4);
        func_020c383c(alarm->line);
        DISPSTAT |= 0x20;
        EnableSpecificInterrupts(IRQ_MASK_LCD_VCOUNTER_MATCH);
    }

    // usa: func_020c949c
    // OS_CancelVAlarm
    void func_020c949c(VCountAlarm* alarm)
    {
        int priorState = DisableIRQInterrupts();

        alarm->canceled = true;
        if (alarm->handler == NULL)
        {
            SetIRQInterruptState(priorState);
            return;
        }

        func_020c9384(alarm);
        alarm->handler = NULL;
        SetIRQInterruptState(priorState);
    }

    long func_020c965c(VCountAlarm* alarm, long currentFrame, long currentLine);

    // usa: func_020c94e4
    // OSi_VAlarmHandler: the V-count match interrupt's handler, calls the handlers of the alarms that fire now
    void func_020c94e4()
    {
        VCountAlarm* alarm;
        VCountAlarmHandler handler;
        long check;
        long currentLine;
        long currentFrame;

        DisableSpecificInterrupts(IRQ_MASK_LCD_VCOUNTER_MATCH);
        DISPSTAT &= ~0x20;
        DTCM_DATA_INTERRUPTS_FIRED |= IRQ_MASK_LCD_VCOUNTER_MATCH;
        currentLine = GetVCountMatchLine();
        currentFrame = func_020c96a8(currentLine - 1);

        while (NULL != (alarm = queue.head))
        {
            currentLine = GetVCount();
            currentFrame = func_020c96a8(currentLine);
            check = func_020c965c(alarm, currentFrame, currentLine);
            switch (check)
            {
            case ALARM_LATER:
                func_020c945c(alarm);
                if (alarm->line != GetVCount() || alarm->frame != currentFrame)
                {
                    return;
                }
                DisableSpecificInterrupts(IRQ_MASK_LCD_VCOUNTER_MATCH);
                DISPSTAT &= ~0x20;
                AcknowledgeSpecificInterrupts(IRQ_MASK_LCD_VCOUNTER_MATCH);
                // fallthrough
            case ALARM_NOW:
                handler = alarm->handler;
                func_020c9384(alarm);
                alarm->handler = NULL;
                if (handler)
                {
                    handler(alarm->arg);
                }
                if (alarm->periodic && !alarm->canceled)
                {
                    alarm->handler = handler;
                    alarm->frame = frameCount + 1;
                    func_020c92d0(alarm);
                }
                break;
            case ALARM_TIMEOUT:
                func_020c9384(alarm);
                alarm->frame = frameCount + 1;
                func_020c92d0(alarm);
                break;
            }
        }
    }

    // usa: func_020c965c
    // OSi_CompareVCount
    long func_020c965c(VCountAlarm* alarm, long currentFrame, long currentLine)
    {
        long delayFrames = currentFrame - alarm->frame;
        long delayLines = currentLine - alarm->line;

        if (delayFrames < 0 || delayFrames == 0 && delayLines < 0)
        {
            return ALARM_LATER;
        }
        if (delayLines < 0)
        {
            delayLines += DISPLAY_LINES;
        }
        return delayLines <= alarm->delay ? ALARM_NOW : ALARM_TIMEOUT;
    }

    // usa: func_020c96a8
    // OSi_GetVFrame: counts the frames, from the lines
    long func_020c96a8(long line)
    {
        int priorState = DisableIRQInterrupts();

        if (line < previousVCount)
        {
            frameCount++;
        }
        previousVCount = line;

        SetIRQInterruptState(priorState);
        return frameCount;
    }
}
