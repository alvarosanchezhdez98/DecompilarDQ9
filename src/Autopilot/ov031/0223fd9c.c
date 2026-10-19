#include <m2c.h>

M2C_UNK _Z15PopulateContextP16ProcessorContextjjjjj(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *, s32, s32);
M2C_UNK _Z25MarkContextReadyAndSwitchP16ProcessorContext(M2C_UNK *);
extern M2C_UNK data_ov031_02290fe0;
extern M2C_UNK data_ov031_022918a0;
extern M2C_UNK ov38_02221B0C;

void ov38_02221AC4(M2C_UNK arg0) {
    _Z15PopulateContextP16ProcessorContextjjjjj(&data_ov031_02290fe0, &ov38_02221B0C, arg0, &data_ov031_022918a0, 0x800, 0x10);
    _Z25MarkContextReadyAndSwitchP16ProcessorContext(&data_ov031_02290fe0);
}
