#include <m2c.h>

M2C_UNK func_0205e9f4(M2C_UNK *, M2C_UNK);
M2C_UNK func_0209ca70(M2C_UNK *, M2C_UNK);
M2C_UNK func_020aaf84(s32, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;
extern M2C_UNK data_ov004_02171034;
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
void func_02012010(void *arg0, s32 arg1);
void func_02012028(void *arg0, s8 arg1);
u8 func_0205ea18(void *arg0);
u8 func_0209ca98(void *arg0);

s32 func_ov004_0216d504(void *arg0) {
    void *temp_r0;

    func_020aaf84(M2C_FIELD(&data_ov004_02171034, s32 *, 0x10), 0, 0, 0);
    M2C_FIELD(&data_ov004_02171034, u8 *, 4) = func_0209ca98(&data_02109bf4);
    M2C_FIELD(&data_ov004_02171034, u8 *, 1) = func_0205ea18(&data_02108760);
    func_0209ca70(&data_02109bf4, 3);
    func_0205e9f4(&data_02108760, 3);
    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_02012028(temp_r0, 0);
    M2C_FIELD(temp_r0, s8 *, 0x7F71) = 0;
    func_0200fb94(temp_r0, 0);
    func_02012010(temp_r0, 5);
    _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
    return 0;
}
