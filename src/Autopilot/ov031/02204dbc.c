#include <m2c.h>

M2C_UNK SOCLi_StartupCPS();
s32 SOCLi_StartupSOCL();
M2C_UNK func_02000b9c(s32);
extern s32 data_ov031_022496a4;

s32 SOCL_Startup(s32 arg0) {
    func_02000b9c(0x02000C1C);
    if (data_ov031_022496a4 != 0) {
        return 0;
    }
    data_ov031_022496a4 = arg0;
    SOCLi_StartupCPS();
    return SOCLi_StartupSOCL();
}
