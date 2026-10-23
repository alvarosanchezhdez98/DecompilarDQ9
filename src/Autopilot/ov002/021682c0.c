#include <m2c.h>

M2C_UNK func_0205d6a0(void *, M2C_UNK);
s8 func_ov002_021574d4(void *, s16);
void _ZN13SafeAllocator5ResetEv(void *);
void _ZN16SkillAbilityList10InitializeEh(void *, u8);
void _ZN16SkillAbilityList5SetupEP13SafeAllocator(void *, void *);
void func_ov002_0215a878(void *arg0);
void func_ov002_0215b428(void *arg0);

void func_ov002_021682c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x247C) = (s32) (M2C_FIELD(arg0, s32 *, 0x247C) & ~4);
    func_ov002_0215a878(arg0);
    func_0205d6a0(arg0 + 0xEC8, 1);
    M2C_FIELD(arg0, s8 *, 0x2454) = 0;
    M2C_FIELD(arg0, s8 *, 0x2455) = 0;
    func_ov002_0215b428(arg0);
    _ZN13SafeAllocator5ResetEv(arg0 + 0x850);
    _ZN16SkillAbilityList10InitializeEh(arg0 + 0x1D04, 1U);
    _ZN16SkillAbilityList5SetupEP13SafeAllocator(arg0 + 0x1D04, arg0 + 0x850);
    M2C_FIELD(arg0, s8 *, 0x1D6B) = func_ov002_021574d4(arg0, M2C_FIELD(arg0, s16 *, 0x1C08));
    M2C_FIELD(arg0, s32 *, 0x1BC0) = (s32) (M2C_FIELD(arg0, s32 *, 0x1BC0) + 1);
}
