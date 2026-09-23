#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_emulator.c

#if defined(jpn)
#define data_020f2284 data_020f23f0
#endif

// The NitroSDK's OSi_ConsoleTypeCache
extern unsigned long data_020f2284;

extern "C"
{
    // usa: func_020c7dc4
    // OS_IsRunOnEmulator: always false in the final ROM
    int func_020c7dc4()
    {
        return false;
    }

    // usa: func_020c7dcc
    // OS_GetConsoleType: a Nintendo DS (not an emulator or a debugger) with 4 MB of memory, running from a card
    unsigned long func_020c7dcc()
    {
        data_020f2284 = 0x82000001;
        return data_020f2284;
    }
}
