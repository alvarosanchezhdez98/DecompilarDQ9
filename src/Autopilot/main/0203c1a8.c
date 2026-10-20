#include <m2c.h>

M2C_UNK func_0203c54c(s32, s32);
extern s32 data_02105244;

void func_0203c198(void *arg0) {
    if (data_02105244 == 0) {
        return;
    }
    func_0203c54c(data_02105244, arg0 + 0x14);
    M2C_FIELD(arg0, s16 *, 0x14) = -1;
}
