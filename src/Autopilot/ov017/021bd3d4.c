#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(s32, void *);
s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, s32);

void func_ov017_021bd3d4(void *arg0, s32 arg1) {
    u8 temp_r0;
    void *temp_r0_2;

    temp_r0 = 1 << arg1;
    M2C_FIELD(arg0, u8 *, 0x174) = (u8) (M2C_FIELD(arg0, u8 *, 0x174) | temp_r0);
    M2C_FIELD(arg0, u8 *, 0x175) = (u8) (M2C_FIELD(arg0, u8 *, 0x175) & ~temp_r0);
    temp_r0_2 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0_2 == NULL) {
        return;
    }
    _ZN8Vector3iaSERKS_((arg1 * 0xC) + (s32) (arg0 + 0x188), temp_r0_2 + 0x44);
    M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x1B8) = (s32) M2C_FIELD(temp_r0_2, s32 *, 0x54);
}
