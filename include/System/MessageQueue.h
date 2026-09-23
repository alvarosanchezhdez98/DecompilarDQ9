#pragma once

#include "System/ProcessorContext.h"

// The NitroSDK's OSMessageQueue: a circular buffer of messages that contexts can wait on
struct MessageQueue
{
    BlockedContextList sendQueue; // contexts waiting for room in the buffer
    BlockedContextList receiveQueue; // contexts waiting for a message
    void** messages;
    int capacity;
    int first; // index of the first message
    int count;
};

#define MESSAGE_QUEUE_BLOCK 1 // wait instead of failing when the queue is full or empty

extern "C"
{
    void func_020c7de4(MessageQueue* queue, void** messages, int capacity);
    int func_020c7e0c(MessageQueue* queue, void* message, int flags);
    int func_020c7ea0(MessageQueue* queue, void** message, int flags);
    int func_020c7f44(MessageQueue* queue, void* message, int flags);
    int func_020c7fe0(MessageQueue* queue, void** message, int flags);
}
