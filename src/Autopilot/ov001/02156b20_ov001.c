#include <m2c.h>
#pragma optimization_level 4

u16 *func_02012fe4();
M2C_UNK func_0203b4b0(s32, M2C_UNK);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_0209c530(M2C_UNK *);
s32 func_0209ca68(M2C_UNK *);
s32 func_ov017_0218b5b0();
extern M2C_UNK data_02109bf4;

void func_ov001_02156b20(void) {
    s32 temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    if (func_0209ca68(&data_02109bf4) == 2) {
        func_0209c530(&data_02109bf4);
    }
    if (*func_02012fe4() != 0x2710) {
        func_0203b4e8(temp_r4, 4);
    }
    func_0203b4e8(temp_r4, 0x40);
    func_0203b4e8(temp_r4, 0x10);
    func_0203b4e8(temp_r4, 2);
    func_0203b4b0(temp_r4, 4);
}
