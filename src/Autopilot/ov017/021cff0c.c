#include <m2c.h>

s32 func_0200ff58(M2C_UNK, u8);
M2C_UNK func_02026394(s32, u8);
s32 func_0202c1a4(s32);
u8 func_020546a8();
M2C_UNK func_ov017_021907dc(void *, u8, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_ov017_02191234(void *);

void func_ov017_021cff0c(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3, s32 arg4) {
    u8 var_r4;

    if (M2C_FIELD(arg1, u8 *, 4) == func_0202c1a4(arg4)) {
        func_ov017_02191234(arg3);
        func_02026394(M2C_FIELD(arg3, s32 *, 0x36D0), M2C_FIELD(arg1, u8 *, 5));
        var_r4 = M2C_FIELD(arg1, u8 *, 5);
        if (func_0200ff58(arg2, var_r4) != 0) {
            var_r4 = func_020546a8();
        }
        func_ov017_021907dc(arg3, var_r4, 1, 1, 1);
    }
}
