#include <m2c.h>

s32 func_02012f24(u16);
s32 func_02012f68();
M2C_UNK func_0202ae18();
s32 func_0202c540();
s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);
s32 func_0201b588();

void func_0201ba68(void *arg0) {
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r4;
    u16 temp_r0;

    func_0202ae18();
    if ((func_0202c540() == 0) && (M2C_FIELD(arg0, u8 *, 0x2820) == 0)) {
        temp_r4 = func_0205ec34();
        temp_r0 = M2C_FIELD(arg0, u16 *, 0);
        if (((u32) temp_r0 >= 0x4E20U) && ((u32) temp_r0 <= 0x752FU)) {
            temp_r0_2 = func_02012f68();
            if (temp_r0_2 < 0) {
                return;
            }
            func_0206df6c(temp_r4, temp_r4 + 0x8C, temp_r0_2 + 0xA5A, 1);
            return;
        }
        if (((u32) temp_r0 >= 0x64U) && ((u32) temp_r0 <= 0x270FU)) {
            temp_r0_3 = (s32) temp_r0 / 100;
            if (temp_r0_3 >= 0x64) {
                return;
            }
            func_0206df6c(temp_r4, temp_r4 + 0x8C, temp_r0_3 + 0xA96, 1);
            return;
        }
        if (func_0201b588() != 0) {
            func_0206df6c(temp_r4, temp_r4 + 0x8C, 0x79D, 1);
            return;
        }
        temp_r0_4 = func_02012f24(M2C_FIELD(arg0, u16 *, 0));
        if (temp_r0_4 < 0) {
            return;
        }
        func_0206df6c(temp_r4, temp_r4 + 0x8C, temp_r0_4 + 0xA5A, 1);
    }
}
