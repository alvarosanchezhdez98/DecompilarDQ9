#pragma once

#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"

// The model of an item of the equipment (8 bytes): what EquipmentModelTable copies from its PartEntry and
// PartModelInfo
struct EquipmentModel
{
    // The item's PartEntry::unk_18
    short id_;
    unsigned short category_ : 4;
    unsigned short unk_2_4 : 12;
    unsigned int unk_4_0 : 7;
    unsigned int unk_4_7 : 4;
    unsigned int unk_4_11 : 12;
    unsigned int unk_4_23 : 1;
    unsigned int unk_4_24 : 2;
    unsigned int unk_4_26 : 1;
    unsigned int unk_4_27 : 1;
    unsigned int unk_4_28 : 1;
    unsigned int unk_4_29 : 3;
};

// The models of the items of the equipment (the categories 0 to 7) of a PartNameTable's file, which overlay 5 uses
struct EquipmentModelTable
{
    EquipmentModel* models_;
    // The items of the equipment, and the ones that have a model
    unsigned short capacity_;
    unsigned short count_;

    void Initialize();
    void Load(SafeAllocator* allocator, void* file, unsigned int size);
    EquipmentModel* Find(int id);
};
