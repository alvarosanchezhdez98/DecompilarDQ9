#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
s32 func_ov031_02216360();
M2C_UNK func_ov031_02216698();
s32 ov00_021FAAC8();
M2C_UNK ov00_021FE070();
extern M2C_UNK data_ov031_0224e5b4;

void func_ov031_022120f8(void) {
    if (M2C_FIELD(&data_ov031_0224e5b4, void **, 4) == NULL) {
        return;
    }
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), u16 *, 4) == 1) {
        if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), s32 *, 0x10) == 1) {
            func_ov031_02216698();
            do {

            } while ((u32) (func_ov031_02216360() - 2) > 2U);
            ov00_021FE070();
        }
        M2C_FIELD(&data_ov031_0224e5b4, void **, 4) = NULL;
        return;
    }
    if (ov00_021FAAC8() == 0) {
        do {
            _Z19SleepCurrentContextj(0xA);
        } while (ov00_021FAAC8() == 0);
    }
    M2C_FIELD(&data_ov031_0224e5b4, void **, 4) = NULL;
}
