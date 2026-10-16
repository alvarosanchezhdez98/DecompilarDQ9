#include <m2c.h>

u32 func_02088418(void *, u8, u16);
u32 func_ov024_021da9c8(void *);
u32 func_ov024_021fa76c(void *);
u32 func_ov024_021fd088(void *, f32, M2C_UNK);
M2C_UNK func_ov024_021fe6b4(void *, M2C_UNK);

u32 func_ov024_021fd1bc(void *arg0) {
    f32 temp_r0_6;
    f32 var_r4;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    void *temp_r0_5;
    void *temp_r1;
    void *temp_r2;
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg0, void **, 0x668);
    temp_r0_4 = func_ov024_021fa76c(temp_r4);
    if (temp_r0_4 == 0) {
        return temp_r0_4;
    }
    temp_r2 = M2C_FIELD(arg0, void **, 0x64C);
    temp_r0_3 = func_02088418(M2C_FIELD(temp_r4, void **, 0x138), (u8) M2C_FIELD(temp_r2, s16 *, 0x32), (u16) ((u32) (M2C_FIELD(temp_r2, s32 *, 4) << 0x14) >> 0x14));
    if (temp_r0_3 == 0) {
        return temp_r0_3;
    }
    temp_r0_2 = func_ov024_021da9c8(temp_r4);
    if (temp_r0_2 != 0) {
        return temp_r0_2;
    }
    temp_r1 = M2C_FIELD(arg0, void **, 0x64C);
    if (M2C_FIELD(temp_r1, s16 *, 0x30) == 2) {
        if (M2C_FIELD(temp_r4, u16 *, 0) & 0x400) {
            temp_r0_5 = M2C_FIELD(temp_r4, void **, 0x144);
            if (temp_r0_5 != NULL) {
                temp_r0 = (u32) (M2C_FIELD(temp_r0_5, u16 *, 0xA) << 0x14) >> 0x1F;
                if (temp_r0 != 0) {
                    return temp_r0;
                }
                goto block_13;
            }
        }
        goto block_13;
    }
block_13:
    temp_r0_6 = (f32) ((u32) (M2C_FIELD(temp_r1, s32 *, 0x14) << 0x12) >> 0x19) * ((f32) M2C_FIELD(M2C_FIELD(temp_r4, void **, 0x138), u8 *, 0x4C) / 100.0f);
    var_r4 = temp_r0_6;
    if (temp_r0_6 > 100.0f) {
        var_r4 = 100.0f;
    }
    func_ov024_021fe6b4(arg0, 1);
    return func_ov024_021fd088(arg0, var_r4, 8);
}
