#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass19SetSpriteEt(void *, u16);

void *func_ov004_02165ea4(void *arg0, s32 arg1, u16 arg2) {
    void *temp_r0;
    void *var_r4;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    var_r4 = temp_r0;
    if (var_r4 == NULL) {
        var_r4 = NULL;
    } else if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 1) {
        var_r4 = NULL;
    }
    if (var_r4 == NULL) {
        return NULL;
    }
    _ZN16MenuObjectClass19SetSpriteEt(var_r4, arg2);
    return var_r4;
}
