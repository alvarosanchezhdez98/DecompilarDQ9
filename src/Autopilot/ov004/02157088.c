#include <m2c.h>

void *func_ov004_02157054();
void * _ZN17MenuObjectClass109GetWindowEv(void *);

void *func_ov004_02157088(void) {
    void *temp_r0;

    temp_r0 = func_ov004_02157054();
    if (temp_r0 == NULL) {
        return NULL;
    }
    return _ZN17MenuObjectClass109GetWindowEv(temp_r0);
}
