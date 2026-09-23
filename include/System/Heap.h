#pragma once

#include "System/Arena.h"

// The NitroSDK's heaps, in the arenas (see Arena.h)

// A block of memory in a heap, free or allocated, with this header at its start
struct HeapCell
{
    HeapCell* prev;
    HeapCell* next;
    long size; // with the header
};

struct HeapDescriptor
{
    long size; // negative when unused
    HeapCell* free;
    HeapCell* allocated;
};

// The heaps of an arena
struct HeapInfo
{
    long currentHeap;
    long heapCount;
    void* arenaStart;
    void* arenaEnd;
    HeapDescriptor* heaps;
};

extern "C"
{
    // usa: func_020c8854
    // OS_AllocFromHeap: allocates size bytes from a heap of an arena (the current one if heap is negative). Returns
    // NULL if there isn't enough free memory.
    void* func_020c8854(ArenaID id, long heap, unsigned long size);
    // usa: func_020c895c
    // OS_FreeToHeap: frees memory allocated with func_020c8854
    void func_020c895c(ArenaID id, long heap, void* ptr);
}
