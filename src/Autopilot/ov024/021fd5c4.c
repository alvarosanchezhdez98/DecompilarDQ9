#include <m2c.h>

s32 func_020883ac(void *);
s32 func_ov024_021de25c(void *);
s32 func_ov024_021fa76c(void *);
M2C_UNK func_ov024_021fd088(void *, f32, M2C_UNK);
M2C_UNK func_ov024_021fe6b4(void *, M2C_UNK);

void func_ov024_021fd5c4(void *arg0) {
    f32 temp_r0;
    f32 var_r5;
    void *temp_r5;

    temp_r5 = M2C_FIELD(arg0, void **, 0x668);
    if (func_ov024_021fa76c(temp_r5) == 0) {
        return;
    }
    if (func_020883ac(M2C_FIELD(temp_r5, void **, 0x138)) == 0) {
        return;
    }
    if (func_ov024_021de25c(temp_r5) != 0) {
        return;
    }
    temp_r0 = (f32) ((u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x64C), s32 *, 0x14) << 0x12) >> 0x19) * ((f32) M2C_FIELD(M2C_FIELD(temp_r5, void **, 0x138), u8 *, 0x4A) / 100.0f);
    var_r5 = temp_r0;
    if (temp_r0 > 100.0f) {
        var_r5 = 100.0f;
    }
    func_ov024_021fe6b4(arg0, 1);
    func_ov024_021fd088(arg0, var_r5, 7);
}
