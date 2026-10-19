#include <m2c.h>

M2C_UNK func_ov001_02158828(void *);

s32 func_ov001_02158e8c(void *arg0, void *arg1, s32 arg2) {
    s32 temp_r4;

    if (arg1 == NULL) {
        return 0;
    }
    temp_r4 = M2C_FIELD(arg1, s32 *, 0x48);
    switch (arg2) {                                 /* irregular */
    case 0:
        if (M2C_FIELD(arg0, s32 *, 0x30) == 0) {
            func_ov001_02158828(arg1);
        }
        break;
    case 1:
        if (M2C_FIELD(arg0, s32 *, 0x34) == 0) {
            func_ov001_02158828(arg1);
        }
        break;
    case 2:
        func_ov001_02158828(arg1);
        break;
    }
    return temp_r4;
}
