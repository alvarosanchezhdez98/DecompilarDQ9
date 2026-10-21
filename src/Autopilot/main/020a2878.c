#include <m2c.h>

M2C_UNK func_0202e694(void *, void *);
M2C_UNK func_0202e9a4(void *, M2C_UNK);

void func_020a2868(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x224) = 0xC666;
    M2C_FIELD(arg0, s32 *, 0x228) = 0xE666;
    func_0202e694(arg0, arg0 + 0x220);
    func_0202e9a4(arg0, 0x19000);
}
