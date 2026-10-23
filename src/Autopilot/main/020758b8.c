#include <m2c.h>

u16 _Z19GenerateLockOwnerIDv();
M2C_UNK _Z21InitializeCardReadingv();
M2C_UNK _Z22SetReadContextPriorityj(M2C_UNK);
M2C_UNK func_020c9be0();
M2C_UNK func_020d0040(u16);
M2C_UNK func_020d0050(u16);
M2C_UNK func_020d06fc(s32);
extern s8 data_020f0dc8;
extern M2C_UNK data_02108dfc;

void func_020758a8(void) {
    u16 temp_r0;

    _Z21InitializeCardReadingv();
    _Z22SetReadContextPriorityj(8);
    temp_r0 = _Z19GenerateLockOwnerIDv();
    if (temp_r0 == -3U) {
        func_020c9be0();
    }
    M2C_FIELD(&data_02108dfc, u16 *, 2) = temp_r0;
    func_020d0040(M2C_FIELD(&data_02108dfc, u16 *, 2));
    func_020d06fc(0x1001);
    func_020d0050(M2C_FIELD(&data_02108dfc, u16 *, 2));
    data_020f0dc8 = 1;
}
