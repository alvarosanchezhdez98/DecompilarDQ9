#include <m2c.h>

M2C_UNK _ZN6Script10InitializeEv(M2C_UNK *);
M2C_UNK _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(M2C_UNK *, M2C_UNK *);
M2C_UNK _ZN6Script4LoadEPKvj(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN6Script7ExecuteEv(M2C_UNK *);
extern M2C_UNK data_ov017_021d7c54;
extern M2C_UNK data_ov017_021d7c58;
extern M2C_UNK data_ov017_021d8438;

s32 func_ov017_021ba810(M2C_UNK arg0, M2C_UNK arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    M2C_UNK sp0[268];
    s32 var_r0;

    if ((arg2 < 0) || (arg2 > 0x3E7)) {
        return 0;
    }
    M2C_FIELD(&data_ov017_021d8438, s32 *, 4) = arg3;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0x1C) = arg2;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 8) = arg4;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0x10) = 0;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0x14) = 0;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0x18) = arg5;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0x20) = arg6;
    M2C_FIELD(&data_ov017_021d8438, s8 *, 2) = 0;
    M2C_FIELD(&data_ov017_021d7c54, s8 *, 0) = -1;
    M2C_FIELD(&data_ov017_021d8438, s8 *, 0) = 0;
    M2C_FIELD(&data_ov017_021d8438, s8 *, 1) = 0;
    M2C_FIELD(&data_ov017_021d8438, s32 *, 0xC) = 0;
    M2C_FIELD(&data_ov017_021d7c54, s8 *, 1) = -1;
    _ZN6Script10InitializeEv(sp0);
    _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(sp0, &data_ov017_021d7c58);
    _ZN6Script4LoadEPKvj(sp0, arg0, arg1);
    _ZN6Script7ExecuteEv(sp0);
    var_r0 = M2C_FIELD(&data_ov017_021d8438, s32 *, 0x10);
    if (var_r0 == 0) {
        var_r0 = M2C_FIELD(&data_ov017_021d8438, s32 *, 0x14);
    }
    return var_r0;
}
