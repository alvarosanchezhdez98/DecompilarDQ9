// The NitroSDK's mi_swap.c, written in assembly

extern "C"
{
#ifdef __MWERKS__
    // usa: func_020ca7e0
    // MI_SwapWord: swaps a word in memory atomically, and returns the old value
    asm unsigned int func_020ca7e0(unsigned int newValue, volatile unsigned int* address)
    {
        swp r0, r0, [r1]
        bx lr
    }
#endif
}
