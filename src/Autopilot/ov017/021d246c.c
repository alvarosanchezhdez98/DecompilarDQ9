#include <m2c.h>

void *_ZN9GameState20GetUnknownGameObjectEv(M2C_UNK);

void func_ov017_021d246c(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    void *temp_r1;

    if (*M2C_FIELD(_ZN9GameState20GetUnknownGameObjectEv(arg2), s32 **, 0x130) & 1) {
        temp_r1 = M2C_FIELD(arg3, void **, 0x3B0C);
        if (temp_r1 != NULL) {
            M2C_FIELD(temp_r1, s32 *, 0x60) = (s32) M2C_FIELD(arg1, s32 *, 4);
        }
    }
}
