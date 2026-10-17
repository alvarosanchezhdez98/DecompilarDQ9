#include <m2c.h>
#pragma optimization_level 4

M2C_UNK CPS_TcpShutdown();

s32 SOCLi_ShutdownCallBack(void *arg0) {
    s32 var_r1;
    s8 temp_r0;

    var_r1 = 1;
    temp_r0 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0x73);
    if ((temp_r0 != 0) && (temp_r0 != 4)) {
        var_r1 = 0;
    }
    if (var_r1 != 0) {
        CPS_TcpShutdown();
    }
    return 0;
}
