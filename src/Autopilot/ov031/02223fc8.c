#include <m2c.h>

extern void *data_ov031_02250bfc;

void ov13_02228414(s8 arg0) {
    M2C_FIELD(data_ov031_02250bfc, s8 *, 0x124) = arg0;
}
