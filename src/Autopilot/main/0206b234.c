#include <m2c.h>

M2C_UNK func_0206aa28(void *);
M2C_UNK func_0206b104();
M2C_UNK func_0206b974(void *, M2C_UNK, s32, s32, s32, s32, s32, s32);
s32 func_020d2ff0(s32);
M2C_UNK memcpy(s32, s32, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0206b224(void *arg0) {
    s32 var_r1;
    void *temp_r1;
    void *temp_r2;

    func_0206b104();
    memset(M2C_FIELD(arg0, s32 *, 0x4C), 0, 0x280);
    memset(M2C_FIELD(arg0, s32 *, 0x50), 0, 0x280);
    temp_r2 = M2C_FIELD(arg0, void **, 0x58);
    var_r1 = 1;
    if (M2C_FIELD(temp_r2, u8 *, 1) == 0xFF) {
        var_r1 = 2;
    }
    temp_r1 = temp_r2 + var_r1;
    M2C_FIELD(arg0, void **, 0x54) = temp_r1;
    M2C_FIELD(arg0, void **, 0x58) = temp_r1;
    func_0206aa28(arg0);
    func_0206b974(arg0, 1, M2C_FIELD(arg0, s32 *, 0x50), M2C_FIELD(arg0, s32 *, 0x60), 0xE3, 0, 1, 1);
    memcpy(M2C_FIELD(arg0, s32 *, 0x50), M2C_FIELD(arg0, s32 *, 0x60), func_020d2ff0(M2C_FIELD(arg0, s32 *, 0x60)));
}
