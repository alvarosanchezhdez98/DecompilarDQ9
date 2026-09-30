// The multipliers of the experience by level (data/bin/expadj.nat), which the end of the battles uses (see
// BattleEnd.cpp)
#include "Scene/Overlay_23/ExperienceTable.h"
#include "Filesystem/BackgroundLoader.h"
#include <std_library_functions.h>

void ExperienceTable::Initialize()
{
    memset(this, 0, 0xc);
    task_ = -1;
    CancelTask();
}

void ExperienceTable::Finish()
{
    CancelTask();
    memset(this, 0, 0xc);
    task_ = -1;
    CancelTask();
}

void ExperienceTable::Load(SafeAllocator* allocator)
{
    CancelTask();
    memset(this, 0, 0xc);
    task_ = -1;
    CancelTask();
    allocator_ = allocator;
    step_ = 1;
    Update();
}

int ExperienceTable::Update()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    switch (step_)
    {
    case 1:
        task_ = loader->QueueLoadFile(sFile, NULL);
        step_ = 2;
        return Update();
    case 2:
        if (!loader->GetTaskStatus(task_))
            return 0;
        step_ = 3;
        return Update();
    case 3:
    {
        void* file = NULL;
        unsigned int size = 0;
        loader->GetLoadedFileByID(task_, &file, &size);
        Parse(allocator_, file, size);
        CancelTask();
        return 1;
    }
    }
    return 1;
}

const char* ExperienceTable::sFile = "data/bin/expadj.nat";

int ExperienceTable::CancelTask()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    step_ = 0;
    allocator_ = NULL;
    return 1;
}

// NONMATCHING: the C matches 49.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation: the compiler assigns the registers differently
#ifdef NONMATCHING
int ExperienceTable::Parse(SafeAllocator* allocator, void* file, unsigned int size)
{
    if (allocator == NULL || file == NULL || size == 0)
        return 0;
    if (allocator != NULL && file != NULL)
    {
        memcpy(this, file, 4);
        unsigned int entriesSize = GetEntriesSize();
        unsigned int size2 = size_;
        entries_ = entriesSize == 0 ? NULL : (ExperienceEntry*)allocator->Allocate(entriesSize);
        unk_8 = size2 == 0 ? NULL : allocator->Allocate(size2);
        if (entries_ != NULL)
            memcpy(entries_, (char*)file + 4, entriesSize);
        if (unk_8 != NULL)
            memcpy(unk_8, (char*)file + (GetEntriesSize() + 4), size2);
        loaded_ = 1;
    }
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN15ExperienceTable14GetEntriesSizeEv(); // ExperienceTable::GetEntriesSize
}

asm int ExperienceTable::Parse(SafeAllocator* allocator, void* file, unsigned int size)
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    movs r7, r1
    mov r6, r2
    cmpne r6, #0x0
    mov r8, r0
    cmpne r3, #0x0
    moveq r0, #0x0
    ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
    cmp r7, #0x0
    cmpne r6, #0x0
    beq @L021f551c
    mov r1, r6
    mov r2, #0x4
    bl memcpy
    mov r0, r8
    bl _ZN15ExperienceTable14GetEntriesSizeEv
    ldr r1, [r8, #0x0]
    movs r4, r0
    mov r0, r1, lsl #0x1
    mov r5, r0, lsr #0xd
    moveq r0, #0x0
    beq @L021f54ac
    mov r0, r7
    mov r1, r4
    bl _ZN13SafeAllocator8AllocateEj
@L021f54ac:
    str r0, [r8, #0x4]
    cmp r5, #0x0
    moveq r0, #0x0
    beq @L021f54c8
    mov r0, r7
    mov r1, r5
    bl _ZN13SafeAllocator8AllocateEj
@L021f54c8:
    str r0, [r8, #0x8]
    ldr r0, [r8, #0x4]
    cmp r0, #0x0
    beq @L021f54e4
    mov r2, r4
    add r1, r6, #0x4
    bl memcpy
@L021f54e4:
    ldr r0, [r8, #0x8]
    cmp r0, #0x0
    beq @L021f550c
    mov r0, r8
    bl _ZN15ExperienceTable14GetEntriesSizeEv
    add r1, r0, #0x4
    ldr r0, [r8, #0x8]
    mov r2, r5
    add r1, r6, r1
    bl memcpy
@L021f550c:
    ldr r0, [r8, #0x0]
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r8, #0x0]
@L021f551c:
    mov r0, #0x1
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
#endif

unsigned int ExperienceTable::GetEntriesSize()
{
    return count_ * sizeof(unsigned int);
}

ExperienceEntry* ExperienceTable::FindEntry(int value)
{
    ExperienceEntry* entry = entries_;
    while (count_ != 0)
    {
        unsigned int limit = entry->limit_;
        if (limit == 0 || value <= (int)limit)
            return entry;
        entry++;
    }
    return NULL;
}

unsigned int ExperienceTable::GetMultiplier(int value, unsigned int multiplier)
{
    unsigned int result = multiplier;
    ExperienceEntry* entry = FindEntry(value);
    if (entry != NULL)
        result = entry->multiplier_;
    return result;
}

