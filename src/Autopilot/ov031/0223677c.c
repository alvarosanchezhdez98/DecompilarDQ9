#include <m2c.h>

M2C_UNK func_020bbd14();
M2C_UNK func_020bbf34(s32, M2C_UNK);
M2C_UNK func_020bbf4c(s32, M2C_UNK);
M2C_UNK func_020bbf6c(s32, s32);
M2C_UNK func_020bc078(void *);
M2C_UNK func_020bd368(void *, s32);
M2C_UNK func_020be6c4(M2C_UNK);
s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
s32 ov13_0223F95C(M2C_UNK *, M2C_UNK *, M2C_UNK);
void *ov13_0224128C(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_0224be60;
extern void *data_ov031_02290d00;
extern M2C_UNK func_ov031_02236900;

void func_ov031_0223677c(void) {
    M2C_UNK sp0;
    s32 var_r7;

    data_ov031_02290d00 = ov13_0224128C(0xA0, 4);
    M2C_FIELD(data_ov031_02290d00, s32 *, 0x98) = ov13_0223F95C(&data_ov031_0224be60, &sp0, 0x20);
    func_020bbd14();
    func_020bd368(data_ov031_02290d00, M2C_FIELD(data_ov031_02290d00, s32 *, 0x98));
    func_020be6c4(0);
    func_020bc078(data_ov031_02290d00 + 0x94);
    var_r7 = 0;
    do {
        func_020bbf34(var_r7, 0x7F);
        func_020bbf4c(var_r7, 1);
        func_020bbf6c(var_r7, 0);
        var_r7 += 1;
    } while (var_r7 < 0x20);
    M2C_FIELD(data_ov031_02290d00, s32 *, 0x9C) = func_ov031_0223e218(0, &func_ov031_02236900, 0, 0xC8);
}
