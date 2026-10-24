#include <m2c.h>

extern M2C_UNK (*data_ov031_0224f4cc)(s32);

#pragma thumb on
void func_ov031_0221e470(s32 arg0, s32 arg1) {
    data_ov031_0224f4cc(arg1);
}
#pragma thumb off
