#include <m2c.h>

extern void *data_ov031_0224e53c;

void WcmInitOption(void) {
    M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2264) = 0xAAA082;
}
