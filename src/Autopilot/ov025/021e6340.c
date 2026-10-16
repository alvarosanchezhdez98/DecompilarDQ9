#include <m2c.h>

M2C_UNK func_0205ebfc(M2C_UNK *, u16, M2C_UNK);
void *func_ov000_02160130();
extern M2C_UNK data_02108760;

s32 func_ov025_021e6340(void *arg0) {
    M2C_FIELD(func_ov000_02160130(), u16 *, 0x6F04) = (u16) M2C_FIELD(arg0, u16 *, 8);
    func_0205ebfc(&data_02108760, M2C_FIELD(arg0, u16 *, 8), 0);
    return 1;
}
