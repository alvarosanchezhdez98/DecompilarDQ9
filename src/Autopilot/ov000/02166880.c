#include <m2c.h>

M2C_UNK _Z19GetCurrentTimestampv();
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader14RemoveAllLocksEv(s32);
M2C_UNK _ZN6Zone3D10SwitchZoneEt(void *, u16, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState14GetProtagonistEv(s32);
s32 func_02011584(s32);
M2C_UNK func_02012de8();
M2C_UNK func_02012fe4();
M2C_UNK func_02013718(s32, s32, s32);
M2C_UNK func_02015438(void *);
M2C_UNK func_0202ae18();
s32 func_02099950(s32, u16);
s32 func_020a3694(void *);
M2C_UNK func_020d84f4();
M2C_UNK func_ov000_02160fa8(void *, M2C_UNK);
M2C_UNK func_ov017_0218b5b0();

void func_ov000_02166880(void *arg0) {
    s32 temp_r4;
    s32 temp_r6;
    u16 temp_r0;
    void *temp_r1;

    func_ov017_0218b5b0();
    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r4 = _ZN16BackgroundLoader11GetInstanceEv();
    _ZN9GameState14GetProtagonistEv(temp_r6);
    func_0202ae18();
    func_02013718(arg0 + 0xEC8, arg0 + 8, arg0 + 0x36F0);
    func_02012fe4();
    if (func_020a3694(M2C_FIELD(arg0, void **, 0x2A0)) != 0) {
        temp_r1 = M2C_FIELD(arg0, void **, 0x2A0);
        temp_r0 = M2C_FIELD(temp_r1, u16 *, 0x20);
        if (temp_r0 != 0) {
            M2C_FIELD(temp_r1, u16 *, 2) = temp_r0;
        }
    }
    if ((func_02099950(func_02011584(temp_r6), M2C_FIELD(M2C_FIELD(arg0, void **, 0x2A0), u16 *, 2)) != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0x2A0), u16 *, 2) != 0x7530)) {

    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x2A0), u16 *, 2) = 0x75A4U;
    }
    _ZN6Zone3D10SwitchZoneEt(arg0 + 0xEC8, M2C_FIELD(M2C_FIELD(arg0, void **, 0x2A0), u16 *, 2), 0);
    _Z19GetCurrentTimestampv();
loop_8:
    func_02012de8();
    _ZN16BackgroundLoader14RemoveAllLocksEv(temp_r4);
    func_02015438(arg0 + 0xEC8);
    if (M2C_FIELD(arg0, s32 *, 0x12EC) != 0) {
        func_020d84f4();
        goto loop_8;
    }
    func_ov000_02160fa8(arg0, 0x10);
}
