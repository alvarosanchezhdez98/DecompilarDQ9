#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);

void *func_ov004_0215e47c(void *arg0, s32 arg1) {
    void *var_r0;

    var_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if (var_r0 == NULL) {
        var_r0 = NULL;
    }
    return var_r0;
}
