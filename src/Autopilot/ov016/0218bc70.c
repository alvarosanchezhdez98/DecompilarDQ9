#include <m2c.h>


void func_ov016_0218bc70(s32 arg0) {
    *(u16 *)0x04000304 = (*(u16 *)0x04000304 & ~0x8000) | (arg0 << 0xF);
}
