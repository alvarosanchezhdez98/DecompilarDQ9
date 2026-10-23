#include <m2c.h>

u16 *func_02012fe4();
M2C_UNK func_0209c3b4(M2C_UNK *, s32);
s32 func_0209cd50(u16);
extern M2C_UNK data_02109bf4;

s32 func_ov001_02163aec(void) {
    func_0209c3b4(&data_02109bf4, func_0209cd50(*func_02012fe4()));
    return 1;
}
