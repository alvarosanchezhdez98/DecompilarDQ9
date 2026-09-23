#include "System/DMA.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's mi_dma_card.c

// The NitroSDK's MIi_DMA_TIMING_ANY
#define DMA_TIMING_ANY 0xffffffff
// The NitroSDK's MI_DMA_SRC_FIX: the source address doesn't change
#define DMA_SOURCE_FIXED 0x01000000
// The NitroSDK's MI_CNT_CARDRECV32(4) | MI_DMA_CONTINUOUS_ON: enabled, when the game card has data, 32-bit, one word
// at a time, repeated, from a fixed address
#define DMA_CONTROL_CARD 0xaf000001
// The NitroSDK's REG_DMA0SAD: each channel has its source, destination and control registers
#define DMA_REGISTERS ((volatile unsigned long*)0x040000b0)
#define DMA_ENABLED 0x80000000

extern "C"
{
    // usa: func_020ca8e8
    // MIi_CardDmaCopy32: copies from the game card with DMA
    void func_020ca8e8(unsigned long channel, const void* src, void* dst, unsigned long size)
    {
        volatile unsigned long* control;

        VerifyDMATimingChangePermitted_020c9fd0(channel, DMA_TIMING_ANY);
        VerifyDMASource(channel, (unsigned long)src, size, DMA_SOURCE_FIXED);

        if (size == 0)
        {
            return;
        }

        // MIi_Wait_BeforeDMA
        control = &DMA_REGISTERS[channel * 3 + 2];
        while (*control & DMA_ENABLED)
        {
        }

        ConfigureDMATransferAtomic(channel, (unsigned long)src, (unsigned long)dst, DMA_CONTROL_CARD);
    }
}
