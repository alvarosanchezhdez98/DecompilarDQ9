#include <m2c.h>

void *func_020421a0();
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void * _ZN16MenuObjectClassA11GetRendererEv(void *);
void * _ZN9GameState11GetInstanceEv(void);
void func_02012028(void *arg0, s8 arg1);

s32 func_ov004_0216e828(void *arg0) {
    s32 temp_r0_3;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r4;
    void *temp_r5;

    temp_r4 = _ZN10MenuScript10GetObjectsEv(arg0);
    temp_r5 = func_020421a0();
    temp_r0 = _ZN14MenuObjectList4FindEi(temp_r4, 0xA);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 0xA) {
        return 0;
    }
    temp_r0_2 = _ZN16MenuObjectClassA11GetRendererEv(temp_r0);
    if (temp_r0_2 != NULL) {
        M2C_FIELD(temp_r5, void **, 0x2D8) = temp_r0_2;
        temp_r0_3 = M2C_FIELD(temp_r0_2, s32 *, 0x3C);
        if (temp_r0_3 != 0) {
            M2C_FIELD(temp_r5, s32 *, 0x2E0) = temp_r0_3;
        }
    }
    func_02012028(_ZN9GameState11GetInstanceEv(), 0);
    return 0;
}
