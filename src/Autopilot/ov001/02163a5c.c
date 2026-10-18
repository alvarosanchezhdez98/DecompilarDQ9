#include <m2c.h>

M2C_UNK func_0205e92c(M2C_UNK *);
M2C_UNK func_0205ea20(M2C_UNK *, M2C_UNK);
M2C_UNK func_0209c278(M2C_UNK *);
M2C_UNK func_0209c290(M2C_UNK *);
M2C_UNK func_0209c2b8(M2C_UNK *);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;

s32 func_ov001_02163a5c(void) {
    if (func_ov017_021d60f4() != 0) {
        func_0205e92c(&data_02108760);
        func_0209c278(&data_02109bf4);
        func_0209c2b8(&data_02109bf4);
    } else {
        func_0209c278(&data_02109bf4);
        func_0209c290(&data_02109bf4);
        func_0205ea20(&data_02108760, 0x64);
    }
    return 1;
}
