#include <m2c.h>

M2C_UNK func_ov017_021d4ccc(M2C_UNK *);
M2C_UNK func_ov001_0215a954();
M2C_UNK func_ov001_0215a9b4();
extern M2C_UNK data_ov001_02165828;

s32 func_ov001_02153994(void) {
    func_ov017_021d4ccc(&data_ov001_02165828);
    if (M2C_FIELD(&data_ov001_02165828, s32 *, 0x3C) == 0) {
        func_ov001_0215a9b4();
    }
    if (M2C_FIELD(&data_ov001_02165828, s32 *, 0x3C) == 0) {
        return 0;
    }
    func_ov001_0215a954();
    return 1;
}
