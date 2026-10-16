#include <m2c.h>

M2C_UNK func_0202ae18();
s32 func_0202b7d8();
M2C_UNK func_020d84e4();
M2C_UNK func_020d84e8();
M2C_UNK func_020d8654();
M2C_UNK func_020d8694();
M2C_UNK func_0205e18c(s32, void *);
void *func_0205e1e4(s32);

void *func_0205e41c(s32 arg0, s32 *arg1) {
    void *var_r4;

    func_020d8654();
    func_020d84e4();
    var_r4 = NULL;
    func_0202ae18();
    if (func_0202b7d8() != 0) {
        var_r4 = func_0205e1e4(arg0 + 0x1518);
        if (var_r4 == NULL) {
            *arg1 = -1;
            var_r4 = NULL;
        } else {
            func_0205e18c(arg0 + 0x1500, var_r4);
            *arg1 = (s32) M2C_FIELD(var_r4, s16 *, 0x14);
        }
    }
    func_020d84e8();
    func_020d8694();
    return var_r4;
}
