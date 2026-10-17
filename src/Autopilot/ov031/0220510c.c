#include <m2c.h>

s32 func_020c7ea0(M2C_UNK *, s32 *, M2C_UNK);
extern M2C_UNK data_ov031_0224e204;

s32 SOCLi_AllocCommandPacket(M2C_UNK arg0) {
    s32 sp0;

    if (func_020c7ea0(&data_ov031_0224e204, &sp0, arg0) != 0) {
        return sp0;
    }
    return 0;
}
