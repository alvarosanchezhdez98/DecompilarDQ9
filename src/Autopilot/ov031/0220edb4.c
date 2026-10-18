#include <m2c.h>

void *func_ov031_0220d60c();

s32 WcmGetOldestApList(void) {
    void *temp_r0;
    void *temp_r1;

    temp_r0 = func_ov031_0220d60c();
    temp_r1 = M2C_FIELD(temp_r0, void **, 0x2270);
    if ((temp_r1 != NULL) && ((u32) M2C_FIELD(temp_r0, u32 *, 0x2274) > 0xCU)) {
        return M2C_FIELD(temp_r1, s32 *, 4);
    }
    return 0;
}
