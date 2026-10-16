#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s16);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s16);
extern s32 data_ov000_02184220;

void func_ov000_02160e94(void *arg0) {
    s32 temp_r0;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, M2C_FIELD(arg0, s16 *, 0x7730)) >= 0) {
        return;
    }
    _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, M2C_FIELD(arg0, s16 *, 0x7730));
    M2C_FIELD(arg0, s16 *, 0x7730) = -1;
    M2C_FIELD(arg0, s32 *, 0xEA8) = 8;
    M2C_FIELD(arg0, s32 *, 0xEAC) = 0;
    data_ov000_02184220 = 1;
}
