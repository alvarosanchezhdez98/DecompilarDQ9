#include <m2c.h>

s32 get_targetip();
s32 inq_arpcache();

s32 no_need_inq(void) {
    if (get_targetip() == 0) {
        return 1;
    }
    return inq_arpcache();
}
