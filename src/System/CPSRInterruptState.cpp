#include "System/Interrupts.h"
#include "System/DTCM.h"

// https://problemkaputt.de/gbatek.htm#armcpuflagsconditionfieldcond
// Notably: 
// - 0x80 bit of cpsr set iff IRQ interrupts are disabled
// - 0x40 bit of cpsr set iff FIQ interrupts are disabled

#define BITMASK_IRQ_INTERRUPTS_DISABLED 0x80
#define BITMASK_FIQ_INTERRUPTS_DISABLED 0x40

#define BITMASK_ALL_INTERRUPTS_DISABLED (BITMASK_IRQ_INTERRUPTS_DISABLED | BITMASK_FIQ_INTERRUPTS_DISABLED)

#define BITMASK_PROCESSOR_MODE 0x1f

int EnableIRQInterrupts()
{
    int oldState;
    __asm("mrs oldState, cpsr");
    int newState = oldState & ~BITMASK_IRQ_INTERRUPTS_DISABLED;
    __asm("msr cpsr_c, newState");
    return oldState & BITMASK_IRQ_INTERRUPTS_DISABLED;
}

int DisableIRQInterrupts()
{
    int oldState;
    __asm("mrs oldState, cpsr");
    int newState = oldState | BITMASK_IRQ_INTERRUPTS_DISABLED;
    __asm("msr cpsr_c, newState");
    return oldState & BITMASK_IRQ_INTERRUPTS_DISABLED;
}

int SetIRQInterruptState(int to)
{
    int oldState;
    __asm("mrs oldState, cpsr");
    int newState = (oldState & ~BITMASK_IRQ_INTERRUPTS_DISABLED);
    newState |= to;
    __asm("msr cpsr_c, newState");
    return oldState & BITMASK_IRQ_INTERRUPTS_DISABLED;
}

int DisableIRQAndFIQInterrupts()
{
    int oldState;
    __asm("mrs oldState, cpsr");
    int newState = oldState | BITMASK_ALL_INTERRUPTS_DISABLED;
    __asm("msr cpsr_c, newState");
    return oldState & BITMASK_ALL_INTERRUPTS_DISABLED;
}

int SetIRQAndFIQInterruptState(int to)
{
    int oldState;
    __asm("mrs oldState, cpsr");
    int newState = (oldState & ~BITMASK_ALL_INTERRUPTS_DISABLED);
    newState |= to;
    __asm("msr cpsr_c, newState");
    return oldState & BITMASK_ALL_INTERRUPTS_DISABLED;
}

int GetIRQInterruptState()
{
    int state;
    __asm("mrs state, cpsr");
    return state & BITMASK_IRQ_INTERRUPTS_DISABLED;
}

int GetProcessorMode()
{
    int state;
    __asm("mrs state, cpsr");
    return state & BITMASK_PROCESSOR_MODE;
}

// The rest of the NitroSDK's os_system.c, whose first part is the functions above

#define INTERRUPT_MASTER_ENABLE (*(volatile unsigned short*)0x04000208)

// The functions above can't be inlined, since their assembly uses their variables
#pragma dont_inline on
#pragma optimize_for_size off
#pragma optimization_level 4

extern "C"
{
    // BIOS: waits for a number of loops of 4 cycles
    void WaitByLoop(int count);
    // usa: func_020c9bf0
    // OS_Halt
    void func_020c9bf0();

    // usa: func_020c976c
    // OS_SpinWait: waits for a number of cycles
    asm void func_020c976c(unsigned long cycles)
    {
    loop:
        subs r0, r0, #4
        bhs loop
        bx lr
    }

    // usa: func_020c9778
    // OS_WaitInterrupt: halts the CPU until one of the interrupts fires, like WaitForInterrupt without the threads
    void func_020c9778(int clear, unsigned int mask)
    {
        int priorState = DisableIRQInterrupts();
        unsigned short previousMasterEnable = INTERRUPT_MASTER_ENABLE;
        INTERRUPT_MASTER_ENABLE = 1;

        if (clear)
        {
            DTCM_DATA_INTERRUPTS_FIRED &= ~mask;
        }

        while (!(mask & DTCM_DATA_INTERRUPTS_FIRED))
        {
            func_020c9bf0();
            EnableIRQInterrupts();
            DisableIRQInterrupts();
        }

        DTCM_DATA_INTERRUPTS_FIRED &= ~mask;
        // OS_RestoreIrq, which reads the previous state to return it
        (void)INTERRUPT_MASTER_ENABLE;
        INTERRUPT_MASTER_ENABLE = previousMasterEnable;
        SetIRQInterruptState(priorState);
    }

    // usa: func_020c9820
    // OS_WaitVBlankIntr
    void func_020c9820()
    {
        WaitByLoop(1);
        WaitForInterrupt(true, IRQ_MASK_LCD_VBLANK);
    }
}
