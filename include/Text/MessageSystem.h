#pragma once

// The text system: it formats texts and shows them in the message window. func_020421a0 returns it
struct MessageSystem
{
    void* arguments_;
    char unk_4[0x2d4];
    int unk_2d8;
    char unk_2dc[0x998 - 0x2dc];
    // While the message is shown
    int busy_;
    char unk_99c[4];
    // The state of the message window: SaveErrorScreen waits for 4 before deleting the save data and for 3 before
    // checking the buttons
    int unk_9a0;
    char unk_9a4[0x1e28 - 0x9a4];
    void* unk_1e28;
};
