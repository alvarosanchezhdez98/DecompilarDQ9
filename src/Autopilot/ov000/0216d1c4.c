#include <m2c.h>

M2C_UNK _ZN6Script10InitializeEv(M2C_UNK *);
M2C_UNK _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(M2C_UNK *, M2C_UNK *);
M2C_UNK _ZN6Script4LoadEPKvj(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN6Script7ExecuteEv(M2C_UNK *);
extern M2C_UNK data_ov000_02183b5c;
extern M2C_UNK data_ov000_02184264;

void func_ov000_0216d1c4(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 *arg3) {
    M2C_UNK sp0[268];

    M2C_FIELD(&data_ov000_02184264, s32 *, 8) = arg0;
    M2C_FIELD(&data_ov000_02184264, s32 *, 4) = 0;
    M2C_FIELD(&data_ov000_02184264, s32 *, 0) = 0;
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov000_02183b5c);
    _ZN6Script4LoadEPKvj(sp0, arg1, arg2);
    _ZN6Script7ExecuteEv(sp0);
    *arg3 = M2C_FIELD(&data_ov000_02184264, s32 *, 0);
}
