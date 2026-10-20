#include <m2c.h>

M2C_UNK memcpy(void *, M2C_UNK, s32);

void func_ov017_021a99dc(void *arg0, M2C_UNK arg1, s32 arg2, s32 arg3, u8 arg4) {
    void *temp_ip;
    void *temp_r1;
    void *temp_r1_2;

    temp_ip = M2C_FIELD(arg0, void **, 0x20);
    if (temp_ip == NULL) {
        return;
    }
    if (arg2 == 0) {
        memcpy(temp_ip + 0xE04 + M2C_FIELD(arg0, u8 *, 0x25), arg1, arg3);
        M2C_FIELD(arg0, u8 *, 0x25) = (u8) (M2C_FIELD(arg0, u8 *, 0x25) + arg3);
    } else if (arg2 == 2) {
        memcpy(temp_ip + 0xDF0, arg1, arg3);
        temp_r1 = M2C_FIELD(arg0, void **, 0x20);
        M2C_FIELD(temp_r1, u8 *, 0xE98) = (u8) (M2C_FIELD(temp_r1, u8 *, 0xE98) | 4);
    } else {
        M2C_FIELD(temp_ip, u8 *, 0xE98) = (u8) (M2C_FIELD(temp_ip, u8 *, 0xE98) | 1);
        memcpy(M2C_FIELD(arg0, void **, 0x20) + 0xE1C + M2C_FIELD(arg0, u8 *, 0x26), arg1, arg3);
        M2C_FIELD(arg0, u8 *, 0x26) = (u8) (M2C_FIELD(arg0, u8 *, 0x26) + arg3);
    }
    if (arg4 != 0) {
        temp_r1_2 = M2C_FIELD(arg0, void **, 0x20);
        M2C_FIELD(temp_r1_2, u8 *, 0xE98) = (u8) (M2C_FIELD(temp_r1_2, u8 *, 0xE98) | 2);
    }
}
