#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022272E4();
M2C_UNK ov13_0222BC0C();
M2C_UNK ov13_022405B8(M2C_UNK);
extern u8 data_ov031_02290c7c;
extern M2C_UNK ov13_0222F0B8;

void ov13_0222F080(void) {
    if (data_ov031_02290c7c == 0) {
        ov13_0222BC0C();
    }
    ov13_022272E4();
    ov13_022405B8(8);
    func_ov031_022274c0(&ov13_0222F0B8);
}
