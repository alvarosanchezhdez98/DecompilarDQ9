#pragma once

#include "ProcessorContext.h"
#include "std_library_functions.h"

// Exists at 0x027e0000
struct DTCMData
{
    void (*interruptProcTable[24])();
    BlockedContextList block_60;
    char unknown_60[0x3b80 - 0x68];
    unsigned int irqModeStack[0x100]; // 0x400 bytes of stack space
    char unknown_3f80[0xf8 - 0x80];
    // Bit n is set when interrupt n fires, if it's a DMA / timer interrupt
    unsigned int interruptsFired;
    unsigned int interruptJumpAddress; // holds 0x01ff8000
};

extern DTCMData data_027e0000;
// block_60, the contexts waiting for an interrupt, which the original code references by its own symbol
extern BlockedContextList data_027e0060;

// The original code accesses the DTCM through the symbol at its start, not through a fixed address. The address is
// unsigned like the NitroSDK's: with int, WaitForInterrupt computes it for its loop before the first check.
#define DTCM_DATA_INTERRUPTS_FIRED (*(unsigned int*)((unsigned int)&data_027e0000 + 0x3ff8))