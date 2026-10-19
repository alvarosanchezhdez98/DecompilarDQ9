#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);
M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_0200fd0c();
M2C_UNK func_02070378();

void *func_ov017_0219c6f4(void *arg0) {
    void *temp_r4;

    _ZN9GameState11GetInstanceEv();
    temp_r4 = func_0200fd0c();
    func_02070378();
    M2C_FIELD(temp_r4, s16 *, 0) = (s16) M2C_FIELD(arg0, s32 *, 0x1C);
    _ZN8Vector3iaSERKS_(temp_r4 + 0x10, arg0 + 0x20);
    M2C_FIELD(temp_r4, s16 *, 0x1C) = (s16) M2C_FIELD(arg0, s16 *, 0x50);
    M2C_FIELD(temp_r4, s8 *, 0xB) = (s8) M2C_FIELD(arg0, s32 *, 0x6C);
    _ZN8Vector3iaSERKS_(temp_r4 + 0x30, arg0 + 0x20);
    _ZN8Vector3iaSERKS_(temp_r4 + 0x3C, arg0 + 0x2C);
    _ZN8Vector3iaSERKS_(temp_r4 + 0x48, arg0 + 0x38);
    _ZN8Vector3iaSERKS_(temp_r4 + 0x54, arg0 + 0x44);
    M2C_FIELD(temp_r4, s8 *, 0xC) = 1;
    M2C_FIELD(temp_r4, s8 *, 7) = 1;
    return temp_r4;
}
