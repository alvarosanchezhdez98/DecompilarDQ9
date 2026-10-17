#include <m2c.h>

s32 parse_record();

s32 mustget_change_cipher_spec_and_finished(s32 arg0) {
    s32 var_r4;

    var_r4 = arg0;
    if (parse_record() != 7) {
        return 1;
    }
    if (parse_record(var_r4) != 6) {
        return 1;
    }
    return 0;
}
