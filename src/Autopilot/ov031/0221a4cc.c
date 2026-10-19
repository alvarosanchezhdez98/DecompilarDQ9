#include <m2c.h>

M2C_UNK ov00_021E9754(void *);
extern M2C_UNK data_ov031_0224a254;
extern void *data_ov031_0224e69c;

void ov00_021EB864(void) {
    if (data_ov031_0224e69c == NULL) {
        return;
    }
    ov00_021E9754(data_ov031_0224e69c + 8);
    M2C_FIELD(data_ov031_0224e69c, M2C_UNK (**)(M2C_UNK *, void *, M2C_UNK), 4)(&data_ov031_0224a254, data_ov031_0224e69c, 0);
    data_ov031_0224e69c = NULL;
}
