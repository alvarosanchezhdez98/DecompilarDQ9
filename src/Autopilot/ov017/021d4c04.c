#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, s32);
s32 strncmp(void *, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov017_021d82d4;

void func_ov017_021d4c04(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    M2C_FIELD(arg0, s32 *, 0x24) = arg4;
    M2C_FIELD(arg0, s32 *, 0x20) = arg5;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + (arg3 * 8));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) ((arg5 * 0xC) + M2C_FIELD(arg0, s32 *, 0x24));
    M2C_FIELD(arg0, void **, 0x44) = arg1;
    M2C_FIELD(arg0, void **, 0x48) = (void *) (arg1 + M2C_FIELD(arg1, s32 *, 8));
    if (strncmp(M2C_FIELD(arg0, void **, 0x44), &data_ov017_021d82d4, 3) != 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0) = 2;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x18) * 8));
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x18));
    memset(M2C_FIELD(arg0, s32 *, 0x1C), 0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x18) * 8);
}
