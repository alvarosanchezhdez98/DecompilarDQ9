#include <m2c.h>

M2C_UNK func_020c9be0();
M2C_UNK func_020cd890();
s32 func_020cd908(void *);
M2C_UNK func_020cd99c(void *);
M2C_UNK func_0201289c();
M2C_UNK func_02012938(void *);
extern void *data_020fb3cc;

void func_0201282c(void *arg0) {
    data_020fb3cc = arg0;
    func_0201289c();
    M2C_FIELD(arg0, s8 *, 0x61) = 1;
    func_020cd890();
    if (func_020cd908(arg0 + 0x28) == 0) {
        func_020c9be0();
    }
    func_020cd99c(arg0 + 0x28);
    func_02012938(arg0);
    M2C_FIELD(arg0, s8 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s32 *, 0x68) = -1;
    M2C_FIELD(arg0, s32 *, 0x6C) = -1;
    M2C_FIELD(arg0, s8 *, 0x62) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = -1;
    M2C_FIELD(arg0, s32 *, 0x34) = -1;
}
