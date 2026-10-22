#include <m2c.h>

s32 _Z27SetResourceMutexOperationalb(s32);
s32 func_02046708(s32, M2C_UNK);
s32 func_020d6c00();
M2C_UNK func_020dbae0(M2C_UNK);

void func_020dbc0c(M2C_UNK arg0) {
    s32 temp_r4;

    temp_r4 = _Z27SetResourceMutexOperationalb(0);
    if (func_02046708(func_020d6c00(), 0x100) == 0) {
        func_020dbae0(arg0);
    }
    _Z27SetResourceMutexOperationalb(temp_r4);
}
