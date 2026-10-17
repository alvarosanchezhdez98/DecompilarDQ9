#include <m2c.h>
#pragma optimize_for_size off

u32 CPSi_SocWrite2(s32, u32, s32, u32);
M2C_UNK memmove(s32, s32, s32);
extern M2C_UNK data_02111304;

u32 CPS_SocWrite(s32 arg0, u32 arg1) {
    s32 temp_r0_2;
    u32 temp_r0;
    u32 temp_r1;
    u32 temp_r4;
    void *temp_r5;

    temp_r5 = M2C_FIELD(M2C_FIELD(&data_02111304, void **, 4), void **, 0xA4);
    if (temp_r5 != NULL) {
        temp_r4 = M2C_FIELD(temp_r5, u32 *, 0x60);
        if (temp_r4 != 0) {
            temp_r0 = CPSi_SocWrite2(M2C_FIELD(temp_r5, s32 *, 0x5C), temp_r4, arg0, arg1);
            temp_r1 = M2C_FIELD(temp_r5, u32 *, 0x60);
            if (temp_r0 < temp_r1) {
                temp_r0_2 = M2C_FIELD(temp_r5, s32 *, 0x5C);
                memmove(temp_r0_2, temp_r0_2 + temp_r0, temp_r1 - temp_r0);
                M2C_FIELD(temp_r5, u32 *, 0x60) = (u32) (M2C_FIELD(temp_r5, u32 *, 0x60) - temp_r0);
                return 0U;
            }
            M2C_FIELD(temp_r5, u32 *, 0x60) = 0U;
            return temp_r0 - temp_r1;
        }
        return CPSi_SocWrite2(arg0, arg1, 0, 0U);
    }
    return 0U;
}
