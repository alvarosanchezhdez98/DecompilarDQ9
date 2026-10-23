#include <m2c.h>

M2C_UNK func_ov004_0216afb0(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_ov004_0216b1c4(void *, M2C_UNK);
M2C_UNK func_ov004_0216b20c(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov004_0216b2c8(void *, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_ov004_0216b7bc(void *, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov004_02171034;
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);

s32 func_ov004_0216c750(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 1);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0, u8 *, 0xC) | 8);
    }
    func_ov004_0216b1c4(arg0, 0x12C);
    func_ov004_0216afb0(arg0, 0x32, 2, 0xD4, 0x36, 0xA, 0xA, 0xC, 1);
    M2C_FIELD(&data_ov004_02171034, s32 *, 0xC) = func_ov004_0216b7bc(arg0, 0xD4, 0x60, 0);
    func_ov004_0216b2c8(arg0, 0x12C, 0x32, 0);
    func_ov004_0216b20c(arg0, 0x32, 0xC9, 0);
    return 0;
}
