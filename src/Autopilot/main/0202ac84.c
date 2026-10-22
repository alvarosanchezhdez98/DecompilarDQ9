#include <m2c.h>

M2C_UNK LoadToMainBGStandardPalette(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_020ca458(M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_0202ab34(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_020e7170;
extern M2C_UNK data_020ef788;
extern M2C_UNK data_020ef78b;
extern M2C_UNK data_020ef78e;
extern M2C_UNK data_020ef791;
extern M2C_UNK data_020ef794;
extern M2C_UNK data_020ef797;
extern M2C_UNK data_020ef79a;
extern M2C_UNK data_020fe9cc;

void func_0202ac74(void) {
    func_0202ab34(&data_020ef788, 2, 0x28);
    func_0202ab34(&data_020ef78b, 0xC, 0x30);
    func_0202ab34(&data_020ef78e, 1, 0x3D);
    func_0202ab34(&data_020ef791, 0x1A, 0x41);
    func_0202ab34(&data_020ef794, 0x1A, 0x2F);
    func_0202ab34(&data_020ef797, 1, 0x2E);
    func_0202ab34(&data_020ef79a, 1, 0x2D);
    LoadToMainBGStandardPalette(&data_020e7170, 0, 0x200);
    func_020ca458(0, &data_020fe9cc, 0x600);
}
