#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
M2C_UNK func_020397c0();
M2C_UNK func_020397cc(s32, M2C_UNK);
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_02046b24(s32);
s32 func_020d6c00();
M2C_UNK func_ov017_02199780(void *);

void func_ov017_02199e98(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;

    if (M2C_FIELD(arg0, s32 *, 0x4080) == 0) {
        return;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r4 = _ZN9GameState20GetUnknownGameObjectEv();
    func_020397c0();
    func_020466f4(func_020d6c00(), 0x400);
    func_ov017_02199780(arg0);
    temp_r0 = func_02046b24(M2C_FIELD(arg0, s32 *, 0x36FC));
    if ((temp_r0 != 0xA) && (temp_r0 != 4) && (temp_r0 != 3) && (temp_r0 != 0x21) && (temp_r0 != 0x24)) {
        return;
    }
    func_020397cc(temp_r4, 1);
}
