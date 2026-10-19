#include <m2c.h>

M2C_UNK CPS_SocBind(M2C_UNK, M2C_UNK, s32);
M2C_UNK CPS_SocDatagramMode();
M2C_UNK CPS_SocRelease();
M2C_UNK CPS_SocUse();
s32 dhcp_analyze_response(s32, s32);
s32 dhcp_send_request(s32);
extern M2C_UNK data_ov031_0224c980;

s32 dhcp_request_server(u32 *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r7;
    u32 temp_r1;

    CPS_SocUse();
    CPS_SocDatagramMode();
    if (arg1 == 1) {
        CPS_SocBind(0x44, 0x43, M2C_FIELD(&data_ov031_0224c980, s32 *, 0x20));
    } else {
        CPS_SocBind(0x44, 0x43, -1);
    }
    var_r7 = 0;
loop_4:
    temp_r0 = dhcp_analyze_response(dhcp_send_request(arg1), var_r7);
    if (temp_r0 == 0) {
        var_r7 += 1;
        if (var_r7 < 4) {
            goto loop_4;
        }
    }
    CPS_SocRelease();
    if (temp_r0 == 2) {
        *arg0 = (u32) M2C_FIELD(&data_ov031_0224c980, u32 *, 0x4C) >> 1;
        M2C_FIELD(&data_ov031_0224c980, u32 *, 0x38) = (u32) ((u32) (M2C_FIELD(&data_ov031_0224c980, u32 *, 0x4C) * 3) >> 3);
        return 1;
    }
    temp_r1 = (u32) M2C_FIELD(&data_ov031_0224c980, u32 *, 0x38) >> 1;
    M2C_FIELD(&data_ov031_0224c980, u32 *, 0x38) = temp_r1;
    *arg0 = temp_r1;
    switch (arg1) {                                 /* irregular */
    case 1:
        if (temp_r1 < 0x3CU) {
            *arg0 = 1;
            M2C_FIELD(&data_ov031_0224c980, u32 *, 0x38) = (u32) ((u32) M2C_FIELD(&data_ov031_0224c980, u32 *, 0x4C) >> 3);
        }
        break;
    case 2:
        if (temp_r1 < 0x3CU) {
            *arg0 = 1;
        }
        break;
    }
    return 0;
}
