#include <m2c.h>

s32 func_ov031_022102c8();
M2C_UNK func_ov031_02210314(M2C_UNK *);
extern void *data_ov031_0224e580;
extern M2C_UNK func_ov031_0220fdec;

s32 func_ov031_0220fe44(s32 arg0) {
    if (data_ov031_0224e580 == NULL) {
        return 0;
    }
    if (func_ov031_022102c8() == 0) {
        return 0;
    }
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x2C) = 0;
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x28) = arg0;
    func_ov031_02210314(&func_ov031_0220fdec);
    return 1;
}
