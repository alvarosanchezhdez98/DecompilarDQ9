#include <m2c.h>

void *func_0202c178(M2C_UNK, M2C_UNK);
s32 func_0202c508();
u16 func_0202d698();

u16 func_0202bc8c(M2C_UNK arg0) {
    if (func_0202c508() != 0) {
        return func_0202d698();
    }
    return M2C_FIELD(func_0202c178(arg0, 0), u16 *, 4);
}
