#include <m2c.h>

void *_ZN9GameState21GetPartyMemberByIndexEi(M2C_UNK, M2C_UNK);

u32 func_02068558(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(arg0, 0);
    if (temp_r0 != NULL) {
        return (u32) (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x150), u8 *, 0x49C) << 0x1F) >> 0x1F;
    }
    return 0U;
}
