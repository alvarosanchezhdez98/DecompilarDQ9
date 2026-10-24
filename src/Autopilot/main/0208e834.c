#include <m2c.h>

s32 memcmp(s8 *, M2C_UNK *, M2C_UNK);
u32 strlen(s8 *);
extern M2C_UNK data_020f12b8;

s32 func_0208e824(s32 arg0, s8 *arg1) {
    if ((*arg1 == 0x46) && (strlen(arg1) <= 3U)) {
        return 1;
    }
    if (memcmp(arg1, &data_020f12b8, 6) == 0) {
        return 1;
    }
    return 0;
}
