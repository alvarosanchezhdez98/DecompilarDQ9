#include <m2c.h>

M2C_UNK cache_session(void *, M2C_UNK, M2C_UNK);
M2C_UNK create_key_block(void *);
M2C_UNK create_master_secret(void *);
M2C_UNK decrypt_premaster_secret(void *, M2C_UNK, s32);

void rcv_client_key_exchange(void *arg0, M2C_UNK arg1) {
    decrypt_premaster_secret(arg0, arg1, M2C_FIELD(arg0, s32 *, 0x81C));
    create_master_secret(arg0);
    cache_session(arg0, 0, 0);
    create_key_block(arg0);
    M2C_FIELD(arg0, s8 *, 0x455) = 5;
}
