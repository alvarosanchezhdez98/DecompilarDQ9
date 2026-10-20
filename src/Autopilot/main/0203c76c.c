#include <m2c.h>

M2C_UNK func_0200ef44(s32, M2C_UNK, M2C_UNK, M2C_UNK *);
M2C_UNK func_0203c304(s32);
extern M2C_UNK func_0203be78;

s32 func_0203c75c(s32 arg0) {
    func_0203c304(arg0 + 0x10);
    func_0203c304(arg0 + 0x10);
    func_0200ef44(arg0 + 0x14, 0x20, 0x28, &func_0203be78);
    return arg0;
}
