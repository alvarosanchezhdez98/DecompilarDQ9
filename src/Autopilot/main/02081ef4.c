#include <m2c.h>


void func_02081ee4(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0) = NULL;
    if (arg1 != NULL) {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg1, s16 *, 0) = 0;
        M2C_FIELD(arg1, s8 *, 2) = 0;
    }
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0x14;
    M2C_FIELD(arg0, s8 *, 7) = 0xA;
    M2C_FIELD(arg0, s8 *, 8) = (s8) M2C_FIELD(arg0, s8 *, 6);
}
