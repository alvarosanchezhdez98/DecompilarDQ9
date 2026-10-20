#include <m2c.h>

M2C_UNK DisableLCDCMappedVRAMBanks();
M2C_UNK MapVRAMBanksToLCDC(s32);
M2C_UNK func_020ca458(M2C_UNK, s32, M2C_UNK);

void ov13_0224225C(void) {
    MapVRAMBanksToLCDC(0x1F3);
    func_020ca458(0, 0x06800000, 0x40000);
    func_020ca458(0, 0x06880000, 0x24000);
    DisableLCDCMappedVRAMBanks();
    func_020ca458(0x200, 0x07000000, 0x400);
    func_020ca458(0, 0x05000000, 0x400);
    func_020ca458(0x200, 0x07000400, 0x400);
    func_020ca458(0, 0x05000400, 0x400);
}
