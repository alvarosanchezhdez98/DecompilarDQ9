#include <m2c.h>

M2C_UNK _Z25MarkContextReadyAndSwitchP16ProcessorContext(s32);
M2C_UNK _Z28CycleCurrentPriorityContextsv();
void *find_socket();

void dt_rst(void) {
    void *temp_r0;

    temp_r0 = find_socket();
    if (temp_r0 == NULL) {
        return;
    }
    _Z28CycleCurrentPriorityContextsv();
    M2C_FIELD(temp_r0, s8 *, 8) = 0;
    if ((u32) (M2C_FIELD(temp_r0, s32 *, 4) - 1) > 1U) {
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    _Z25MarkContextReadyAndSwitchP16ProcessorContext(M2C_FIELD(temp_r0, s32 *, 0));
}
