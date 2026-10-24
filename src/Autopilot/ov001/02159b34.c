#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_ov001_021646b8(s32, s32);
extern s32 data_ov001_02165884[0xD];

s32 func_ov001_02159b34(s32 arg0, void *arg1) {
    func_ov001_021646b8(*data_ov001_02165884, M2C_FIELD(arg1, s32 *, 0x70));
    return 0;
}
