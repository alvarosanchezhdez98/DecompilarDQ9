#include <m2c.h>

s32 func_0202c1a4(s32);
M2C_UNK func_ov017_021a23b0(void *, u16);
void *func_ov017_021b8478(void *);
M2C_UNK func_ov017_021b8b6c(void *);

void func_ov017_021c5e80(s32 arg0, void *arg1, s32 arg2, void *arg3, s32 arg4) {
    u8 temp_r4;
    u16 temp_r5;
    void *temp_r0;
    void *temp_r6;

    temp_r4 = M2C_FIELD(arg1, u8 *, 4);
    temp_r6 = M2C_FIELD(arg3, void **, 0x3718);
    temp_r5 = M2C_FIELD(arg1, u16 *, 6);
    if (temp_r4 != func_0202c1a4(arg4)) {
        if (M2C_FIELD(temp_r6, u8 *, 2) == 0) {
            return;
        }
        temp_r0 = func_ov017_021b8478(temp_r6);
        if (temp_r0 == NULL) {
            return;
        }
        if (M2C_FIELD(temp_r0, u16 *, 8) != temp_r5) {
            return;
        }
        func_ov017_021b8b6c(temp_r6);
        func_ov017_021a23b0(arg3, temp_r5);
        return;
    }
    func_ov017_021b8b6c(temp_r6);
    func_ov017_021a23b0(arg3, temp_r5);
}
