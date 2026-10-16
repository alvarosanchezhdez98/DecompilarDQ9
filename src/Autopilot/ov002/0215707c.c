#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, s8);
s32 func_02010828();
s32 func_02053c6c();

s16 GetInventoryItemByID(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;

    if (arg1 < 0) {
        return -1;
    }
    if (arg2 < 0) {
        return -1;
    }
    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (arg2 == 5) {
        return M2C_FIELD((func_02010828() + 0xE04 + (arg1 * 2)), s16 *, 0xC);
    }
    if (arg2 == 4) {
        return M2C_FIELD((func_02010828() + (arg1 * 2)), s16 *, 0xC);
    }
    if (func_0200ff1c(temp_r0, M2C_FIELD(arg0, s8 *, 0x1C20)) == 0) {
        return -1;
    }
    return M2C_FIELD((func_02053c6c() + (arg1 * 2)), s16 *, 0x454);
}
