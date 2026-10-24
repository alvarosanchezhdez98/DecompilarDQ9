#include <m2c.h>

s32 func_02012fe4();
s32 func_0202ae24();
u32 func_0202c1a4(s32);
u32 func_0205e804(s32, M2C_UNK);
M2C_UNK func_02098efc(s32, u16, void *, u32);

u32 func_ov017_021d3dcc(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r0_3;
    u32 temp_r0;
    u32 temp_r0_2;

    temp_r0_2 = func_0202c1a4(arg4);
    if (temp_r0_2 != ((u32) (M2C_FIELD(arg1, u8 *, 0x11) << 0x19) >> 0x1D)) {
        return temp_r0_2;
    }
    temp_r0_3 = func_02012fe4();
    func_02098efc(temp_r0_3 + 0x840, M2C_FIELD(arg1, u16 *, 0x12), arg1 + 4, (u32) (M2C_FIELD(arg1, u8 *, 0x11) << 0x1C) >> 0x1C);
    temp_r0 = (u32) (M2C_FIELD(arg1, u8 *, 0x11) << 0x18) >> 0x1F;
    if (temp_r0 == 0) {
        return temp_r0;
    }
    M2C_FIELD((temp_r0_3 + 0x1840), s8 *, 0xB62) = 1;
    return func_0205e804(func_0202ae24(), 0xB9);
}
