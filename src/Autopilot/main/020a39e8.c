#include <m2c.h>

M2C_UNK _ZN13SafeAllocator4FreeEPv(M2C_UNK, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState26GetTreasureMapLanguageDataEv(s32);
M2C_UNK _ZN9GameState29SetTreasureMapLanguageDataPtrEPh(s32, M2C_UNK);
void *func_ov017_0218b5b0();

void func_020a39d8(M2C_UNK arg0) {
    s32 temp_r4;
    s32 temp_r6;
    void *temp_r5;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_ov017_0218b5b0();
    temp_r4 = _ZN9GameState26GetTreasureMapLanguageDataEv(temp_r6);
    _ZN13SafeAllocator4FreeEPv(arg0, M2C_FIELD(temp_r5, s32 *, 0x448C));
    _ZN13SafeAllocator4FreeEPv(arg0, temp_r4);
    _ZN9GameState29SetTreasureMapLanguageDataPtrEPh(temp_r6, 0);
    M2C_FIELD(temp_r5, s32 *, 0x448C) = 0;
}
