#include <m2c.h>

void _ZN17CharacterCreation14UpdateGraphicsEv(void *);

void func_ov003_0217eef4(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_r0 == NULL) {
        return;
    }
    _ZN17CharacterCreation14UpdateGraphicsEv(temp_r0);
}
