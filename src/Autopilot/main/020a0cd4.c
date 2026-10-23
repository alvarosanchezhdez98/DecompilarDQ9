#include <m2c.h>

M2C_UNK _Z27NitroHandle_FindBySignaturePKci(M2C_UNK *, M2C_UNK);
M2C_UNK _Z29NitroHandle_ReleaseFileTablesP11NitroHandle();
M2C_UNK _ZN16BackgroundLoader10RemoveLockEv(s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader13MaybeWaitIdleEv();
M2C_UNK func_02012da4(M2C_UNK *, s32);
u32 func_02012dd0(M2C_UNK *);
extern M2C_UNK data_020f18e8;
extern s32 data_02109d90;
extern M2C_UNK data_02114e20;

s32 func_020a0cc4(s32 arg0) {
    s32 temp_r0;

    if (((arg0 < 0) || (func_02012dd0(&data_02114e20) < (u32) arg0)) && (data_02109d90 != 0)) {
        temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
        if (temp_r0 != 0) {
            _ZN16BackgroundLoader13MaybeWaitIdleEv();
        }
        _Z27NitroHandle_FindBySignaturePKci(&data_020f18e8, 3);
        _Z29NitroHandle_ReleaseFileTablesP11NitroHandle();
        func_02012da4(&data_02114e20, data_02109d90);
        data_02109d90 = 0;
        if (temp_r0 != 0) {
            _ZN16BackgroundLoader10RemoveLockEv(temp_r0);
        }
        return 1;
    }
    return 0;
}
