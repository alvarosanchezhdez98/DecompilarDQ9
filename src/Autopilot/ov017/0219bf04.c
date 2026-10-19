#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_0200fd0c(s32);
s32 func_020936f8();
M2C_UNK func_02094030(s32, s32, M2C_UNK, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_0219bcac(M2C_UNK);

void func_ov017_0219bf04(M2C_UNK arg0, s32 arg1) {
    s32 temp_r5;
    void *temp_r0;
    void *temp_r4;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_ov017_0218b5b0();
    func_ov017_0219bcac(arg0);
    temp_r0 = func_0200fd0c(temp_r5);
    M2C_FIELD(temp_r0, s8 *, 0x6E) = 1;
    M2C_FIELD(temp_r0, s8 *, 0xA) = 0;
    M2C_FIELD(temp_r0, s8 *, 0x67) = 1;
    if (arg1 == 0) {
        M2C_FIELD(temp_r4, s16 *, 0x44B2) = 0x4E23;
        return;
    }
    func_02094030(func_020936f8(), 0x4E23, -1, 0);
}
