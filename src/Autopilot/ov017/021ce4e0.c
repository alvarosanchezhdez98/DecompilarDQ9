#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
u16 *func_02012fe4();
M2C_UNK func_0202ae18();
s32 func_0202c540();
M2C_UNK func_ov017_021ce400(u8, u16);

void func_ov017_021ce4e0(void) {
    void *temp_r0;

    func_0202ae18();
    if (func_0202c540() != 0) {
        return;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_02010828();
    if (M2C_FIELD(temp_r0, u8 *, 0xF7D) == 0) {
        return;
    }
    func_ov017_021ce400(M2C_FIELD(temp_r0, u8 *, 0xF7D), *func_02012fe4());
}
