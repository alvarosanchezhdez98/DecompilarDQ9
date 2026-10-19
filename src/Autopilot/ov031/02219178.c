#include <m2c.h>

M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(void *);
M2C_UNK ov00_021E7D48();
M2C_UNK ov00_021E9210();
extern M2C_UNK data_ov031_0224e60c;

void ov00_021EA518(void) {
    if (M2C_FIELD(&data_ov031_0224e60c, void **, 0) == NULL) {
        return;
    }
    if (M2C_FIELD(&data_ov031_0224e60c, s32 *, 0x14) != 0) {
        ov00_021E9210();
    }
    ov00_021E7D48();
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e60c, void **, 0), s32 *, 0x1188) != 0) {
        _Z22AwaitContextCompletionP16ProcessorContext(M2C_FIELD(&data_ov031_0224e60c, void **, 0) + 0x111C);
    }
    M2C_FIELD(M2C_FIELD(&data_ov031_0224e60c, void **, 0), s32 *, 0x1004) = -7;
}
