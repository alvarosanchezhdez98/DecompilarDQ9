#include <m2c.h>

M2C_UNK _ZN6Script10InitializeEv(M2C_UNK *);
M2C_UNK _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(M2C_UNK *, M2C_UNK *);
M2C_UNK _ZN6Script4LoadEPKvj(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN6Script7ExecuteEv(M2C_UNK *);
extern M2C_UNK data_ov017_021d7900;
extern M2C_UNK data_ov017_021d83cc;

void func_ov017_021acc8c(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    M2C_UNK sp0[268];

    M2C_FIELD(&data_ov017_021d83cc, s32 *, 0) = arg0;
    M2C_FIELD(&data_ov017_021d83cc, s32 *, 4) = arg3;
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov017_021d7900);
    _ZN6Script4LoadEPKvj(sp0, arg1, arg2);
    _ZN6Script7ExecuteEv(sp0);
}
