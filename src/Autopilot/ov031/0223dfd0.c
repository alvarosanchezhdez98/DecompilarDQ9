#include <m2c.h>

M2C_UNK func_020cedfc(M2C_UNK);
s32 func_020cee18(s32 *);

void ov13_022422E0(void) {
    s32 sp0;

    if (func_020cee18(&sp0) != 0) {
        return;
    }
    if (sp0 == 0xF) {
        return;
    }
    func_020cedfc(0xF);
}
