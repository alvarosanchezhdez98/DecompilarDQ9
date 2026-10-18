#include <m2c.h>

s32 func_0202ae18();
M2C_UNK func_0202ae24();
M2C_UNK func_0202c600(s32, M2C_UNK);
M2C_UNK func_0203b4a0(void *, M2C_UNK);
M2C_UNK func_0205e22c();

void func_ov017_02195618(void *arg0) {
    s32 temp_r4;

    temp_r4 = func_0202ae18();
    func_0203b4a0(arg0, 2);
    M2C_FIELD(arg0, s8 *, 0x42E2) = 1;
    func_0202c600(temp_r4, 0);
    func_0202ae24();
    func_0205e22c();
}
