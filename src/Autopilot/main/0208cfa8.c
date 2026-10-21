#include <m2c.h>


void func_0208cf98(void *arg0) {
    u16 temp_r1;

    temp_r1 = M2C_FIELD(arg0, u16 *, 0xDA);
    if (temp_r1 & 1) {
        M2C_FIELD(arg0, s8 *, 0xD4) = 2;
        M2C_FIELD(arg0, s8 *, 0xD5) = 0;
        return;
    }
    if (temp_r1 & 2) {
        M2C_FIELD(arg0, s8 *, 0xD4) = 3;
        M2C_FIELD(arg0, s8 *, 0xD5) = 0;
    }
}
