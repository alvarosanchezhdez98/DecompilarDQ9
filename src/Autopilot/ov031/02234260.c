#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0223429c();
M2C_UNK func_ov031_022342a0();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223C198();
s32 ov13_0223C1DC();
extern M2C_UNK ov13_02238624;

void ov13_022385E0(void) {
    func_ov031_0223429c();
    func_ov031_022342a0();
    if (ov13_0223C1DC() != 0) {
        return;
    }
    ov13_0223ABB8(6);
    ov13_0223C198();
    ov13_0223ABB8(6);
    func_ov031_022274c0(&ov13_02238624);
}
