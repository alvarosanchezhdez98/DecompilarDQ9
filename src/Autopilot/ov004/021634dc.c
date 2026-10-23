#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
u16 _ZN16MenuObjectClass76GetRowEv(void *);

s32 func_ov004_021634dc(void *arg0) {
    s16 temp_r4;
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0xA);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 7) {
        return 0;
    }
    temp_r4 = M2C_FIELD(temp_r0, s16 *, 0x5C);
    return _ZN16MenuObjectClass76GetRowEv(temp_r0) + (temp_r4 * 8);
}
