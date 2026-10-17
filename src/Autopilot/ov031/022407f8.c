#include <m2c.h>

M2C_UNK func_ov031_02241480(void *, M2C_UNK, s32, s32, s32);

void ov38_02222520(void *arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    void *temp_ip;

    temp_ip = M2C_FIELD(arg0, void **, 0x30);
    func_ov031_02241480(arg0, arg1, M2C_FIELD(temp_ip, s32 *, 0x18) + arg2, M2C_FIELD(temp_ip, s32 *, 0xC) - arg2, arg3);
}
