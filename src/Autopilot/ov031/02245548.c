#include <m2c.h>


void func_ov031_02245548(void *arg0) {
    s32 temp_r1_3;
    s32 temp_r1_4;
    s32 temp_r1_6;
    s32 temp_r1_8;
    s32 temp_r1_9;
    s32 temp_r2;
    s32 temp_r2_2;
    s32 temp_r2_3;
    u8 temp_r1;
    u8 temp_r1_2;
    u8 temp_r1_5;
    u8 temp_r1_7;

    temp_r1 = M2C_FIELD(arg0, u8 *, 0x374);
    if (temp_r1 & 1) {
        temp_r1_2 = M2C_FIELD(arg0, u8 *, 0x34);
        switch (temp_r1_2) {                        /* switch 1; irregular */
        case 2:                                     /* switch 1 */
            temp_r1_3 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r1_3 < 0x3C000) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r1_3 + 0x28);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x3C000;
            }
            return;
        case 3:                                     /* switch 1 */
            temp_r1_4 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r1_4 < 0x46000) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r1_4 + 0x51);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x46000;
            }
            return;
        case 4:                                     /* switch 1 */
            temp_r2 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r2 < 0x77F33) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r2 + 0xCC);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 5) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x78000;
            }
            return;
        }
    } else if (temp_r1 & 4) {
        temp_r1_5 = M2C_FIELD(arg0, u8 *, 0x34);
        switch (temp_r1_5) {                        /* switch 2; irregular */
        case 2:                                     /* switch 2 */
            temp_r1_6 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r1_6 < 0x64000) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r1_6 + 0x51);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x64000;
            }
            return;
        case 3:                                     /* switch 2 */
            temp_r2_2 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r2_2 < 0x77F85) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r2_2 + 0x7A);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x78000;
            }
            return;
        }
    } else {
        if (!(temp_r1 & 2)) {
            return;
        }
        temp_r1_7 = M2C_FIELD(arg0, u8 *, 0x34);
        switch (temp_r1_7) {                        /* switch 3; irregular */
        case 2:                                     /* switch 3 */
            temp_r1_8 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r1_8 < 0x3C000) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r1_8 + 0x28);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x3C000;
            }
            return;
        case 3:                                     /* switch 3 */
            temp_r1_9 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r1_9 < 0x46000) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r1_9 + 0x51);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 6) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x46000;
            }
            return;
        case 5:                                     /* switch 3 */
            temp_r2_3 = M2C_FIELD(arg0, s32 *, 0x384);
            if (temp_r2_3 < 0x77F33) {
                M2C_FIELD(arg0, s32 *, 0x384) = (s32) (temp_r2_3 + 0xCC);
            }
            if (M2C_FIELD(arg0, u8 *, 0x35) == 5) {
                M2C_FIELD(arg0, s32 *, 0x384) = 0x78000;
            }
            return;
        }
    }
}
