#include <m2c.h>

M2C_UNK ov13_02240AA0(s32);
extern s32 data_ov031_02290d38;

void ov13_02240B04(s32 arg0) {
    ov13_02240AA0((0x30 * arg0) + (data_ov031_02290d38 + 0x610));
}
