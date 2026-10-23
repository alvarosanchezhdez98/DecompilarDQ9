#include <m2c.h>

u32 func_0200fb08();
M2C_UNK func_0204b0e8(void *, M2C_UNK);
M2C_UNK func_0204b8d0(void *, u32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_0204b988(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void * _ZN16MenuObjectClass213GetBackgroundEv(void *);
void * _ZN9GameState11GetInstanceEv(void);

s32 func_ov004_02154f1c(void *arg0) {
    u32 temp_r0;
    u32 var_r4;
    void *temp_r0_2;
    void *temp_r0_3;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fb08();
    var_r4 = 1;
    switch (temp_r0) {
    default:
        break;
    case 2:
        var_r4 = 2;
        break;
    case 4:
        var_r4 = 3;
        break;
    case 3:
        var_r4 = 4;
        break;
    case 5:
        var_r4 = 5;
        break;
    }
    temp_r0_2 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0xC);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 2) {
        return 0;
    }
    M2C_FIELD(temp_r0_2, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0xC) | 1);
    temp_r0_3 = _ZN16MenuObjectClass213GetBackgroundEv(temp_r0_2);
    func_0204b988(temp_r0_3, 1, 0, 0, 0xFFFF);
    if (var_r4 > 1U) {
        func_0204b8d0(temp_r0_3, var_r4, 0, 0, 0x16, 2, 9, 2, 0xFFFF);
    }
    func_0204b0e8(temp_r0_3, 0);
    return 0;
}
