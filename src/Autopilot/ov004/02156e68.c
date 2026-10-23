#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
u16 _ZN16MenuObjectClass76GetRowEv(void *);
u16 _ZN16MenuObjectClass77GetItemEtt(void *, u16, u16);
u16 _ZN16MenuObjectClass79GetColumnEv(void *);

void *func_ov004_02156e68(void *arg0, s32 arg1) {
    u16 temp_r4;
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, arg1);
    if (temp_r0_2 == NULL) {
        return NULL;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 7) {
        return NULL;
    }
    temp_r4 = _ZN16MenuObjectClass79GetColumnEv(temp_r0_2);
    return _ZN14MenuObjectList4FindEi(temp_r0, (s32) _ZN16MenuObjectClass77GetItemEtt(temp_r0_2, _ZN16MenuObjectClass76GetRowEv(temp_r0_2), temp_r4));
}
