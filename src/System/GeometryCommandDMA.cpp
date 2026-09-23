#include "System/DMA.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's mi_dma_gxcommand.c: sends commands to the geometry engine's FIFO with DMA, in the background

// The NitroSDK's MIi_GX_LENGTH_ONCE: how much to send each time that the FIFO is half empty
#define LENGTH_ONCE (118 * sizeof(unsigned long))

#define REG_GXSTAT (*(volatile unsigned long*)0x04000600)
#define REG_GXFIFO_ADDR 0x04000400
// GXSTAT's FIFO status (the NitroSDK's GX_FIFOSTAT_UNDERHALF: less than half full) and FIFO interrupt condition
#define GXSTAT_FIFO_STATUS_MASK 0x07000000
#define GXSTAT_FIFO_STATUS_SHIFT 24
#define FIFO_STATUS_UNDER_HALF 2
#define GXSTAT_FIFO_INTERRUPT_MASK 0xc0000000
#define GXSTAT_FIFO_INTERRUPT_SHIFT 30
#define FIFO_INTERRUPT_UNDER_HALF 1
// The NitroSDK's OS_IE_GXFIFO
#define INTERRUPT_GXFIFO 0x200000

// The NitroSDK's MI_DMA_SRC_INC and MI_DMA_TIMING_GXFIFO
#define DMA_SOURCE_INCREMENT 0
#define DMA_TIMING_GXFIFO 0x38000000
// The NitroSDK's MI_CNT_SEND32, MI_CNT_SEND32_IF and MI_CNT_GXCOPY_IF: 32 bits at a time to a fixed address, with an
// interrupt at the end (IF), and when the FIFO is half empty (GXCOPY)
#define DMA_CONTROL_SEND32(length) (0x84400000 | ((length) / 4))
#define DMA_CONTROL_SEND32_INTERRUPT(length) (0xc4400000 | ((length) / 4))
#define DMA_CONTROL_GXCOPY_INTERRUPT(length) (0xfc400000 | ((length) / 4))

typedef void (*GXCommandDMACallback)(void* arg);

// The NitroSDK's MIiGXDmaParams
struct GXCommandDMAParams
{
    volatile int isBusy;
    unsigned long channel;
    unsigned long src;
    unsigned long length;
    GXCommandDMACallback callback;
    void* arg;
    unsigned long fifoInterruptCondition; // before the transfer
    InterruptHandlerProc fifoInterruptHandler; // before the transfer
};

// The NitroSDK's MIi_GXDmaParams
static GXCommandDMAParams gxCommandDMAParams;

// The NitroSDK's G3X_SetFifoIntrCond: when the FIFO interrupt happens
static inline void SetFifoInterruptCondition(unsigned long condition)
{
    REG_GXSTAT = (condition << GXSTAT_FIFO_INTERRUPT_SHIFT) | (REG_GXSTAT & ~GXSTAT_FIFO_INTERRUPT_MASK);
}

// The NitroSDK's MIi_CallCallback
static inline void CallCallback(GXCommandDMACallback callback, void* arg)
{
    if (callback)
    {
        callback(arg);
    }
}

