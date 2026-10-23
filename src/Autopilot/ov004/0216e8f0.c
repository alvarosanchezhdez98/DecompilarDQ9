#include <m2c.h>

extern M2C_UNK data_ov004_02171034;
void * _ZN10MenuScript10GetObjectsEv(void *);
void _ZN10MenuScript9SetUnk1c8Ev(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void * _ZN9GameState11GetInstanceEv(void);
void func_02012028(void *arg0, s8 arg1);

s32 func_ov004_0216e8f0(void *arg0) {
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r5;

    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    if (temp_r0 != NULL) {
        temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, (s32) M2C_FIELD(&data_ov004_02171034, u16 *, 0xA));
        if (temp_r0_2 != NULL) {
            M2C_FIELD(temp_r0_2, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0xC) & ~0x10);
        }
    }
    _ZN10MenuScript9SetUnk1c8Ev(arg0);
    temp_r5 = _ZN9GameState11GetInstanceEv();
    if (M2C_FIELD(&data_ov004_02171034, u8 *, 3) != 6) {
        temp_r0_3 = _ZN14MenuObjectList4FindEi(temp_r0, 1);
        if ((temp_r0_3 != NULL) && (_ZN15MenuObjectClass7GetTypeEv(temp_r0_3) == 0xB)) {
            M2C_FIELD(temp_r0_3, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0xC) & ~8);
            func_02012028(temp_r5, 1);
        }
    }
    return 0;
}
