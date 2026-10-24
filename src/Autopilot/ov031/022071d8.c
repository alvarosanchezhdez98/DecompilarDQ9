#include <m2c.h>

M2C_UNK SOCL_CreateSocket(M2C_UNK *);
extern M2C_UNK data_ov031_022496ac;
extern M2C_UNK data_ov031_022496c4;

void SOC_Socket(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        SOCL_CreateSocket(&data_ov031_022496c4);
        return;
    }
    SOCL_CreateSocket(&data_ov031_022496ac);
}
