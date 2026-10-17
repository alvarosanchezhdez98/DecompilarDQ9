#include <m2c.h>

s32 func_ov031_02211aec();
s32 func_ov031_0223f1e8(M2C_UNK);

s32 ov00_021ED388(M2C_UNK arg0) {
    if (func_ov031_02211aec() != 0) {
        return 0;
    }
    return func_ov031_0223f1e8(arg0);
}
