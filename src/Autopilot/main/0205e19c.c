#include <m2c.h>

M2C_UNK func_020d8654();
M2C_UNK func_020d8694();

void func_0205e18c(void *arg0, void *arg1) {
    func_020d8654();
    if (M2C_FIELD(arg0, void **, 0) != NULL) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x18) = arg1;
        M2C_FIELD(arg0, void **, 4) = arg1;
    } else {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, void **, 4) = arg1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x18) = 0;
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x18) = NULL;
    func_020d8694();
}
