#include <m2c.h>


u8 func_ov000_0216f0bc(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x260) != 0) {
        return M2C_FIELD(arg0, u8 *, 0x261);
    }
    return 1U;
}
