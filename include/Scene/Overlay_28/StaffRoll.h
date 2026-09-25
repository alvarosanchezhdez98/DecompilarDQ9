#pragma once

#include "Memory/SafeAllocator.h"
#include "System/VCountAlarm.h"

// A line of the staff roll's text, from staffroll.bin
struct StaffRollLine
{
    // The lines of a group are drawn when the group reaches the screen
    short group_;
    // The space from the group to the next one, in pixels
    short height_;
    union
    {
        unsigned int flags_;
        struct
        {
            // Also the line's height in the text's font
            unsigned int size_ : 4;
            // 0: left, 1: centered, 2: right
            unsigned int alignment_ : 2;
            unsigned int unk_4_6 : 1;
            unsigned int color_ : 4;
            unsigned int unk_4_11 : 21;
        };
    };
    char* text_;

    void Initialize()
    {
        group_ = -1;
        height_ = 0;
        flags_ = 0;
        text_ = NULL;
    }
};

// The lines of the staff roll
struct StaffRollLines
{
    // How fast the text scrolls, in pixels per frame
    float speed_;
    StaffRollLine* lines_;
    unsigned short count_;
    unsigned short capacity_;

    void Initialize();
    void Clear();
    // Runs staffroll.bin's script, which adds the lines
    void Load(SafeAllocator* allocator, void* file, unsigned int size);
    void Allocate(SafeAllocator* allocator, unsigned short capacity);
    void Add(const StaffRollLine* line);
    StaffRollLine* Get(unsigned int index);
};

// How far the text has scrolled on the sub screen's BG 1, in fixed point
struct StaffRollScroll
{
    int position_;
    // Where the next group of lines goes
    int nextGroup_;
    // The scrolled distance that the background's buffer hasn't cleared yet
    int pending_;
    unsigned short nextLine_;
    // The background's characters have to be loaded again
    bool dirty_;

    void Advance(float pixels);
    void ClearPassedRows(void* characters);
};

// Overlay 28's code: the staff roll (data/evspt_lv5/staffroll.bin). Overlay 1 (events) runs one itself, and the
// overlay has one that's run by a V-count alarm, TimedStaffRoll
class StaffRoll
{
public:
    enum State
    {
        State_Load,
        State_Scroll,
        State_ScrollOut,
        State_End,
    };

    StaffRollLines lines_;
    // What func_02074af4 and func_02074bd0 take
    char unk_c[0x10];
    unsigned char unk_1c;
    unsigned char unk_1d;
    char unk_1e[2];
    // What func_020979c0, func_02097b34, func_02097bc4 and func_02097c18 take
    char unk_20[0x20];
    // The sub screen BG 1's characters, and its palette and screen before
    char* buffer_;
    // For staffroll.bin's script
    SafeAllocator allocator_;
    // The planes that are visible before
    unsigned int mainPlanes_;
    unsigned int subPlanes_;
    StaffRollScroll scroll_;
    int taskID_;
    // The values of func_0203b498, func_0203b4d0 and func_0203b508 before, which Finish() gives back
    int unk_74;
    int unk_78;
    int unk_7c;
    // State
    unsigned char state_;
    unsigned char step_;

    // The sizes of the buffers. Nothing reads them, the code has the values
    static const unsigned int sScreenEntries;
    static const unsigned int sCharacterDataSize;
    static const unsigned int sBufferSize;
    static const unsigned int sScreenDataSize;
    static const unsigned int sScriptBufferSize;
    static const unsigned int sCharacterDataSize2;
    static const unsigned int sCharacterDataSize3;

    void Setup(SafeAllocator* allocator);
    void Initialize();
    void Finish();
    // Returns whether it's over
    bool Update(int frames);
    void Load(int frames);
    void Draw();
    void Scroll(int frames);
    void ScrollOut(int frames);
};

// The staff roll that the overlay runs by itself, from a V-count alarm, with the time that passes
class TimedStaffRoll : public StaffRoll
{
public:
    unsigned long long start_;
    unsigned long long now_;
    int previousFrames_;
    int frames_;
    // Draw() and Update() take turns
    bool draw_;
    unsigned long long setupTime_;
    unsigned long long elapsed_;

    TimedStaffRoll();
    ~TimedStaffRoll();

    void Initialize();
    void Finish();
    void Setup(SafeAllocator* allocator);
    void Update();
    void Load();
};

// Overlay 28's functions that overlay 1 calls
void StartStaffRoll(SafeAllocator* allocator);
void StopStaffRoll();
void LoadStaffRoll();
unsigned int GetStaffRollMilliseconds();

// The staff roll that the overlay runs, and its V-count alarm (StaffRollLines.cpp)
extern VCountAlarm gStaffRollAlarm;
extern TimedStaffRoll gStaffRoll;
