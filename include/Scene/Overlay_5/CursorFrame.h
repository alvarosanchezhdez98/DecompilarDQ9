#pragma once

// A frame around what the equipment menu selects (0x3c bytes): four objects at its corners, which move towards a
// target rectangle a fraction of the way each frame
struct CursorFrame
{
    // The corners: 3D models (0x88 bytes each), 0x28-byte objects or sprites (0x70 bytes each), see Draw()
    char* corners_;
    // The size of a corner, which the right and bottom ones are moved by
    int size_;
    // What the frame adds to the rectangle that it's given: to its left, right, top and bottom
    int left_;
    int right_;
    int top_;
    int bottom_;
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
    // Overlay 5's EquipmentMenu.cpp has these
    void SetTargetPosition(int x, int y);
    void SetPosition(int x, int y);
    void SetTargetSize(int width, int height);
    void SetSize(int width, int height);
};
