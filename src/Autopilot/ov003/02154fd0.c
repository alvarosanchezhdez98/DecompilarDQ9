#include <m2c.h>

M2C_UNK func_0207fd88();
M2C_UNK func_020e2834();
void _ZN11GuideWindow5Draw2Ev(void *);

void func_ov003_02154fd0(void *arg0) {
    void *temp_r0;

    if (M2C_FIELD(arg0, u8 *, 0x1F8) == 0) {
        return;
    }
    temp_r0 = M2C_FIELD(arg0, void **, 0x204);
    if (temp_r0 != NULL) {
        _ZN11GuideWindow5Draw2Ev(temp_r0);
    } else if (M2C_FIELD(arg0, s32 *, 0x18) != 0) {
        func_0207fd88();
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) == 0) {
        return;
    }
    func_020e2834();
}
