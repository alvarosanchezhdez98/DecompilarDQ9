#include <m2c.h>

M2C_UNK ov00_021ECFF4();
M2C_UNK ov38_02220620(M2C_UNK (*)());
extern void *data_ov031_0224e5c0;

s32 ov00_021ED308(s32 arg0) {
    if (data_ov031_0224e5c0 == NULL) {
        return 0;
    }
    M2C_FIELD(data_ov031_0224e5c0, s32 *, 4) = arg0;
    if (M2C_FIELD(data_ov031_0224e5c0, s32 *, 0x48) == 0) {
        ov00_021ECFF4();
    } else {
        ov38_02220620(ov00_021ECFF4);
    }
    return 1;
}
