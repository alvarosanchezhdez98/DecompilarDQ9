#include <m2c.h>

M2C_UNK _Z15UnblockContextsP18BlockedContextList(s32);
s32 _Z17IsContextInactiveP16ProcessorContext(s32);
M2C_UNK func_ov031_0221038c(M2C_UNK);
M2C_UNK func_ov031_02210618();
extern s32 data_ov031_0224e588;

s32 func_ov031_022101e0(void) {
    if (data_ov031_0224e588 == 0) {
        return 1;
    }
    func_ov031_0221038c(2);
    if (_Z17IsContextInactiveP16ProcessorContext(data_ov031_0224e588 + 0xA10) == 0) {
        func_ov031_02210618();
        return 0;
    }
    _Z15UnblockContextsP18BlockedContextList(data_ov031_0224e588 + 0xA04);
    data_ov031_0224e588 = 0;
    return 1;
}
