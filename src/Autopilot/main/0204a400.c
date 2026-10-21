#include <m2c.h>

M2C_UNK _ZN8Object3D18EnableBoneTrackingEv(void *);

void *func_0204a3f0(void *arg0, void *arg1) {
    s32 *var_r1;
    s32 var_r0;
    void *temp_r0;

    M2C_FIELD(arg0, void **, 0x21C) = arg1;
    _ZN8Object3D18EnableBoneTrackingEv(arg1);
    temp_r0 = M2C_FIELD(arg0, void **, 0x21C);
    var_r1 = M2C_FIELD(temp_r0, s32 **, 8);
    if (var_r1 == NULL) {
        return temp_r0;
    }
    var_r0 = (s32) (M2C_FIELD(var_r1, s32 *, 0xA8) << 0x1F) >> 0x1F;
    if (var_r0 == 0) {
        var_r1 = NULL;
    }
    if (var_r1 != NULL) {
        var_r0 = *var_r1 | 4;
        *var_r1 = var_r0;
    }
    return (void *) var_r0;
}
