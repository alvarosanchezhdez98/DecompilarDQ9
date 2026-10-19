#include <m2c.h>

M2C_UNK func_ov001_02164578(s32, s32, void *, s32, f32);
s32 func_ov001_02164624(s32, s32);
extern s32 data_ov001_02165884[0xD];

s32 func_ov001_02159a74(void *arg0, void *arg1) {
    s32 *temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x18) == 0) {
        if (func_ov001_02164624(*data_ov001_02165884, M2C_FIELD(arg1, s32 *, 0x70)) != 0) {
            func_ov001_02164578(*data_ov001_02165884, M2C_FIELD(arg1, s32 *, 0x70), arg0 + 0x1C, M2C_FIELD(arg0, s32 *, 0x10), (f32) M2C_FIELD(arg0, s32 *, 0x14));
            temp_r0 = M2C_FIELD(arg0, s32 **, 0x3C);
            if ((temp_r0 != NULL) && (*temp_r0 == 0xD)) {
                return 0;
            }
            M2C_FIELD(arg0, s32 *, 0x18) = 1;
            return 1;
        }
        return 1;
    }
    return 0;
}
