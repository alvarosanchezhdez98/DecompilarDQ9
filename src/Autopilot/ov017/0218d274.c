#include <m2c.h>

M2C_UNK MapVRAMBanksToTextureImage(M2C_UNK);
M2C_UNK func_020bb48c(M2C_UNK, M2C_UNK);
M2C_UNK func_020bb780(M2C_UNK, M2C_UNK);
void * _ZN9GameState11GetInstanceEv(void);
u8 func_0200fb9c(void *arg0);

void func_ov017_0218d274(void) {
    if (func_0200fb9c(_ZN9GameState11GetInstanceEv()) == 6) {
        MapVRAMBanksToTextureImage(3);
        func_020bb48c(2, 1);
    } else {
        MapVRAMBanksToTextureImage(0xF);
        func_020bb48c(4, 1);
    }
    func_020bb780(0x4000, 1);
}