extern "C"
{
    void func_020ca1a0();
    void func_020ca24c(int);
    void func_020ca364(int);

    // usa: func_020ca0a8
    // MI_SendGXCommandAsync: sends the commands in parts, each time that the FIFO is half empty, and calls the callback
    // at the end
    void func_020ca0a8(unsigned long channel, const void* src, unsigned long length, GXCommandDMACallback callback,
                       void* arg)
    {
        if (length == 0)
        {
            CallCallback(callback, arg);
            return;
        }

        while (gxCommandDMAParams.isBusy)
        {
        }

        // G3X_GetCommandFifoStatus
        while (!(((REG_GXSTAT & GXSTAT_FIFO_STATUS_MASK) >> GXSTAT_FIFO_STATUS_SHIFT) & FIFO_STATUS_UNDER_HALF))
        {
        }

        gxCommandDMAParams.isBusy = 1;
        gxCommandDMAParams.channel = channel;
        gxCommandDMAParams.src = (unsigned long)src;
        gxCommandDMAParams.length = length;
        gxCommandDMAParams.callback = callback;
        gxCommandDMAParams.arg = arg;

        VerifyDMASource(channel, (unsigned long)src, length, DMA_SOURCE_INCREMENT);
        AwaitDMACompletion(channel);

        {
            int priorState = DisableIRQInterrupts();

            gxCommandDMAParams.fifoInterruptCondition =
                (REG_GXSTAT & GXSTAT_FIFO_INTERRUPT_MASK) >> GXSTAT_FIFO_INTERRUPT_SHIFT;
            gxCommandDMAParams.fifoInterruptHandler = GetInterruptHandler(INTERRUPT_GXFIFO);

            SetFifoInterruptCondition(FIFO_INTERRUPT_UNDER_HALF);
            SetInterruptHandler(INTERRUPT_GXFIFO, (const void*)func_020ca1a0);
            EnableSpecificInterrupts(INTERRUPT_GXFIFO);
            func_020ca1a0();

            SetIRQInterruptState(priorState);
        }
    }

    // usa: func_020ca1a0
    // MIi_FIFOCallback: sends the next part when the FIFO is half empty
    void func_020ca1a0()
    {
        unsigned long length;
        unsigned long src;

        if (gxCommandDMAParams.length == 0)
        {
            return;
        }

        length = (gxCommandDMAParams.length >= LENGTH_ONCE) ? LENGTH_ONCE : gxCommandDMAParams.length;
        src = gxCommandDMAParams.src;

        gxCommandDMAParams.length -= length;
        gxCommandDMAParams.src += length;

        if (gxCommandDMAParams.length == 0)
        {
            SetDMACompletionCallback(gxCommandDMAParams.channel, func_020ca24c, 0);
            ConfigureDMATransferAtomic(gxCommandDMAParams.channel, src, REG_GXFIFO_ADDR,
                                       DMA_CONTROL_SEND32_INTERRUPT(length));
            AcknowledgeSpecificInterrupts(INTERRUPT_GXFIFO);
        }
        else
        {
            ConfigureDMATransferAtomic(gxCommandDMAParams.channel, src, REG_GXFIFO_ADDR, DMA_CONTROL_SEND32(length));
            AcknowledgeSpecificInterrupts(INTERRUPT_GXFIFO);
        }
    }

    // usa: func_020ca24c
    // MIi_DMACallback: at the end of MI_SendGXCommandAsync
    void func_020ca24c(int)
    {
        DisableSpecificInterrupts(INTERRUPT_GXFIFO);

        SetFifoInterruptCondition(gxCommandDMAParams.fifoInterruptCondition);
        SetInterruptHandler(INTERRUPT_GXFIFO, (const void*)gxCommandDMAParams.fifoInterruptHandler);

        gxCommandDMAParams.isBusy = 0;
        CallCallback(gxCommandDMAParams.callback, gxCommandDMAParams.arg);
    }

    // usa: func_020ca2ac
    // MI_SendGXCommandAsyncFast: sends the commands in one transfer, which the geometry engine paces
    void func_020ca2ac(unsigned long channel, const void* src, unsigned long length, GXCommandDMACallback callback,
                       void* arg)
    {
        if (length == 0)
        {
            CallCallback(callback, arg);
            return;
        }

        while (gxCommandDMAParams.isBusy)
        {
        }

        gxCommandDMAParams.isBusy = 1;
        gxCommandDMAParams.channel = channel;
        gxCommandDMAParams.callback = callback;
        gxCommandDMAParams.arg = arg;

        VerifyDMATimingChangePermitted_020c9fd0(channel, DMA_TIMING_GXFIFO);
        VerifyDMASource(channel, (unsigned long)src, length, DMA_SOURCE_INCREMENT);
        AwaitDMACompletion(channel);

        SetDMACompletionCallback(channel, func_020ca364, 0);
        ConfigureDMATransferAtomic(channel, (unsigned long)src, REG_GXFIFO_ADDR, DMA_CONTROL_GXCOPY_INTERRUPT(length));
    }

    // usa: func_020ca364
    // MIi_DMAFastCallback: at the end of MI_SendGXCommandAsyncFast
    void func_020ca364(int)
    {
        gxCommandDMAParams.isBusy = 0;
        CallCallback(gxCommandDMAParams.callback, gxCommandDMAParams.arg);
    }
}
