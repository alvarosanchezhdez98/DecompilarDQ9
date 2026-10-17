#include <m2c.h>

M2C_UNK _ZN11GuideWindow5Draw1Ev();
M2C_UNK func_0207fcb8(s32);
M2C_UNK func_0207fd00(s32);
M2C_UNK func_0207fd44(s32);
M2C_UNK func_0207fe80(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020e2794(s32, void *);
s32 func_020e28dc();
M2C_UNK func_ov003_0215501c(void *);

void func_ov003_02154eec(void *arg0) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, u8 *, 0x1F8) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x204) != 0) {
        _ZN11GuideWindow5Draw1Ev();
    } else {
        temp_r4 = M2C_FIELD(arg0, s32 *, 0x18);
        if (temp_r4 != 0) {
            func_0207fcb8(temp_r4);
            func_0207fd00(temp_r4);
            func_0207fe80(temp_r4, 2, 1, 1);
            func_0207fd44(temp_r4);
        }
    }
    if ((M2C_FIELD(arg0, s32 *, 0x1C) != 0) && (func_020e28dc() != 0)) {
        func_020e2794(M2C_FIELD(arg0, s32 *, 0x1C), arg0 + 0x2C);
        return;
    }
    func_ov003_0215501c(arg0);
}
