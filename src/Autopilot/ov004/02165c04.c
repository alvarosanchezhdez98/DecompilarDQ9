#include <m2c.h>

u32 func_0200fb08();
M2C_UNK func_0204b0e8(void *, M2C_UNK);
M2C_UNK func_0204b8d0(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_0204b988(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass112SetTouchAreaEiiii(void *, s32, s32, s32, s32);
void * _ZN16MenuObjectClass213GetBackgroundEv(void *);
void * _ZN9GameState11GetInstanceEv(void);

s32 func_ov004_02165c04(void *arg0) {
    s32 var_r4;
    s32 var_r5;
    u32 temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fb08();
    var_r4 = 0x4A;
    var_r5 = 0;
    switch (temp_r0) {
    default:
        break;
    case 2:
        var_r5 = 1;
        var_r4 = 0x5A;
        break;
    case 4:
        var_r5 = 2;
        var_r4 = 0x80;
        break;
    case 3:
        var_r5 = 3;
        break;
    case 5:
        var_r5 = 4;
        var_r4 = 0x78;
        break;
    }
    temp_r0_2 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 3);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 2) {
        return 0;
    }
    M2C_FIELD(temp_r0_2, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0xC) | 1);
    temp_r0_3 = _ZN16MenuObjectClass213GetBackgroundEv(temp_r0_2);
    func_0204b988(temp_r0_3, 0, 0, 0, 0xFFFF);
    if (var_r5 != 0) {
        func_0204b8d0(temp_r0_3, var_r5, 0, 0, 0x16, 2, 9, 3, 0xFFFF);
    }
    func_0204b0e8(temp_r0_3, 0);
    temp_r0_4 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x1F8);
    if ((temp_r0_4 != NULL) && (_ZN15MenuObjectClass7GetTypeEv(temp_r0_4) == 1)) {
        if (temp_r0_4 == NULL) {
            return 0;
        }
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 0, 0, var_r4, 0x11);
        goto block_24;
    }
block_24:
    return 0;
}
