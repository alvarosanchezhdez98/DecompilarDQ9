#include <m2c.h>

M2C_UNK func_ov024_021fd088(void *, f32, M2C_UNK);
M2C_UNK func_ov024_021fd104(void *, M2C_UNK);
M2C_UNK func_ov024_021fe6b4(void *, M2C_UNK);

void func_ov024_021fd504(void *arg0) {
    f32 temp_r0;
    f32 var_r5;
    u8 temp_r6;
    void *temp_r3;
    void *temp_r7;

    temp_r3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x668), void **, 0x138);
    if ((s32) ((s32) (M2C_FIELD(temp_r3, s32 *, 0x58) << 0x1A) >> 0x1D) <= -2) {
        return;
    }
    temp_r6 = M2C_FIELD(temp_r3, u8 *, 0x50);
    if (temp_r6 == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x661) != 0) {
        temp_r7 = M2C_FIELD(arg0, void **, 0x64C);
        temp_r0 = (f32) ((u32) (M2C_FIELD(temp_r7, s32 *, 0x14) << 0x12) >> 0x19) * ((f32) temp_r6 / 100.0f);
        var_r5 = temp_r0;
        if (temp_r0 > 100.0f) {
            var_r5 = 100.0f;
        }
        if ((s32) M2C_FIELD(temp_r7, s16 *, 0x32) >= 0) {
            return;
        }
        func_ov024_021fe6b4(arg0, 0xD);
        func_ov024_021fd088(arg0, var_r5, 0x12);
        return;
    }
    func_ov024_021fd104(arg0, 0x12);
}
