#include <m2c.h>

extern M2C_UNK data_ov031_0224e5dc;

void func_ov031_02216698(void) {
    if (M2C_FIELD(&data_ov031_0224e5dc, s32 *, 8) == 4) {
        M2C_FIELD(&data_ov031_0224e5dc, s32 *, 8) = 5;
    }
}
