#include <m2c.h>

M2C_UNK _Z25MarkContextReadyAndSwitchP16ProcessorContext(s32);
void *find_socket();
M2C_UNK tcp_send_ack(void *, M2C_UNK);
M2C_UNK tcp_send_finack(void *, M2C_UNK);
M2C_UNK tcp_send_rst(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);

void dt_fin(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u8 temp_r1;
    void *temp_r0;

    temp_r0 = find_socket();
    if (temp_r0 == NULL) {
        return;
    }
    temp_r1 = M2C_FIELD(temp_r0, u8 *, 8);
    switch (temp_r1) {                              /* irregular */
    case 7:
        M2C_FIELD(temp_r0, s32 *, 0x24) = (s32) (M2C_FIELD(temp_r0, s32 *, 0x24) + 1);
        tcp_send_ack(temp_r0, 0);
        M2C_FIELD(temp_r0, u8 *, 8) = 9U;
        return;
    case 8:
        M2C_FIELD(temp_r0, s32 *, 0x24) = (s32) (M2C_FIELD(temp_r0, s32 *, 0x24) + 1);
        tcp_send_ack(temp_r0, 0);
        M2C_FIELD(temp_r0, u8 *, 8) = 0U;
        if (M2C_FIELD(temp_r0, s32 *, 4) != 2) {
            return;
        }
        M2C_FIELD(temp_r0, s32 *, 4) = 0;
        _Z25MarkContextReadyAndSwitchP16ProcessorContext(M2C_FIELD(temp_r0, s32 *, 0));
        return;
    case 4:
        M2C_FIELD(temp_r0, s32 *, 0x24) = (s32) (M2C_FIELD(temp_r0, s32 *, 0x24) + 1);
        tcp_send_finack(temp_r0, 0);
        M2C_FIELD(temp_r0, u8 *, 8) = 6U;
        return;
    default:
        tcp_send_rst(arg0, arg1, arg2, 0);
        return;
    }
}
