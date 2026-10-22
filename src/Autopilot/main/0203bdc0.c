#include <m2c.h>

M2C_UNK LoadToMainOAM(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK LoadToSubOAM(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _Z20DMAMemsetSynchronousijjj(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_021052b4;
extern M2C_UNK data_021056b4;

void func_0203bdb0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xC) != 0) {
        LoadToMainOAM(&data_021052b4, 0, 0x400);
        _Z20DMAMemsetSynchronousijjj(3, &data_021052b4, 0xC0, 0x400);
    }
    if (M2C_FIELD(arg0, u8 *, 0xD) != 0) {
        LoadToSubOAM(&data_021056b4, 0, 0x400);
        _Z20DMAMemsetSynchronousijjj(3, &data_021056b4, 0xC0, 0x400);
    }
    if ((M2C_FIELD(arg0, u8 *, 0xC) == 0) && (M2C_FIELD(arg0, u8 *, 0xD) == 0)) {
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x520) = 4;
}
