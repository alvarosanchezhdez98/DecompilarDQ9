#include "System/Interrupts.h"
#include "System/DMA.h"
#include "System/BiosData.h"
#include "System/DTCM.h"
#include <globaldefs.h>

#pragma optimize_for_size off
// This NitroSDK file was compiled with -O4, like NameList.cpp from NitroSystem: at the game's -O2, the loops are
// compiled differently
#pragma optimization_level 4

#if defined(jpn)
#define data_0211127c data_02110f1c
#define data_020f2274 data_020f23e0
#endif

struct DMAOrTimerResponse
{
    DMACompletionCallback callback;
    unsigned int stayEnabledAfter;
    int userdata;
};

// 0-3 are DMA, 4-7 are timers
extern DMAOrTimerResponse data_0211127c[8];
// maps index in the previous array to interrupt ID
extern unsigned short data_020f2274[8];

// Start of exposed functions

void WaitForInterrupt(bool onlySubsequent, unsigned int mask)
{
    int priorState = DisableIRQInterrupts();
    if (onlySubsequent)
        DTCM_DATA_INTERRUPTS_FIRED &= ~mask;
    SetIRQInterruptState(priorState);

    while (!(mask & DTCM_DATA_INTERRUPTS_FIRED))
        BlockCurrentContext(&data_027e0060);
}

void EmptyInterruptHandler() {}

void OnDMAOrTimerCompletion(int index)
{
    unsigned int mask = 1 << data_020f2274[index];
    DMACompletionCallback callback = data_0211127c[index].callback;
    data_0211127c[index].callback = NULL;
    if (callback != NULL)
        callback(data_0211127c[index].userdata);
    DTCM_DATA_INTERRUPTS_FIRED |= mask;
    if (!data_0211127c[index].stayEnabledAfter)
        DisableSpecificInterrupts(mask);
}

void DMA0InterruptHandler() { OnDMAOrTimerCompletion(0); }
void DMA1InterruptHandler() { OnDMAOrTimerCompletion(1); }
void DMA2InterruptHandler() { OnDMAOrTimerCompletion(2); }
void DMA3InterruptHandler() { OnDMAOrTimerCompletion(3); }

void Timer0OverflowInterruptHandler() { OnDMAOrTimerCompletion(4); }
void Timer1OverflowInterruptHandler() { OnDMAOrTimerCompletion(5); }
void Timer2OverflowInterruptHandler() { OnDMAOrTimerCompletion(6); }
void Timer3OverflowInterruptHandler() { OnDMAOrTimerCompletion(7); }

void InitializeInterruptContextBlock_020c6ad4()
{
    data_027e0060.first = data_027e0060.last = NULL;
}

// proc can either be of type void(*)() for regular interrupts,
// or void(*)(int) for DMA / timer response interrupts
void SetInterruptHandler(unsigned int mask, const void* proc)
{
    int i;
    DMAOrTimerResponse* response;
    for (i = 0; i < 22; i++)
    {
        if (mask & 1)
        {
            response = NULL;
            if (8 <= i && i <= 11) // DMA channels
                response = &data_0211127c[i - 8];
            else if (3 <= i && i <= 6) // timer overflows
                response = &data_0211127c[i - 3 + 4];
            else
                data_027e0000.interruptProcTable[i] = (InterruptHandlerProc)proc;

            if (response != NULL)
            {
                response->callback = (DMACompletionCallback)proc;
                response->userdata = 0;
                response->stayEnabledAfter = true;
            }
        }
        mask >>= 1;
    }
}

InterruptHandlerProc GetInterruptHandler(unsigned int mask)
{
    int i;
    InterruptHandlerProc* proc = &data_027e0000.interruptProcTable[0];
    for (i = 0; i < 22; i++)
    {
        if (mask & 1)
        {
            if (8 <= i && i <= 11) // DMA channels
                return (InterruptHandlerProc)data_0211127c[i - 8].callback;
            else if (3 <= i && i <= 6) // timer overflows
                return (InterruptHandlerProc)data_0211127c[i - 3 + 4].callback;
            return *proc;
        }
        mask >>= 1;
        proc++;
    }
    return NULL;
}

void SetDMACompletionCallback(int channel, DMACompletionCallback callback, int userdata)
{
    unsigned int mask = 1 << (channel + 8);
    data_0211127c[channel].callback = callback;
    data_0211127c[channel].userdata = userdata;
    data_0211127c[channel].stayEnabledAfter = EnableSpecificInterrupts(mask) & mask;
}

void SetTimerOverflowCallback(int timer, DMACompletionCallback callback, int userdata)
{
    // unsigned long like the NitroSDK's u32: with int, the compiler doesn't add the timers' offset to the table's address
    unsigned long timerNo = timer;
    unsigned int mask = 1 << (timerNo + 3);
    data_0211127c[timerNo + 4].callback = callback;
    data_0211127c[timerNo + 4].userdata = userdata;
    EnableSpecificInterrupts(mask);
    data_0211127c[timerNo + 4].stayEnabledAfter = true;
}