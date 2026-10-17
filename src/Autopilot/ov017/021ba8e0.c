#include <m2c.h>

M2C_UNK func_020421a0();
M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_ov017_021ba90c(s32);

void func_ov017_021ba8e0(void *arg0) {
    func_020421a0();
    func_ov017_021ba90c(M2C_FIELD(arg0, s32 *, 0x372C));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x372C));
}
