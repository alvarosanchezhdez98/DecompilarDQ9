#include <m2c.h>

s32 _ZNK8Object3D10GetField06Ev(void *);
u16 *func_02012fe4();
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02108760;

void func_02034044(void *arg0, s32 arg1) {
    u16 temp_r5;

    temp_r5 = *func_02012fe4();
    if (temp_r5 == _ZNK8Object3D10GetField06Ev(arg0)) {
        func_0205eaa0(&data_02108760, 0x60, 0);
    }
    M2C_FIELD(arg0, u16 *, 0xC4) = (u16) ((M2C_FIELD(arg0, u16 *, 0xC4) & ~0x7FFF) | (arg1 & (-0x8000U >> 0x11)));
}
