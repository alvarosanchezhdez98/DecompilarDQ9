#include <m2c.h>

s32 ov00_021EB7CC(M2C_UNK *, M2C_UNK *);
M2C_UNK ov00_021EB864();
s32 ov00_021EB8B0(M2C_UNK *, M2C_UNK);
s32 strlen(M2C_UNK *);
extern M2C_UNK data_ov031_02249a80;
extern M2C_UNK ov00_021EC2A8;
extern M2C_UNK ov00_021EC2EC;

s32 ov00_021ECC6C(M2C_UNK *arg0, M2C_UNK arg1) {
    s32 var_r0;

    if (ov00_021EB7CC(&ov00_021EC2A8, &ov00_021EC2EC) == 0) {
        return 0;
    }
    if (strlen(arg0) == 0) {
        var_r0 = ov00_021EB8B0(&data_ov031_02249a80, arg1);
    } else {
        var_r0 = ov00_021EB8B0(arg0, arg1);
    }
    if (var_r0 != 0) {
        return 1;
    }
    ov00_021EB864();
    return 0;
}
