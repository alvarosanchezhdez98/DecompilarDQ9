#include <m2c.h>

void *func_ov004_02153944(void *, M2C_UNK);
M2C_UNK func_ov004_02154618();
void _ZN16MenuObjectClass67RefreshEP10MenuScript(void *, void *);

s32 func_ov004_02154718(void *arg0) {
    void *temp_r0;

    func_ov004_02154618();
    temp_r0 = func_ov004_02153944(arg0, 0x37);
    if (temp_r0 != NULL) {
        _ZN16MenuObjectClass67RefreshEP10MenuScript(temp_r0, arg0);
    }
    return 0;
}
