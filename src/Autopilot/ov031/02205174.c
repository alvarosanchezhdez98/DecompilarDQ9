#include <m2c.h>

M2C_UNK func_020c7e0c(M2C_UNK *, s32, M2C_UNK);
extern M2C_UNK data_ov031_0224e204;

void SOCLi_FreeCommandPacket(s32 arg0) {
    if (arg0 == 0) {
        return;
    }
    func_020c7e0c(&data_ov031_0224e204, arg0, 0);
}
