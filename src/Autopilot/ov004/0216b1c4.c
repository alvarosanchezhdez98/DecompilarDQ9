#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void _ZN10MenuScript9SetUnk1b0Et(void *, u16);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass710ClearItemsEv(void *);

void func_ov004_0216b1c4(void *arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if (temp_r0 == NULL) {
        return;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 7) {
        return;
    }
    _ZN10MenuScript9SetUnk1b0Et(arg0, (u16) arg1);
    _ZN16MenuObjectClass710ClearItemsEv(temp_r0);
}
