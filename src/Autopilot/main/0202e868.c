#include <m2c.h>

M2C_UNK func_0202e808(void *, s32);

void func_0202e858(void *arg0, s32 arg1) {
    s32 var_r1;

    var_r1 = arg1 + M2C_FIELD(arg0, s32 *, 0x78);
    if (var_r1 < 0x1000) {
        var_r1 = 0x1000;
    }
    func_0202e808(arg0, var_r1);
}
