#include "Scene/Overlay_28/StaffRoll.h"
#include "Resource/Script.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    // strlen
    int func_020d2ff0(const char* string);
}

// What the script's opcodes use. It's defined at the end of the file, where the original has it: the compiler then
// addresses it by its own symbol, instead of from the start of the section
extern struct StaffRollLoading
{
    StaffRollLines* lines;
    SafeAllocator* allocator;
} gStaffRollLoading;

VCountAlarm gStaffRollAlarm;
TimedStaffRoll gStaffRoll;

TimedStaffRoll::TimedStaffRoll()
{
    Initialize();
}

TimedStaffRoll::~TimedStaffRoll()
{
    Finish();
}

// Opcode 100: the number of lines
static int SetLineCount(Script::Parameter* params, int numParams)
{
    gStaffRollLoading.lines->Allocate(gStaffRollLoading.allocator, params[0].ToInt());
    return 1;
}

// Opcode 101: a line
static int AddLine(Script::Parameter* params, int numParams)
{
    StaffRollLine line;
    line.Initialize();
    line.group_ = params[0].ToInt();
    line.flags_ = params[1].ToInt();
    line.height_ = params[2].ToInt();
    const char* text = params[3].ToString();
    if (text != NULL)
    {
        int length = func_020d2ff0(text);
        char* copy = (char*)gStaffRollLoading.allocator->Allocate(length + 1);
        if (copy != NULL)
        {
            memset(copy, 0, length);
            sprintf(copy, text);
            line.text_ = copy;
        }
    }
    gStaffRollLoading.lines->Add(&line);
    return 1;
}

// Opcode 102: the speed
static int SetSpeed(Script::Parameter* params, int numParams)
{
    gStaffRollLoading.lines->speed_ = params[0].ToFloat();
    return 1;
}

static Script::OpcodeLookupEntry sOpcodes[] = {
    {100, SetLineCount},
    {101, AddLine},
    {102, SetSpeed},
    {0, NULL},
};

void StaffRollLines::Initialize()
{
    lines_ = NULL;
    count_ = 0;
    capacity_ = 0;
    speed_ = 1.0f;
}

void StaffRollLines::Clear()
{
    Initialize();
}

void StaffRollLines::Load(SafeAllocator* allocator, void* file, unsigned int size)
{
    lines_ = NULL;
    count_ = 0;
    gStaffRollLoading.allocator = allocator;
    gStaffRollLoading.lines = this;
    Script script;
    script.Initialize();
    script.SetOpcodeLookup(sOpcodes);
    script.Load(file, size);
    script.Execute();
}

void StaffRollLines::Allocate(SafeAllocator* allocator, unsigned short capacity)
{
    lines_ = (StaffRollLine*)allocator->Allocate(capacity * sizeof(StaffRollLine));
    for (unsigned short i = 0; i < capacity; i++)
        lines_[i].Initialize();
    count_ = 0;
    capacity_ = capacity;
}

void StaffRollLines::Add(const StaffRollLine* line)
{
    if (capacity_ <= count_)
        return;
    if (line == NULL)
        return;
    StaffRollLine* destination = &lines_[count_];
    destination->group_ = line->group_;
    destination->height_ = line->height_;
    destination->flags_ = line->flags_;
    destination->text_ = line->text_;
    count_++;
}

StaffRollLine* StaffRollLines::Get(unsigned int index)
{
    StaffRollLine* line = NULL;
    if (index < count_)
        line = &lines_[index];
    return line;
}

StaffRollLoading gStaffRollLoading;
