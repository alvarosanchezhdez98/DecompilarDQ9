#include <m2c.h>

M2C_UNK func_0204693c();
extern s32 data_ov017_021d83ac;

void func_ov017_021a5568(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0xC;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    data_ov017_021d83ac = 0;
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s16 *, 0x22) = -1;
}
