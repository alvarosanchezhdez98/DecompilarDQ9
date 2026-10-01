#pragma once

// A name that the message system writes, e.g. a monster's (0xc bytes): func_020e46c4 initializes it
struct MessageName
{
    const char* text_;
    const char* unk_4;
    unsigned int unk_8_0 : 6;
    unsigned int unk_8_6 : 6;
    unsigned int unk_8_12 : 6;
    unsigned int unk_8_18 : 6;
    unsigned int unk_8_24 : 2;
    unsigned int unk_8_26 : 1;
    unsigned int unk_8_27 : 1;
    unsigned int unk_8_28 : 1;
    unsigned int unk_8_29 : 2;
    unsigned int unk_8_31 : 1;

    // The ROM has it after End_Start, where the compiler put the implicit one
    MessageName& operator=(const MessageName& other);
};
