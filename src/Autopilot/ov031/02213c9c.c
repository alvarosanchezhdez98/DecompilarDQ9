#include <m2c.h>

M2C_UNK ov00_021FAE14(M2C_UNK);
s32 ov00_021FAECC();
s32 ov00_021FB6FC();
s32 ov00_021FB7F4();

s32 ov00_021FB6B8(void) {
    s32 var_r4;

    var_r4 = ov00_021FAECC();
    ov00_021FAE14(0x10);
    switch (var_r4) {                               /* irregular */
    case 7:
        var_r4 = ov00_021FB6FC();
        break;
    case 8:
        var_r4 = ov00_021FB7F4();
        break;
    }
    return var_r4;
}
