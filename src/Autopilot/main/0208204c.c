#include <m2c.h>


void func_0208203c(void *arg0) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0);
    if (temp_r2 != NULL) {
        M2C_FIELD(temp_r2, s16 *, 0) = 0;
        M2C_FIELD(temp_r2, s8 *, 2) = 0;
    }
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 8) = (s8) M2C_FIELD(arg0, s8 *, 6);
}
