#include <m2c.h>
#pragma optimization_level 4

s32 func_ov001_02164624(s32, s32);
extern s32 data_ov001_02165884[0xD];

s32 func_ov001_02159b04(s32 arg0, void *arg1) {
    if (func_ov001_02164624(*data_ov001_02165884, M2C_FIELD(arg1, s32 *, 0x70)) == 0) {
        return 1;
    }
    return 0;
}
