#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader20MaybeFreeAllocationsEv();
s32 func_0209ca2c(M2C_UNK *);
extern M2C_UNK data_02109bf4;

void func_ov003_0215c510(void *arg0) {
    s32 temp_r4;

    if ((func_0209ca2c(&data_02109bf4) == 0) && (M2C_FIELD(arg0, u8 *, 0x59D) == 0)) {
        temp_r4 = _ZN16BackgroundLoader11GetInstanceEv();
        _ZN16BackgroundLoader20MaybeFreeAllocationsEv();
        _ZN16BackgroundLoader10RemoveTaskEi(temp_r4, M2C_FIELD(arg0, s32 *, 0x578));
        M2C_FIELD(arg0, s32 *, 0x578) = -1;
        M2C_FIELD(arg0, s8 *, 0x588) = 0xB;
        M2C_FIELD(arg0, s8 *, 0x580) = 0;
    }
}
