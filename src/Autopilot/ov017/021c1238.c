#include <m2c.h>

M2C_UNK _ZN13BattleRecords6FinishEv();
M2C_UNK func_ov017_021c07d0(void *);

void func_ov017_021c1238(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        _ZN13BattleRecords6FinishEv();
    }
    func_ov017_021c07d0(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
