#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState14GetProtagonistEv();
M2C_UNK func_020397cc(s32, M2C_UNK);
M2C_UNK func_ov017_021b6bb8(s16);
M2C_UNK func_ov017_021b6c2c(s16, M2C_UNK);

void func_ov003_02166f40(void *arg0) {
    s32 temp_r0;

    func_ov017_021b6bb8(M2C_FIELD(arg0, s16 *, 0x482));
    func_ov017_021b6c2c(M2C_FIELD(arg0, s16 *, 0x482), 0);
    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN9GameState14GetProtagonistEv();
    if (temp_r0 == 0) {
        return;
    }
    func_020397cc(temp_r0, 1);
}
