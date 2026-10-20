#include <m2c.h>

M2C_UNK func_020bc078(s32);
M2C_UNK func_020bec74(void *);

void func_0203a914(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_020bc078(arg0 + 0x98);
    func_020bec74(arg0 + 0x9C);
    M2C_FIELD(arg0, s16 *, 0xA4) = -1;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    M2C_FIELD(arg0, s16 *, 0xAC) = -1;
    M2C_FIELD(arg0, s16 *, 0xAE) = -1;
}
