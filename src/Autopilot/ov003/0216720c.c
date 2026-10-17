#include <m2c.h>

M2C_UNK func_0204b088(s32, M2C_UNK);

void func_ov003_0216720c(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x464) & 0x40000)) {
        return;
    }
    func_0204b088(M2C_FIELD(arg0, s32 *, 0x328) + 0x40, 0);
    M2C_FIELD(arg0, s32 *, 0x464) = (s32) (M2C_FIELD(arg0, s32 *, 0x464) & ~0x40000);
}
