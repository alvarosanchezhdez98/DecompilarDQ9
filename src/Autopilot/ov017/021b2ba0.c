#include <m2c.h>

M2C_UNK func_020c9be0();
M2C_UNK strcpy(s32, M2C_UNK);
u32 strlen(M2C_UNK);

void func_ov017_021b2ba0(s32 arg0, M2C_UNK arg1) {
    if (strlen(arg1) >= 0xCU) {
        func_020c9be0();
    }
    strcpy(arg0 + 0x24, arg1);
}
