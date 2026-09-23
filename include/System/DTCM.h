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
// The NitroSDK's HW_EXCP_VECTOR_BUF: the exception handler that the BIOS calls
#define DTCM_DATA_EXCEPTION_HANDLER (*(unsigned int*)((unsigned int)&data_027e0000 + 0x3fdc))

// The sizes of the IRQ stack and of the system stack (0: all the free DTCM below the IRQ stack). The NitroSDK's linker
// script defines them, so the code loads them like addresses (see tools/add_linker_symbols.py).
extern "C" void SDK_IRQ_STACKSIZE();
extern "C" void SDK_SYS_STACKSIZE();
#define IRQ_STACK_SIZE ((long)SDK_IRQ_STACKSIZE)
#define SYS_STACK_SIZE ((long)SDK_SYS_STACKSIZE)

// The NitroSDK's HW_DTCM_SVC_STACK: where the IRQ stack starts (it grows down), below the supervisor mode's stack
#define ADDR_DTCM_IRQ_STACK_BOTTOM ((unsigned long)&data_027e0000 + 0x3f80)
