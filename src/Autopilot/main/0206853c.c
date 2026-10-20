#include <m2c.h>

void *func_02010828();
s32 func_02011538(M2C_UNK);

s32 func_0206852c(M2C_UNK arg0) {
    void *temp_r4;

    temp_r4 = func_02010828();
    if (M2C_FIELD(temp_r4, u8 *, 0xF7C) != func_02011538(arg0)) {
        return 1;
    }
    return 0;
}
