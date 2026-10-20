#include <m2c.h>

M2C_UNK func_0202e694(void *, void *);
M2C_UNK func_020a0d58(s32);

void func_020a2744(void *arg0) {
    func_020a0d58(arg0 + 0x248);
    M2C_FIELD(arg0, s32 *, 0x220) = (s32) M2C_FIELD(arg0, s16 *, 0x21E);
    func_0202e694(arg0, arg0 + 0x220);
}
