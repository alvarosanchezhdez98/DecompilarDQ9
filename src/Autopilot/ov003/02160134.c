#include <m2c.h>

M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205ae8c(void *);
M2C_UNK func_0207fcb8(s32);
M2C_UNK func_0207fd00(s32);
M2C_UNK func_0207fd44(s32);
M2C_UNK func_0207fe80(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020e2794(s32, void *);
M2C_UNK func_020e27ec(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_020e28dc();
M2C_UNK func_ov003_0216039c(void *);
M2C_UNK func_ov003_02166fc4(void *);
M2C_UNK func_ov003_02167548();

void func_ov003_02160134(void *arg0) {
    s32 temp_r5;
    void *temp_r0;
    void *temp_r0_2;

    if (M2C_FIELD(arg0, u8 *, 0x4A3) == 0) {
        return;
    }
    temp_r5 = M2C_FIELD(arg0, s32 *, 0x324);
    if (temp_r5 != 0) {
        func_0207fcb8(temp_r5);
        func_0207fd00(temp_r5);
        func_0207fe80(temp_r5, 1, 2, 1);
        func_0207fd44(temp_r5);
    }
    func_ov003_02166fc4(arg0);
    if ((M2C_FIELD(arg0, s32 *, 0x390) != 0) && (func_020e28dc() != 0)) {
        func_020e2794(M2C_FIELD(arg0, s32 *, 0x390), arg0 + 0x334);
    }
    func_ov003_0216039c(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x318) != 0) {
        func_ov003_02167548();
    }
    if (!(M2C_FIELD(arg0, s32 *, 0x464) & 0x02000000)) {
        return;
    }
    func_0205a370(M2C_FIELD(arg0, s32 *, 0x38C), 1);
    temp_r0 = func_0205a3d0(M2C_FIELD(arg0, s32 *, 0x38C), 0);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x15) & ~8);
    }
    temp_r0_2 = func_0205a3d0(M2C_FIELD(arg0, s32 *, 0x38C), 1);
    if (temp_r0_2 != NULL) {
        M2C_FIELD(temp_r0_2, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0x15) | 8);
    }
    func_0205a330(M2C_FIELD(arg0, s32 *, 0x38C), M2C_FIELD(arg0, s32 *, 0x460));
    func_020e27ec(M2C_FIELD(arg0, s32 *, 0x38C), 1, 0xD7, 0x96);
    func_0205ae8c(arg0 + 0x334);
}
