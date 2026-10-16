#include <m2c.h>


s32 version_ok(s32 arg0) {
    if (arg0 == 3) {
        return 1;
    }
    return 0;
}
