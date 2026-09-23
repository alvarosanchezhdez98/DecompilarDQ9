#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's heap.c (snd_heap.c): a heap for the sound data, on a frame heap (HMRFAllocator). Its state can be
// saved and loaded, and each block has a callback that's called when it's freed.
// NNS_SndHeapGetCurrentLevel, NNS_SndHeapGetSize and NNS_SndHeapGetFreeSize aren't in the ROM.

// The alignment of the blocks
#define HEAP_ALIGN 32
// NitroSystem's NNS_FND_HEAP_DEFAULT_ALIGNMENT
#define DEFAULT_ALIGN 4
// NitroSystem's NNS_FND_FRMHEAP_FREE_ALL: frees both ends of the frame heap
#define FREE_ALL 3

#define ROUND_UP(value, align) (((unsigned long)(value) + ((align) - 1)) & ~((align) - 1))

// NitroSystem's NNSSndHeap
struct SoundHeap
{
    HMRFAllocator* handle;
    SignedAllocatorList sectionList; // HeapSection
};

// NitroSystem's NNSSndHeapBlock: a block, before its buffer
struct HeapBlock
{
    ListLink link;
    unsigned long size;
    SoundHeapDisposeCallback callback;
    unsigned long data1;
    unsigned long data2;
    unsigned char padding[0x20 - ((sizeof(ListLink) + sizeof(SoundHeapDisposeCallback) + sizeof(unsigned long) * 3)
        & 0x1f)];
    unsigned long buffer[];
};

// NitroSystem's NNSSndHeapSection: the blocks allocated since a state was saved
struct HeapSection
{
    SignedAllocatorList blockList; // HeapBlock
    ListLink link;
};

extern "C"
{
    int func_020bdbf0(SoundHeap* heap, HMRFAllocator* handle);
    int func_020bdc24(SoundHeap* heap);
    void func_020bdc60();

    // usa: func_020bd914
    // NNS_SndHeapCreate
    SoundHeap* func_020bd914(void* startAddress, unsigned long size)
    {
        SoundHeap* heap;
        void* endAddress;
        HMRFAllocator* handle;

        endAddress = (unsigned char*)startAddress + size;
        startAddress = (void*)ROUND_UP(startAddress, 4);

        if (startAddress > endAddress)
            return NULL;

        size = (unsigned long)((unsigned char*)endAddress - (unsigned char*)startAddress);
        if (size < sizeof(SoundHeap))
            return NULL;
        size -= sizeof(SoundHeap);

        heap = (SoundHeap*)startAddress;
        startAddress = heap + 1;

        handle = HMRFAllocator::CreateAtLocation(startAddress, size, 0);
        if (handle == NULL)
            return NULL;

        if (!func_020bdbf0(heap, handle))
        {
            handle->RemoveFromTree();
            return NULL;
        }
        return heap;
    }

    // usa: func_020bd984
    // NNS_SndHeapDestroy
    void func_020bd984(SoundHeap* heap)
    {
        func_020bd99c(heap);
        heap->handle->RemoveFromTree();
    }

    // usa: func_020bd99c
    // NNS_SndHeapClear: frees all the blocks, calling their callbacks from the last to the first
    void func_020bd99c(SoundHeap* heap)
    {
        HeapSection* section = NULL;
        void* object;
        int result;
        int doCallback = 0;

        while ((section = (HeapSection*)GetPrevListObject(&heap->sectionList, NULL)) != NULL)
        {
            object = NULL;
            while ((object = GetPrevListObject(&section->blockList, object)) != NULL)
            {
                HeapBlock* block = (HeapBlock*)object;
                if (block->callback != NULL)
                {
                    block->callback(block->buffer, block->size, block->data1, block->data2);
                    doCallback = 1;
                }
            }
            RemoveListObject(&heap->sectionList, section);
        }

        heap->handle->Free(FREE_ALL);

        if (doCallback)
            func_020bdc60();

        result = func_020bdc24(heap);
    }

    // usa: func_020bda58
    // NNS_SndHeapAlloc
    void* func_020bda58(SoundHeap* heap, unsigned long size, SoundHeapDisposeCallback callback, unsigned long data1,
        unsigned long data2)
    {
        HeapSection* section;
        HeapBlock* block;

        block = (HeapBlock*)heap->handle->Allocate(sizeof(HeapBlock) + ROUND_UP(size, HEAP_ALIGN), HEAP_ALIGN);
        if (block == NULL)
            return NULL;

        section = (HeapSection*)GetPrevListObject(&heap->sectionList, NULL);

        block->size = size;
        block->callback = callback;
        block->data1 = data1;
        block->data2 = data2;
        AppendListObject(&section->blockList, block);

        return block->buffer;
    }

    // usa: func_020bdac0
    // NNS_SndHeapSaveState: the level of the saved state, or -1
    int func_020bdac0(SoundHeap* heap)
    {
        int result;

        if (!heap->handle->SaveCurrentState(heap->sectionList.numElements))
            return -1;

        if (!func_020bdc24(heap))
        {
            result = heap->handle->RestoreState(0);
            return -1;
        }

        return heap->sectionList.numElements - 1;
    }

    // usa: func_020bdb0c
    // NNS_SndHeapLoadState: frees the blocks allocated since the state of a level was saved
    void func_020bdb0c(SoundHeap* heap, int level)
    {
        HeapSection* section;
        void* object = NULL;
        int result;
        int doCallback = 0;

        if (level == 0)
        {
            func_020bd99c(heap);
            return;
        }

        while (level < heap->sectionList.numElements)
        {
            section = (HeapSection*)GetPrevListObject(&heap->sectionList, NULL);

            while ((object = GetPrevListObject(&section->blockList, object)) != NULL)
            {
                HeapBlock* block = (HeapBlock*)object;
                if (block->callback != NULL)
                {
                    block->callback(block->buffer, block->size, block->data1, block->data2);
                    doCallback = 1;
                }
            }

            RemoveListObject(&heap->sectionList, section);
        }

        result = heap->handle->RestoreState(level);

        if (doCallback)
            func_020bdc60();

        result = heap->handle->SaveCurrentState(heap->sectionList.numElements);
        result = func_020bdc24(heap);
    }

    // usa: func_020bdbe0
    // InitHeapSection
    void func_020bdbe0(HeapSection* section)
    {
        InitList(&section->blockList, LIST_LINK_OFFSET(HeapBlock, link));
    }

    // usa: func_020bdbf0
    // InitHeap
    int func_020bdbf0(SoundHeap* heap, HMRFAllocator* handle)
    {
        InitList(&heap->sectionList, LIST_LINK_OFFSET(HeapSection, link));
        heap->handle = handle;

        if (!func_020bdc24(heap))
            return 0;
        return 1;
    }

    // usa: func_020bdc24
    // NewSection
    int func_020bdc24(SoundHeap* heap)
    {
        HeapSection* section;

        section = (HeapSection*)heap->handle->Allocate(sizeof(HeapSection), DEFAULT_ALIGN);
        if (section == NULL)
            return 0;

        func_020bdbe0(section);
        AppendListObject(&heap->sectionList, section);
        return 1;
    }

    // usa: func_020bdc60
    // EraseSync: waits for the sound driver to stop using the freed data
    void func_020bdc60()
    {
        unsigned long commandTag;

        commandTag = func_020d26ec();
        func_020d24c4(COMMAND_BLOCK);
        func_020d2680(commandTag);
    }
}
