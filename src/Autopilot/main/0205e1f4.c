#include <m2c.h>

M2C_UNK func_020d8654();
M2C_UNK func_020d8694();

void *func_0205e1e4(void *arg0) {
    void *temp_r4;

    func_020d8654();
    temp_r4 = M2C_FIELD(arg0, void **, 0);
    if (temp_r4 != NULL) {
        M2C_FIELD(arg0, void **, 0) = (void *) M2C_FIELD(temp_r4, void **, 0x18);
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) - 1);
    }
    func_020d8694();
    return temp_r4;
}
