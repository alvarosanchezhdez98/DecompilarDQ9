#include <m2c.h>

void *_Z14GetMenuObject7P10MenuScriptt(void *, M2C_UNK);
s32 func_0204c7e0(void *);
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
void *func_ov004_02168aa0(void *, M2C_UNK);
M2C_UNK func_ov004_02169658(void *);
extern M2C_UNK data_02108760;
extern void *data_ov004_02171030;
void * _ZN10MenuScript10GetObjectsEv(void *);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN10MenuScript8FindHeapEi(void *, s32);
void _ZN10MenuScript9SetUnk1b0Et(void *, u16);
void _ZN13SafeAllocator5ResetEv(void *);
void _ZN14MenuObjectList10RemoveHeapEi(void *, s32);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass110SetPaletteEa(void *, s8);
void _ZN16MenuObjectClass65ClearEv(void *);
void _ZN16MenuObjectClass710ClearItemsEv(void *);

s32 func_ov004_021698f4(void *arg0) {
    s32 var_r5;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;
    void *var_r4;

    var_r5 = 0;
    temp_r0 = func_ov004_02168aa0(arg0, 0x1F);
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r0_2 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x15);
    var_r4 = temp_r0_2;
    if ((var_r4 == NULL) || (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 6)) {
        var_r4 = NULL;
    }
    if (var_r4 != NULL) {
        temp_r0_3 = var_r4 + 0x20;
        if ((temp_r0_3 != NULL) && (func_0204c7e0(temp_r0_3) != 0)) {
            _ZN16MenuObjectClass65ClearEv(var_r4);
            temp_r0_4 = _ZN10MenuScript8FindHeapEi(arg0, 2);
            if (temp_r0_4 != NULL) {
                _ZN14MenuObjectList10RemoveHeapEi(_ZN10MenuScript10GetObjectsEv(arg0), 2);
                _ZN13SafeAllocator5ResetEv(temp_r0_4 + 4);
            }
            _ZN10MenuScript9SetUnk1b0Et(arg0, 0U);
            temp_r0_5 = _Z14GetMenuObject7P10MenuScriptt(arg0, 0x64);
            if (temp_r0_5 != NULL) {
                _ZN16MenuObjectClass710ClearItemsEv(temp_r0_5);
                var_r5 = 1;
            }
        }
    }
    _ZN16MenuObjectClass110SetPaletteEa(temp_r0, 2);
    func_ov004_02169658(arg0);
    _ZN10MenuScript10StartEntryEi(arg0, 0x53);
    if (var_r5 != 0) {
        _ZN10MenuScript9SetUnk1b0Et(arg0, 0x64U);
    }
    if (M2C_FIELD(data_ov004_02171030, u8 *, 0x1A0) != 0) {
        func_0205eaa0(&data_02108760, 1, 0);
    }
    M2C_FIELD(data_ov004_02171030, u8 *, 0x1A0) = 0U;
    return 0;
}
