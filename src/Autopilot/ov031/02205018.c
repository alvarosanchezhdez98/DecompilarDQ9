#include <m2c.h>

s32 WCM_GetApMacAddress();

s32 func_ov031_02205018(void) {
    if (WCM_GetApMacAddress() != 0) {
        return 1;
    }
    return 0;
}
