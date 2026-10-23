#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
s32 _ZN16MenuObjectClass78GetIndexEv(void *);

s32 func_ov004_02156e2c(void *arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if (temp_r0 == NULL) {
        return -1;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 7) {
        return -1;
    }
    return _ZN16MenuObjectClass78GetIndexEv(temp_r0);
}
