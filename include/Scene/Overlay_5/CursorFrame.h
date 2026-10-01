#pragma once

// A frame around what the equipment menu selects (0x3c bytes): four objects at its corners, which move towards a
// target rectangle a fraction of the way each frame
struct CursorFrame
{
    // The corners: 3D models (0x88 bytes each), 0x28-byte objects or sprites (0x70 bytes each), see Draw()
    char* corners_;
    // The size of a corner, which the right and bottom ones are moved by
    int size_;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    // Where the frame goes: x, y, width and height
    int target_[4];
    // Where it is now
    int current_[4];
    // The depth of the models
    int z_;

    void Initialize();
    void Update(int speed);
    void Draw(int kind, short alpha);
    void Approach(int* target, int* current, int rate, int threshold);
};
