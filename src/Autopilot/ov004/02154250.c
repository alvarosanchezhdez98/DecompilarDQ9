#include <m2c.h>

M2C_UNK func_ov004_021536e0(void *, M2C_UNK, M2C_UNK);
extern void *data_ov004_021707c0;
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass67RefreshEP10MenuScript(void *, void *);

s32 func_ov004_02154250(void *arg0) {
    s16 temp_r4;
    s16 var_r7;
    void **temp_r0_2;
    void **temp_r0_3;
    void *temp_r0;
    void *temp_r0_4;

    temp_r4 = M2C_FIELD(data_ov004_021707c0, s16 *, 0x7A);
    var_r7 = (s16) ((s32) (temp_r4 * 0x64) / (s16) M2C_FIELD(data_ov004_021707c0, s16 *, 0x78));
    if ((var_r7 == 0) && (temp_r4 == 0)) {
        var_r7 = 0;
    }
    if ((var_r7 == 0) && (temp_r4 != 0)) {
        var_r7 = 1;
    }
    if ((s32) var_r7 > 0x64) {
        var_r7 = 0x64;
    }
    if ((s32) var_r7 < 0) {
        var_r7 = 0;
    }
    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, 0x13);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    M2C_FIELD(*temp_r0_2, M2C_UNK (**)(void **, s16), 0xE0)(temp_r0_2, var_r7);
    temp_r0_3 = _ZN14MenuObjectList4FindEi(temp_r0, 0x14);
    if (temp_r0_3 == NULL) {
        return 0;
    }
    M2C_FIELD(*temp_r0_3, M2C_UNK (**)(void **, s16), 0xE0)(temp_r0_3, temp_r4);
    func_ov004_021536e0(arg0, 0x14, 0x19);
    temp_r0_4 = _ZN14MenuObjectList4FindEi(temp_r0, 0x10);
    if (temp_r0_4 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_4) != 6) {
        return 0;
    }
    _ZN16MenuObjectClass67RefreshEP10MenuScript(temp_r0_4, arg0);
    return 0;
}
