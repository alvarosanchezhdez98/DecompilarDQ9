#include <m2c.h>

M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(void *);
M2C_UNK ov00_021ECEE4();
extern void *data_ov031_0224e5c0;

void ov00_021ECFF4(void) {
    M2C_UNK (*temp_r4)();

    _Z22AwaitContextCompletionP16ProcessorContext(data_ov031_0224e5c0 + 0x9C0);
    temp_r4 = M2C_FIELD(data_ov031_0224e5c0, M2C_UNK (**)(), 4);
    ov00_021ECEE4();
    data_ov031_0224e5c0 = NULL;
    if (temp_r4 == NULL) {
        return;
    }
    temp_r4();
}
