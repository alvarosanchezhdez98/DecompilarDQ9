#include <m2c.h>

void *_ZN15LightingManager11GetInstanceEv();
M2C_UNK func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_021603b0(M2C_UNK arg0) {
    void *temp_r4;

    temp_r4 = _ZN15LightingManager11GetInstanceEv();
    func_ov017_021d60f4(arg0);
    M2C_FIELD(temp_r4, s32 *, 0x90) = 0;
    return 1;
}
