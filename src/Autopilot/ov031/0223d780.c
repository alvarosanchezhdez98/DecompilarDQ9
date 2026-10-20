#include <m2c.h>

M2C_UNK _Z19EnableIRQInterruptsv(M2C_UNK, u16);
s32 _Z19GetInterruptHandlerj(M2C_UNK);
M2C_UNK _Z19SetInterruptHandlerjPKv(M2C_UNK, M2C_UNK *);
M2C_UNK _Z24EnableSpecificInterruptsj(M2C_UNK);
M2C_UNK _Z28SetSpecificInterruptsEnabledj(s32);
M2C_UNK _Z29AcknowledgeSpecificInterruptsj(M2C_UNK);
extern M2C_UNK data_ov031_02290d58;
extern M2C_UNK ov13_02241B70;

void ov13_02241AC0(void) {
    u16 temp_r1;

    M2C_FIELD(&data_ov031_02290d58, s32 *, 4) = (s32) *(s32 *)0x04000210;
    _Z28SetSpecificInterruptsEnabledj(0x40018);
    _Z24EnableSpecificInterruptsj(1);
    M2C_FIELD(&data_ov031_02290d58, s32 *, 0) = _Z19GetInterruptHandlerj(1);
    _Z19SetInterruptHandlerjPKv(1, &ov13_02241B70);
    _Z29AcknowledgeSpecificInterruptsj(1);
    temp_r1 = *(u16 *)0x04000208;
    *(u16 *)0x04000208 = 1;
    _Z19EnableIRQInterruptsv(1, temp_r1);
}
