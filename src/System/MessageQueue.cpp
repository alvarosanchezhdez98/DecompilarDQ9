#include "System/MessageQueue.h"
#include "System/Interrupts.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_message.c

extern "C"
{
    // usa: func_020c7de4
    // OS_InitMessageQueue
    void func_020c7de4(MessageQueue* queue, void** messages, int capacity)
    {
        queue->sendQueue.first = queue->sendQueue.last = NULL;
        queue->receiveQueue.first = queue->receiveQueue.last = NULL;
        queue->messages = messages;
        queue->capacity = capacity;
        queue->first = 0;
        queue->count = 0;
    }

    // usa: func_020c7e0c
    // OS_SendMessage: adds a message at the end. Returns false if the queue is full and flags doesn't have
    // MESSAGE_QUEUE_BLOCK.
    int func_020c7e0c(MessageQueue* queue, void* message, int flags)
    {
        int priorState = DisableIRQInterrupts();
        int last;

        while (queue->capacity <= queue->count)
        {
            if (!(flags & MESSAGE_QUEUE_BLOCK))
            {
                SetIRQInterruptState(priorState);
                return false;
            }
            BlockCurrentContext(&queue->sendQueue);
        }

        last = (queue->first + queue->count) % queue->capacity;
        queue->messages[last] = message;
        queue->count++;

        UnblockContexts(&queue->receiveQueue);

        SetIRQInterruptState(priorState);
        return true;
    }

    // usa: func_020c7ea0
    // OS_ReceiveMessage: removes the first message. Returns false if the queue is empty and flags doesn't have
    // MESSAGE_QUEUE_BLOCK.
    int func_020c7ea0(MessageQueue* queue, void** message, int flags)
    {
        int priorState = DisableIRQInterrupts();

        while (queue->count == 0)
        {
            if (!(flags & MESSAGE_QUEUE_BLOCK))
            {
                SetIRQInterruptState(priorState);
                return false;
            }
            BlockCurrentContext(&queue->receiveQueue);
        }

        if (message != NULL)
            *message = queue->messages[queue->first];

        queue->first = (queue->first + 1) % queue->capacity;
        queue->count--;

        UnblockContexts(&queue->sendQueue);

        SetIRQInterruptState(priorState);
        return true;
    }

    // usa: func_020c7f44
    // OS_JamMessage: adds a message at the front. Returns false if the queue is full and flags doesn't have
    // MESSAGE_QUEUE_BLOCK.
    int func_020c7f44(MessageQueue* queue, void* message, int flags)
    {
        int priorState = DisableIRQInterrupts();

        while (queue->capacity <= queue->count)
        {
            if (!(flags & MESSAGE_QUEUE_BLOCK))
            {
                SetIRQInterruptState(priorState);
                return false;
            }
            BlockCurrentContext(&queue->sendQueue);
        }

        queue->first = (queue->first + queue->capacity - 1) % queue->capacity;
        queue->messages[queue->first] = message;
        queue->count++;

        UnblockContexts(&queue->receiveQueue);

        SetIRQInterruptState(priorState);
        return true;
    }

    // usa: func_020c7fe0
    // OS_ReadMessage: reads the first message without removing it. Returns false if the queue is empty and flags
    // doesn't have MESSAGE_QUEUE_BLOCK.
    int func_020c7fe0(MessageQueue* queue, void** message, int flags)
    {
        int priorState = DisableIRQInterrupts();

        while (queue->count == 0)
        {
            if (!(flags & MESSAGE_QUEUE_BLOCK))
            {
                SetIRQInterruptState(priorState);
                return false;
            }
            BlockCurrentContext(&queue->receiveQueue);
        }

        if (message != NULL)
            *message = queue->messages[queue->first];

        SetIRQInterruptState(priorState);
        return true;
    }
}
