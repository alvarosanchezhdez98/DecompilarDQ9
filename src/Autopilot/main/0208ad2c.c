#include <m2c.h>

M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
s32 func_020704fc();
M2C_UNK func_02070950(s32, s32, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK data_02108760;

void func_0208ad1c(s32 arg0) {
    s32 temp_r0;

    temp_r0 = func_020704fc();
    if (temp_r0 != 0) {
        func_02070950(temp_r0, arg0 + 0xC, 0x14, 5, 0xF);
        func_0205eaa0(&data_02108760, 0x78, 0);
    }
}
