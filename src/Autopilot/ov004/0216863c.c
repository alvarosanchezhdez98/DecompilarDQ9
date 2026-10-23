#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN17MenuObjectClass105CloseEv(void *);

s32 func_ov004_0216863c(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 7);
    if ((temp_r0 != NULL) && (_ZN15MenuObjectClass7GetTypeEv(temp_r0) == 0x10)) {
        _ZN17MenuObjectClass105CloseEv(temp_r0);
    }
    return 0;
}
