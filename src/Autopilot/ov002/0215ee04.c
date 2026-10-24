#include <m2c.h>

M2C_UNK func_0205d304();
void * func_0205d81c();
M2C_UNK func_0205de24();
M2C_UNK memset();
M2C_UNK func_ov002_0215be00();
M2C_UNK func_ov002_0215eec0();

void func_ov002_0215ee04(void *arg0) {
    s16 var_r5;
    void *temp_r0;

    var_r5 = 0x10;
    temp_r0 = func_0205d81c(arg0 + 0xEC8, 0x10);
    if (temp_r0 != NULL) {
        var_r5 = M2C_FIELD(temp_r0, s16 *, 0xAC) + M2C_FIELD(temp_r0, s16 *, 0xA8);
    }
    func_0205de24(arg0 + 0xEC8, 0, 2);
    func_ov002_0215be00(arg0, 0x12, var_r5, 0x11);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_ov002_0215eec0(arg0, M2C_FIELD(arg0, s32 *, 0x1BD0), 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 0, 0, 0);
}
