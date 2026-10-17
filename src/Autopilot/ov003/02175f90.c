#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_02010828();
M2C_UNK func_0207c638(s32, s32);
s32 func_0207ca94(s16);

void func_ov003_02175f90(void *arg0) {
    s32 temp_r4;

    _ZN9GameState11GetInstanceEv();
    temp_r4 = func_02010828();
    func_0207c638(temp_r4 + 0x1D4, func_0207ca94((s16) (M2C_FIELD(arg0, s16 *, 0x1012) + 0xFFFFFEE2)));
}
