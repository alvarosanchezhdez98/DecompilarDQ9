#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
s32 func_02039820();
M2C_UNK func_0204693c();
M2C_UNK func_0205c790(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov017_021af59c(void *arg0) {
    s8 var_r0;

    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x26;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0;
    memset(arg0 + 0x1B, 0, 4);
    M2C_FIELD(arg0, s8 *, 0x1F) = 0;
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x25) = 0;
    M2C_FIELD(arg0, s8 *, 0x26) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s8 *, 0x27) = 0;
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    memset(arg0 + 0x43, 0, 5);
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = 0;
    M2C_FIELD(arg0, s8 *, 0x42) = 0;
    func_0205c790(arg0 + 0x48);
    M2C_FIELD(arg0, u32 *, 0x280) = (u32) ((u32) (*(s32 *)0x04000000 & 0x1F00) >> 8);
    _ZN9GameState11GetInstanceEv();
    if (_ZN9GameState20GetUnknownGameObjectEv() != 0) {
        if (func_02039820() != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    } else {
        var_r0 = 1;
    }
    M2C_FIELD(arg0, s8 *, 0x284) = var_r0;
    M2C_FIELD(arg0, s32 *, 0x288) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
}
