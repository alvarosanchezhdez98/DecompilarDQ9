#include <m2c.h>

void *_ZN9GameState21GetPartyMemberByIndexEi(void *, s8);
void *func_02053c6c();
M2C_UNK func_ov017_0218f5a4(M2C_UNK, s8, M2C_UNK, M2C_UNK, s32);

void func_ov017_021d0e64(s32 arg0, void *arg1, void *arg2, M2C_UNK arg3) {
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(arg2, M2C_FIELD(arg1, s8 *, 4));
    if (temp_r0 != NULL) {
        temp_r0_2 = func_02053c6c();
        if (temp_r0_2 != NULL) {
            if ((M2C_FIELD(temp_r0_2, u8 *, 0x56A) != M2C_FIELD(arg1, u8 *, 5)) && ((s32) M2C_FIELD(temp_r0_2, s16 *, 0x488) < 0)) {
                M2C_FIELD(temp_r0, s16 *, 2) = -1;
                func_ov017_0218f5a4(arg3, M2C_FIELD(arg1, s8 *, 4), 0, 0, 0);
            }
            M2C_FIELD(temp_r0_2, u8 *, 0x56A) = (u8) M2C_FIELD(arg1, u8 *, 5);
            M2C_FIELD(arg2, s32 *, 0x5CCC) = (s32) (M2C_FIELD(arg2, s32 *, 0x5CCC) | 2);
        }
    }
}
