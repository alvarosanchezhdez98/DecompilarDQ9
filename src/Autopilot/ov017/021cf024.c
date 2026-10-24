#include <m2c.h>

M2C_UNK func_ov000_02163338(void *, u8);
void *func_ov017_021b8468(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021cf024(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r5;

    temp_r4 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r5 = func_ov017_021b8478(temp_r4);
    temp_r0 = func_ov017_021b8468(temp_r4);
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r5, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    func_ov000_02163338(temp_r0, M2C_FIELD(arg1, u8 *, 6));
    M2C_FIELD(temp_r0, u8 *, 0x7748) = (u8) M2C_FIELD(arg1, u8 *, 7);
}
