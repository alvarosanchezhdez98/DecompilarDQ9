#include <m2c.h>

s32 func_0205bafc(void *);
M2C_UNK func_0205bb04(void *, s32);
M2C_UNK func_0205bcdc(void *, s32);

void func_0205d7a0(void *arg0, s32 arg1) {
    void *temp_r5;
    void *var_r0;

    var_r0 = arg0;
    temp_r5 = var_r0;
    if (M2C_FIELD(temp_r5, u8 *, 0x95) != 0) {
        var_r0 = (void *) func_0205bafc(temp_r5 + 0x54);
    } else if (M2C_FIELD(temp_r5, u8 *, 0x94) != 0) {
        var_r0 = (void *) func_0205bafc(temp_r5 + 4);
    }
    if ((arg1 < 0) && ((s32) var_r0 <= arg1)) {
        return;
    }
    if (M2C_FIELD(temp_r5, u8 *, 0x95) != 0) {
        func_0205bb04(temp_r5 + 0x54, arg1);
    }
    if (M2C_FIELD(temp_r5, u8 *, 0x94) == 0) {
        return;
    }
    func_0205bcdc(temp_r5 + 4, arg1);
}
