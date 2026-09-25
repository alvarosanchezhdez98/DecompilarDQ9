#include "Wireless/WirelessDataSharing.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's wm_ks.c: key sharing, which the SDK now does with data sharing. Each console shares 2 bytes, its keys,
// with every other one.

// The data that each console shares (WM_KEYDATA_SIZE? The pad's keys)
#define KEY_DATA_SIZE 2

extern "C"
{
    // WM_StartKeySharing
    int func_020d68b4(WMDataSharingInfo* buf, unsigned short port)
    {
        return func_020d5d34(buf, port, 0xffff, KEY_DATA_SIZE, true);
    }

    // WM_EndKeySharing
    int func_020d68d0(WMDataSharingInfo* buf)
    {
        return func_020d5f88(buf);
    }
}
