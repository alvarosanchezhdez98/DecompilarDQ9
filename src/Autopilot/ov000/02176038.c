#include <m2c.h>

M2C_UNK func_02092b34(void *);

void func_ov000_02176038(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0xB3) = (u8) (M2C_FIELD(arg0, u8 *, 0xB3) | 8);
    func_02092b34(arg0 + 0x7C);
}
