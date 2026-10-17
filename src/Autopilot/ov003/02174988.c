#include <m2c.h>

s32 _ZN14ItemInfoWindow6UpdateEv(void *);

void func_ov003_02174988(void *arg0) {
    if (!(M2C_FIELD(arg0, u16 *, 0x1046) & 0x80)) {
        return;
    }
    if (_ZN14ItemInfoWindow6UpdateEv(arg0 + 0x3C) != 0) {
        M2C_FIELD(arg0, u16 *, 0x1046) = (u16) (M2C_FIELD(arg0, u16 *, 0x1046) & ~0x80);
    }
}
