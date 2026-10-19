#include <m2c.h>

M2C_UNK func_02048150();

void func_02053fe4(void *arg0) {
    func_02048150();
    M2C_FIELD(arg0, s32 *, 0x18C) = (s32) (M2C_FIELD(arg0, s32 *, 0x18C) & ~1);
}
