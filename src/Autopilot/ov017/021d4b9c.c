#include <m2c.h>


s32 func_ov017_021d4b9c(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x28) - 0xC;
    M2C_FIELD(arg0, void **, 0x28) = temp_r1;
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(temp_r1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), s32 *, 8);
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), s32 *, 0);
}
