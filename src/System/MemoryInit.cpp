#include "System/DMA.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's mi_init.c

// The NitroSDK's MI_WRAM_ARM7_ALL: all of the shared WRAM goes to the ARM7
#define WRAM_ARM7_ALL 3

extern "C"
{
    // usa: func_020c9bfc
    // The NitroSDK's MI_SetWramBank
    void func_020c9bfc(int banks);

    // usa: func_020cad00
    // MI_Init
    void func_020cad00()
    {
        func_020c9bfc(WRAM_ARM7_ALL);
        // MI_StopDma
        ResetDMAChannel(0);
    }
}
