#include <m2c.h>

s32 func_0202c1a4(s32);
s32 func_0207d78c();
M2C_UNK func_0207d7f4(s32, u16, M2C_UNK, u8, s32, s32, s32);
s32 func_0207d978(s32, u16);
s32 func_0207d9bc(s32, u16);
s32 func_0207da30(s32, u16, M2C_UNK);
M2C_UNK func_0207dcf0(u16);
s32 func_ov017_021a278c(M2C_UNK, u16);
M2C_UNK func_ov017_021c5e28(M2C_UNK, u16);

void func_ov017_021c5f54(M2C_UNK arg0, void *arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_r4;

    if (func_0202c1a4(arg4) == 0) {
        temp_r4 = func_0207d78c();
        if ((M2C_FIELD(arg1, u8 *, 9) == 0) && (M2C_FIELD(arg1, u8 *, 0xA) == 0)) {
            if ((func_ov017_021a278c(arg3, M2C_FIELD(arg1, u16 *, 4)) == 0) && (func_0207d9bc(temp_r4, M2C_FIELD(arg1, u16 *, 4)) == 0)) {
                func_ov017_021c5e28(arg0, M2C_FIELD(arg1, u16 *, 4));
                return;
            }
            goto block_8;
        }
block_8:
        if ((func_0207d978(temp_r4, M2C_FIELD(arg1, u16 *, 4)) == 0) && (func_0207da30(temp_r4, M2C_FIELD(arg1, u16 *, 4), arg0) == 0)) {
            func_0207d7f4(temp_r4, M2C_FIELD(arg1, u16 *, 4), arg0, M2C_FIELD(arg1, u8 *, 8), -1, (s32) M2C_FIELD(arg1, u16 *, 6), 0);
            func_0207dcf0(M2C_FIELD(arg1, u16 *, 4));
        }
    }
}
