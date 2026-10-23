#include <m2c.h>

u32 func_0200fb08(void *);
void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN16MenuObjectClass112SetTouchAreaEiiii(void *, s32, s32, s32, s32);
void * _ZN9GameState11GetInstanceEv(void);

s32 func_ov004_0216a810(void *arg0) {
    u32 temp_r0_3;
    u32 temp_r0_5;
    void *temp_r0_2;
    void *temp_r0_4;
    void *temp_r5;

    void *temp_r0;
    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN10MenuScript10GetObjectsEv(arg0);
    temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, 0x1E);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_2) != 1) {
        return 0;
    }
    temp_r0_3 = func_0200fb08(temp_r5);
    switch (temp_r0_3) {                            /* switch 1 */
    default:                                        /* switch 1 */
        break;
    case 1:                                         /* switch 1 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_2, 0, 0, 0x58, 0x10);
        break;
    case 2:                                         /* switch 1 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_2, 0, 0, 0x50, 0x10);
        break;
    case 3:                                         /* switch 1 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_2, 0, 0, 0x50, 0x10);
        break;
    case 4:                                         /* switch 1 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_2, 0, 0, 0x60, 0x10);
        break;
    case 5:                                         /* switch 1 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_2, 0, 0, 0x60, 0x10);
        break;
    }
    temp_r0_4 = _ZN14MenuObjectList4FindEi(temp_r0, 0x1F);
    if (temp_r0_4 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0_4) != 1) {
        return 0;
    }
    temp_r0_5 = func_0200fb08(temp_r5);
    switch (temp_r0_5) {                            /* switch 2 */
    default:                                        /* switch 2 */
        break;
    case 1:                                         /* switch 2 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 8, 0, 0x58, 0x10);
        break;
    case 2:                                         /* switch 2 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 0x10, 0, 0x50, 0x10);
        break;
    case 3:                                         /* switch 2 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 0x10, 0, 0x50, 0x10);
        break;
    case 4:                                         /* switch 2 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 0, 0, 0x60, 0x10);
        break;
    case 5:                                         /* switch 2 */
        _ZN16MenuObjectClass112SetTouchAreaEiiii(temp_r0_4, 0, 0, 0x60, 0x10);
        break;
    }
    return 0;
}
