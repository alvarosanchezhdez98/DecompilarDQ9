#include <m2c.h>

M2C_UNK _ZN6Script10InitializeEv(M2C_UNK *);
M2C_UNK _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(M2C_UNK *, M2C_UNK *);
M2C_UNK _ZN6Script4LoadEPKvj(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN6Script7ExecuteEv(M2C_UNK *);
extern M2C_UNK data_ov003_0217ff40;
extern M2C_UNK data_ov003_02180cb8;

void func_ov003_0215e6f8(s32 arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3) {
    M2C_UNK sp0[268];

    M2C_FIELD(&data_ov003_02180cb8, s32 *, 4) = arg0;
    M2C_FIELD(&data_ov003_02180cb8, s32 *, 0) = arg1;
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov003_0217ff40);
    _ZN6Script4LoadEPKvj(sp0, arg2, arg3);
    _ZN6Script7ExecuteEv(sp0);
}
