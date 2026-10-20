#include <m2c.h>

M2C_UNK func_020c51a4(void *);
M2C_UNK func_02016e14(void *, void *, s32, M2C_UNK);

void func_02016db4(void *arg0, void *arg1) {
    *(s32 *)0x04000444 = 0;
    if (M2C_FIELD(arg0, s16 *, 0x474) != 0) {
        func_020c51a4(arg0 + 0x444);
    }
    func_02016e14(arg0, arg1, M2C_FIELD(arg1, s32 *, 0x44), 0);
    *(s32 *)0x04000448 = 1;
}
