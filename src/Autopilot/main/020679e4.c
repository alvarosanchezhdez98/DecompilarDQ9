#include <m2c.h>

M2C_UNK func_0205c840();
M2C_UNK func_0205eaa0();
M2C_UNK func_0206b104();
M2C_UNK func_0206b2c8();
extern M2C_UNK data_02108760;

void func_020679d4(void *arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0:
        func_0206b104();
        func_0205eaa0(&data_02108760, 1, 0);
        func_0206b2c8(arg0, 0xFF16, M2C_FIELD(arg0, s32 *, 0x58));
        func_0205c840(arg0 + 0x90);
        M2C_FIELD(arg0, s8 *, 0x19CD) = 1;
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        return;
    case 1:
        func_0205eaa0(&data_02108760, 1, 0);
        /* fallthrough */
    case -2:
        M2C_FIELD(arg0, s32 *, 0x954) = 1;
        func_0206b104(arg0);
        func_0206b2c8(arg0, 0xFF17, M2C_FIELD(arg0, s32 *, 0x58));
        func_0205c840(arg0 + 0x90);
        M2C_FIELD(arg0, s8 *, 0x19CD) = 1;
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        return;
    }
}
