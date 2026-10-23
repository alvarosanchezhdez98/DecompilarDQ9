#include <m2c.h>

extern M2C_UNK data_ov004_02171034;
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
void _ZN16MenuObjectClass710MoveCursorEP10MenuScript(void *, void *);

s32 func_ov004_0216e984(void *arg0) {
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    if (temp_r0 != NULL) {
        temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, (s32) M2C_FIELD(&data_ov004_02171034, u16 *, 0xA));
        if (temp_r0_2 != NULL) {
            M2C_FIELD(temp_r0_2, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0xC) | 0x10);
            _ZN16MenuObjectClass710MoveCursorEP10MenuScript(temp_r0_2, arg0);
        }
    }
    return 0;
}
