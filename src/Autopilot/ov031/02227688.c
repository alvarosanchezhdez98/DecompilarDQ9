#include <m2c.h>

M2C_UNK ov13_0223FA50(s32);
M2C_UNK ov13_02240288(s32, void *);
extern void *data_ov031_02290c40;

void ov13_0222BAB0(void *arg0) {
    ov13_0223FA50(M2C_FIELD(arg0, s32 *, 8));
    ov13_02240288(M2C_FIELD(data_ov031_02290c40, s32 *, 0x60), arg0);
}
