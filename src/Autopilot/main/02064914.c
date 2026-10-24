#include <m2c.h>

s32 func_02094d6c();
s32 func_02096134(s32, M2C_UNK);

s32 func_02064904(s32 arg0, M2C_UNK arg1, u32 arg2) {
    s32 temp_r0;
    s32 var_r1;

    temp_r0 = func_02096134(func_02094d6c(), arg1);
    var_r1 = 0;
    if (temp_r0 != 0) {
        switch (arg2) {
        default:
            break;
        case 0:
            var_r1 = temp_r0 + 0xA;
            break;
        case 1:
            var_r1 = temp_r0 + 0xA;
            break;
        case 2:
            var_r1 = temp_r0 + 0xC;
            break;
        case 3:
            var_r1 = temp_r0 + 0xE;
            break;
        case 4:
            var_r1 = temp_r0 + 4;
            break;
        case 5:
            var_r1 = temp_r0 + 6;
            break;
        case 6:
            var_r1 = temp_r0 + 8;
            break;
        case 7:
            var_r1 = temp_r0 + 0xA;
            break;
        case 8:
            var_r1 = temp_r0 + 0xC;
            break;
        case 9:
            var_r1 = temp_r0 + 0xE;
            break;
        }
    }
    return var_r1;
}
