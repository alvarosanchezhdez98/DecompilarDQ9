#include <m2c.h>

s32 WCM_GetPhase();
M2C_UNK ov00_021EA420();
M2C_UNK ov00_021EA518();
void *ov00_021FAE14(M2C_UNK);
s32 ov00_021FAECC();
s32 ov00_021FCD5C(void *);
s32 ov00_021FCDC0(void *);
s32 ov00_021FCE50();
s32 ov00_021FCE7C(void *);
s32 ov00_021FCEE8(void *);
s32 ov00_021FCEFC();

s32 ov00_021FCC60(void) {
    s32 var_r4;
    u32 temp_r0;
    void *temp_r5;

    var_r4 = ov00_021FAECC();
    temp_r5 = ov00_021FAE14(0x10);
    if (WCM_GetPhase() == 9) {
        temp_r0 = var_r4 - 0xA;
        switch (temp_r0) {                          /* switch 1 */
        default:                                    /* switch 1 */
            break;
        case 0:                                     /* switch 1 */
            var_r4 = ov00_021FCD5C(temp_r5);
            break;
        case 2:                                     /* switch 1 */
            var_r4 = ov00_021FCDC0(temp_r5);
            break;
        case 3:                                     /* switch 1 */
            var_r4 = ov00_021FCE50();
            break;
        case 4:                                     /* switch 1 */
            var_r4 = ov00_021FCE7C(temp_r5);
            break;
        case 5:                                     /* switch 1 */
            var_r4 = ov00_021FCEE8(temp_r5);
            break;
        case 1:                                     /* switch 1 */
            var_r4 = ov00_021FCEFC();
            break;
        }
    } else {
        switch (var_r4) {                           /* switch 2; irregular */
        case 15:                                    /* switch 2 */
            var_r4 = ov00_021FCEE8(temp_r5);
            break;
        case 11:                                    /* switch 2 */
            var_r4 = ov00_021FCEFC();
            break;
        case 14:                                    /* switch 2 */
            ov00_021EA518();
            ov00_021EA420();
            /* fallthrough */
        default:                                    /* switch 2 */
            var_r4 = 0xB;
            M2C_FIELD((temp_r5 + (M2C_FIELD(temp_r5, u8 *, 0xD13) * 4)), s8 *, 0x444) = 2;
            break;
        }
    }
    return var_r4;
}
