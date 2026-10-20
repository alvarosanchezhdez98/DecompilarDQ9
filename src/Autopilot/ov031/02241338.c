#include <m2c.h>

s32 SOCL_EnableSsl(s32, void *);
s32 SOC_Socket(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov031_02207434(s32);
M2C_UNK ov38_022230BC();
extern M2C_UNK func_ov031_0224130c;

s32 ov38_022230DC(void *arg0) {
    s32 var_r4;

    var_r4 = SOC_Socket(2, 1, 0);
    if ((var_r4 >= 0) && (M2C_FIELD(arg0, s32 *, 8) != 0)) {
        ov38_022230BC();
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s32 *, 0x814) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s32 *, 0x818) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), M2C_UNK **, 0x810) = &func_ov031_0224130c;
        if (SOCL_EnableSsl(var_r4, M2C_FIELD(arg0, void **, 0x20)) < 0) {
            func_ov031_02207434(var_r4);
            var_r4 = -1;
        }
    }
    return var_r4;
}
