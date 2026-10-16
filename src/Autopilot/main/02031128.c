#include <m2c.h>


s32 func_02031118(void *arg0, void *arg1) {
    s32 temp_ip;
    s32 temp_r2;
    s32 temp_r3;

    temp_ip = M2C_FIELD(arg0, s32 *, 0);
    if ((s32) M2C_FIELD(arg1, s32 *, 0) < temp_ip) {
        return 0;
    }
    temp_r3 = M2C_FIELD(arg0, s32 *, 4);
    if ((s32) M2C_FIELD(arg1, s32 *, 4) < temp_r3) {
        return 0;
    }
    temp_r2 = M2C_FIELD(arg0, s32 *, 8);
    if ((s32) M2C_FIELD(arg1, s32 *, 8) < temp_r2) {
        return 0;
    }
    if (temp_ip < (s32) M2C_FIELD(arg1, s32 *, 0xC)) {
        return 0;
    }
    if (temp_r3 < (s32) M2C_FIELD(arg1, s32 *, 0x10)) {
        return 0;
    }
    if (temp_r2 >= (s32) M2C_FIELD(arg1, s32 *, 0x14)) {
        return 1;
    }
    return 0;
}
