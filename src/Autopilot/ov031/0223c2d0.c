#include <m2c.h>

M2C_UNK ov13_022425D0(M2C_UNK, M2C_UNK);

void ov13_02240610(M2C_UNK arg0, void *arg1) {
    M2C_FIELD(arg1, s16 *, 4) = (s16) (M2C_FIELD(arg1, s16 *, 4) + 1);
    if ((s32) M2C_FIELD(arg1, s16 *, 4) < (s32) M2C_FIELD(arg1, u16 *, 6)) {
        return;
    }
    M2C_FIELD(arg1, s8 *, 9) = 0;
    ov13_022425D0(1, arg0);
}
