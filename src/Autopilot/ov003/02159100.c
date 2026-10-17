#include <m2c.h>

M2C_UNK func_0205d2bc(void *);
M2C_UNK func_020e2834(void *);
s32 func_020e28dc(void *);
M2C_UNK func_020e2cc4(s32, s32);
M2C_UNK func_020e2d24(s32, M2C_UNK, M2C_UNK);

void func_ov003_02159100(void *arg0) {
    s32 temp_r4;
    void *temp_r0;

    if (M2C_FIELD(arg0, s8 *, 0x588) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x587) != 0) {
        return;
    }
    func_0205d2bc(arg0 + 0xF4);
    temp_r0 = M2C_FIELD(arg0, void **, 0x570);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x10);
    func_020e2d24(temp_r4 + 0x28, 0x11, 1);
    func_020e2cc4(temp_r4 + 0x28, func_020e28dc(M2C_FIELD(arg0, void **, 0x570)));
    func_020e2834(M2C_FIELD(arg0, void **, 0x570));
}
