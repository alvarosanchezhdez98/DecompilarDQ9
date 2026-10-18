#include <m2c.h>

M2C_UNK ov13_02240B04(M2C_UNK);
extern u8 data_ov031_02250bac;

s32 ov13_0222788C(void) {
    if (data_ov031_02250bac == 0) {
        return 0;
    }
    ov13_02240B04(1);
    data_ov031_02250bac = 0;
    return 1;
}
