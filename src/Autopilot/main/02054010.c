#include <m2c.h>


void *func_02054000(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x150);
    if ((temp_r1 != NULL) && ((s32) M2C_FIELD(temp_r1, s16 *, 0x496) > 0)) {
        return temp_r1 + 0x294;
    }
    return NULL;
}
