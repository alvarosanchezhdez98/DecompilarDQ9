#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
M2C_UNK func_ov031_0221038c(M2C_UNK);
M2C_UNK func_ov031_022103dc(M2C_UNK);
s32 func_ov031_02211848();
extern void *data_ov031_0224e588;

void func_ov031_02210720(void) {
    s32 temp_r0;

    if (func_ov031_02211848() != 0) {
        func_ov031_0221038c(2);
    }
    temp_r0 = M2C_FIELD(data_ov031_0224e588, s32 *, 4);
    switch (temp_r0) {                              /* irregular */
    case 1:
        func_ov031_022103dc(2);
        return;
    case 2:
        func_ov031_022103dc(0);
        return;
    default:
        _Z19SleepCurrentContextj(0x64);
        return;
    }
}
