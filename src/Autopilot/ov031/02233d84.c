#include <m2c.h>

M2C_UNK func_ov031_022274c0();
M2C_UNK func_ov031_0222ea14();
s32 ov00_021FA904();
s32 ov00_021FA9D4();
M2C_UNK ov13_02227F68();
M2C_UNK ov13_0223ABB8();
M2C_UNK ov13_0223AC20();
M2C_UNK ov13_022425D0();
extern M2C_UNK data_ov031_02290cd0;
extern M2C_UNK func_ov031_02233c94;

void func_ov031_02233d84(M2C_UNK arg0) {
    s32 saved_reg_r5;
    s32 var_r0;
    s32 var_r5;

    var_r5 = saved_reg_r5;
    if (M2C_FIELD(&data_ov031_02290cd0, s32 *, 4) != 0) {
        var_r5 = ov00_021FA904();
        if (var_r5 == 0) {
            return;
        }
    }
    ov13_02227F68();
    ov13_0223AC20();
    if ((M2C_FIELD(&data_ov031_02290cd0, s32 *, 4) != 0) && (var_r5 > 0)) {
        M2C_FIELD(&data_ov031_02290cd0, s8 *, 0) = 1;
        ov13_0223ABB8(0x11);
    } else {
        if (M2C_FIELD(&data_ov031_02290cd0, s32 *, 4) == 0) {
            var_r0 = -0xC417;
        } else {
            var_r0 = ov00_021FA9D4();
        }
        if (var_r0 >= -0xA) {
            var_r0 = -0xC417;
        }
        func_ov031_0222ea14(var_r0);
        ov13_0223ABB8(0x12);
    }
    func_ov031_022274c0(&func_ov031_02233c94);
    ov13_022425D0(0, arg0);
}
