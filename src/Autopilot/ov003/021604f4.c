#include <m2c.h>

M2C_UNK func_0205ac40(void *, void *);

void func_ov003_021604f4(void *arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4) {
    void *temp_ip;

    temp_ip = M2C_FIELD(arg0, s32 *, 0x388) + (arg3 * 0x28);
    M2C_FIELD(temp_ip, s32 *, 0x14) = (s32) (arg1 << 0xC);
    M2C_FIELD(temp_ip, s32 *, 0x18) = (s32) (arg2 << 0xC);
    M2C_FIELD(temp_ip, u8 *, 0x22) = arg4;
    func_0205ac40(arg0 + 0x334, temp_ip);
}
