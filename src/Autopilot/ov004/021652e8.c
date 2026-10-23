#include <m2c.h>

s32 func_0203b5f8(void *, M2C_UNK);
void *func_020421a0();
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov004_021651c8(M2C_UNK);
extern M2C_UNK data_02108760;
extern void *data_ov004_02171010;
void func_02026420(void *arg0, s8 arg1);

s32 func_ov004_021652e8(M2C_UNK arg0) {
    u8 temp_r1;
    u8 temp_r1_2;
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = func_ov017_0218b5b0();
    if ((func_0203b5f8(temp_r0, 0) == 0) || (func_0203b5f8(temp_r0, 1) == 0)) {
        return 0;
    }
    if (M2C_FIELD(func_020421a0(), s32 *, 0x998) != 0) {
        return 0;
    }
    if (M2C_FIELD(data_ov004_02171010, u8 *, 0x18F4) == 0) {
        return 0;
    }
    temp_r1 = M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC);
    if (temp_r1 == 0) {
        M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC) = 1U;
    } else if (temp_r1 == 1) {
        M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC) = 0U;
    }
    temp_r0_2 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x36D0);
    temp_r1_2 = M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC);
    if (temp_r1_2 == 1) {
        func_02026420(temp_r0_2, 0);
    } else if (temp_r1_2 == 0) {
        func_02026420(temp_r0_2, 1);
    }
    func_ov004_021651c8(arg0);
    func_0205eaa0(&data_02108760, 1, 0);
    return 0;
}
