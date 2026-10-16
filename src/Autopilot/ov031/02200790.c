#include <m2c.h>


s32 is_multicast(s32 arg0) {
    if ((arg0 & 0xF0000000) == 0xE0000000) {
        return 1;
    }
    return 0;
}
