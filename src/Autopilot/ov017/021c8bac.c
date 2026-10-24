#include <m2c.h>

M2C_UNK func_ov000_02160fa8(s32, M2C_UNK);
s32 func_ov017_021b8468(void *);
void *func_ov017_021b8478(void *);

void func_ov017_021c8bac(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    s32 temp_r0_2;
    void *temp_r0;
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg3, void **, 0x3718);
    if (M2C_FIELD(temp_r4, u8 *, 2) == 0) {
        return;
    }
    temp_r0 = func_ov017_021b8478(temp_r4);
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    temp_r0_2 = func_ov017_021b8468(temp_r4);
    if (temp_r0_2 == 0) {
        return;
    }
    func_ov000_02160fa8(temp_r0_2, 0x02000000);
}
