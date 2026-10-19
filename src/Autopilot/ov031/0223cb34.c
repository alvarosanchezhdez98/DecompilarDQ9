#include <m2c.h>


void ov13_02240E74(void *arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg2, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0);
    M2C_FIELD(arg2, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
    M2C_FIELD(arg2, s16 *, 4) = (s16) (M2C_FIELD(arg0, u16 *, 0) + M2C_FIELD(arg1, u16 *, 0));
    M2C_FIELD(arg2, s16 *, 6) = (s16) (M2C_FIELD(arg0, u16 *, 2) + M2C_FIELD(arg1, u16 *, 2));
}
