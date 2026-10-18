#include <m2c.h>

M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(void *);
extern M2C_UNK data_ov031_0224e5e8;

void ov00_021E7E2C(void) {
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x1384) == 0) {
        return;
    }
    _Z22AwaitContextCompletionP16ProcessorContext(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x1318);
}
