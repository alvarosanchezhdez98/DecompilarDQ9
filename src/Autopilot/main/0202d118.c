#include <m2c.h>

M2C_UNK func_0202c848();
s32 func_0202d180();
s32 func_0202d224();
extern M2C_UNK data_021015a0;

void func_0202d108(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        func_0202c848();
        return;
    }
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 1;
    if (M2C_FIELD(&data_021015a0, u16 *, 4) == 0) {
        return;
    }
    M2C_FIELD(&data_021015a0, u16 *, 4) = 0U;
    if (M2C_FIELD(&data_021015a0, s32 *, 0x30) != 0) {
        if (func_0202d180() == 0) {
            M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
        }
        return;
    }
    if (func_0202d224() == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
    }
}
