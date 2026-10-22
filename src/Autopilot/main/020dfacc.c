#include <m2c.h>

M2C_UNK memcpy(void *, void *, M2C_UNK);
M2C_UNK func_020dfa68(void *, M2C_UNK);
s32 func_020dfbc0(void *);

s32 func_020dfabc(void *arg0, void *arg1, s8 *arg2, M2C_UNK arg3) {
    *arg2 = 0;
    if (arg1 == NULL) {
        return 0;
    }
    memcpy(arg0, arg1, 8);
    M2C_FIELD(arg0, void **, 8) = (void *) (arg1 + 8);
    M2C_FIELD(arg0, void **, 0xC) = (void *) (arg1 + (func_020dfbc0(arg0) + 8));
    if (((u32) (M2C_FIELD(arg0, s32 *, 4) << 0x10) >> 0x1F) != 0) {
        *arg2 = 1;
        return 1;
    }
    func_020dfa68(arg0, arg3);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) | 0x8000);
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) | 0x8000);
    return 1;
}
