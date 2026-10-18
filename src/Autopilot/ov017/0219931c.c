#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_ov017_021ac2ec(s32);
M2C_UNK func_ov017_021aca14(s32, s32);

void func_ov017_0219931c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x36B8) == 0) {
        return;
    }
    func_ov017_021ac2ec(M2C_FIELD(arg0, s32 *, 0x3B18));
    func_ov017_021aca14(M2C_FIELD(arg0, s32 *, 0x3B18), M2C_FIELD(arg0, s32 *, 0x36BC));
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x3B18));
}
