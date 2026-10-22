#include <m2c.h>

M2C_UNK func_020bb7cc();
M2C_UNK func_020bb908();
M2C_UNK func_020bb948();
extern M2C_UNK (*data_020f1ef0)();
extern M2C_UNK (*data_020f1ef4)();
extern M2C_UNK data_0210cf88;

void func_020bb780(s32 arg0, s32 arg1) {
    M2C_FIELD(&data_0210cf88, s32 *, 8) = arg0;
    func_020bb948();
    if (arg1 == 0) {
        return;
    }
    data_020f1ef0 = func_020bb7cc;
    data_020f1ef4 = func_020bb908;
}
