#include <m2c.h>

M2C_UNK func_0202c848();
extern M2C_UNK data_021015a0;

void func_0202cd28(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 1;
        return;
    }
    func_0202c848();
}
