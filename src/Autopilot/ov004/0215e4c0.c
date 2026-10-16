#include <m2c.h>

void *func_ov004_0215e47c();
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

void *func_ov004_0215e4c0(void) {
    void *temp_r0;
    void *var_r4;

    temp_r0 = func_ov004_0215e47c();
    var_r4 = temp_r0;
    if (var_r4 == NULL) {
        return NULL;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 6) {
        var_r4 = NULL;
    }
    return var_r4;
}
