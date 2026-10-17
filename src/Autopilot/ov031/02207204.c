#include <m2c.h>

M2C_UNK SOCL_Bind(M2C_UNK, u16);

void SOC_Bind(M2C_UNK arg0, void *arg1) {
    u16 temp_r1;

    temp_r1 = M2C_FIELD(arg1, u16 *, 2);
    SOCL_Bind(arg0, (u16) ((u8) ((s32) temp_r1 >> 8) | ((temp_r1 << 8) & 0xFF00)));
}
