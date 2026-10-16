#include <m2c.h>

extern void *data_ov031_02250c00;

void ov13_0222A084(s8 arg0) {
    M2C_FIELD(data_ov031_02250c00, s8 *, 0x66) = arg0;
}
