#include <m2c.h>

s32 _Z18GetContextPriorityP16ProcessorContext(s32);
M2C_UNK _Z21ChangeContextPriorityP16ProcessorContextj(s32, u32);
extern M2C_UNK data_02111304;
extern M2C_UNK data_ov031_022496fc;

s32 enter_computebound(void) {
    s32 temp_r4;
    s32 temp_r5;

    if ((u32) M2C_FIELD(&data_ov031_022496fc, u32 *, 4) >= 0x20U) {
        return -1;
    }
    temp_r5 = M2C_FIELD(&data_02111304, s32 *, 4);
    temp_r4 = _Z18GetContextPriorityP16ProcessorContext(temp_r5);
    _Z21ChangeContextPriorityP16ProcessorContextj(temp_r5, M2C_FIELD(&data_ov031_022496fc, u32 *, 4));
    return temp_r4;
}
