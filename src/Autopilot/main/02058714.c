#include <m2c.h>

M2C_UNK func_02057930(s32);
M2C_UNK func_02059cb4(u32);

s32 func_02058704(s32 arg0) {
    u32 var_r5;

    var_r5 = arg0 + 8;
    do {
        func_02059cb4(var_r5);
        var_r5 += 0xD4;
    } while (var_r5 < (u32) (arg0 + 0xD48));
    func_02057930(arg0);
    return arg0;
}
