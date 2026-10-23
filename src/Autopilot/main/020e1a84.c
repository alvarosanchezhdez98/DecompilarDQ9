#include <m2c.h>

M2C_UNK func_020e13dc(void *);
u32 func_020e2c34(void *);
M2C_UNK func_020e2cc4(void *, M2C_UNK);
M2C_UNK func_020e2d2c(void *, s32, s32, s32, s32);
M2C_UNK func_020e2d4c(void *, u8);

u32 func_020e1a74(void *arg0) {
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r3;
    void *var_r0;

    var_r0 = M2C_FIELD(arg0, void **, 4);
    if (var_r0 != NULL) {
        if (((u32) (M2C_FIELD(var_r0, u8 *, 0x3F) << 0x1E) >> 0x1F) != 0) {
            func_020e2cc4(arg0 + 0x28, 0);
            func_020e13dc(M2C_FIELD(arg0, void **, 4) + 0xC);
            temp_r1 = M2C_FIELD(arg0, void **, 4);
            M2C_FIELD(temp_r1, u8 *, 0x3F) = (u8) (M2C_FIELD(temp_r1, u8 *, 0x3F) & ~2);
        }
        temp_r1_2 = M2C_FIELD(arg0, void **, 4);
        var_r0 = (void *) ((u32) (M2C_FIELD(temp_r1_2, u8 *, 0x3F) << 0x1F) >> 0x1F);
        if (var_r0 != NULL) {
            func_020e2d4c(arg0 + 0x28, M2C_FIELD(temp_r1_2, u8 *, 0x3E));
            temp_r3 = M2C_FIELD(arg0, void **, 4);
            func_020e2d2c(arg0 + 0x28, M2C_FIELD(temp_r3, u8 *, 0x38) + 2, M2C_FIELD(temp_r3, u8 *, 0x39) + 2, M2C_FIELD(temp_r3, u8 *, 0x3A) - 4, M2C_FIELD(temp_r3, u8 *, 0x3B) - 4);
            var_r0 = (void *) func_020e2c34(arg0 + 0x28);
        }
    }
    return (u32) var_r0;
}
