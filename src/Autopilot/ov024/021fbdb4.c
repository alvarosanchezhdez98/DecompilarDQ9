#include <m2c.h>

M2C_UNK func_ov024_021fd954(void *, M2C_UNK);
M2C_UNK func_ov024_021fdf04(void *, M2C_UNK);
s32 func_ov024_021fe698(void *, M2C_UNK);

void func_ov024_021fbdb4(void *arg0) {
    if (((u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x64C), s32 *, 8) << 0x16) >> 0x1E) == 1) {
        if (func_ov024_021fe698(arg0, 2) == 0) {
            return;
        }
        if (func_ov024_021fe698(arg0, 0xE) == 0) {
            return;
        }
        func_ov024_021fdf04(arg0, 0x12);
        return;
    }
    if (func_ov024_021fe698(arg0, 3) == 0) {
        return;
    }
    if (func_ov024_021fe698(arg0, 6) == 0) {
        return;
    }
    func_ov024_021fd954(arg0, 0x12);
}
