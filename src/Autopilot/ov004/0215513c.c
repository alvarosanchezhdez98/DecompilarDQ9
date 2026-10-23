#include <m2c.h>

void *_Z22GetMenuObject7SelectedP10MenuScriptt(M2C_UNK, M2C_UNK);
s32 _ZN15MenuObjectClass5GetIdEv(void *);

void func_ov004_0215513c(M2C_UNK arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    s16 temp_r3;
    s32 temp_r0_2;
    void *temp_r0;

    *arg3 = -1;
    temp_r3 = *arg3;
    *arg2 = temp_r3;
    *arg1 = temp_r3;
    temp_r0 = _Z22GetMenuObject7SelectedP10MenuScriptt(arg0, 5);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r0_2 = _ZN15MenuObjectClass5GetIdEv(temp_r0);
    switch (temp_r0_2) {                            /* irregular */
    case 28:
        *arg2 = 9;
        return;
    case 26:
        *arg1 = 0;
        return;
    case 27:
        *arg2 = 8;
        return;
    }
}
