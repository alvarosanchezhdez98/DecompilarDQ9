#include <m2c.h>

M2C_UNK func_0201155c(void *);
s32 func_020421a0();
M2C_UNK func_02043124(s32);
M2C_UNK func_02043204();
M2C_UNK func_0205e9f4(M2C_UNK *, M2C_UNK);
M2C_UNK func_0209ca70(M2C_UNK *, M2C_UNK);
s32 func_020aaf84(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_020aba5c(M2C_UNK);
s32 func_020ac864(M2C_UNK);
void *func_ov004_0216ae9c(void *, M2C_UNK);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;
extern M2C_UNK data_ov004_02171034;
void _ZN10MenuScript10StartEntryEi(void *, s32);
void _ZN16MenuObjectClass69SetUnk10cEss(void *, s16, s16);
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
u8 func_0205ea18(void *arg0);
u8 func_0209ca98(void *arg0);

s32 func_ov004_0216e490(void *arg0) {
    s32 temp_r4_2;
    void *temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    M2C_FIELD(&data_ov004_02171034, u8 *, 5) = 0U;
    if (func_020aaf84(M2C_FIELD(&data_ov004_02171034, s32 *, 0x10), 0, 1, 0) == 0) {
        func_0201155c(temp_r4);
        M2C_FIELD(&data_ov004_02171034, u8 *, 5) = 1U;
    } else {
        M2C_FIELD(&data_ov004_02171034, u8 *, 4) = func_0209ca98(&data_02109bf4);
        M2C_FIELD(&data_ov004_02171034, u8 *, 1) = func_0205ea18(&data_02108760);
        func_0209ca70(&data_02109bf4, 3);
        func_0205e9f4(&data_02108760, 3);
        if (func_020ac864(1) == 0) {
            M2C_FIELD(&data_ov004_02171034, u8 *, 5) = 1U;
        }
    }
    if (M2C_FIELD(&data_ov004_02171034, u8 *, 5) != 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
        return 0;
    }
    if (M2C_FIELD(&data_ov004_02171034, u8 *, 0) == 1) {
        if (func_020aba5c(1) == 0) {
            temp_r4_2 = func_020421a0();
            func_02043204();
            func_02043124(temp_r4_2);
            _ZN16MenuObjectClass69SetUnk10cEss(func_ov004_0216ae9c(arg0, 0xD4), 0, 7);
            _ZN10MenuScript10StartEntryEi(arg0, 0x1F5);
            return 0;
        }
        func_0200fb94(temp_r4, 5);
        M2C_FIELD(&data_ov004_02171034, s8 *, 2) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
        return 0;
    }
    return 0;
}
