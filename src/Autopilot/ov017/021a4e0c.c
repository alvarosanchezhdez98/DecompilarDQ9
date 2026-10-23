#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *_ZN9GameState20GetUnknownGameObjectEv();
M2C_UNK func_ov017_021c12fc(void *, M2C_UNK, M2C_UNK);

void func_ov017_021a4e0c(void *arg0) {
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN9GameState20GetUnknownGameObjectEv();
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x371C), s16 *, 0x22) = (s16) M2C_FIELD(temp_r0, s16 *, 4);
    func_ov017_021c12fc(arg0, 1, 1);
}
