#include <m2c.h>

M2C_UNK CPSi_sha1_calc(M2C_UNK *, M2C_UNK *, M2C_UNK);
M2C_UNK CPSi_sha1_init(M2C_UNK *);
M2C_UNK CPSi_sha1_result(M2C_UNK *, M2C_UNK *);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
extern s8 data_ov031_0224e3b0;
extern M2C_UNK data_ov031_0224e528;

void CPS_SslAddRandomSeed(M2C_UNK *arg0, M2C_UNK arg1) {
    M2C_UNK sp0[23];
    s32 temp_r4;

    CPSi_sha1_init(sp0);
    temp_r4 = _Z20DisableIRQInterruptsv();
    CPSi_sha1_calc(sp0, &data_ov031_0224e528, 0x14);
    CPSi_sha1_calc(sp0, arg0, arg1);
    CPSi_sha1_result(sp0, &data_ov031_0224e528);
    _Z20SetIRQInterruptStatei(temp_r4);
    data_ov031_0224e3b0 = 1;
}
