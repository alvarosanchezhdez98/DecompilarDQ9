#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
M2C_UNK _ZN6Script10InitializeEv(M2C_UNK *);
M2C_UNK _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(M2C_UNK *, M2C_UNK *);
M2C_UNK _ZN6Script4LoadEPKvj(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN6Script7ExecuteEv(M2C_UNK *);
extern M2C_UNK data_ov001_02164b80;
extern M2C_UNK data_ov001_02164b90;
extern M2C_UNK data_ov001_02165800;

void func_ov001_021537b0(void *arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3) {
    M2C_UNK sp0[268];
    s32 temp_r0;

    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(&data_ov001_02165800, s32 *, 0) = 0;
    M2C_FIELD(&data_ov001_02165800, s32 *, 4) = arg1;
    M2C_FIELD(&data_ov001_02165800, void **, 8) = arg0;
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov001_02164b80);
    _ZN6Script4LoadEPKvj(sp0, arg2, arg3);
    _ZN6Script7ExecuteEv(sp0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(&data_ov001_02165800, s32 *, 0);
    M2C_FIELD(&data_ov001_02165800, s32 *, 0) = 0;
    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg1, M2C_FIELD(arg0, s32 *, 4) * 8);
    M2C_FIELD(arg0, s32 *, 0) = temp_r0;
    if (temp_r0 == 0) {
        M2C_FIELD(arg0, s32 *, 4) = 0;
        return;
    }
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov001_02164b90);
    _ZN6Script4LoadEPKvj(sp0, arg2, arg3);
    _ZN6Script7ExecuteEv(sp0);
}
