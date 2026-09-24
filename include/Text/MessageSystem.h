#pragma once

// The text system: it formats texts and shows them in the message window. func_020421a0 returns it
struct MessageSystem
{
    void* arguments_;
    char unk_4[0x58];
    // 0x960 bytes, which TitleScreen clears before writing the library versions to it
    void* unk_5c;
    char unk_60[0x2d8 - 0x60];
    int unk_2d8;
    char unk_2dc[4];
    void* unk_2e0;
    char unk_2e4[3];
    // TitleScreen waits for 2 after func_02043368
    unsigned char unk_2e7;
    char unk_2e8[0x998 - 0x2e8];
    // While the message is shown
    int busy_;
    char unk_99c[4];
    // The state of the message window: SaveErrorScreen waits for 4 before deleting the save data and for 3 before
    // checking the buttons
    int unk_9a0;
    char unk_9a4[0x1e28 - 0x9a4];
    void* unk_1e28;
};
