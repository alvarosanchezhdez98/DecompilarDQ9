#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);
s32 func_02010088();
s32 func_020882f8(s32);
s32 func_ov000_02153c0c(void *);
s32 func_ov000_021543f4(void *);
s32 func_ov000_02156038(void *);
s32 func_ov000_02156050(void *);

s32 func_ov000_02155f9c(s32 arg0, M2C_UNK arg1, s32 arg2) {
    void *temp_r0;

    temp_r0 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == NULL) {
        return 1;
    }
    if ((func_02010088() != 0) || (func_ov000_02153c0c(temp_r0) != 0) || (func_ov000_02156038(temp_r0) != 0) || (func_020882f8(M2C_FIELD(temp_r0, s32 *, 0x138)) != 0) || (func_ov000_02156050(temp_r0) != 0)) {
        return 1;
    }
    if ((arg2 != 0) && (func_ov000_021543f4(temp_r0) != 0)) {
        return 1;
    }
    return 0;
}
