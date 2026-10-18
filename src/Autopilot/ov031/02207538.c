#include <m2c.h>

M2C_UNK SOCL_SetResolver(s32, s32);

void SOC_SetResolver(u32 *arg0, u32 *arg1) {
    u32 temp_ip;
    u32 temp_r0;

    temp_ip = *arg1;
    temp_r0 = *arg0;
    SOCL_SetResolver(((temp_r0 << 0x18) & 0xFF000000) | (((temp_r0 << 8) & 0xFF0000) | ((u8) (temp_r0 >> 0x18) | ((temp_r0 >> 8) & 0xFF00))), ((temp_ip << 0x18) & 0xFF000000) | (((temp_ip << 8) & 0xFF0000) | ((u8) (temp_ip >> 0x18) | ((temp_ip >> 8) & 0xFF00))));
}
