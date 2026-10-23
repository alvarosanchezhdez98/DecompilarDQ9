#include <m2c.h>

M2C_UNK func_0202e08c(void *, M2C_UNK);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020a0d58(void *);
M2C_UNK func_020a2718(void *);
M2C_UNK func_020a2ca0(void *);
M2C_UNK func_020a2cf0();

void func_020a2010(void *arg0) {
    func_020a2cf0();
    func_0202e08c(arg0, 4);
    M2C_FIELD(arg0, s32 *, 0x220) = 0;
    M2C_FIELD(arg0, s32 *, 0x224) = 0x6000;
    M2C_FIELD(arg0, s32 *, 0x228) = 0xB000;
    M2C_FIELD(arg0, s16 *, 0x21C) = -1;
    M2C_FIELD(arg0, s32 *, 0x22C) = 0;
    M2C_FIELD(arg0, s32 *, 0x230) = 0;
    M2C_FIELD(arg0, s32 *, 0x234) = 0;
    M2C_FIELD(arg0, s32 *, 0x238) = 1;
    M2C_FIELD(arg0, s32 *, 0x23C) = 1;
    M2C_FIELD(arg0, s32 *, 0x240) = 1;
    M2C_FIELD(arg0, s8 *, 0x244) = 0;
    M2C_FIELD(arg0, s8 *, 0x245) = 0;
    M2C_FIELD(arg0, s16 *, 0x246) = 0;
    func_020a0d58(arg0 + 0x248);
    M2C_FIELD(arg0, s8 *, 0x270) = -1;
    M2C_FIELD(arg0, s32 *, 0x274) = 0;
    M2C_FIELD(arg0, s32 *, 0x278) = 0;
    M2C_FIELD(arg0, s32 *, 0x27C) = 0;
    M2C_FIELD(arg0, s32 *, 0x280) = 0;
    M2C_FIELD(arg0, s32 *, 0x284) = 0;
    M2C_FIELD(arg0, s32 *, 0x288) = 0;
    M2C_FIELD(arg0, s32 *, 0x28C) = 0;
    M2C_FIELD(arg0, s32 *, 0x290) = 0;
    M2C_FIELD(arg0, s32 *, 0x294) = 0;
    memset(arg0 + 0x298, 0, 0x2C);
    M2C_FIELD(arg0, s16 *, 0x21E) = 0;
    func_020a2ca0(arg0);
    func_020a2718(arg0);
}
