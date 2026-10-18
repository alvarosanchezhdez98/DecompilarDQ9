#include <m2c.h>

M2C_UNK CPS_SocBind(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK CPS_SocDatagramMode();
M2C_UNK CPS_SocRelease();
M2C_UNK CPS_SocUse();
s32 dhcp_analyze_response(s32, s32);
s32 dhcp_send_discover();

s32 dhcp_discover_server(void) {
    s32 temp_r0;
    s32 var_r5;

    CPS_SocUse();
    CPS_SocDatagramMode();
    CPS_SocBind(0x44, 0x43, -1);
    var_r5 = 0;
loop_1:
    temp_r0 = dhcp_analyze_response(dhcp_send_discover(), var_r5);
    if (temp_r0 != 1) {
        var_r5 += 1;
        if (var_r5 < 4) {
            goto loop_1;
        }
    }
    CPS_SocRelease();
    if (temp_r0 == 1) {
        return 1;
    }
    return 0;
}
