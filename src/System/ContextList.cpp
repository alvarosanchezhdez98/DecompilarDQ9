#include "System/ProcessorContext.h"
#include "System/Mutex.h"
#include "System/Interrupts.h"
#include "System/DTCM.h"
#include <globaldefs.h>
#include <asmhacks.h>

extern "C"
{
    void func_020c7c30();

    void func_020c7c08(PFNSwitchContextProc);
    void func_020c75b4(ProcessorContext*, const void* proc, void* maybeUserdata, void* stackBottom, unsigned stackSize, int prio);
}

int GenerateUniqueContextID()
{
    return ++(data_021112e0.contextUniqueIDCounter);
}

#pragma optimize_for_size off

void BlockedContextList::Insert(ProcessorContext* insertion)
{
    ProcessorContext* elementAfter = this->first;
    while (elementAfter != NULL && elementAfter->priority <= insertion->priority)
    {
        if (elementAfter == insertion)
            return;
        elementAfter = elementAfter->pNextBlocked;
    }

    if (elementAfter == NULL)
    {
        // Insert at end
        ProcessorContext* elementBefore = this->last;
        if (elementBefore == NULL)
            this->first = insertion;
        else
            elementBefore->pNextBlocked = insertion;
        insertion->pPrevBlocked = elementBefore;
        insertion->pNextBlocked = NULL;
        this->last = insertion;
    }
    else
    {
        ProcessorContext* elementBefore = elementAfter->pPrevBlocked;
        if (elementBefore == NULL)
            this->first = insertion;
        else
            elementBefore->pNextBlocked = insertion;
        insertion->pPrevBlocked = elementBefore;
        insertion->pNextBlocked = elementAfter;
        elementAfter->pPrevBlocked = insertion;
    }
}

ProcessorContext* BlockedContextList::PopFront()
{
    ProcessorContext* front = this->first;
    if (front != NULL)
    {
        ProcessorContext* newFront = front->pNextBlocked;
        this->first = newFront;
        if (newFront != NULL)
            newFront->pPrevBlocked = NULL;
        else
        {
            this->last = NULL;
            // Slightly strange that this only happens if we empty the list, but
            // the function calling this also clears this entry manually in all
            // popped contexts
            front->containerBlockedQueue = NULL;
        }
    }
    return front;
}

ProcessorContext* BlockedContextList::Remove(ProcessorContext* context)
{
    ProcessorContext* searchNode = this->first;
    ProcessorContext* nodeAfter;
    ProcessorContext* nodeBefore;

    if (searchNode != NULL)
    {
        do
        {
            nodeAfter = searchNode->pNextBlocked;
            if (searchNode != context)
                continue;

            nodeBefore = searchNode->pPrevBlocked;
            
            if (this->first == searchNode)
                this->first = nodeAfter;
            else
                nodeBefore->pNextBlocked = nodeAfter;

            if (this->last == searchNode)
                this->last = nodeBefore;
            else
                nodeAfter->pPrevBlocked = nodeBefore;
            
            break;
        } while ((searchNode = nodeAfter) != NULL);
    }
    return searchNode;
}

Mutex* PopFrontMutexFromList(MutexList* list)
{
    Mutex* front = list->pFirst;
    if (front != NULL)
    {
        Mutex* next = front->pNext_;
        list->pFirst = next;
        if (next != NULL)  
            next->pPrev_ = NULL;
        else
            list->pLast = NULL;
    }
    return front;
}

ProcessorContext* InsertContextIntoGlobalList(ProcessorContext *context)
{
    ProcessorContext* loopEntry = data_021112e0.substruct_24.firstContext;
    ProcessorContext* nodeBefore = NULL;

    while (loopEntry != NULL && loopEntry->priority < context->priority)
    {
        nodeBefore = loopEntry;
        loopEntry = loopEntry->pNext;
    }

    if (nodeBefore == NULL)
    {
        context->pNext = data_021112e0.substruct_24.firstContext;
        data_021112e0.substruct_24.firstContext = context;
    }
    else
    {
        context->pNext = nodeBefore->pNext;
        nodeBefore->pNext = context;
    }
    return context;
}

void RemoveContextFromGlobalList(ProcessorContext *context)
{
    ProcessorContext* loopEntry = data_021112e0.substruct_24.firstContext;
    ProcessorContext* nodeBefore = NULL;

    while (loopEntry != NULL && loopEntry != context)
    {
        nodeBefore = loopEntry;
        loopEntry = loopEntry->pNext;
    }

    if (nodeBefore == NULL)
        data_021112e0.substruct_24.firstContext = context->pNext;
    else
        nodeBefore->pNext = context->pNext;
}

