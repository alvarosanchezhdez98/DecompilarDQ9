#include "System/Heap.h"
#include "System/Interrupts.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_alloc.c. The other functions (creating and destroying heaps...) aren't in the ROM: the game has
// its own allocators.

#define HEAP_ALIGNMENT 32
#define HEAP_ROUND(n, a) (((unsigned long)(n) + (a) - 1) & ~((a) - 1))
// The size of a cell's header, unsigned like in the NitroSDK
#define HEAP_HEADER_SIZE HEAP_ROUND(sizeof(HeapCell), HEAP_ALIGNMENT)
// The smallest free cell that's worth keeping
#define HEAP_MIN_CELL_SIZE (HEAP_HEADER_SIZE + HEAP_ALIGNMENT)

// The NitroSDK's OSiHeapInfo: the heaps of each arena, if it has any
HeapInfo* heapInfoByArena[ARENA_COUNT];

extern "C"
{
    // usa: func_020c8768
    // DLAddFront: adds a cell at the front of a list, and returns the new list
    HeapCell* func_020c8768(HeapCell* list, HeapCell* cell)
    {
        cell->next = list;
        cell->prev = NULL;
        if (list != NULL)
        {
            list->prev = cell;
        }
        return cell;
    }

    // usa: func_020c8784
    // DLExtract: removes a cell from a list, and returns the new list
    HeapCell* func_020c8784(HeapCell* list, HeapCell* cell)
    {
        if (cell->next != NULL)
        {
            cell->next->prev = cell->prev;
        }
        if (cell->prev == NULL)
        {
            return cell->next;
        }
        else
        {
            cell->prev->next = cell->next;
            return list;
        }
    }

    // usa: func_020c87ac
    // DLInsert: inserts a cell in a list sorted by address, merging it with the cells next to it, and returns the new
    // list
    HeapCell* func_020c87ac(HeapCell* list, HeapCell* cell)
    {
        HeapCell* prev;
        HeapCell* next;

        for (next = list, prev = NULL; next; prev = next, next = next->next)
        {
            if (cell <= next)
            {
                break;
            }
        }

        cell->next = next;
        cell->prev = prev;

        if (next)
        {
            next->prev = cell;
            if ((char*)cell + cell->size == (char*)next)
            {
                cell->size += next->size;
                cell->next = next = next->next;
                if (next)
                {
                    next->prev = cell;
                }
            }
        }

        if (prev)
        {
            prev->next = cell;
            if ((char*)prev + prev->size == (char*)cell)
            {
                prev->size += cell->size;
                prev->next = next;
                if (next)
                {
                    next->prev = prev;
                }
            }
            return list;
        }
        else
        {
            return cell;
        }
    }

    // usa: func_020c8854
    // OS_AllocFromHeap
    void* func_020c8854(ArenaID id, long heap, unsigned long size)
    {
        HeapInfo* heapInfo;
        HeapDescriptor* descriptor;
        HeapCell* cell;
        HeapCell* newCell;
        long leftoverSize;
        int priorState = DisableIRQInterrupts();

        heapInfo = heapInfoByArena[id];
        if (heapInfo == NULL)
        {
            SetIRQInterruptState(priorState);
            return NULL;
        }

        if (heap < 0)
        {
            heap = heapInfo->currentHeap;
        }
        descriptor = &heapInfo->heaps[heap];

        size += HEAP_HEADER_SIZE;
        size = HEAP_ROUND(size, HEAP_ALIGNMENT);

        // The first free cell that's big enough
        for (cell = descriptor->free; cell != NULL; cell = cell->next)
        {
            if ((long)size <= cell->size)
            {
                break;
            }
        }

        if (cell == NULL)
        {
            SetIRQInterruptState(priorState);
            return NULL;
        }

        leftoverSize = cell->size - size;
        if (leftoverSize < HEAP_MIN_CELL_SIZE)
        {
            // Too small to keep: allocate the whole cell
            descriptor->free = func_020c8784(descriptor->free, cell);
        }
        else
        {
            // Split the cell, and keep the rest in the free list
            cell->size = (long)size;
            newCell = (HeapCell*)((char*)cell + size);
            newCell->size = leftoverSize;
            newCell->prev = cell->prev;
            newCell->next = cell->next;
            if (newCell->next != NULL)
            {
                newCell->next->prev = newCell;
            }
            if (newCell->prev != NULL)
            {
                newCell->prev->next = newCell;
            }
            else
            {
                descriptor->free = newCell;
            }
        }

        descriptor->allocated = func_020c8768(descriptor->allocated, cell);

        SetIRQInterruptState(priorState);
        return (char*)cell + HEAP_HEADER_SIZE;
    }

    // usa: func_020c895c
    // OS_FreeToHeap
    void func_020c895c(ArenaID id, long heap, void* ptr)
    {
        HeapInfo* heapInfo;
        HeapDescriptor* descriptor;
        HeapCell* cell;
        int priorState = DisableIRQInterrupts();

        heapInfo = heapInfoByArena[id];
        if (heap < 0)
        {
            heap = heapInfo->currentHeap;
        }
        descriptor = &heapInfo->heaps[heap];

        cell = (HeapCell*)((char*)ptr - HEAP_HEADER_SIZE);
        descriptor->allocated = func_020c8784(descriptor->allocated, cell);
        descriptor->free = func_020c87ac(descriptor->free, cell);

        SetIRQInterruptState(priorState);
    }
}
