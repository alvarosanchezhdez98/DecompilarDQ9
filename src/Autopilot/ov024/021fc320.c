#include <m2c.h>

M2C_UNK func_ov024_021fd954(void *, M2C_UNK);
s32 func_ov024_021fe698(void *, M2C_UNK);

void func_ov024_021fc320(void *arg0) {
    if ((((u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x64C), s32 *, 8) << 0x16) >> 0x1E) != 1) && (M2C_FIELD(arg0, u8 *, 0x6E) != 0)) {
        if (func_ov024_021fe698(arg0, 0xB) == 0) {
            return;
        }
        func_ov024_021fd954(arg0, 0x17);
    }
}
