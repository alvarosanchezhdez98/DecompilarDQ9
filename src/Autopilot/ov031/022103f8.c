#include <m2c.h>

M2C_UNK _Z15UnblockContextsP18BlockedContextList(s32);
M2C_UNK func_ov031_0221038c(M2C_UNK);
M2C_UNK func_ov031_022103dc(M2C_UNK);
extern s32 data_ov031_0224e588;

void func_ov031_022103f8(M2C_UNK arg0) {
    func_ov031_0221038c(0);
    func_ov031_022103dc(arg0);
    _Z15UnblockContextsP18BlockedContextList(data_ov031_0224e588 + 0xA04);
}
