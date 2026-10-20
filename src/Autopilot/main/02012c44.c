#include <m2c.h>

M2C_UNK _Z19SetInterruptHandlerjPKv(M2C_UNK, M2C_UNK (*)());
M2C_UNK _Z20Initialize64BitTimerv();
M2C_UNK _Z23ChangeROMLoadDMAChannelj(M2C_UNK);
M2C_UNK _Z23InitializeROMFilesystemi(M2C_UNK);
M2C_UNK _Z23InitializeResourceMutexv();
M2C_UNK _Z24EnableSpecificInterruptsj(s32);
M2C_UNK _Z25InitializeActiveAlarmListv();
M2C_UNK _Z28SetSpecificInterruptsEnabledj(M2C_UNK);
M2C_UNK func_020758a8();
M2C_UNK func_020bbd14();
M2C_UNK func_020c36ec();
M2C_UNK func_020c36f0();
M2C_UNK func_020c3864(M2C_UNK, u16);
M2C_UNK func_020c8368();
M2C_UNK func_020c9288();
M2C_UNK func_020ce270();
M2C_UNK func_020cf020();
M2C_UNK func_020e1114();
M2C_UNK func_02012244(M2C_UNK *);
M2C_UNK func_0201282c(M2C_UNK *);
M2C_UNK func_02012bd8();
M2C_UNK func_02012d18(M2C_UNK *);
extern s32 data_020f2270;
extern s8 data_02114e00;
extern M2C_UNK data_02114e20;
extern M2C_UNK data_02114e30;
extern s32 data_02114e50;
extern M2C_UNK data_02114e54;

void func_02012c34(void) {
    u16 temp_r1;

    func_020c8368();
    func_020c36ec();
    data_020f2270 = 0;
    func_020c36f0();
    func_020ce270();
    func_020cf020();
    _Z20Initialize64BitTimerv();
    _Z25InitializeActiveAlarmListv();
    func_020c9288();
    _Z23InitializeResourceMutexv();
    _Z28SetSpecificInterruptsEnabledj(0);
    _Z19SetInterruptHandlerjPKv(1, func_02012bd8);
    _Z24EnableSpecificInterruptsj(1);
    _Z24EnableSpecificInterruptsj(0xF08);
    temp_r1 = *(u16 *)0x04000208;
    *(u16 *)0x04000208 = 1;
    func_020c3864(1, temp_r1);
    func_02012d18(&data_02114e20);
    _Z24EnableSpecificInterruptsj(0x40000);
    _Z23InitializeROMFilesystemi(2);
    _Z23ChangeROMLoadDMAChannelj(2);
    func_020758a8();
    func_020bbd14();
    func_02012244(&data_02114e30);
    func_0201282c(&data_02114e54);
    func_020e1114();
    data_02114e00 = 0;
    data_02114e50 = 0;
}