void SwitchContext()
{
    if (data_021112e0.contextSwitchLock != 0)
        return;

    Struct_02111304* contextData = &data_021112e0.substruct_24;

    // 0x12 = interrupt handling mode
    if (data_021112e0.substruct_24.unknown_2 != 0 || GetProcessorMode() == 0x12)
    {
        contextData->unknown_0 = true;
        return;
    }

    ProcessorContext* outgoing = *(data_021112e0.ppActiveContext);
    ProcessorContext* incoming = GetFirstReadyContext();

    if (outgoing == incoming || incoming == NULL)
        return;

    if (outgoing->blockState != CONTEXT_STATE_INVALID)
    {
        if (SaveContext(outgoing) != 0)
            return;
    }

    if (data_021112e0.switchContextProcA != NULL)
        data_021112e0.switchContextProcA(outgoing, incoming);

    if (contextData->switchContextProcB != NULL)
        contextData->switchContextProcB(outgoing, incoming);

    data_021112e0.substruct_24.activeContext = incoming;
    RestoreContext(incoming);
}

// data_021112e0.hasSetupPrimaryContext and data_02111304.activeContext, which the original code references by their own
// symbols in these functions
extern int data_021112ec;
extern ProcessorContext* data_02111308;

// The NitroSDK's OS_GetSystemWork()->threadinfo_mainp
#define PTR_SYSTEM_THREAD_INFO (*(Struct_02111304**)0x027fffa0)

// Where the DTCM's arena starts by default, after its data
#define ADDR_DTCM_ARENA_LO 0x027e0080

extern "C"
{
    // usa: func_020c745c
    // The NitroSDK's OS_InitThread: makes the running code the primary context (data_021113d4), with the system stack,
    // and creates the idle context (data_02111314)
    void func_020c745c()
    {
        unsigned int stackTop;

        if (data_021112e0.hasSetupPrimaryContext)
        {
            return;
        }
        data_021112e0.hasSetupPrimaryContext = true;

        data_021112e0.ppActiveContext = &data_02111308;

        data_021112e0.contextB.priority = 0x10;
        data_021112e0.contextB.uniqueID = 0;
        data_021112e0.contextB.blockState = CONTEXT_STATE_READY;
        data_021112e0.contextB.pNext = NULL;
        data_021112e0.contextB.unknown_74 = 0;

        data_021112e0.substruct_24.firstContext = &data_021113d4;
        data_021112e0.substruct_24.activeContext = &data_021113d4;

        // The system stack is below the IRQ stack, or at the start of the DTCM's arena if its size is negative
        stackTop = SYS_STACK_SIZE <= 0 ? ADDR_DTCM_ARENA_LO - SYS_STACK_SIZE
                                       : ADDR_DTCM_IRQ_STACK_BOTTOM - IRQ_STACK_SIZE - SYS_STACK_SIZE;

        data_021112e0.contextB.stackBottom = ADDR_DTCM_IRQ_STACK_BOTTOM - IRQ_STACK_SIZE;
        data_021112e0.contextB.stackTop = stackTop;
        data_021112e0.contextB.stackUnknownTopSubspaceSize = 0;

        *(unsigned int*)(data_021112e0.contextB.stackBottom - sizeof(unsigned int)) = STACK_BOTTOM_MAGIC;
        *(unsigned int*)data_021112e0.contextB.stackTop = STACK_TOP_MAGIC;

        data_021112e0.contextB.contextsAwaitingThisCompletion.first =
            data_021112e0.contextB.contextsAwaitingThisCompletion.last = NULL;

        data_021112e0.substruct_24.unknown_0 = 0;
        data_021112e0.substruct_24.unknown_2 = 0;

        PTR_SYSTEM_THREAD_INFO = &data_02111304;

        SetSwitchContextProcB(NULL);

        PopulateContext(&data_02111314, (unsigned int)InterruptWaitLoopFunction, 0,
            (unsigned int)(data_02111494 + sizeof(data_02111494) / sizeof(unsigned int)), sizeof(data_02111494), 0x1f);
        data_021112e0.contextA.priority = 0x20;
        data_021112e0.contextA.blockState = CONTEXT_STATE_READY;
    }

    // usa: func_020c75a4
    // The NitroSDK's OS_IsThreadAvailable
    int func_020c75a4()
    {
        return data_021112ec;
    }
}
