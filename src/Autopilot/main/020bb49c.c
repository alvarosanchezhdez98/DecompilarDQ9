#include <m2c.h>

M2C_UNK func_020bb444(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_020bb514();
M2C_UNK func_020bb588();
M2C_UNK func_020bb6f8();
extern M2C_UNK (*data_020f1ee8)();
extern M2C_UNK (*data_020f1eec)();
extern s16 data_0210cf84;

void func_020bb48c(u32 arg0, s32 arg1) {
    if (arg0 <= 2U) {
        func_020bb444(4, 3, 2, 0, 1);
    } else {
        func_020bb444(4, 3, 0, 2, 1);
    }
    data_0210cf84 = (s16) arg0;
    func_020bb514();
    if (arg1 == 0) {
        return;
    }
    data_020f1ee8 = func_020bb588;
    data_020f1eec = func_020bb6f8;
}
