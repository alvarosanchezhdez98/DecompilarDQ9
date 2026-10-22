#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_020108f0(s32, s16);
void *func_02010954(s32);
M2C_UNK func_020c9be0();
M2C_UNK func_02053c4c(M2C_UNK, void *);

void func_02053c74(M2C_UNK arg0, s16 arg1) {
    s32 temp_r0;
    void *var_r5;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    var_r5 = func_020108f0(temp_r0, arg1);
    if (var_r5 == NULL) {
        var_r5 = func_02010954(temp_r0);
        if (var_r5 != NULL) {
            M2C_FIELD(var_r5, s16 *, 0x568) = arg1;
        } else {
            func_020c9be0();
        }
    }
    func_02053c4c(arg0, var_r5);
}
