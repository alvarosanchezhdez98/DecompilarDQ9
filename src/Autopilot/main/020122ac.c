#include <m2c.h>

s32 abs();
s32 func_0205ec34();
M2C_UNK func_0206df6c();
s32 func_020c39c8();
u16 func_02012354();

void func_0201229c(void *arg0) {
    s32 temp_r0;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r4;

    var_r4 = 0;
    if ((M2C_FIELD(arg0, u8 *, 0x1C) == 0) || (((s32) (*(u16 *)0x027FFFA8 & 0x8000) >> 0xF) != 0) || (temp_r7 = func_020c39c8(0x0400106C), func_020c39c8(0x0400006C), temp_r6 = abs(), ((s32) (temp_r6 + abs(temp_r7)) >= 0x20))) {
        var_r4 = 1;
    }
    if (var_r4 != 0) {
        M2C_FIELD(arg0, u16 *, 2) = 0U;
        M2C_FIELD(arg0, u16 *, 0) = 0U;
        return;
    }
    M2C_FIELD(arg0, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0);
    M2C_FIELD(arg0, u16 *, 0) = func_02012354();
    if (M2C_FIELD(arg0, u16 *, 0) == 0) {
        return;
    }
    temp_r0 = func_0205ec34();
    func_0206df6c(temp_r0, temp_r0 + 0x8C, 0x113E, 1);
}
