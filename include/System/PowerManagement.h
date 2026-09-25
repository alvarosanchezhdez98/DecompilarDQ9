#pragma once

// The NitroSDK's power management (PM, pm.c): the ARM9 asks the ARM7 to put the console to sleep, to turn the
// backlights, the LCDs and the LED on and off, and to turn the console off

// The results of the functions that send a command (PM_SUCCESS, PM_BUSY and PM_INVALID_COMMAND)
#define PM_SUCCESS 0
// Another command is being sent
#define PM_BUSY 1
#define PM_INVALID_COMMAND 0xffff
// The ARM7's answer to a command that it can't run yet (PM_RESULT_BUSY)
#define PM_RESULT_BUSY 4

// PMLCDTarget and PMBackLightSwitch
#define PM_LCD_TOP 0
#define PM_LCD_BOTTOM 1
#define PM_LCD_ALL 2
#define PM_BACKLIGHT_OFF 0
#define PM_BACKLIGHT_ON 1

// PMLCDPower
#define PM_LCD_POWER_OFF 0
#define PM_LCD_POWER_ON 1

// PMLEDStatus: the power LED
#define PM_LED_NONE 0
#define PM_LED_ON 1
#define PM_LED_BLINK_LOW 2
#define PM_LED_BLINK_HIGH 3

// PMLEDPattern: the patterns of the LED that PM_SetLEDPattern sets. The LED blinks this way while the console
// communicates wirelessly.
#define PM_LED_PATTERN_ON 1
#define PM_LED_PATTERN_WIRELESS 0xf

// PMWakeUpTrigger: what wakes the console up
#define PM_TRIGGER_KEY 0x1
#define PM_TRIGGER_RTC_ALARM 0x2
#define PM_TRIGGER_COVER_OPEN 0x4
#define PM_TRIGGER_CARD 0x8
#define PM_TRIGGER_CARTRIDGE 0x10

// PMLogic: how the keys of the pattern wake the console up
#define PM_PAD_LOGIC_OR 0x0
#define PM_PAD_LOGIC_AND 0x8000

// What a command's callback gets (PMCallback)
typedef void (*PMCallback)(unsigned long result, void* arg);

typedef void (*SleepCallback)(void* arg);

// The NitroSDK's PMSleepCallbackInfo: a function called before or after the console sleeps
struct SleepCallbackInfo
{
    SleepCallback callback;
    void* arg;
    SleepCallbackInfo* next;
};

// The NitroSDK's PM_SetSleepCallbackInfo
static inline void SetSleepCallbackInfo(SleepCallbackInfo* info, SleepCallback callback, void* arg)
{
    info->callback = callback;
    info->arg = arg;
}

extern "C"
{
    // PM_Init
    void func_020ce270();
    // PM_GoSleepMode: sleeps until one of the triggers, and calls the callbacks before and after
    void func_020ce89c(int trigger, int logic, unsigned short keyPattern);
    // PM_ForceToPowerOff: turns the console off, and doesn't return
    unsigned long func_020ce7a4();
    // PM_SetLCDPower and PM_GetLCDPower
    int func_020cedc0(int sw);
    int func_020cede0();
    // PM_SetLEDPattern and PM_GetLEDPattern
    unsigned long func_020cedfc(unsigned long pattern);
    unsigned long func_020cee18(unsigned long* patternBuf);
    // PM_PrependPreSleepCallback, PM_AppendPostSleepCallback, PM_DeletePreSleepCallback and PM_DeletePostSleepCallback
    void func_020cef34(SleepCallbackInfo* info);
    void func_020cef4c(SleepCallbackInfo* info);
    void func_020cef64(SleepCallbackInfo* info);
    void func_020cef7c(SleepCallbackInfo* info);
}
