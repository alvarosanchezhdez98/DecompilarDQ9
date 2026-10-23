#include <m2c.h>

void **func_ov004_02156f38(void *, s32);
void *func_ov004_02156f6c(void *, M2C_UNK);
extern M2C_UNK data_ov004_021707d8;
void _ZN16MenuObjectClass67RefreshEP10MenuScript(void *, void *);

s32 func_ov004_0215c684(void *arg0) {
    void **temp_r0;
    void *temp_r0_2;

    if ((u32) M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x6E) > 1U) {
        M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x6E) = 1U;
        temp_r0 = func_ov004_02156f38(arg0, 0x25A);
        if (temp_r0 != NULL) {
            M2C_FIELD(*temp_r0, M2C_UNK (**)(void **, u8), 0xE0)(temp_r0, M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x6E));
        }
        temp_r0_2 = func_ov004_02156f6c(arg0, 0x19);
        if (temp_r0_2 != NULL) {
            _ZN16MenuObjectClass67RefreshEP10MenuScript(temp_r0_2, arg0);
        }
    }
    return 0;
}
