#include <m2c.h>

M2C_UNK func_0203b97c(s32, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32);
extern M2C_UNK data_02105fd8;
extern M2C_UNK data_021065d8;

void func_0203b8bc(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u16 arg8) {
    M2C_FIELD((arg0 + ((arg2 + (arg1 * 4)) * 4)), s32 *, 0x40) = 1;
    if (arg1 == 1) {
        switch (arg2) {                             /* irregular */
        case 0:
            func_0203b97c(arg0, &data_021065d8, 0x40, 0x20, arg3, arg4, arg5, arg6, arg7, (s32) arg8);
            return;
        case 1:
            func_0203b97c(arg0, &data_02105fd8, 0x20, 0x18, arg3, arg4, arg5, arg6, arg7, (s32) arg8);
            break;
        }
    }
}
