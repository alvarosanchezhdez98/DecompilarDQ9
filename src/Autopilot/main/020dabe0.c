#include <m2c.h>

s32 func_02057924();
M2C_UNK func_02057f00(s32, M2C_UNK);

s32 func_020dabd0(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;
    u8 temp_r1;

    temp_r0 = func_02057924();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0xE);
    temp_r4 = temp_r0;
    switch (temp_r1) {                              /* irregular */
    case 1:
        func_02057f00(temp_r0, 0x14);
        func_02057f00(temp_r4, 0x15);
        break;
    case 2:
        func_02057f00(temp_r0, 0x14);
        func_02057f00(temp_r4, 0x15);
        break;
    case 3:
        func_02057f00(temp_r0, 0x16);
        break;
    }
    return 1;
}
