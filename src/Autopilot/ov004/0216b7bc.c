#include <m2c.h>

void *func_ov004_0216ae9c();
extern M2C_UNK data_ov004_02171034;
void _ZN10MenuScript9SetUnk1c8Ev(void *);
void _ZN16MenuObjectClass65ClearEv(void *);
void _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(void *, void *, s32, s16, s16, s16, s32, u8, u8, u8);
void _ZN16MenuObjectClass69SetUnk10cEss(void *, s16, s16);

s32 func_ov004_0216b7bc(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r5;
    void *temp_r0;

    var_r5 = arg2;
    temp_r0 = func_ov004_0216ae9c();
    _ZN16MenuObjectClass65ClearEv(temp_r0);
    switch (arg1) {                                 /* irregular */
    case 0xD4:
        if ((M2C_FIELD(&data_ov004_02171034, u8 *, 3) != 0) && (arg3 != 1)) {

        } else {
            _ZN16MenuObjectClass69SetUnk10cEss(temp_r0, 0, 6);
        }
        _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0, 0x10, 0x20, 8, 0U, 1U, 0U);
        var_r5 += 0x2800;
        break;
    case 0xD3:
        if (M2C_FIELD(&data_ov004_02171034, u8 *, 3) == 4) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0x19, 0xA, 7, 5, 0U, 1U, 0U);
            var_r5 += 0x460;
        } else if (M2C_FIELD(&data_ov004_02171034, u8 *, 2) == 0) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0x19, 0xB, 7, 5, 0U, 1U, 0U);
            var_r5 += 0x460;
        } else if (M2C_FIELD(&data_ov004_02171034, u8 *, 2) == 1) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 8, 0xA, 0x18, 5, 0U, 1U, 0U);
            var_r5 += 0xF00;
        }
        break;
    case 0x3E8:
        if (M2C_FIELD(&data_ov004_02171034, u8 *, 3) == 4) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0x19, 0xA, 7, 5, 0U, 1U, 0U);
            var_r5 += 0x460;
        } else if (M2C_FIELD(&data_ov004_02171034, u8 *, 2) == 0) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0x19, 0xB, 7, 5, 0U, 1U, 0U);
            var_r5 += 0x460;
        } else if (M2C_FIELD(&data_ov004_02171034, u8 *, 2) == 1) {
            _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(temp_r0, arg0, var_r5, 0xC, 0xB, 0x14, 4, 0U, 1U, 0U);
            var_r5 += 0xA00;
        }
        break;
    }
    _ZN10MenuScript9SetUnk1c8Ev(arg0);
    return var_r5;
}
