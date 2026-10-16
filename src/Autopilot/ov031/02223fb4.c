#include <m2c.h>

extern void *data_ov031_02250bfc;

void ov13_02228400(s8 arg0) {
    M2C_FIELD(data_ov031_02250bfc, s8 *, 0x123) = arg0;
}
