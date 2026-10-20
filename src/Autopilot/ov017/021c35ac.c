#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState14GetProtagonistEv(s32);
s32 func_0202ae18();
s32 func_0202ae24();
s32 func_0202b000(s32);
M2C_UNK func_0202b2f0(s32);
M2C_UNK func_0202b7ec(s32);
M2C_UNK func_0202b828(s32);
M2C_UNK func_0202c288(s32);
M2C_UNK func_0202c360(s32, s32);
M2C_UNK func_0202c778(s32);
M2C_UNK func_0203b4b0(s32, M2C_UNK);
M2C_UNK func_02053c6c();
M2C_UNK func_0205e22c(s32);
M2C_UNK func_020d84dc();
s32 func_020e2ff8();
M2C_UNK func_020e3004(s32);
s32 func_020e3580();
M2C_UNK func_020e358c(s32);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_02191108(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_ov017_02191234(s32);
M2C_UNK func_ov017_02195520(s32);
M2C_UNK func_ov017_02195748(s32);
M2C_UNK func_ov017_021972cc(s32);
M2C_UNK func_ov017_021c37a4();

void func_ov017_021c35ac(void) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r9;
    void *temp_r4_2;

    temp_r9 = _ZN9GameState11GetInstanceEv();
    temp_r8 = func_ov017_0218b5b0();
    temp_r7 = func_0202ae18();
    temp_r6 = func_0202ae24();
    temp_r5 = func_020e2ff8();
    temp_r4 = func_020e3580();
    if (func_0202b000(temp_r7) != 0) {
        func_ov017_021c37a4();
        return;
    }
    func_0202c778(temp_r7);
    func_0202b7ec(temp_r7);
    func_0205e22c(temp_r6);
    func_020e3004(temp_r5);
    func_020e358c(temp_r4);
    func_ov017_02195748(temp_r8);
    temp_r4_2 = _ZN9GameState14GetProtagonistEv(temp_r9);
    func_02053c6c();
    func_0202c360(temp_r7, M2C_FIELD(temp_r4_2, s32 *, 0x134));
    func_0202b2f0(temp_r7);
    func_0202b828(temp_r7);
    func_0203b4b0(temp_r8, 2);
    func_020d84dc();
    func_ov017_02191108(temp_r8, 1, 1, 1, 1);
    func_ov017_02191234(temp_r8);
    func_0202c288(temp_r7);
    func_ov017_021972cc(temp_r8);
    func_ov017_02195520(temp_r8);
}
