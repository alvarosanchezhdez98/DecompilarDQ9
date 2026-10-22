#include <m2c.h>

M2C_UNK func_0205bf3c(void *);
M2C_UNK func_0205d6e4(void *, u8);
M2C_UNK func_0205d904(void *);

void func_0205d6a0(void *arg0, s32 arg1) {
    u8 var_r1;

    if ((M2C_FIELD(arg0, s32 *, 0x98) != 0) && (M2C_FIELD(arg0, s32 *, 0x9C) != 0)) {
        var_r1 = 1;
        if (arg1 != 0) {
            var_r1 = M2C_FIELD(arg0, u8 *, 0xB3);
        }
        func_0205d6e4(arg0, var_r1);
        func_0205bf3c(arg0 + 0x54);
        func_0205d904(arg0);
    }
}
