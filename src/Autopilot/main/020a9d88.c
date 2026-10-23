#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(s32, void *);
void *_ZN9GameState11GetInstanceEv();
void *func_0200fd0c();
s32 func_02012fe4();
M2C_UNK func_0201bc7c(s32, u16);
M2C_UNK func_0201bc88(s32, u16);
extern M2C_UNK data_02109bf4;

s32 func_020a9d78(void *arg0) {
    s32 temp_r0_2;
    s32 var_r1;
    void *temp_r0;
    void *temp_r3;
    void *temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fd0c();
    M2C_FIELD(temp_r0, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0);
    _ZN8Vector3iaSERKS_(temp_r0 + 0x10, arg0 + 4);
    M2C_FIELD(temp_r0, s16 *, 0x1C) = (s16) M2C_FIELD(arg0, s16 *, 2);
    M2C_FIELD(temp_r0, s8 *, 7) = 1;
    temp_r0_2 = func_02012fe4();
    func_0201bc7c(temp_r0_2, M2C_FIELD(arg0, u16 *, 0x12));
    func_0201bc88(temp_r0_2, M2C_FIELD(arg0, u16 *, 0x10));
    if (M2C_FIELD(arg0, u8 *, 0x14) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(&data_02109bf4, u8 *, 0xC8) = (u8) ((M2C_FIELD(&data_02109bf4, u8 *, 0xC8) & ~8) | ((u32) (var_r1 << 0x1F) >> 0x1C));
    temp_r3 = temp_r4 + 0x7E78;
    M2C_FIELD(temp_r4, s16 *, 0x7E78) = (s16) M2C_FIELD(arg0, s16 *, 0x16);
    M2C_FIELD(temp_r3, s16 *, 2) = (s16) M2C_FIELD(arg0, s16 *, 0x18);
    M2C_FIELD(temp_r3, s16 *, 4) = (s16) M2C_FIELD(arg0, s16 *, 0x1A);
    M2C_FIELD(temp_r3, s8 *, 6) = (s8) M2C_FIELD(arg0, s8 *, 0x15);
    return 1;
}
