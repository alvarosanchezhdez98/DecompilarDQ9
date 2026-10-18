#include <m2c.h>

M2C_UNK func_02032e58();

void func_02048120(void *arg0) {
    func_02032e58();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x40);
    M2C_FIELD(arg0, s32 *, 0x130) = 0;
}
