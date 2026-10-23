#include <m2c.h>

void *_ZN17ActiveGrottoClass15GetDetailedDataEv(s32);
s32 func_02012fe4();
M2C_UNK func_ov017_021d6134(M2C_UNK, u8);

s32 func_0209dbfc(M2C_UNK arg0) {
    s32 temp_r0;
    void *temp_r0_2;

    temp_r0 = func_02012fe4() + 0x23EC;
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r0_2 = _ZN17ActiveGrottoClass15GetDetailedDataEv(temp_r0);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (M2C_FIELD(temp_r0_2, u8 *, 1) != 1) {
        return 0;
    }
    func_ov017_021d6134(arg0, M2C_FIELD(temp_r0_2, u8 *, 0x64));
    return 1;
}
