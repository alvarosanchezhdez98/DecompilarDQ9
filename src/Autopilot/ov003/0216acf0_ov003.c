#include <m2c.h>

s32 func_0204c7e0();
M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205ae8c(void *);
void *func_0205d8c4(void *);

void func_ov003_0216acf0(void *arg0) {
    s16 temp_r5;
    s16 temp_r6;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;

    if (!(M2C_FIELD(arg0, u8 *, 0x59F) & 1)) {
        return;
    }
    temp_r0 = func_0205d8c4(arg0 + 0xE4);
    if (temp_r0 == NULL) {
        return;
    }
    if (func_0204c7e0() == 0) {
        return;
    }
    if (M2C_FIELD(temp_r0, u8 *, 0xC5) & 0x20) {
        return;
    }
    temp_r5 = M2C_FIELD(temp_r0, s16 *, 0xBC) + (s16) (M2C_FIELD(temp_r0, s16 *, 0xAC) * 8);
    temp_r6 = M2C_FIELD(temp_r0, s16 *, 0xBE) + (s16) (M2C_FIELD(temp_r0, s16 *, 0xAE) * 8);
    func_0205a370(M2C_FIELD(arg0, s32 *, 0x4D8), 0);
    temp_r0_2 = func_0205a3d0(M2C_FIELD(arg0, s32 *, 0x4D8), 0);
    if (temp_r0_2 != NULL) {
        M2C_FIELD(temp_r0_2, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0x15) | 8);
    }
    func_0205a330(M2C_FIELD(arg0, s32 *, 0x4D8), M2C_FIELD(arg0, s32 *, 0x4DC));
    temp_r0_3 = func_0205a3d0(M2C_FIELD(arg0, s32 *, 0x4D8), 0);
    if (temp_r0_3 != NULL) {
        M2C_FIELD(temp_r0_3, s16 *, 4) = (s16) (temp_r5 - 8);
        M2C_FIELD(temp_r0_3, s16 *, 6) = (s16) (temp_r6 - 2);
    }
    func_0205ae8c(arg0 + 0x480);
}
