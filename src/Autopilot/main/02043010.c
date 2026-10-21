#include <m2c.h>

M2C_UNK func_0202f1dc(s32);
M2C_UNK func_02043040(void *);
M2C_UNK func_020430b0(void *);
M2C_UNK func_02043124(void *);
M2C_UNK func_02043224(void *);

void func_02043000(void *arg0) {
    func_0202f1dc(arg0 + 0x19E0);
    func_02043224(arg0);
    func_02043040(arg0);
    func_02043124(arg0);
    func_020430b0(arg0);
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
}
