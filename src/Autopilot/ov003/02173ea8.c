#include <m2c.h>

M2C_UNK func_020936f8();
M2C_UNK func_02093f68();
M2C_UNK func_ov003_02173b4c(void *);
M2C_UNK func_ov003_02173bd8(void *);

void func_ov003_02173ea8(void *arg0) {
    u8 temp_r1;

    func_020936f8();
    func_02093f68();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0xEC);
    if (temp_r1 == 0) {
        return;
    }
    if ((temp_r1 == 1) && ((u32) M2C_FIELD(arg0, u8 *, 0xEE) < 2U)) {
        return;
    }
    if (temp_r1 == 6) {
        return;
    }
    func_ov003_02173b4c(arg0);
    func_ov003_02173bd8(arg0);
}
