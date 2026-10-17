#include <m2c.h>


void func_ov017_02195748(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x441C);
    M2C_FIELD(temp_r1, s8 *, 0) = 0;
    M2C_FIELD(temp_r1, s8 *, 1) = 0;
}
