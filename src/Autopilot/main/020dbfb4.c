#include <m2c.h>

s32 func_02057924();
M2C_UNK func_02057fb4(s32, s32, M2C_UNK);

void func_020dbfa4(void *arg0, M2C_UNK arg1) {
    if ((M2C_FIELD(arg0, s32 *, 0x10) == 2) && (M2C_FIELD(arg0, u8 *, 0x14) == 0)) {
        func_02057fb4(func_02057924(), M2C_FIELD(arg0, s32 *, 8), arg1);
        M2C_FIELD(arg0, u8 *, 0x14) = 1U;
    }
}
