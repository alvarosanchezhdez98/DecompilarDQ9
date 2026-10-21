#include <m2c.h>

s32 func_020d472c(s32);
M2C_UNK func_0202c848();
extern M2C_UNK data_021015a0;

void func_0202db08(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        func_0202c848();
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 0xA;
        return;
    }
    if (func_020d472c(M2C_FIELD(&data_021015a0, s32 *, 0x40)) == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 1;
        return;
    }
    func_0202c848();
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 0xA;
}
