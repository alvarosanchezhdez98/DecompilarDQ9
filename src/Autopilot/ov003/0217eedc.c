#include <m2c.h>

void _ZN17CharacterCreation6Draw3DEv(void *);

void func_ov003_0217eedc(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_r0 == NULL) {
        return;
    }
    _ZN17CharacterCreation6Draw3DEv(temp_r0);
}
