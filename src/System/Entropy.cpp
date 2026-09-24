#include "System/Graphics.h"
#include "System/Timing.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_entropy.c: data that changes often, to seed random numbers

// What the system and the ARM7 write at 0x027ffc00 (the NitroSDK's OSSystemWork), only what's used here
struct SystemWork
{
    char unknown_0[0x3c];
    unsigned long vblankCount; // 3c
    char unknown_40[0x80 - 0x40];
    unsigned char userSettings[0x74]; // 80, the NitroSDK's NVRAMConfig
    unsigned char macAddress[6]; // f4
    char unknown_fa[0x1e8 - 0xfa];
    unsigned char realTimeClock[8]; // 1e8
    char unknown_1f0[0x390 - 0x1f0];
    unsigned long micLastAddress; // 390
    unsigned short micSamplingData; // 394
    char unknown_396[2];
    unsigned short wirelessSignal; // 398, the NitroSDK's wm_rssi_pool
    char unknown_39a[0x3aa - 0x39a];
    unsigned char touchPanel[4]; // 3aa
};

#define SYSTEM_WORK ((const SystemWork*)0x027ffc00)

// HW_BUTTON_XY_BUF, in the system's work area too: the buttons X and Y, and the hinge, which the ARM7 reads
#define BUTTONS_XY (*(volatile unsigned short*)0x027fffa8)
#define KEYINPUT (*(volatile unsigned short*)0x04000130)
#define GXSTAT (*(volatile unsigned long*)0x04000600)

// OSi_TickCounter, the counter of the tick timer's overflows (in Timing.cpp's data_02111638)
extern volatile unsigned long long data_02111640;

// GX_GetVCount
static inline long GetVCount()
{
    return VCOUNT;
}

extern "C"
{
    // usa: func_020c9b10
    // OS_GetLowEntropyData: fills 32 bytes
    void func_020c9b10(unsigned long* buffer)
    {
        const SystemWork* work = SYSTEM_WORK;
        const unsigned char* macAddress = work->macAddress;

        buffer[0] = (unsigned long)((GetVCount() << 16) | GetMain16BitTimerCounter());
        buffer[1] = (unsigned long)(*(unsigned short*)(macAddress + 4) << 16) ^ (unsigned long)data_02111640;
        buffer[2] = (unsigned long)(data_02111640 >> 32) ^ *(unsigned long*)macAddress ^ work->vblankCount;
        buffer[2] ^= GXSTAT;
        buffer[3] = *(unsigned long*)&work->realTimeClock[0];
        buffer[4] = *(unsigned long*)&work->realTimeClock[4];
        buffer[5] = ((unsigned long)work->micSamplingData << 16) ^ work->micLastAddress;
        buffer[6] = (unsigned long)((*(unsigned short*)&work->touchPanel[0] << 16) | *(unsigned short*)&work->touchPanel[2]);
        buffer[7] = (unsigned long)((work->wirelessSignal << 16) | (KEYINPUT | BUTTONS_XY));
    }
}
