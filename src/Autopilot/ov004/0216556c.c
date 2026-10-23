#include <m2c.h>

M2C_UNK func_ov004_021636b0(void *, s32);
extern void *data_ov004_02171010;
s32 _Z28IsBrightnessTransitionActiveP13GameResources(void *);
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
u16 _ZN16MenuObjectClass76GetRowEv(void *);
void * _ZN9GameState11GetInstanceEv(void);
s32 func_0200fb8c(s32 *arg0);

s32 func_ov004_0216556c(void *arg0) {
    void *temp_r0;

    if (M2C_FIELD(data_ov004_02171010, u8 *, 0x18F4) == 0) {
        return 0;
    }
    if (_Z28IsBrightnessTransitionActiveP13GameResources((void *) func_0200fb8c(_ZN9GameState11GetInstanceEv())) != 0) {
        return 0;
    }
    if (M2C_FIELD(data_ov004_02171010, u8 *, 0x18FD) != 0) {
        M2C_FIELD(data_ov004_02171010, u8 *, 0x18FD) = 0U;
        return 0;
    }
    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0xA);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 7) {
        return 0;
    }
    func_ov004_021636b0(arg0, (_ZN16MenuObjectClass76GetRowEv(temp_r0) * 0x1C4) + (s32) (data_ov004_02171010 + 0xB01));
    return 0;
}
