#include <m2c.h>

M2C_UNK __construct_array(s32, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *);
M2C_UNK func_02039e7c(s32);
extern M2C_UNK _ZN16Unknown_0201c0e8C1Ev;
extern M2C_UNK _ZN16Unknown_0201c0e8D1Ev;

s32 func_0203a878(s32 arg0) {
    __construct_array(arg0, 5, 0x88, &_ZN16Unknown_0201c0e8C1Ev, &_ZN16Unknown_0201c0e8D1Ev);
    __construct_array(arg0 + 0x2A8, 5, 0x88, &_ZN16Unknown_0201c0e8C1Ev, &_ZN16Unknown_0201c0e8D1Ev);
    func_02039e7c(arg0);
    return arg0;
}
