#include <m2c.h>

extern s32 data_ov031_02290d60;

s32 ov13_02241DE4(s32 arg0, s32 arg1) {
    return data_ov031_02290d60 + (arg0 << 0xA) + (arg1 * 8);
}
