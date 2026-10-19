#include <m2c.h>

M2C_UNK CPS_SocRegister(void *);
M2C_UNK VectorizedMemset(s32, M2C_UNK, M2C_UNK);

void ov00_021E92E4(void *arg0) {
    VectorizedMemset(arg0 + 0x1138, 0, 0x64);
    M2C_FIELD(arg0, s32 *, 0x1174) = 0xB68;
    M2C_FIELD(arg0, s32 *, 0x1178) = (s32) M2C_FIELD(arg0, s32 *, 0x19CC);
    M2C_FIELD(arg0, s32 *, 0x1180) = 0x5EA;
    M2C_FIELD(arg0, s32 *, 0x1184) = (s32) M2C_FIELD(arg0, s32 *, 0x19D0);
    CPS_SocRegister(arg0 + 0x1138);
}
