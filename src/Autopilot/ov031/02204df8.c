#include <m2c.h>

s32 SOCL_CreateSocket(M2C_UNK *);
s32 SOCLi_StartupCommandPacketQueue(s32);
extern void *data_ov031_022496a4;
extern M2C_UNK data_ov031_022496dc;
extern M2C_UNK data_ov031_0224e1c0;

s32 SOCLi_StartupSOCL(void) {
    s32 temp_r0;

    temp_r0 = SOCLi_StartupCommandPacketQueue(M2C_FIELD(data_ov031_022496a4, s32 *, 0x20));
    if (temp_r0 >= 0) {
        M2C_FIELD(&data_ov031_0224e1c0, s32 *, 0xC) = SOCL_CreateSocket(&data_ov031_022496dc);
    }
    return temp_r0;
}
