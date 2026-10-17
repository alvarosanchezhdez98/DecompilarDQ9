#include <m2c.h>

M2C_UNK func_0202ae18();
M2C_UNK func_0202b0f4();
M2C_UNK func_0203b4b0(void *, M2C_UNK);
M2C_UNK func_0203b4e8(void *, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_0219bd1c(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov003_02170d38(void) {
    void *temp_r0;

    func_0202ae18();
    func_0202b0f4();
    M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x4494) = 0;
    temp_r0 = func_ov017_0218b5b0();
    func_0203b4e8(temp_r0, 2);
    func_0203b4b0(temp_r0, 4);
    func_ov017_0219bd1c(1, 0, 0, 0);
}
