#include <m2c.h>

M2C_UNK _Z19SetMenuObject7PagesP10MenuScripttss(M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern void *data_ov004_0217101c;

void func_ov004_02165ef4(M2C_UNK arg0) {
    s32 temp_ip;

    temp_ip = M2C_FIELD(data_ov004_0217101c, s16 *, 0x4C) + 7;
    _Z19SetMenuObject7PagesP10MenuScripttss(arg0, 0x5B, 0, (s32) ((temp_ip + ((u32) (temp_ip >> 2) >> 0x1D)) << 0xD) >> 0x10);
}
