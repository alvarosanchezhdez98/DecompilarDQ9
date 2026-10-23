#include <m2c.h>

M2C_UNK func_0208becc(s32, s32, M2C_UNK);
s32 func_ov004_02165e70(M2C_UNK, M2C_UNK);

s32 func_ov004_02167648(M2C_UNK arg0) {
    s32 temp_r0;

    temp_r0 = func_ov004_02165e70(arg0, 7);
    if (temp_r0 != 0) {
        func_0208becc(temp_r0 + 0x34, 0x270F, 0);
    }
    return 0;
}
