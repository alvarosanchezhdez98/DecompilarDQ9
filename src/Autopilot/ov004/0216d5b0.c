#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0204500c(void *, s32, M2C_UNK, M2C_UNK);
s32 func_02072a68(void *, s32);
s32 func_020abb64();
void * _ZN10MenuScript10GetObjectsEv(void *);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void * _ZN16MenuObjectClass48GetTextsEv(void *);
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
void func_02012028(void *arg0, s8 arg1);

s32 func_ov004_0216d5b0(void *arg0) {
    void *temp_r0;
    void *temp_r4;
    void *temp_r5;
    void *temp_r6;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x192);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 4) {
        return 0;
    }
    temp_r6 = _ZN16MenuObjectClass48GetTextsEv(temp_r0);
    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_020421a0();
    if (func_020abb64() == 0) {
        func_0204500c(temp_r4, func_02072a68(temp_r6, 0x5DD), 0, 0xE3);
        M2C_FIELD(temp_r4, s8 *, 0x19CA) = 0;
        M2C_FIELD(temp_r4, s8 *, 0x19AF) = 0;
        func_02012028(temp_r5, 0);
        return 0;
    }
    func_0204500c(temp_r4, func_02072a68(temp_r6, 0x4B1), 0, 0xE3);
    func_0200fb94(temp_r5, 7);
    func_02012028(temp_r5, 0);
    _ZN10MenuScript10StartEntryEi(arg0, 0x97);
    return 0;
}
