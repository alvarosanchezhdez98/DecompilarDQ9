#include <m2c.h>

extern s32 data_ov017_021d847c[7];

void func_ov017_021d3eb4(s32 arg0, void *arg1) {
    *data_ov017_021d847c = M2C_FIELD(arg1, s32 *, 4);
}
