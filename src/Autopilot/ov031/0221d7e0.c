#include <m2c.h>

M2C_UNK func_ov031_0221e354(void *, s32, M2C_UNK *, s32);
s32 func_ov031_0221e4fc(void *, void *, s32);
s32 func_ov031_0221e638(u16);
s32 func_ov031_0221e650(M2C_UNK *);
extern M2C_UNK data_ov031_0224b0dc;

#pragma thumb on
s32 func_ov031_0221d7e0(void *arg0, void *arg1) {
    s32 temp_r6;
    s32 var_r4;

    var_r4 = 0;
    func_ov031_0221e354(arg1, 8, &data_ov031_0224b0dc, func_ov031_0221e650(&data_ov031_0224b0dc));
    if (func_ov031_0221e4fc(arg0, arg1, 6) != 0) {
        var_r4 = -1;
    } else {
        temp_r6 = func_ov031_0221e638(M2C_FIELD(arg0, u16 *, 6));
        if ((temp_r6 + 1) != func_ov031_0221e638(M2C_FIELD(arg1, u16 *, 6))) {
            var_r4 = -2;
        }
    }
    return var_r4;
}
#pragma thumb off
