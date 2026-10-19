#include <m2c.h>

M2C_UNK _Z19BlockCurrentContextP18BlockedContextList(s32);
M2C_UNK func_ov031_0221038c(M2C_UNK);
s32 func_ov031_02210ef8();
extern s32 data_ov031_0224e588;

s32 func_ov031_022102c8(void) {
    if (data_ov031_0224e588 == 0) {
        return 0;
    }
    if (func_ov031_02210ef8() == 0) {
        func_ov031_0221038c(1);
        _Z19BlockCurrentContextP18BlockedContextList(data_ov031_0224e588 + 0xA04);
    }
    return func_ov031_02210ef8();
}
