#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s8 func_020100a8(s32);
void *func_02010828();
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_0207fe44(void *);
s16 func_02080468(void *, s16);
M2C_UNK func_0208203c(void *);
s32 func_ov003_021550dc(void *);
s32 func_ov003_02155208(void *);
M2C_UNK func_ov003_02155580(void *, M2C_UNK);
s32 func_ov003_02155618(void *);
s32 func_ov003_02155f88(void *, s8);
s32 func_ov003_02155fc0(void *, s8);
M2C_UNK func_ov003_02158334(void *);
extern M2C_UNK data_02108760;

void func_ov003_02156d40(void *arg0) {
    s32 temp_r0_2;
    s32 temp_r6;
    u8 temp_r0_3;
    u8 temp_r1;
    void *temp_r0;
    void *temp_r4;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r0 = func_02010828();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x1F9);
    temp_r4 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_r1 == 0) {
        func_ov003_02155580(arg0, 0);
        M2C_FIELD(arg0, u8 *, 0x1F9) = (u8) (M2C_FIELD(arg0, u8 *, 0x1F9) + 1);
        return;
    }
    if (temp_r1 == 1) {
        temp_r0_2 = func_ov003_02155618(arg0);
        if (temp_r0_2 != -1) {
            if (temp_r0_2 != 1) {
                return;
            }
            if (M2C_FIELD(arg0, u8 *, 0x1FB) == 0) {
                M2C_FIELD(arg0, s8 *, 0x1F7) = func_020100a8(temp_r6);
                M2C_FIELD(arg0, u8 *, 0x1F9) = 0U;
                if (func_ov003_02155f88(arg0, M2C_FIELD(arg0, s8 *, 0x1F7)) != 0) {
                    M2C_FIELD(arg0, s16 *, 0x1EC) = 8;
                    M2C_FIELD(arg0, s8 *, 0x1F8) = 7;
                    func_0207fe44(temp_r4);
                    return;
                }
                M2C_FIELD(arg0, s32 *, 0x1FC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1FC) | 2);
                M2C_FIELD(arg0, s16 *, 0x1EC) = 9;
                M2C_FIELD(arg0, s8 *, 0x1F8) = 3;
                M2C_FIELD(arg0, u8 *, 0x1F9) = 0U;
                return;
            }
            M2C_FIELD(arg0, s8 *, 0x1F7) = (s8) M2C_FIELD(arg0, u8 *, 0x1F2);
            M2C_FIELD(arg0, s16 *, 0x1EC) = 6;
            M2C_FIELD(arg0, s8 *, 0x1F8) = 2;
            M2C_FIELD(arg0, u8 *, 0x1F9) = (u8) (M2C_FIELD(arg0, u8 *, 0x1F9) + 1);
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x1EC) = 3;
        M2C_FIELD(arg0, s8 *, 0x1F8) = 7;
        return;
    }
    if (temp_r1 == 2) {
        M2C_FIELD(arg0, s16 *, 0x1E6) = 3;
        temp_r0_3 = M2C_FIELD(temp_r0, u8 *, 0xF7C);
        if (temp_r0_3 != 3) {
            if (temp_r0_3 == 4) {
                M2C_FIELD(arg0, s16 *, 0x1E6) = 5;
            }
        } else {
            M2C_FIELD(arg0, s16 *, 0x1E6) = 4;
        }
        if ((s32) M2C_FIELD(arg0, s16 *, 0x1E2) < 0) {
            M2C_FIELD(arg0, s16 *, 0x1E2) = func_02080468(temp_r4, M2C_FIELD(arg0, s16 *, 0x1E6));
            M2C_FIELD(arg0, s16 *, 0x1E8) = (s16) M2C_FIELD(arg0, s16 *, 0x1E2);
        }
        M2C_FIELD(temp_r4, s16 *, 0x36) = (s16) M2C_FIELD(arg0, s16 *, 0x1E2);
        func_ov003_02158334(arg0);
        func_0208203c(arg0 + 0x80);
        M2C_FIELD(arg0, void **, 8) = NULL;
        M2C_FIELD(arg0, u8 *, 0x1F9) = (u8) (M2C_FIELD(arg0, u8 *, 0x1F9) + 1);
        return;
    }
    if (temp_r1 != 3) {
        return;
    }
    M2C_FIELD(arg0, void **, 8) = (void *) (arg0 + 0x1E2);
    if (func_ov003_021550dc(arg0) != 0) {
        func_0205eaa0(&data_02108760, 1, 0);
        func_0208203c(arg0 + 0x80);
        M2C_FIELD(arg0, void **, 8) = NULL;
        M2C_FIELD(arg0, s8 *, 0x1F7) = (s8) M2C_FIELD((arg0 + (s16) (M2C_FIELD(arg0, s16 *, 0x1E2) - func_02080468(temp_r4, M2C_FIELD(arg0, s16 *, 0x1E6)))), u8 *, 0x1F2);
        if (func_ov003_02155fc0(arg0, M2C_FIELD(arg0, s8 *, 0x1F7)) != 0) {
            M2C_FIELD(arg0, s16 *, 0x1EC) = 0x31;
            M2C_FIELD(arg0, s8 *, 0x1F8) = 7;
            func_0207fe44(temp_r4);
            return;
        }
        if (func_ov003_02155f88(arg0, M2C_FIELD(arg0, s8 *, 0x1F7)) != 0) {
            M2C_FIELD(arg0, s16 *, 0x1EC) = 8;
            M2C_FIELD(arg0, s8 *, 0x1F8) = 7;
            func_0207fe44(temp_r4);
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x1FC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1FC) | 2);
        M2C_FIELD(arg0, s16 *, 0x1EC) = 9;
        M2C_FIELD(arg0, s8 *, 0x1F8) = 3;
        M2C_FIELD(arg0, u8 *, 0x1F9) = 0U;
        func_0207fe44(temp_r4);
        return;
    }
    if (func_ov003_02155208(arg0) == 0) {
        return;
    }
    M2C_FIELD(arg0, void **, 8) = NULL;
    M2C_FIELD(arg0, s16 *, 0x1EC) = 7;
    M2C_FIELD(arg0, s8 *, 0x1F8) = 7;
    func_0207fe44(temp_r4);
}
