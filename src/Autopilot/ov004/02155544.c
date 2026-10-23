#include <m2c.h>

M2C_UNK func_ov004_0215534c(void *);
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

s32 func_ov004_02155544(void *arg0) {
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;

    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, 0x2C);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 7) {
        return 0;
    }
    temp_r0_3 = _ZN14MenuObjectList4FindEi(temp_r0, 3);
    if (temp_r0_3 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_3) != 6) {
        return 0;
    }
    func_ov004_0215534c(arg0);
    return 0;
}
