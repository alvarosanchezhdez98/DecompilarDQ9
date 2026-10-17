#include <m2c.h>

M2C_UNK _ZN8Object3D4DrawEb(void *, M2C_UNK);
M2C_UNK func_ov003_02173ef4(void *);

void func_ov003_0216d5f0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x13E8) != 0) {
        _ZN8Object3D4DrawEb(arg0 + 0x133C, 1);
    }
    if ((M2C_FIELD(arg0, s16 *, 4) == 5) && (M2C_FIELD(arg0, s16 *, 6) == 6)) {
        func_ov003_02173ef4(arg0 + 0xF1C);
    }
}
