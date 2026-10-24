#include <m2c.h>

s32 func_0205ec34();
M2C_UNK func_0206e748(s32, u8, u8, u16, s32);
M2C_UNK func_ov017_021a01bc(M2C_UNK);

void func_ov017_021d097c(s32 arg0, void *arg1, s32 arg2, M2C_UNK arg3) {
    u8 temp_r0;

    func_0206e748(func_0205ec34(), M2C_FIELD(arg1, u8 *, 4), M2C_FIELD(arg1, u8 *, 5), M2C_FIELD(arg1, u16 *, 6), (s32) M2C_FIELD(arg1, u16 *, 8));
    temp_r0 = M2C_FIELD(arg1, u8 *, 4);
    if ((temp_r0 != 0) && (temp_r0 != 2) && (temp_r0 != 7)) {
        return;
    }
    func_ov017_021a01bc(arg3);
}
