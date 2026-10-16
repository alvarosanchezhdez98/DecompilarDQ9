#include <m2c.h>


void func_ov025_021e23d0(void **arg0, void *arg1) {
    void *var_r2;

    var_r2 = *arg0;
    if (var_r2 == NULL) {
        var_r2 = NULL;
    }
    M2C_FIELD(arg1, void **, 8) = var_r2;
    *arg0 = arg1;
}
