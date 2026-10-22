#include <m2c.h>

s32 func_020d2ff0();
s32 sprintf(s32, M2C_UNK *);
extern M2C_UNK data_020eff4d;
extern M2C_UNK data_020eff57;
extern M2C_UNK data_020eff61;
extern M2C_UNK data_020eff6b;

s32 func_02041dd0(s32 arg0, u32 arg1) {
    s32 var_r4;

    var_r4 = arg0 + func_020d2ff0();
    switch (arg1) {
    default:
        break;
    case 0:
        var_r4 += sprintf(var_r4, &data_020eff4d);
        break;
    case 5:
        var_r4 += sprintf(var_r4, &data_020eff57);
        break;
    case 4:
        var_r4 += sprintf(var_r4, &data_020eff61);
        break;
    case 6:
        var_r4 += sprintf(var_r4, &data_020eff6b);
        break;
    }
    return var_r4 - arg0;
}
