#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK func_02042804(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *);
extern M2C_UNK data_020f0079;
extern M2C_UNK data_020f007c;
extern M2C_UNK data_0210782c;
extern M2C_UNK data_02107830;
extern M2C_UNK data_02107834;
extern M2C_UNK data_02107838;

void func_02042944(M2C_UNK arg0) {
    _ZN16BackgroundLoader13AddLockGlobalEv();
    func_02042804(arg0, &data_020f0079, &data_0210782c, &data_02107834);
    func_02042804(arg0, &data_020f007c, &data_02107830, &data_02107838);
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
}
