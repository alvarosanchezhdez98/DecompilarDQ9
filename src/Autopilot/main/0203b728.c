#include <m2c.h>

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02105fd8;
extern M2C_UNK data_021065d8;

void func_0203b718(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    if ((arg1 != 0) && (arg1 != 1)) {

    } else {
        switch (arg2) {                             /* irregular */
        case 0:
            memset(&data_021065d8, arg3, 0x1000);
            break;
        case 1:
            memset(&data_02105fd8, arg3, 0x600);
            break;
        }
    }
    M2C_FIELD((arg0 + ((arg2 + (arg1 * 4)) * 4)), s32 *, 0x40) = 1;
}
