#include <m2c.h>

M2C_UNK func_0207fcb8(s32);
M2C_UNK func_0207fd00(s32);
M2C_UNK func_0207fd44(s32);
M2C_UNK func_0207fe80(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov003_0217545c(void *);
M2C_UNK func_ov003_02175504(void *);
M2C_UNK func_ov003_0217577c(void *);
M2C_UNK func_ov003_02175fd4(void *);
M2C_UNK func_ov003_02176098(void *);

void func_ov003_0217480c(void *arg0) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, u8 *, 0x103E) == 0) {
        return;
    }
    temp_r4 = M2C_FIELD(arg0, s32 *, 0x89C);
    func_0207fcb8(temp_r4);
    func_0207fd00(temp_r4);
    func_0207fe80(temp_r4, 1, 2, 1);
    func_0207fd44(temp_r4);
    func_ov003_02175fd4(arg0);
    func_ov003_02176098(arg0);
    func_ov003_0217545c(arg0);
    func_ov003_02175504(arg0);
    func_ov003_0217577c(arg0);
    M2C_FIELD(arg0, s8 *, 0x104C) = 0;
    M2C_FIELD(arg0, s8 *, 0x104B) = 0;
}
