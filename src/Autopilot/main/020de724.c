#include <m2c.h>

M2C_UNK memcpy(void *, void *, M2C_UNK);
s32 func_020de7a4(void *);
M2C_UNK func_020de7d0(void *, M2C_UNK);

s32 func_020de714(void *arg0, void *arg1, s8 *arg2, M2C_UNK arg3) {
    *arg2 = 0;
    if (arg1 == NULL) {
        return 0;
    }
    memcpy(arg0, arg1, 0xC);
    M2C_FIELD(arg0, void **, 0xC) = (void *) (arg1 + 0xC);
    M2C_FIELD(arg0, void **, 0x10) = (void *) (arg1 + (func_020de7a4(arg0) + 0xC));
    if (((u32) M2C_FIELD(arg0, u32 *, 8) >> 0x1F) != 0) {
        *arg2 = 1;
        return 1;
    }
    func_020de7d0(arg0, arg3);
    M2C_FIELD(arg0, u32 *, 8) = (u32) ((M2C_FIELD(arg0, u32 *, 8) & ~0x80000000) | 0x80000000);
    M2C_FIELD(arg1, s32 *, 8) = (s32) ((M2C_FIELD(arg1, s32 *, 8) & ~0x80000000) | 0x80000000);
    return 1;
}
