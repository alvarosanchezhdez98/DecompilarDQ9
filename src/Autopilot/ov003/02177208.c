#include <m2c.h>

M2C_UNK func_02080b2c(s32, M2C_UNK);
M2C_UNK func_02080c20(s32, M2C_UNK);
M2C_UNK func_02080c68(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_02080fa8(s32, M2C_UNK, u8);
M2C_UNK func_020813ec(s32, M2C_UNK);

void func_ov003_02177208(void *arg0) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(arg0, s32 *, 0x89C);
    func_02080c20(temp_r4, 9);
    func_02080c68(temp_r4, 9, 0);
    func_02080fa8(temp_r4, 0x57, M2C_FIELD(arg0, u8 *, 0x103C));
    func_02080b2c(temp_r4, 0x58);
    func_02080b2c(temp_r4, 0x59);
    func_020813ec(temp_r4, 9);
}
