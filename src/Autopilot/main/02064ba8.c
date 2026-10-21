#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_02010774(s32, u8);
M2C_UNK func_020107a8(s32, u8);
M2C_UNK func_020107dc(s32, u8);

void func_02064b98(void *arg0, s32 arg1) {
    s32 temp_r0;
    void *var_r4;

    var_r4 = arg0;
    if (((arg1 >= 0x1068) && (arg1 <= 0x106A)) || ((arg1 >= 0x2328) && (arg1 <= 0x2330))) {
        M2C_FIELD(var_r4, s8 *, 0x332) = 1;
        var_r4 += 0x1C;
    } else if (((arg1 >= 0x6A4) && (arg1 <= 0x6AA)) || ((arg1 >= 0x708) && (arg1 <= 0x710)) || ((arg1 >= 0x1770) && (arg1 <= 0x1771)) || ((arg1 >= 0x1E14) && (arg1 <= 0x1E1D))) {
        M2C_FIELD(var_r4, s8 *, 0x332) = 2;
        var_r4 += 0x38;
    } else if (((arg1 >= 0xC8) && (arg1 <= 0xDB)) || ((arg1 >= 0x1E7A) && (arg1 <= 0x1E81))) {
        M2C_FIELD(var_r4, s8 *, 0x332) = 3;
        var_r4 += 0x54;
    } else if (((arg1 >= 0x834) && (arg1 <= 0x83D)) || ((arg1 >= 0x206D) && (arg1 <= 0x206F))) {
        M2C_FIELD(var_r4, s8 *, 0x332) = 4;
        var_r4 += 0x70;
    } else {
        M2C_FIELD(var_r4, s8 *, 0x332) = 0;
    }
    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_02010774(temp_r0, M2C_FIELD(var_r4, u8 *, 0));
    func_020107a8(temp_r0, M2C_FIELD(var_r4, u8 *, 1));
    func_020107dc(temp_r0, M2C_FIELD(var_r4, u8 *, 2));
}
