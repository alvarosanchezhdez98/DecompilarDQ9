#include <m2c.h>

s32 _Z17IsContextInactiveP16ProcessorContext(void *);
M2C_UNK ov00_021E9210(void *);
extern void *data_ov031_0224e69c;

void func_ov031_0221a854(void) {
    if ((data_ov031_0224e69c != NULL) && (M2C_FIELD(data_ov031_0224e69c, s32 *, 0x1BAC) != 0)) {
        if (_Z17IsContextInactiveP16ProcessorContext(data_ov031_0224e69c + 0x1B40) != 0) {
            return;
        }
        ov00_021E9210(data_ov031_0224e69c + 8);
    }
}
