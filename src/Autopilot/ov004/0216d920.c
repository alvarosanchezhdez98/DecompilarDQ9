#include <m2c.h>

M2C_UNK func_02011544(void *);
M2C_UNK func_0203b4b0(s32, M2C_UNK);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_0203b520(s32, M2C_UNK);
M2C_UNK func_0205e8ec(M2C_UNK *);
M2C_UNK func_0205e9f4(M2C_UNK *, u8);
M2C_UNK func_0209c678(M2C_UNK *, M2C_UNK);
M2C_UNK func_0209ca70(M2C_UNK *, u8);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218d258(s32);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02109bf4;
extern M2C_UNK data_ov004_02171034;
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
u8 func_0200fb9c(void *arg0);
void func_02012010(void *arg0, s32 arg1);
void func_02012028(void *arg0, s8 arg1);
u8 func_02012034(void *arg0);
void func_0209c20c(void *arg0);

s32 func_ov004_0216d920(void) {
    s32 temp_r5;
    void *temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_ov017_0218b5b0();
    if (func_0200fb9c(temp_r4) != 2) {
        func_0209c678(&data_02109bf4, 0);
        func_0209c20c(&data_02109bf4);
        func_0205e8ec(&data_02108760);
    }
    func_0209ca70(&data_02109bf4, M2C_FIELD(&data_ov004_02171034, u8 *, 4));
    func_0205e9f4(&data_02108760, M2C_FIELD(&data_ov004_02171034, u8 *, 1));
    func_0203b4b0(temp_r5, -1);
    func_0203b4e8(temp_r5, -1);
    func_0203b520(temp_r5, -1);
    func_ov017_0218d258(temp_r5);
    func_02012010(temp_r4, 5);
    if ((M2C_FIELD(&data_ov004_02171034, u8 *, 2) == 1) && (M2C_FIELD(&data_ov004_02171034, u8 *, 3) != 4)) {
        func_0200fb94(temp_r4, 6);
        func_02012010(temp_r4, 2);
    }
    if (func_02012034(temp_r4) == 1) {
        func_0200fb94(temp_r4, 6);
        func_02012010(temp_r4, 0);
        func_02012028(temp_r4, 0);
    }
    if (M2C_FIELD(&data_ov004_02171034, u8 *, 5) != 0) {
        func_02011544(temp_r4);
        M2C_FIELD(&data_ov004_02171034, u8 *, 5) = 0U;
    }
    return 0;
}
