#include <m2c.h>

M2C_UNK func_02080b40(M2C_UNK, M2C_UNK);
M2C_UNK func_02080fa8(M2C_UNK, M2C_UNK, s32);

void func_ov003_0215f5e8(M2C_UNK arg0, s32 arg1, s32 arg2) {
    s32 temp_r4;

    if (arg2 <= 4) {
        return;
    }
    temp_r4 = (arg2 + 3) & ~3;
    func_02080b40(arg0, 0xD3);
    func_02080b40(arg0, 0xD4);
    func_02080b40(arg0, 0xD5);
    func_02080fa8(arg0, 0xD4, arg1 + 1);
    func_02080fa8(arg0, 0xD5, (s32) (temp_r4 + ((u32) (temp_r4 >> 1) >> 0x1E)) >> 2);
}
