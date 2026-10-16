#include <m2c.h>

s32 _ZN14ItemInfoWindow6UpdateEv(void *);

void func_ov002_02156178(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x247C) & 1)) {
        return;
    }
    if (_ZN14ItemInfoWindow6UpdateEv(arg0 + 0x50) != 0) {
        M2C_FIELD(arg0, s32 *, 0x247C) = (s32) (M2C_FIELD(arg0, s32 *, 0x247C) & ~1);
    }
}
