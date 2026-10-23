#include <m2c.h>

M2C_UNK func_0208bb78(void *, u32);
void * _ZN9GameState11GetInstanceEv(void);
u32 _ZNK9GameState12GetTickCountEv(void *);

void func_ov004_021678d8(void *arg0) {
    u32 var_r1;

    if (M2C_FIELD(arg0, u8 *, 0xC) & 0x10) {
        return;
    }
    var_r1 = _ZNK9GameState12GetTickCountEv(_ZN9GameState11GetInstanceEv());
    if (var_r1 == 0) {
        var_r1 = 1;
    }
    func_0208bb78(arg0 + 0x34, var_r1);
}
