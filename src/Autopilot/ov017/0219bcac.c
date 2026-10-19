#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);
s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState14GetProtagonistEv(s32);
void *func_0200fd0c();
u16 *func_02012fe4();
M2C_UNK func_02070378(void *);

void func_ov017_0219bcac(s8 arg0) {
    s32 temp_r6;
    u16 *temp_r7;
    void *temp_r4;
    void *temp_r6_2;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_0200fd0c();
    temp_r7 = func_02012fe4();
    temp_r6_2 = _ZN9GameState14GetProtagonistEv(temp_r6);
    func_02070378(temp_r4);
    M2C_FIELD(temp_r4, u16 *, 0) = (u16) *temp_r7;
    _ZN8Vector3iaSERKS_(temp_r4 + 0x10, temp_r6_2 + 0x44);
    M2C_FIELD(temp_r4, s16 *, 0x1C) = (s16) M2C_FIELD(temp_r6_2, s32 *, 0x54);
    M2C_FIELD(temp_r4, s8 *, 7) = 1;
    M2C_FIELD(temp_r4, s8 *, 2) = 1;
    M2C_FIELD(temp_r4, s8 *, 9) = 0;
    M2C_FIELD(temp_r4, s8 *, 0xA) = 1;
    M2C_FIELD(temp_r4, s8 *, 0x65) = arg0;
}
