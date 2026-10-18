#include <m2c.h>

void *_ZN9GameState14GetProtagonistEv();

u32 func_02068580(void) {
    void *temp_r0;

    temp_r0 = _ZN9GameState14GetProtagonistEv();
    if (temp_r0 != NULL) {
        return (u32) (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x150), u8 *, 0x49C) << 0x1F) >> 0x1F;
    }
    return 0U;
}
