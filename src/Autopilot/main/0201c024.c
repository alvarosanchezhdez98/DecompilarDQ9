#include <m2c.h>

M2C_UNK _ZN12LightingInfo10InitializeEv(s32);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK _ZN17ActiveGrottoClass5ClearEv(void *);
M2C_UNK _ZN7Model3DC1Ev();
M2C_UNK _ZN7Model3DD1Ev();
M2C_UNK _ZN8FloorMap5ClearEv(void *);
M2C_UNK __construct_array(void *, M2C_UNK, M2C_UNK, M2C_UNK (*)(), M2C_UNK (*)());
M2C_UNK func_020134e0(void *);
M2C_UNK func_0208f7ec(void *);
M2C_UNK func_02094d00(void *);
M2C_UNK func_020982b4(void *);
M2C_UNK func_020de824(void *);
M2C_UNK _ZN16Unknown_0201c0e8C1Ev();
M2C_UNK _ZN16Unknown_0201c0e8D1Ev();
M2C_UNK func_0201e248(s32);

void *func_0201c014(void *arg0) {
    void *temp_r5;

    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x54);
    func_0201e248(arg0 + 0x6C);
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    _ZN12LightingInfo10InitializeEv(arg0 + 0x10C);
    __construct_array(arg0 + 0x498, 2, 0xAC, _ZN7Model3DC1Ev, _ZN7Model3DD1Ev);
    __construct_array(arg0 + 0x600, 4, 0x88, _ZN16Unknown_0201c0e8C1Ev, _ZN16Unknown_0201c0e8D1Ev);
    func_020982b4(arg0 + 0x840);
    temp_r5 = arg0 + 0x23EC;
    _ZN8FloorMap5ClearEv(temp_r5 + 0x1C8);
    _ZN17ActiveGrottoClass5ClearEv(temp_r5);
    func_0208f7ec(arg0 + 0x2664);
    func_02094d00(arg0 + 0x2724);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x2730);
    func_020de824(arg0 + 0x2754);
    func_020134e0(arg0);
    return arg0;
}
