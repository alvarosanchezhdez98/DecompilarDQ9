#include <m2c.h>

M2C_UNK func_0205e9f4(M2C_UNK *, u8);
s32 func_0205ea18(M2C_UNK *);
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_0209ca70(M2C_UNK *, u8);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;

void func_ov002_0215b268(void *arg0) {
    s32 temp_r4;

    temp_r4 = func_0205ea18(&data_02108760);
    func_0209ca70(&data_02109bf4, M2C_FIELD(arg0, u8 *, 0x1C2C));
    func_0205e9f4(&data_02108760, M2C_FIELD(arg0, u8 *, 0x1C2D));
    if (temp_r4 == M2C_FIELD(arg0, u8 *, 0x1C2D)) {
        return;
    }
    func_0205eaa0(&data_02108760, 1, 0);
}
