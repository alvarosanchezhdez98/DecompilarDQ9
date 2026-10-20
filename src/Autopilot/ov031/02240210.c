#include <m2c.h>

void *ov38_02221EE0();
M2C_UNK ov38_02222B98();
extern M2C_UNK (*data_ov031_02290fc8)(void *);
extern void **data_ov031_02290fdc;

s32 ov38_02221F38(void) {
    M2C_UNK (*temp_r5)(M2C_UNK, s32, s32);
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r5;
    void *temp_r0;
    void *temp_r0_2;

    var_r5 = 0;
    temp_r0 = ov38_02221EE0();
    if (temp_r0 != NULL) {
        if (data_ov031_02290fdc != *data_ov031_02290fdc) {
            M2C_FIELD(M2C_FIELD(temp_r0, void **, 0), void ***, 4) = (void **) M2C_FIELD(temp_r0, void ***, 4);
            *M2C_FIELD(temp_r0, void ***, 4) = M2C_FIELD(temp_r0, void **, 0);
            if (data_ov031_02290fdc == temp_r0) {
                data_ov031_02290fdc = M2C_FIELD(temp_r0, void ***, 4);
            }
        } else {
            data_ov031_02290fdc = NULL;
        }
        temp_r0_2 = M2C_FIELD(temp_r0, void **, 0xC);
        temp_r5 = M2C_FIELD(temp_r0_2, M2C_UNK (**)(M2C_UNK, s32, s32), 0x3C);
        temp_r6 = M2C_FIELD(temp_r0_2, s32 *, 0x30);
        temp_r7 = M2C_FIELD(temp_r0_2, s32 *, 0x2C);
        ov38_02222B98();
        data_ov031_02290fc8(temp_r0);
        temp_r5(8, temp_r6, temp_r7);
        var_r5 = 1;
    }
    return var_r5;
}
