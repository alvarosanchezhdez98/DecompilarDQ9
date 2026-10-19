#include <m2c.h>

M2C_UNK ov13_02240288(s32, void *);
M2C_UNK ov13_02242034(s32);
extern void *data_ov031_02290d38;

void ov13_02240874(void *arg0) {
    ov13_02242034(M2C_FIELD(arg0, s32 *, 0x28));
    ov13_02240288(M2C_FIELD(data_ov031_02290d38, s32 *, 0x670), arg0);
}
