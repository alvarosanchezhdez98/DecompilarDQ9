#include <m2c.h>

extern void *data_ov031_0224e588;

void func_ov031_022101ac(s32 arg0) {
    if (data_ov031_0224e588 != NULL) {
        M2C_FIELD(data_ov031_0224e588, s32 *, 0x30) = arg0;
    }
}
