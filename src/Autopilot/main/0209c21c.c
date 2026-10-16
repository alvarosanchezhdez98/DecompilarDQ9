#include <m2c.h>

M2C_UNK func_0203aa44(void *);
M2C_UNK func_0203ad88(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020bbd9c();
M2C_UNK func_020bc078(void *);
M2C_UNK func_0209c2e0(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0209c678(void *, M2C_UNK);

void func_0209c20c(void *arg0) {
    func_0203ad88(arg0, 0, 0);
    func_0209c678(arg0, 0);
    func_020bbd9c();
    func_0203aa44(arg0);
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    M2C_FIELD(arg0, s16 *, 0xB8) = -1;
    func_020bc078(arg0 + 0xBC);
    M2C_FIELD(arg0, s16 *, 0xBA) = -1;
    func_020bc078(arg0 + 0xC0);
    func_0209c2e0(arg0, 0x7F, 0);
}
