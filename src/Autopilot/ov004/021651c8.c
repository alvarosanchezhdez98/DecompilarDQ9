#include <m2c.h>

extern void *data_ov004_02171010;
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

s32 func_ov004_021651c8(void *arg0) {
    u8 temp_r0_2;
    u8 temp_r0_4;
    void *temp_r0;
    void *temp_r0_3;

    if (M2C_FIELD(data_ov004_02171010, u8 *, 0x18F4) == 0) {
        return 0;
    }
    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x1F5);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 1) {
        return 0;
    }
    temp_r0_2 = M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC);
    if (temp_r0_2 == 0) {
        M2C_FIELD(temp_r0, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0, u8 *, 0xC) | 8);
    } else if (temp_r0_2 == 1) {
        M2C_FIELD(temp_r0, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0, u8 *, 0xC) & ~8);
    }
    temp_r0_3 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x1F6);
    if (temp_r0_3 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_3) != 1) {
        return 0;
    }
    temp_r0_4 = M2C_FIELD(data_ov004_02171010, u8 *, 0x18FC);
    if (temp_r0_4 == 0) {
        M2C_FIELD(temp_r0_3, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0xC) & ~8);
    } else if (temp_r0_4 == 1) {
        M2C_FIELD(temp_r0_3, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0xC) | 8);
    }
    return 0;
}
