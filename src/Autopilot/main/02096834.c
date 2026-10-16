#include <m2c.h>

void *func_020421a0();
s32 func_02046708(s32, M2C_UNK);
s32 func_020d6c00();
M2C_UNK func_02096c38(void *, u8, u8, u8, s32);
extern M2C_UNK data_02114e54;

void func_02096824(void *arg0) {
    void *temp_r0;

    if (func_02046708(func_020d6c00(), 0x4000) == 0) {
        if ((M2C_FIELD(&data_02114e54, u8 *, 0x5F) != 0) && (M2C_FIELD(&data_02114e54, u16 *, 0x24) != 0)) {
            temp_r0 = func_020421a0();
            if ((temp_r0 != NULL) && (M2C_FIELD(temp_r0, s32 *, 0x998) != 0)) {
                return;
            }
            if (M2C_FIELD(arg0, u8 *, 0x225) != 0) {
                func_02096c38(arg0, M2C_FIELD(arg0, u8 *, 0x220), M2C_FIELD(arg0, u8 *, 0x221), M2C_FIELD(arg0, u8 *, 0x222), (s32) M2C_FIELD(arg0, u8 *, 0x223));
            }
        }
    }
}
