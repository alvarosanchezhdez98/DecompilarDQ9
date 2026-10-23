#include <m2c.h>


u16 func_0202053c(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x150);
    return M2C_FIELD((temp_r1 + (M2C_FIELD(temp_r1, s32 *, 0x950) * 2)), u16 *, 0x16C);
}
