#include <m2c.h>

u16 *func_02012fe4();
s32 func_0201b5d8(u16);
M2C_UNK func_02033b58(void *, M2C_UNK);
M2C_UNK func_02076ccc(void *, M2C_UNK);

void func_02076d5c(void *arg0) {
    if ((func_0201b5d8(*func_02012fe4()) == 0) && ((u32) M2C_FIELD(arg0, u32 *, 0x14C) <= 0x3E8U)) {
        return;
    }
    func_02033b58(arg0, 0);
    func_02076ccc(arg0, 1);
}
