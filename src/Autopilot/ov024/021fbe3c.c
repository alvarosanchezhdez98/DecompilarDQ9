#include <m2c.h>

M2C_UNK func_ov024_021fd954(void *, M2C_UNK);
M2C_UNK func_ov024_021fdf04(void *, M2C_UNK);
s32 func_ov024_021fe698(void *arg0, s32 arg1);

void func_ov024_021fbe3c(void *arg0) {
    if (((u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x64C), s32 *, 8) << 0x16) >> 0x1E) == 1) {
        if (func_ov024_021fe698(arg0, 3) == 0) {
            return;
        }
        if (func_ov024_021fe698(arg0, 0xF) == 0) {
            return;
        }
        func_ov024_021fdf04(arg0, 0x13);
        return;
    }
    if (func_ov024_021fe698(arg0, 3) == 0) {
        return;
    }
    if (func_ov024_021fe698(arg0, 7) == 0) {
        return;
    }
    func_ov024_021fd954(arg0, 0x13);
}
