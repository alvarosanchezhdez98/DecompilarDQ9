#include <m2c.h>


u16 func_02012354(void) {
    return (u16) (((*(u16 *)0x04000130 | *(u16 *)0x027FFFA8) ^ 0x2FFF) & 0x2FFF);
}
