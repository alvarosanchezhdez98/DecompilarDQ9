#include <m2c.h>

M2C_UNK func_020e54bc(s32, M2C_UNK *, s32, M2C_UNK, s32, M2C_UNK *);
extern M2C_UNK data_020f296c;
extern M2C_UNK data_020f297e;

void func_020dcf7c(s32 arg0, s32 arg1) {
    if ((arg0 > 0) && (arg1 != 0)) {
        func_020e54bc(arg1, &data_020f296c, arg0, 0, 1, &data_020f297e);
    }
}
