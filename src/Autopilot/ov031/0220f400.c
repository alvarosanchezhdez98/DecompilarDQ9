#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, s32);
M2C_UNK _Z15PopulateContextP16ProcessorContextjjjjj(void *, M2C_UNK *, M2C_UNK, void *, s32, s32);
s32 _Z18GetContextPriorityP16ProcessorContext(s32);
M2C_UNK _Z34MarkContextStackTopUnknownSubspaceP16ProcessorContextj(void *, M2C_UNK);
M2C_UNK func_020c7de4(void *, void *, M2C_UNK);
extern M2C_UNK data_02111304;
extern void *data_ov031_0224e580;
extern M2C_UNK func_ov031_0220f5b4;

void func_ov031_0220f400(void *arg0) {
    void *temp_r4;

    data_ov031_0224e580 = arg0;
    VectorizedMemset(arg0, 0, 0x8F4);
    func_020c7de4(data_ov031_0224e580, data_ov031_0224e580 + 0x20, 1);
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x24) = 0;
    temp_r4 = data_ov031_0224e580;
    _Z15PopulateContextP16ProcessorContextjjjjj(temp_r4 + 0x34, &func_ov031_0220f5b4, 0, temp_r4 + 0x8F4, 0x800, _Z18GetContextPriorityP16ProcessorContext(M2C_FIELD(&data_02111304, s32 *, 4)));
    _Z34MarkContextStackTopUnknownSubspaceP16ProcessorContextj(data_ov031_0224e580 + 0x34, 0x80);
}
