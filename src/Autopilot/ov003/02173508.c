#include <m2c.h>

M2C_UNK func_02074b64(void *);
M2C_UNK func_020dc2bc();
M2C_UNK func_ov017_0218b5b0();

void func_ov003_02173508(void *arg0) {
    func_ov017_0218b5b0();
    if (M2C_FIELD(arg0, u8 *, 0xEF) != 0) {
        return;
    }
    func_020dc2bc();
    func_02074b64(arg0 + 0x10C);
    M2C_FIELD(arg0, u32 *, 0x124) = (u32) ((u32) (M2C_FIELD((void *)0x04001000, s32 *, 0) & 0x1F00) >> 8);
    M2C_FIELD((void *)0x04001000, s32 *, 0) = (s32) ((M2C_FIELD((void *)0x04001000, s32 *, 0) & ~0x1F00) | 0x1300);
    M2C_FIELD((void *)0x04001000, u16 *, 8) = (u16) (M2C_FIELD((void *)0x04001000, u16 *, 8) & ~3);
    M2C_FIELD((void *)0x04001000, u16 *, 0xA) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xA) & ~3) | 1);
    M2C_FIELD((void *)0x04001000, u16 *, 0xC) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xC) & ~3) | 2);
    M2C_FIELD((void *)0x04001000, u16 *, 0xE) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xE) & ~3) | 3);
    M2C_FIELD((void *)0x04001000, u16 *, 8) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 8) & 0x43) | 0xE00);
    M2C_FIELD((void *)0x04001000, u16 *, 0xA) = (u16) ((M2C_FIELD((void *)0x04001000, u16 *, 0xA) & 0x43) | 0xF00);
    M2C_FIELD(arg0, s8 *, 0xED) = 1;
    M2C_FIELD(arg0, u8 *, 0xEF) = 0U;
}
