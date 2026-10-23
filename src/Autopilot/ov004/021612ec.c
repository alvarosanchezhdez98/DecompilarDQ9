#include <m2c.h>

void *func_ov004_0215e4c0(void *, M2C_UNK);
u8 func_ov004_0215e9dc(void *, s32, u8, M2C_UNK);
s32 func_ov004_0215f74c(void *, s32);
M2C_UNK func_ov004_0215fdfc(void *);
M2C_UNK func_ov004_0216033c(void *);
M2C_UNK func_ov004_02161514(void *);
M2C_UNK func_ov004_02161c18(void *);
M2C_UNK func_ov004_02162108(void *);
extern M2C_UNK data_ov004_021707e8;
void _ZN16MenuObjectClass67RefreshEP10MenuScript(void *, void *);

s32 func_ov004_021612ec(void *arg0) {
    u32 temp_r1;

    if ((s32) M2C_FIELD(&data_ov004_021707e8, s8 *, 6) <= 1) {
        return 0;
    }
    if (func_ov004_0215f74c(arg0, M2C_FIELD(&data_ov004_021707e8, s32 *, 0x1C)) == 0) {
        func_ov004_0215fdfc(arg0);
        return 0;
    }
    M2C_FIELD(&data_ov004_021707e8, s8 *, 0xB) = (s8) (M2C_FIELD(&data_ov004_021707e8, s8 *, 0xB) + 1);
    if ((s32) M2C_FIELD(&data_ov004_021707e8, s8 *, 6) <= (s32) M2C_FIELD(&data_ov004_021707e8, s8 *, 0xB)) {
        M2C_FIELD(&data_ov004_021707e8, s8 *, 0xB) = 0;
    }
    temp_r1 = M2C_FIELD(&data_ov004_021707e8, u8 *, 7) - 0x64;
    switch (temp_r1) {
    default:
        break;
    case 0:
        M2C_FIELD(&data_ov004_021707e8, u8 *, 8) = func_ov004_0215e9dc(arg0, M2C_FIELD(&data_ov004_021707e8, s32 *, 0x1C), M2C_FIELD(&data_ov004_021707e8, u8 *, 8), 1);
        func_ov004_0216033c(arg0);
        break;
    case 1:
        M2C_FIELD(&data_ov004_021707e8, u8 *, 8) = func_ov004_0215e9dc(arg0, M2C_FIELD(&data_ov004_021707e8, s32 *, 0x1C), M2C_FIELD(&data_ov004_021707e8, u8 *, 8), 1);
        func_ov004_02161514(arg0);
        break;
    case 2:
        func_ov004_02161c18(arg0);
        break;
    case 3:
        func_ov004_02162108(arg0);
        break;
    }
    _ZN16MenuObjectClass67RefreshEP10MenuScript(func_ov004_0215e4c0(arg0, 3), arg0);
    return 0;
}
