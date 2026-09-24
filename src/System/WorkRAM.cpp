#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's mi_wram.c

// WRAMCNT: how the shared work RAM is split between the ARM9 and the ARM7
#define WRAMCNT (*(volatile unsigned char*)0x04000247)

extern "C"
{
    // usa: func_020c9bfc
    // MI_SetWramBank
    void func_020c9bfc(int setting)
    {
        WRAMCNT = (unsigned char)setting;
    }
}
