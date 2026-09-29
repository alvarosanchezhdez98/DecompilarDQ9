#pragma once

// A date and hour packed in a word
struct DownloadDate
{
    unsigned int year_ : 12;
    unsigned int month_ : 4;
    unsigned int day_ : 5;
    unsigned int hour_ : 5;
    unsigned int unk_26 : 6;
};

// An entry that a downloaded file chooses at random (0x28 bytes)
struct DownloadedEntry
{
    short id_;
    char unk_2[2];
    // Random, between the bounds that the file gives
    unsigned int value_ : 7;
    unsigned int unk_4_7 : 25;
    char unk_8[0x28 - 8];
};

// What the scripts of the downloaded files set in GameState (0x114 bytes, see DownloadContent.cpp)
struct DownloadedData
{
    short unk_0;
    char unk_2[2];
    DownloadedEntry entries_[6];
    DownloadDate start_;
    // The item that the "k" command checks
    short itemId_;
    char unk_fa[2];
    unsigned short price_;
    char unk_fe[2];
    DownloadDate end_;
    char unk_104[8];
    // 0x1, 0x2: the item's price is checked; 0x40: a story flag was set; 0x200: a zone was unlocked
    unsigned short flags_ : 13;
    unsigned short unk_10c_13 : 3;
    char unk_10e[0x114 - 0x10e];
};
