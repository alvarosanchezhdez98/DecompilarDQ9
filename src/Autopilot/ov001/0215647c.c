#include <m2c.h>

void *func_ov017_0218b5b0();

u16 func_ov001_0215647c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xFC) != 0) {
        return 0xAU;
    }
    if (M2C_FIELD(func_ov017_0218b5b0(), u8 *, 0x42E2) != 0) {
        return 0xAU;
    }
    return M2C_FIELD(arg0, u16 *, 0xA);
}
