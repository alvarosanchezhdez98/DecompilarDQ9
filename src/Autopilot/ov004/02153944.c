#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

void *func_ov004_02153944(void *arg0, s32 arg1) {
    void *temp_r0;
    void *var_r4;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    var_r4 = temp_r0;
    if (var_r4 == NULL) {
        return NULL;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 6) {
        var_r4 = NULL;
    }
    return var_r4;
}
