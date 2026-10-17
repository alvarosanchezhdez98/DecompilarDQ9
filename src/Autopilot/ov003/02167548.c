#include <m2c.h>

M2C_UNK func_0207fcb8();
M2C_UNK func_0207fd00(s32);
M2C_UNK func_0207fd44(s32);

void func_ov003_02167548(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x74) != 0) && (M2C_FIELD(arg0, s32 *, 0x10) != 0)) {
        func_0207fcb8();
        func_0207fd00(M2C_FIELD(arg0, s32 *, 0x10));
        func_0207fd44(M2C_FIELD(arg0, s32 *, 0x10));
    }
}
