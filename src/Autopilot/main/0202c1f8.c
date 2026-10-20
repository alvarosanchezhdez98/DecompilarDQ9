#include <m2c.h>

s32 func_0202bcbc();
M2C_UNK func_0202c288(void *);

void func_0202c1e8(void *arg0) {
    s32 temp_r0;

    temp_r0 = func_0202bcbc();
    if (temp_r0 < 0) {
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x100C) = (u8) (M2C_FIELD(arg0, u8 *, 0x100C) | (1 << temp_r0));
    func_0202c288(arg0);
}
