#include <m2c.h>

s32 func_ov031_0220fe44(M2C_UNK *);
M2C_UNK func_ov031_0220fea0();
M2C_UNK func_ov031_0220fed8();
s32 func_ov031_0220ff18(void *);
extern void *data_ov031_0224e580;
extern M2C_UNK func_ov031_0220fff8;

void func_ov031_0220fd78(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = 0x14;
    M2C_FIELD(arg1, s32 *, 4) = 0x44535359;
    M2C_FIELD(arg1, s32 *, 8) = 0xD5;
    M2C_FIELD(arg1, s32 *, 0xC) = 1;
    M2C_FIELD(arg1, s32 *, 0x10) = arg0;
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x30) = 0;
    if ((func_ov031_0220fe44(&func_ov031_0220fff8) != 0) && (func_ov031_0220ff18(arg1) != 0)) {
        func_ov031_0220fea0();
    }
    func_ov031_0220fed8();
}
