#include <m2c.h>

s32 _Z28IsBrightnessTransitionActiveP13GameResources();
M2C_UNK func_ov017_0218b5b0();

s32 func_ov025_021e58d4(void) {
    func_ov017_0218b5b0();
    if (_Z28IsBrightnessTransitionActiveP13GameResources() == 0) {
        return 1;
    }
    return 0;
}
