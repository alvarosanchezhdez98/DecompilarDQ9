#include <m2c.h>

s32 func_0204c7cc();
M2C_UNK func_0205bc24(s32, M2C_UNK);
s8 func_0205d0e0(s32, M2C_UNK);
void *func_0205d8c4(s32);

void func_ov003_021694b8(void *arg0, M2C_UNK arg1) {
    void *temp_r0;

    temp_r0 = func_0205d8c4(arg0 + 0xE4);
    if ((temp_r0 != NULL) && (func_0204c7cc() != 0) && !(M2C_FIELD(temp_r0, u8 *, 0xC5) & 2)) {
        func_0205bc24(arg0 + 0xE8, -1);
    }
    M2C_FIELD(arg0, s8 *, 0x4EA) = func_0205d0e0(arg0 + 0xE4, arg1);
}
