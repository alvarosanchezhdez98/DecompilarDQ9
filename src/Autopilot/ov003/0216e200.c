#include <m2c.h>

s32 func_0203b4d0();
void *func_020421a0();
M2C_UNK func_02074af4(void *);
M2C_UNK func_020c5588(M2C_UNK, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_ov003_02170688(void *);
M2C_UNK func_ov003_02170898(void *);
M2C_UNK func_ov017_0218b5b0();

void func_ov003_0216e200(void *arg0) {
    if (M2C_FIELD(arg0, s8 *, 2) == 0) {
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(func_020421a0(), s32 *, 0x5C);
        func_ov003_02170898(arg0);
        func_ov003_02170688(arg0);
        func_02074af4(arg0 + 0x48);
        M2C_FIELD(arg0, u32 *, 0x5C) = (u32) ((u32) (*(s32 *)0x04000000 & 0x1F00) >> 8);
        *(s32 *)0x04000000 = (*(s32 *)0x04000000 & ~0x1F00) | 0x700;
        func_ov017_0218b5b0();
        M2C_FIELD(arg0, s32 *, 0x174) = func_0203b4d0();
        func_020c5588(0, 0, 0x7FFF, 0, 0);
        M2C_FIELD(arg0, s8 *, 1) = 1;
        M2C_FIELD(arg0, s8 *, 2) = 0;
        M2C_FIELD(arg0, s32 *, 0x16C) = 0;
    }
}
