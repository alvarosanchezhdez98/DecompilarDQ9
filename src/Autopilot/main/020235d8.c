#include <m2c.h>

void *_ZN9GameState11GetInstanceEv();
s32 func_02046708(s32, M2C_UNK);
s32 func_020d6c00();
s32 func_020dc7e8(M2C_UNK, M2C_UNK);
M2C_UNK func_02024000(void *);
M2C_UNK func_0202427c(void *);
M2C_UNK func_02024518(void *);
M2C_UNK func_02024e78(void *);
M2C_UNK func_020251bc(void *);
M2C_UNK func_0202555c(void *);
M2C_UNK func_02025b0c(void *);
M2C_UNK func_02025f28(void *);
M2C_UNK func_02026ebc(void *);
M2C_UNK func_02027100(void *);
M2C_UNK func_0202720c(void *);
M2C_UNK func_020276dc(void *);

s32 func_020235c8(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    u32 temp_r0_4;
    u8 temp_r0_3;
    void *temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r0_2 = func_02046708(func_020d6c00(), 0x41);
    if (temp_r0_2 != 0) {
        return temp_r0_2;
    }
    temp_r0_3 = M2C_FIELD(arg0, u8 *, 0x9C1);
    switch (temp_r0_3) {                            /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        func_0202720c(arg0);
        break;
    case 4:                                         /* switch 1 */
        func_02025f28(arg0);
        break;
    default:                                        /* switch 1 */
        func_02024000(arg0);
        func_0202427c(arg0);
        func_02026ebc(arg0);
        temp_r0_4 = M2C_FIELD(arg0, u32 *, 0x14);
        switch (temp_r0_4) {                        /* switch 2 */
        default:                                    /* switch 2 */
            break;
        case 0:                                     /* switch 2 */
            func_02024518(arg0);
            break;
        case 1:                                     /* switch 2 */
            func_02024e78(arg0);
            break;
        case 2:                                     /* switch 2 */
            func_020251bc(arg0);
            break;
        case 3:                                     /* switch 2 */
            func_0202555c(arg0);
            break;
        case 4:                                     /* switch 2 */
            func_02025b0c(arg0);
            break;
        }
        break;
    }
    func_020276dc(arg0);
    if (!(M2C_FIELD(arg0, u8 *, 0xA97) & 1)) {
        func_02027100(arg0);
    }
    temp_r0 = (s32) (M2C_FIELD(temp_r4, s32 *, 0x5CCC) << 0x1E) >> 0x1F;
    if (temp_r0 == 0) {
        return temp_r0;
    }
    func_020dc7e8(6, -1);
    return func_020dc7e8(7, -1);
}
