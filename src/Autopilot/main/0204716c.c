#include <m2c.h>

M2C_UNK _ZN8Object3D4DrawEb(void *, M2C_UNK);

void func_0204715c(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0xE8);
    if (temp_r1 != NULL) {
        _ZN8Object3D4DrawEb(temp_r1, 1);
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x1D) == 0) {
        return;
    }
    _ZN8Object3D4DrawEb(arg0 + 0x3C, 1);
}
