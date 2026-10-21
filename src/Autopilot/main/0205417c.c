#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
u32 _ZNK9GameState21GetEffectiveDeltaTimeEv();
M2C_UNK func_02054028(void *, M2C_UNK);

void func_0205416c(void *arg0) {
    u16 temp_r2;
    u32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZNK9GameState21GetEffectiveDeltaTimeEv();
    temp_r2 = M2C_FIELD(arg0, u16 *, 0x1C0);
    if ((u32) temp_r2 >= temp_r0) {
        M2C_FIELD(arg0, u16 *, 0x1C0) = (u16) (temp_r2 - temp_r0);
        return;
    }
    func_02054028(arg0, 0);
}
