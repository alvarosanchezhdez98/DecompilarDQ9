#include <m2c.h>

M2C_UNK func_0203c304(void *);
extern void *data_02105244;
extern M2C_UNK data_021056b4;

void func_0203bd24(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 1;
    M2C_FIELD(arg0, s8 *, 0xD) = 1;
    M2C_FIELD(arg0, s32 *, 0) = 0x1000;
    M2C_FIELD(arg0, s32 *, 4) = 0xE0;
    func_0203c304(arg0 + 0x10);
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = &data_021056b4;
    data_02105244 = arg0 + 0x10;
}
