#include <m2c.h>

M2C_UNK func_020c9820();
M2C_UNK func_ov031_022167a8(M2C_UNK *);
M2C_UNK *func_ov031_022167b8();
s32 func_ov031_022270ac(M2C_UNK, M2C_UNK);
M2C_UNK func_ov031_02227468();
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0223677c();
M2C_UNK func_ov031_0223d0a4();
M2C_UNK ov13_0222B558();
M2C_UNK ov13_0222B620();
M2C_UNK ov13_02241A44();
M2C_UNK ov13_022422E0();
M2C_UNK ov13_02242478(M2C_UNK);
extern M2C_UNK data_ov031_0224b608;
extern M2C_UNK data_ov031_02250c0c;
extern M2C_UNK ov13_0222C1BC;

s32 func_ov031_02226fe4(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK *temp_r6;

    M2C_FIELD(&data_ov031_02250c0c, s32 *, 4) = arg0;
    if (func_ov031_022270ac(arg1, arg2) == 0) {
        return -1;
    }
    temp_r6 = func_ov031_022167b8();
    func_ov031_022167a8(&data_ov031_0224b608);
    M2C_FIELD(&data_ov031_02250c0c, u8 *, 1) = 0U;
    ov13_0222B558();
    ov13_0222B620();
    func_ov031_0223677c();
    func_ov031_022274c0(&ov13_0222C1BC);
    do {
        func_ov031_0223d0a4();
        M2C_FIELD(&data_ov031_02250c0c, M2C_UNK (**)(), 0xC)();
        ov13_02242478(0);
        ov13_02241A44();
        ov13_022422E0();
        func_020c9820();
    } while (M2C_FIELD(&data_ov031_02250c0c, u8 *, 1) == 0);
    func_ov031_02227468();
    func_ov031_022167a8(temp_r6);
    return 0;
}
