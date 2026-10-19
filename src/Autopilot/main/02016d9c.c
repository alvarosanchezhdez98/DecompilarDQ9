#include <m2c.h>

M2C_UNK func_020ca528(M2C_UNK, M2C_UNK *);
extern M2C_UNK data_0210a010;
extern M2C_UNK data_0210a0cc;

void func_02016d8c(M2C_UNK arg0) {
    func_020ca528(arg0, &data_0210a0cc);
    M2C_FIELD(&data_0210a010, s32 *, 0xFC) = (s32) (M2C_FIELD(&data_0210a010, s32 *, 0xFC) & ~0xA4);
}
