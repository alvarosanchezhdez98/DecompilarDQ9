#include <m2c.h>

s32 func_02012430(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_02114e30;

s32 func_0202a9f4(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x40);
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (func_02012430(&data_02114e30, 0x40) != 0) {
            return 1;
        }
    case 1:
        if ((func_02012430(&data_02114e30, 0x40) != 0) && (func_02012430(&data_02114e30, 0x400) != 0)) {
            return 1;
        }
    case 2:
        if ((func_02012430(&data_02114e30, 0x40) != 0) && (func_02012430(&data_02114e30, 0x800) != 0)) {
            return 1;
        }
    default:
        return 0;
    }
}
