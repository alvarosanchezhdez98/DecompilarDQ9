#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState12GetTickCountEv(s32);
M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205a42c(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0205ae8c(void *);
M2C_UNK func_0208be8c();

void func_ov017_021bb930(void *arg0) {
    s32 temp_r5;
    s32 temp_r6;
    void *temp_r0;
    void *temp_r0_2;

    if ((M2C_FIELD(arg0, u8 *, 0xFE) != 0) && (M2C_FIELD(arg0, void **, 0x168) != NULL)) {
        temp_r5 = _ZN9GameState11GetInstanceEv();
        temp_r6 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x168), s32 *, 0x3C);
        if (temp_r6 != 0) {
            func_0205a370(temp_r6, 1);
            temp_r0 = func_0205a3d0(temp_r6, 1);
            if (temp_r0 != NULL) {
                M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x15) | 8);
            }
            func_0205a330(temp_r6, _ZNK9GameState12GetTickCountEv(temp_r5));
            temp_r0_2 = func_0205a3d0(temp_r6, 1);
            if (temp_r0_2 != NULL) {
                M2C_FIELD(temp_r0_2, s16 *, 4) = 0xD8;
                M2C_FIELD(temp_r0_2, s16 *, 6) = 0x98;
            }
            func_0205a42c(temp_r6, 1, 6);
        }
        func_0205ae8c(M2C_FIELD(arg0, void **, 0x168));
    }
    if (M2C_FIELD(arg0, s32 *, 0x120) == 0) {
        return;
    }
    func_0208be8c();
}
