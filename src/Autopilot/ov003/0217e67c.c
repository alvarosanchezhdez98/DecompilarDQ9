#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
M2C_UNK _ZN17CharacterCreation6FinishEv();
M2C_UNK func_020a1f4c(M2C_UNK);

void func_ov003_0217e67c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        _ZN17CharacterCreation6FinishEv();
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        func_020a1f4c(1);
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 8);
}
