#include <m2c.h>

M2C_UNK LoadToSubObjVRAM(s32, M2C_UNK, s32);
M2C_UNK VectorizedInvertedMemcpy(s32, s32, s32);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, s32);
M2C_UNK _ZN13SafeAllocator4FreeEPv(s32, s32);
s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
s32 func_02046708(s32, M2C_UNK);
M2C_UNK func_020c9820();
s32 func_020d6c00();
M2C_UNK func_020e0b4c(void *, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020e0cfc(void *, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020e0df8(void *, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020e0ec4(void *, s32, M2C_UNK, M2C_UNK);

s32 func_020e0a78(void *arg0) {
    s32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x76C) == 0) {
        return 0;
    }
    if (func_02046708(func_020d6c00(), 0x41) != 0) {
        return 0;
    }
    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(arg0, s32 *, 0x76C), M2C_FIELD(arg0, s32 *, 0x774));
    VectorizedInvertedMemcpy(M2C_FIELD(arg0, s32 *, 0x770), temp_r0, M2C_FIELD(arg0, s32 *, 0x774));
    func_020e0df8(arg0, temp_r0, 0, 0x700);
    func_020e0b4c(arg0, temp_r0, 0x700, 0xFC0);
    func_020e0ec4(arg0, temp_r0, 0x16C0, 0x9C0);
    func_020e0cfc(arg0, temp_r0, 0x2080, 0xD00);
    func_020c9820();
    _Z25CleanInvalidateCacheRangePKvj(temp_r0, M2C_FIELD(arg0, s32 *, 0x774));
    LoadToSubObjVRAM(temp_r0, 0, M2C_FIELD(arg0, s32 *, 0x774));
    _ZN13SafeAllocator4FreeEPv(M2C_FIELD(arg0, s32 *, 0x76C), temp_r0);
    return 1;
}
