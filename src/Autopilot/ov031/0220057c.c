#include <m2c.h>

M2C_UNK _Z21ChangeContextPriorityP16ProcessorContextj(M2C_UNK *, s32);
extern s32 data_ov031_02249680;
extern M2C_UNK data_ov031_0224cb28;
extern M2C_UNK data_ov031_0224cbe8;

void CPS_SetThreadPriority(s32 arg0) {
    data_ov031_02249680 = arg0;
    _Z21ChangeContextPriorityP16ProcessorContextj(&data_ov031_0224cbe8, arg0);
    _Z21ChangeContextPriorityP16ProcessorContextj(&data_ov031_0224cb28, arg0);
}
