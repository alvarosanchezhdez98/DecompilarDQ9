#include <m2c.h>

M2C_UNK __construct_array(s32, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *);
M2C_UNK func_0203c304(s32);
extern M2C_UNK func_0203be64;
extern M2C_UNK func_0203be78;

s32 func_0203c2c0(s32 arg0) {
    __construct_array(arg0 + 4, 0x20, 0x28, &func_0203be64, &func_0203be78);
    func_0203c304(arg0);
    return arg0;
}
