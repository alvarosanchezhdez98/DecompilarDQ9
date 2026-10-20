#include <m2c.h>

M2C_UNK func_02012a84(M2C_UNK, s32 *, s32 *);

s32 func_02012b54(M2C_UNK arg0) {
    s32 sp4;
    s32 sp0;

    func_02012a84(arg0, &sp4, &sp0);
    if (sp4 < 2) {
        return 1;
    }
    if (sp4 > 0xFD) {
        return 1;
    }
    if (sp0 < 2) {
        return 1;
    }
    if (sp0 > 0xBD) {
        return 1;
    }
    return 0;
}
