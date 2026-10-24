#include <m2c.h>

s32 _ZN10MenuScript10GetObjectsEv();
s32 _ZN14MenuObjectList4FindEi(s32, M2C_UNK);
s32 _ZN15MenuObjectClass7GetTypeEv();
M2C_UNK _ZN16MenuObjectClass710MoveCursorEP10MenuScript(s32, M2C_UNK);
M2C_UNK _ZN16MenuObjectClass76SetRowEt(s32, u16);

void func_ov004_0216b338(M2C_UNK arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(), arg1);
    if (temp_r0 == 0) {
        return;
    }
    if (_ZN15MenuObjectClass7GetTypeEv() != 7) {
        return;
    }
    if (temp_r0 == 0) {
        return;
    }
    _ZN16MenuObjectClass76SetRowEt(temp_r0, arg2);
    _ZN16MenuObjectClass710MoveCursorEP10MenuScript(temp_r0, arg0);
}
