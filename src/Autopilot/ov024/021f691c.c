#include <m2c.h>

M2C_UNK func_ov000_02160130();
s32 func_ov000_02160f08();
void *func_ov000_02171b9c(void *, s8);
void *func_ov024_021f69b4(s32, M2C_UNK);

s32 func_ov024_021f691c(void *arg0, u16 *arg1, void *arg2, M2C_UNK arg3) {
    u16 temp_r4;
    u8 temp_r0_3;
    u8 temp_r0_4;
    void *temp_r0;
    void *temp_r0_2;

    if (M2C_FIELD(arg0, f32 *, 4) > 0.0f) {
        temp_r4 = M2C_FIELD(arg0, u16 *, 0);
        if ((s32) M2C_FIELD(arg0, s8 *, 2) >= 0) {
            func_ov000_02160130();
            temp_r0 = func_ov024_021f69b4(func_ov000_02160f08(), arg3);
            if (temp_r0 != NULL) {
                M2C_FIELD(temp_r0, s8 *, 0x22) = (s8) M2C_FIELD(arg0, s8 *, 2);
                temp_r0_2 = func_ov000_02171b9c(temp_r0, M2C_FIELD(arg0, s8 *, 2));
                if (temp_r0_2 != NULL) {
                    M2C_FIELD(temp_r0, s16 *, 0x2C) = (s16) M2C_FIELD(temp_r0_2, s16 *, 0x18);
                }
            }
        }
        M2C_FIELD(arg2, u16 *, 0) = temp_r4;
        *arg1 = temp_r4;
        temp_r0_3 = M2C_FIELD(arg0, u8 *, 0xA);
        if (temp_r0_3 != 0xFF) {
            M2C_FIELD(arg2, u8 *, 3) = temp_r0_3;
        }
        temp_r0_4 = M2C_FIELD(arg0, u8 *, 0xB);
        if (temp_r0_4 != 0xFF) {
            M2C_FIELD(arg2, u8 *, 2) = temp_r0_4;
        }
        return 1;
    }
    return 0;
}
