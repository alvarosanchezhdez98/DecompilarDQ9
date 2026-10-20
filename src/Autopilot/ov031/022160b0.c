#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
s16 func_020d4aa8();
s16 func_020d4be8();
s32 func_020d5340(M2C_UNK *, void *);
extern void *data_ov031_0224e5d8;
extern M2C_UNK func_ov031_02215ce0;

s32 ov00_021FDA9C(s32 arg0) {
    s32 var_r0;

    if (arg0 == 0) {
        return -1;
    }
    M2C_FIELD(data_ov031_0224e5d8, void **, 0x1300) = (void *) (data_ov031_0224e5d8 + 0xF00);
    M2C_FIELD(data_ov031_0224e5d8, s16 *, 0x1304) = 0x400;
    M2C_FIELD(data_ov031_0224e5d8, s16 *, 0x1306) = func_020d4aa8();
    M2C_FIELD(data_ov031_0224e5d8, s16 *, 0x1308) = func_020d4be8();
    M2C_FIELD(data_ov031_0224e5d8, s16 *, 0x1310) = 1;
    VectorizedMemset(data_ov031_0224e5d8 + 0x130A, 0xFF, 6);
    M2C_FIELD(data_ov031_0224e5d8, s32 *, 0x1344) = arg0;
    M2C_FIELD(data_ov031_0224e5d8, s32 *, 0x1A90) = 1;
    var_r0 = func_020d5340(&func_ov031_02215ce0, data_ov031_0224e5d8 + 0x1300);
    if (var_r0 == 2) {
        var_r0 = 0;
    }
    return var_r0;
}
