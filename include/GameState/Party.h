#pragma once

// The party, which func_02010828 returns
struct Party
{
    char unk_0[0xf6c];
    unsigned int gold_;
    char unk_f70[8];
    // The indexes of the party members (see func_0200ff1c), and how many there are
    unsigned char members_[4];
    unsigned char count_;
};
