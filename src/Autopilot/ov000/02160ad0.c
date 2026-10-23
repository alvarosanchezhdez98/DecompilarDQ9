#include <m2c.h>

M2C_UNK func_ov000_021742c8(void *);
void _ZN11GuideWindow5Draw2Ev(void *);
void _ZN14SkillPointMenu13UpdateMessageEv(void *);
void _ZN16SkillAbilityList6UpdateEv(void *);
void _ZN18BattleResultWindow5Draw2Ev(void *);

void func_ov000_02160ad0(void *arg0) {
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r0_4;

    if (M2C_FIELD(arg0, s32 *, 0x55F8) == 0) {
        return;
    }
    temp_r0 = M2C_FIELD(arg0, void **, 0x55CC);
    if (temp_r0 != NULL) {
        _ZN11GuideWindow5Draw2Ev(temp_r0);
    }
    temp_r0_2 = M2C_FIELD(arg0, void **, 0x5574);
    if (temp_r0_2 != NULL) {
        _ZN14SkillPointMenu13UpdateMessageEv(temp_r0_2);
        temp_r0_3 = M2C_FIELD(arg0, void **, 0x5578);
        if (temp_r0_3 == NULL) {
            return;
        }
        _ZN16SkillAbilityList6UpdateEv(temp_r0_3);
        return;
    }
    temp_r0_4 = M2C_FIELD(arg0, void **, 0x5588);
    if (temp_r0_4 != NULL) {
        _ZN18BattleResultWindow5Draw2Ev(temp_r0_4);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x55F4) & 0x40000) {
        return;
    }
    func_ov000_021742c8(arg0 + 0x3760);
}
