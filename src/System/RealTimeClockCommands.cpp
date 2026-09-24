#include "System/RealTimeClock.h"
#include "System/IPC.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's rtc_internal.c: sends the commands to the ARM7, which reads or writes the clock's registers. Only
// those that RealTimeClock.cpp uses are in the ROM.

// The IPC command of the real-time clock (the NitroSDK's PXI_FIFO_TAG_RTC), and the commands (RTC_PXI_COMMAND_*)
#define IPC_COMMAND_REAL_TIME_CLOCK 5
#define RTC_COMMAND_MASK 0x7f00
#define RTC_COMMAND_SHIFT 8

#define RTC_COMMAND_READ_DATETIME 0x10
#define RTC_COMMAND_READ_DATE 0x11
#define RTC_COMMAND_READ_TIME 0x12
#define RTC_COMMAND_WRITE_STATUS2 0x27

extern "C"
{
    int func_020cf8bc(unsigned long command);

    // usa: func_020cf87c
    // RTCi_ReadRawDateTimeAsync
    int func_020cf87c()
    {
        return func_020cf8bc(RTC_COMMAND_READ_DATETIME);
    }

    // usa: func_020cf88c
    // RTCi_ReadRawDateAsync
    int func_020cf88c()
    {
        return func_020cf8bc(RTC_COMMAND_READ_DATE);
    }

    // usa: func_020cf89c
    // RTCi_ReadRawTimeAsync
    int func_020cf89c()
    {
        return func_020cf8bc(RTC_COMMAND_READ_TIME);
    }

    // usa: func_020cf8ac
    // RTCi_WriteRawStatus2Async
    int func_020cf8ac()
    {
        return func_020cf8bc(RTC_COMMAND_WRITE_STATUS2);
    }

    // usa: func_020cf8bc
    // RtcSendPxiCommand
    int func_020cf8bc(unsigned long command)
    {
        if (0 > SendCommandToArm7(IPC_COMMAND_REAL_TIME_CLOCK, (command << RTC_COMMAND_SHIFT) & RTC_COMMAND_MASK, false))
        {
            return false;
        }
        return true;
    }
}
