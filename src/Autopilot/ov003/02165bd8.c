#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
M2C_UNK func_ov003_02160c58(void *, M2C_UNK *, s16 *);
M2C_UNK func_ov003_02165c9c(void *);

void func_ov003_02165bd8(void *arg0) {
    s16 sp2;
    s16 sp0;
    s32 temp_r1;
    s32 temp_r2;
    s32 temp_r2_2;
    s8 temp_r0;
    s32 var_r0;

    func_ov003_02160c58(arg0, &sp2, &sp0);
    _ZN9GameState11GetInstanceEv();
    sp0 -= M2C_FIELD(func_02010828(), u8 *, 0xF7C) - 1;
    _ZN9GameState11GetInstanceEv();
    var_r0 = M2C_FIELD(func_02010828(), u8 *, 0x2C8C);
    if (sp0 != 0) {
        var_r0 += 1;
    }
    temp_r2 = var_r0 + 3;
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x45C);
    temp_r2_2 = (s32) (temp_r2 + ((u32) (temp_r2 >> 1) >> 0x1E)) >> 2;
    if (temp_r1 & 0x10) {
        M2C_FIELD(arg0, s8 *, 0x49F) = (s8) (M2C_FIELD(arg0, s8 *, 0x49F) + 1);
    } else if (temp_r1 & 0x20) {
        M2C_FIELD(arg0, s8 *, 0x49F) = (s8) (M2C_FIELD(arg0, s8 *, 0x49F) - 1);
    }
    temp_r0 = M2C_FIELD(arg0, s8 *, 0x49F);
    if (temp_r2_2 <= (s32) temp_r0) {
        M2C_FIELD(arg0, s8 *, 0x49F) = 0;
    } else if ((s32) temp_r0 < 0) {
        M2C_FIELD(arg0, s8 *, 0x49F) = (s8) (temp_r2_2 - 1);
    }
    func_ov003_02165c9c(arg0);
}
