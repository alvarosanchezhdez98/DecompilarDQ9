#include <m2c.h>

s32 func_0204c7cc();
M2C_UNK func_0205bc24(s32, M2C_UNK);
void *func_0205d888(s32);

void func_ov000_02175440(s32 arg0) {
    void *temp_r0;

    temp_r0 = func_0205d888(arg0 + 0x188);
    if (temp_r0 == NULL) {
        return;
    }
    if (func_0204c7cc() == 0) {
        return;
    }
    if (M2C_FIELD(temp_r0, u8 *, 0xC5) & 2) {
        return;
    }
    func_0205bc24(arg0 + 0x18C, -1);
}
