#include <m2c.h>

M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(M2C_UNK *);
M2C_UNK ov38_0222211C();
extern s32 data_ov031_02290fd0;
extern M2C_UNK data_ov031_022918dc;

void ov38_022220D8(void) {
    data_ov031_02290fd0 = 1;
    ov38_0222211C();
    _Z22AwaitContextCompletionP16ProcessorContext(&data_ov031_022918dc);
}
