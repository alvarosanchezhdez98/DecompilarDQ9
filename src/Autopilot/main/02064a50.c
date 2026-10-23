#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState14GetProtagonistEv();
void *func_02053ccc();
M2C_UNK func_020649b0(void *, M2C_UNK, void *);

void func_02064a40(void *arg0, void *arg1) {
    s8 temp_r1;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    _ZN9GameState14GetProtagonistEv();
    temp_r0 = func_02053ccc();
    if (temp_r0 != NULL) {
        if (M2C_FIELD(temp_r0, s32 *, 4) == 3) {
            M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_r0, u8 *, 0x2C);
        }
    } else {
        temp_r1 = M2C_FIELD(arg0, s8 *, 0x491);
        if ((s32) temp_r1 > -1) {
            M2C_FIELD(arg1, s32 *, 4) = (s32) temp_r1;
        }
    }
    func_020649b0(arg0, 9, arg1);
}
