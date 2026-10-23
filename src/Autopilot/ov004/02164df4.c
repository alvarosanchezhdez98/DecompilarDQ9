#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass76SetRowEt(void *, u16);
void _ZN16MenuObjectClass79SetColumnEt(void *, u16);

s32 func_ov004_02164df4(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0xB);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 7) {
        return 0;
    }
    _ZN16MenuObjectClass76SetRowEt(temp_r0, 0U);
    _ZN16MenuObjectClass79SetColumnEt(temp_r0, 0U);
    return 0;
}
