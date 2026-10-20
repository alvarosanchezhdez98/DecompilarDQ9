#include <m2c.h>

s32 func_ov031_022415a8(M2C_UNK);
s32 ov38_02221B48(void *, M2C_UNK, M2C_UNK, M2C_UNK);
s32 ov38_02221CD8(void *, M2C_UNK, s32);

s32 ov38_02221D9C(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r0;
    s32 var_r5;

    var_r5 = 0;
    if (M2C_FIELD(arg0, s32 *, 0) != 0) {
        return 0;
    }
    temp_r0 = func_ov031_022415a8(arg2);
    if (ov38_02221CD8(arg0, arg2, temp_r0) != 0) {
        var_r5 = ov38_02221B48(arg0 + 0x38, arg1, arg2, 0x18);
        if (var_r5 != 0) {
            M2C_FIELD(*M2C_FIELD(arg0, void ***, 0x38), s32 *, 0x10) = temp_r0;
        }
    }
    return var_r5;
}
