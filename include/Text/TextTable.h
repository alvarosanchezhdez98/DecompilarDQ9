#pragma once

// A loaded .nat file of texts, such as str_sml_<LG>.nat
struct TextTable
{
    char unk_0[0x18];
};

// A list of texts loaded from a .bin file of a .gp2 archive, found by their IDs: func_020727d8 initializes it,
// func_020728ac loads it and func_02072a68 returns a text. sizeof == 8
struct TextList
{
    void* entries_;
    short count_;
    short unk_6;
};
