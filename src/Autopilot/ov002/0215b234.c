#include <m2c.h>

s8 func_0205ea18(M2C_UNK *);
s8 func_0209ca98(M2C_UNK *);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;

void func_ov002_0215b234(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x1C2C) = func_0209ca98(&data_02109bf4);
    M2C_FIELD(arg0, s8 *, 0x1C2D) = func_0205ea18(&data_02108760);
}
