// The models of the items of the equipment, which overlay 5 uses (see EquipmentModelTable.h)
#pragma ipa file
#include "Scene/Overlay_23/EquipmentModelTable.h"
#include <std_library_functions.h>

extern "C"
{
    // Fixes an entry's pointers
    void func_020de574(PartNameHeader* header, PartEntry* entry);
    void func_020de5b0(PartNameHeader* header);
}

// Runs a function for each entry of the file
static inline void ForEachEntry(PartNameHeader* header, void (*function)(PartNameHeader* header, PartEntry* entry))
{
    PartEntry* entry = header->entries_;
    int count;
    if (entry != NULL && (count = header->count_) != 0 && (int)function != 0)
    {
        for (int i = 0; i < count; i++, entry++)
            function(header, entry);
    }
}

void EquipmentModelTable::Initialize()
{
    models_ = NULL;
    capacity_ = 0;
    count_ = 0;
}

// NONMATCHING: the C matches 84.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original reads the number of entries again after it stores where the rest of the file is, and computes that
// address in another order
#ifdef NONMATCHING
void EquipmentModelTable::Load(SafeAllocator* allocator, void* file, unsigned int size)
{
    int count;
    PartModelInfo* info;
    if (allocator == NULL || file == NULL || size == 0)
        return;
    capacity_ = 0;
    count_ = 0;
    PartNameHeader header;
    memset(&header, 0, sizeof(header));
    int fixed = 0;
    if (file != NULL)
    {
        memcpy(&header, file, 0xc);
        header.entries_ = (PartEntry*)((char*)file + 0xc);
        header.unk_10 = (char*)file + ((header.unk_2_15 ? 0x58 : 0) + header.count2_ * 0x20 + header.count_ * 0x20 + 0xc);
        if (header.fixed_)
        {
            fixed = 1;
        }
        else
        {
            ForEachEntry(&header, func_020de574);
            header.fixed_ = 1;
            ((PartNameHeader*)file)->fixed_ = 1;
        }
    }
    if (!fixed)
        func_020de5b0(&header);
    PartEntry* entry = header.entries_;
    count = header.count_;
    for (int i = 0; i < count; i++, entry++)
    {
        int equipment = entry->category_ <= 7 ? 1 : 0;
        if (equipment)
            capacity_++;
    }
    EquipmentModel* model = (EquipmentModel*)allocator->Allocate(capacity_ * sizeof(EquipmentModel));
    models_ = model;
    if (model == NULL)
        return;
    entry = header.entries_;
    for (int i = 0; i < count; i++, entry++)
    {
        int equipment = entry->category_ <= 7 ? 1 : 0;
        PartModelInfo* info;
        if (equipment && (info = entry->model_) != NULL)
        {
            count_++;
            model->id_ = entry->unk_18;
            model->category_ = entry->category_;
            model->unk_4_0 = info->unk_0_0;
            model->unk_4_7 = info->unk_0_7;
            model->unk_4_11 = info->unk_4_0;
            model->unk_4_23 = info->unk_0_29;
            model->unk_4_24 = info->unk_0_30;
            model->unk_4_26 = info->unk_4_27;
            model->unk_4_27 = info->unk_4_28;
            model->unk_4_28 = info->unk_4_29;
            model++;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
}

asm void EquipmentModelTable::Load(SafeAllocator* allocator, void* file, unsigned int size)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x14
    mov r8, r2
    movs r9, r1
    cmpne r8, #0x0
    mov r10, r0
    cmpne r3, #0x0
    beq @L021db07c
    mov r1, #0x0
    strh r1, [r10, #0x4]
    add r0, sp, #0x0
    mov r2, #0x14
    strh r1, [r10, #0x6]
    bl memset
    cmp r8, #0x0
    mov r4, #0x0
    beq @L021dae90
    add r0, sp, #0x0
    mov r1, r8
    mov r2, #0xc
    bl memcpy
    add r1, r8, #0xc
    ldrh r0, [sp, #0x2]
    str r1, [sp, #0xc]
    ldrh r2, [sp, #0x0]
    mov r1, r0, lsl #0x11
    mov r0, r0, lsl #0x10
    movs r0, r0, lsr #0x1f
    movne r0, #0x58
    mov r1, r1, lsr #0x11
    moveq r0, r4
    add r0, r0, r1, lsl #0x5
    add r0, r0, r2, lsl #0x5
    add r1, r0, #0xc
    ldr r0, [sp, #0x8]
    add r1, r8, r1
    movs r0, r0, lsr #0x1f
    str r1, [sp, #0x10]
    movne r4, #0x1
    bne @L021dae90
    ldr r5, [sp, #0xc]
    cmp r5, #0x0
    ldrneh r7, [sp, #0x0]
    cmpne r7, #0x0
    ldrne r0, =func_020de574
    cmpne r0, #0x0
    beq @L021dae70
    mov r6, #0x0
    add r11, sp, #0x0
    b @L021dae68
@L021dae54:
    mov r0, r11
    mov r1, r5
    bl func_020de574
    add r6, r6, #0x1
    add r5, r5, #0x20
@L021dae68:
    cmp r6, r7
    blt @L021dae54
@L021dae70:
    ldr r0, [sp, #0x8]
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [sp, #0x8]
    ldr r0, [r8, #0x8]
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r8, #0x8]
@L021dae90:
    cmp r4, #0x0
    bne @L021daea0
    add r0, sp, #0x0
    bl func_020de5b0
@L021daea0:
    mov r4, #0x0
    ldrh r5, [sp, #0x0]
    ldr r3, [sp, #0xc]
    mov r1, r4
    mov r2, #0x1
    b @L021daee8
@L021daeb8:
    ldr r0, [r3, #0x8]
    add r4, r4, #0x1
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    cmp r0, #0x7
    movls r0, r2
    movhi r0, r1
    cmp r0, #0x0
    ldrneh r0, [r10, #0x4]
    add r3, r3, #0x20
    addne r0, r0, #0x1
    strneh r0, [r10, #0x4]
@L021daee8:
    cmp r4, r5
    blt @L021daeb8
    ldrh r1, [r10, #0x4]
    mov r0, r9
    mov r1, r1, lsl #0x3
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x0]
    cmp r0, #0x0
    beq @L021db07c
    mov r7, #0x0
    ldr r6, [sp, #0xc]
    mov r3, r7
    mov r4, #0x1
    ldr r9, =0xff8007ff
    b @L021db074
@L021daf24:
    ldr r1, [r6, #0x8]
    mov r1, r1, lsl #0x1c
    mov r1, r1, lsr #0x1c
    cmp r1, #0x7
    movls r1, r4
    movhi r1, r3
    cmp r1, #0x0
    ldrne r2, [r6, #0x0]
    cmpne r2, #0x0
    beq @L021db06c
    ldrh r1, [r10, #0x6]
    add r1, r1, #0x1
    strh r1, [r10, #0x6]
    ldrsh r1, [r6, #0x18]
    strh r1, [r0, #0x0]
    ldr r8, [r6, #0x8]
    ldrh r1, [r0, #0x2]
    mov r8, r8, lsl #0x1c
    mov r8, r8, lsr #0x1c
    mov r8, r8, lsl #0x10
    mov r8, r8, lsr #0x10
    bic r11, r1, #0xf
    and r1, r8, #0xf
    orr r1, r11, r1
    strh r1, [r0, #0x2]
    ldr r1, [r2, #0x0]
    ldr r8, [r0, #0x4]
    mov r1, r1, lsl #0x19
    mov r1, r1, lsr #0x19
    bic r8, r8, #0x7f
    and r1, r1, #0x7f
    orr r8, r8, r1
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x0]
    bic r8, r8, #0x780
    mov r1, r1, lsl #0x15
    mov r1, r1, lsr #0x1c
    mov r1, r1, lsl #0x1c
    orr r8, r8, r1, lsr #0x15
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x4]
    and r8, r8, r9
    mov r1, r1, lsl #0x14
    mov r1, r1, lsr #0x14
    mov r1, r1, lsl #0x14
    orr r8, r8, r1, lsr #0x9
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x0]
    bic r8, r8, #0x800000
    mov r1, r1, lsl #0x2
    mov r1, r1, lsr #0x1f
    mov r1, r1, lsl #0x1f
    orr r8, r8, r1, lsr #0x8
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x0]
    bic r8, r8, #0x3000000
    mov r1, r1, lsr #0x1e
    mov r1, r1, lsl #0x1e
    orr r8, r8, r1, lsr #0x6
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x4]
    bic r8, r8, #0x4000000
    mov r1, r1, lsl #0x4
    mov r1, r1, lsr #0x1f
    mov r1, r1, lsl #0x1f
    orr r8, r8, r1, lsr #0x5
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x4]
    bic r8, r8, #0x8000000
    mov r1, r1, lsl #0x3
    mov r1, r1, lsr #0x1f
    mov r1, r1, lsl #0x1f
    orr r8, r8, r1, lsr #0x4
    str r8, [r0, #0x4]
    ldr r1, [r2, #0x4]
    bic r2, r8, #0x10000000
    mov r1, r1, lsl #0x2
    mov r1, r1, lsr #0x1f
    mov r1, r1, lsl #0x1f
    orr r1, r2, r1, lsr #0x3
    str r1, [r0, #0x4]
    add r0, r0, #0x8
@L021db06c:
    add r7, r7, #0x1
    add r6, r6, #0x20
@L021db074:
    cmp r7, r5
    blt @L021daf24
@L021db07c:
    add sp, sp, #0x14
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

EquipmentModel* EquipmentModelTable::Find(int id)
{
    if (id < 0)
        return NULL;
    for (int i = 0; i < count_; i++)
    {
        if (id == models_[i].id_)
            return &models_[i];
    }
    return NULL;
}
