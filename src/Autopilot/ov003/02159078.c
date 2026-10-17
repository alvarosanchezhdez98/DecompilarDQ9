#include <m2c.h>

M2C_UNK func_0205d1e0(void *);
M2C_UNK func_0205d228(void *);
M2C_UNK func_0205d274(void *);
M2C_UNK func_0205da88(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020e2794(s32, void *);
s32 func_020e28dc();
M2C_UNK func_ov003_0215c32c(void *);
M2C_UNK func_ov003_0215c464(void *);

void func_ov003_02159078(void *arg0) {
    if (M2C_FIELD(arg0, s8 *, 0x588) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x587) != 0) {
        return;
    }
    func_0205d1e0(arg0 + 0xF4);
    func_0205d228(arg0 + 0xF4);
    func_0205da88(arg0 + 0xF4, 1, 2, 1);
    func_0205d274(arg0 + 0xF4);
    func_ov003_0215c32c(arg0);
    func_ov003_0215c464(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x570) == 0) {
        return;
    }
    if (func_020e28dc() == 0) {
        return;
    }
    func_020e2794(M2C_FIELD(arg0, s32 *, 0x570), arg0 + 0x98);
}
