#include <m2c.h>
#pragma optimization_level 4

void *SOCLi_AllocCommandPacket(s8);

void SOCLi_CreateCommandPacket(s32 arg0, void *arg1, s8 arg2) {
    void *temp_r0;

    temp_r0 = SOCLi_AllocCommandPacket(arg2);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = arg0;
    M2C_FIELD(temp_r0, void **, 4) = arg1;
    M2C_FIELD(temp_r0, s32 *, 8) = 0;
    M2C_FIELD(temp_r0, s8 *, 0xC) = (s8) M2C_FIELD(arg1, s8 *, 0x73);
    M2C_FIELD(temp_r0, s8 *, 0xD) = arg2;
}
