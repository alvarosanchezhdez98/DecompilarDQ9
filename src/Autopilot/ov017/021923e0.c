#include <m2c.h>

M2C_UNK NSBXX_Model_SetPolygonID();

void func_ov017_021923e0(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_r0 != NULL) && (M2C_FIELD(temp_r0, s32 *, 0x54) != 0)) {
        NSBXX_Model_SetPolygonID();
    }
}
