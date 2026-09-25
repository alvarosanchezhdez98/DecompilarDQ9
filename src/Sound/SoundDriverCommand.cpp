#include "Sound/Sound.h"
#include "Sound/SoundDriver.h"
#include "System/Cache.h"
#include "System/IPC.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_command.c: the commands for the sound driver. They're allocated from a free list, added to a
// reserved list, and SND_FlushCommand sends that list to the ARM7, which answers when it has run it.

// The IPC command of the sound driver (the NitroSDK's PXI_FIFO_TAG_SOUND)
#define IPC_COMMAND_SOUND 7
// SND_PXI_FIFO_MESSAGE_BUFSIZE: the lists that the ARM7 can be running at once
#define WAITING_LIST_COUNT 8

// SND_COMMAND_IMMEDIATE: SND_FlushCommand also tells the ARM7 to run the commands now
#define COMMAND_IMMEDIATE 2

// The variables are defined in this order so that the compiler lays them out like the original
static SoundCommand* sReserveList;
static SoundCommand* sFreeList;
static unsigned long sCurrentTag;
static int sWaitingCommandListCount;
static SoundSharedWork sSharedWork __attribute__((aligned(32)));
static int sWaitingCommandListQueueRead;
static SoundCommand* sFreeListEnd;
static SoundCommand* sReserveListEnd;
static int sWaitingCommandListQueueWrite;
static unsigned long sFinishedTag;
static SoundCommand* sWaitingCommandListQueue[WAITING_LIST_COUNT + 1];
static SoundCommand sCommandArray[SOUND_COMMAND_COUNT] __attribute__((aligned(32)));

extern "C"
{
    // OS_IsRunOnEmulator
    int func_020c7dc4();
    // OS_SpinWait
    void func_020c976c(unsigned long cycles);

    static void func_020d27fc(unsigned int command, unsigned int data, unsigned int error);
    static void func_020d2820();
    static void func_020d2880();
    static SoundCommand* func_020d28a8();
    static int func_020d28f0();
    int func_020d2768();
    int func_020d27a4();

    void func_020d2220()
    {
        int i;
        func_020d2820();
        sFreeList = &sCommandArray[0];
        for (i = 0; i < SOUND_COMMAND_COUNT - 1; i++)
            sCommandArray[i].next = &sCommandArray[i + 1];
        sCommandArray[SOUND_COMMAND_COUNT - 1].next = NULL;
        sFreeListEnd = &sCommandArray[SOUND_COMMAND_COUNT - 1];
        sReserveList = NULL;
        sReserveListEnd = NULL;
        sWaitingCommandListCount = 0;
        sWaitingCommandListQueueRead = 0;
        sWaitingCommandListQueueWrite = 0;
        sCurrentTag = 1;
        sFinishedTag = 0;
        data_021142c0 = &sSharedWork;
        func_020d2a48(data_021142c0);
        {
            SoundCommand* const command = func_020d2404(COMMAND_BLOCK);
            if (command == NULL)
                return;
            command->id = COMMAND_SHARED_WORK;
            command->arg[0] = (unsigned long)data_021142c0;
            func_020d248c(command);
            func_020d24c4(COMMAND_BLOCK);
        }
    }

    void* func_020d22f4(unsigned long flags)
    {
        int lastState = DisableIRQInterrupts();
        SoundCommand* list;
        SoundCommand* end;
        if (flags & COMMAND_BLOCK)
        {
            while (sFinishedTag == func_020d2a20())
            {
                SetIRQInterruptState(lastState);
                func_020c976c(100);
                lastState = DisableIRQInterrupts();
            }
        }
        else if (sFinishedTag == func_020d2a20())
        {
            SetIRQInterruptState(lastState);
            return NULL;
        }
        list = sWaitingCommandListQueue[sWaitingCommandListQueueRead];
        sWaitingCommandListQueueRead++;
        if (sWaitingCommandListQueueRead > WAITING_LIST_COUNT)
            sWaitingCommandListQueueRead = 0;
        end = list;
        while (end->next != NULL)
            end = end->next;
        if (sFreeListEnd != NULL)
            sFreeListEnd->next = list;
        else
            sFreeList = list;
        sFreeListEnd = end;
        sWaitingCommandListCount--;
        sFinishedTag++;
        SetIRQInterruptState(lastState);
        return list;
    }

    SoundCommand* func_020d2404(unsigned long flags)
    {
        SoundCommand* command;
        if (!func_020d28f0())
            return NULL;
        command = func_020d28a8();
        if (command != NULL)
            return command;
        if (!(flags & COMMAND_BLOCK))
            return NULL;
        if (func_020d27e0() > 0)
        {
            while (func_020d22f4(COMMAND_NO_BLOCK) != NULL)
            {
            }
            command = func_020d28a8();
            if (command != NULL)
                return command;
        }
        else
        {
            func_020d24c4(COMMAND_BLOCK);
        }
        func_020d2880();
        do
        {
            func_020d22f4(COMMAND_BLOCK);
            command = func_020d28a8();
        } while (command == NULL);
        return command;
    }

    void func_020d248c(SoundCommand* command)
    {
        int lastState = DisableIRQInterrupts();
        if (sReserveListEnd == NULL)
        {
            sReserveList = command;
            sReserveListEnd = command;
        }
        else
        {
            sReserveListEnd->next = command;
            sReserveListEnd = command;
        }
        command->next = NULL;
        SetIRQInterruptState(lastState);
    }

    int func_020d24c4(unsigned long flags)
    {
        int lastState = DisableIRQInterrupts();
        if (sReserveList == NULL)
        {
            SetIRQInterruptState(lastState);
            return true;
        }
        if (sWaitingCommandListCount >= WAITING_LIST_COUNT)
        {
            if (!(flags & COMMAND_BLOCK))
            {
                SetIRQInterruptState(lastState);
                return false;
            }
            do
            {
                func_020d22f4(COMMAND_BLOCK);
            } while (sWaitingCommandListCount >= WAITING_LIST_COUNT);
            if (sReserveList == NULL)
            {
                SetIRQInterruptState(lastState);
                return true;
            }
        }
        CleanInvalidateCacheRange(sCommandArray, sizeof(sCommandArray));
        if (SendCommandToArm7(IPC_COMMAND_SOUND, (int)sReserveList, false) < 0)
        {
            if (!(flags & COMMAND_BLOCK))
            {
                SetIRQInterruptState(lastState);
                return false;
            }
            while (sWaitingCommandListCount >= WAITING_LIST_COUNT ||
                   SendCommandToArm7(IPC_COMMAND_SOUND, (int)sReserveList, false) < 0)
            {
                SetIRQInterruptState(lastState);
                func_020d22f4(COMMAND_NO_BLOCK);
                lastState = DisableIRQInterrupts();
                CleanInvalidateCacheRange(sCommandArray, sizeof(sCommandArray));
                if (sReserveList == NULL)
                {
                    SetIRQInterruptState(lastState);
                    return true;
                }
            }
        }
        sWaitingCommandListQueue[sWaitingCommandListQueueWrite] = sReserveList;
        sWaitingCommandListQueueWrite++;
        if (sWaitingCommandListQueueWrite > WAITING_LIST_COUNT)
            sWaitingCommandListQueueWrite = 0;
        sReserveList = NULL;
        sReserveListEnd = NULL;
        sWaitingCommandListCount++;
        sCurrentTag++;
        SetIRQInterruptState(lastState);
        if (flags & COMMAND_IMMEDIATE)
            func_020d2880();
        return true;
    }

    void func_020d2680(unsigned long tag)
    {
        if (func_020d2718(tag))
            return;
        while (func_020d22f4(COMMAND_NO_BLOCK) != NULL)
        {
        }
        if (func_020d2718(tag))
            return;
        func_020d2880();
        if (func_020d2718(tag))
            return;
        do
        {
            func_020d22f4(COMMAND_BLOCK);
        } while (!func_020d2718(tag));
    }

    unsigned long func_020d26ec()
    {
        unsigned long tag;
        int lastState = DisableIRQInterrupts();
        if (sReserveList == NULL)
            tag = sFinishedTag;
        else
            tag = sCurrentTag;
        SetIRQInterruptState(lastState);
        return tag;
    }

    int func_020d2718(unsigned long tag)
    {
        int result;
        int lastState = DisableIRQInterrupts();
        if (tag > sFinishedTag)
        {
            if (tag - sFinishedTag < 0x80000000)
                result = false;
            else
                result = true;
        }
        else
            result = sFinishedTag - tag < 0x80000000 ? true : false;
        SetIRQInterruptState(lastState);
        return result;
    }

    int func_020d2768()
    {
        int lastState = DisableIRQInterrupts();
        int count = 0;
        for (SoundCommand* command = sFreeList; command != NULL; command = command->next)
            count++;
        SetIRQInterruptState(lastState);
        return count;
    }

    int func_020d27a4()
    {
        int lastState = DisableIRQInterrupts();
        int count = 0;
        for (SoundCommand* command = sReserveList; command != NULL; command = command->next)
            count++;
        SetIRQInterruptState(lastState);
        return count;
    }

    int func_020d27e0()
    {
        const int freeCount = func_020d2768();
        return SOUND_COMMAND_COUNT - freeCount - func_020d27a4();
    }

    // PxiFifoCallback
    static void func_020d27fc(unsigned int command, unsigned int data, unsigned int error)
    {
        int lastState = DisableIRQInterrupts();
        func_020d29b0(data);
        SetIRQInterruptState(lastState);
    }

    // InitPXI
    static void func_020d2820()
    {
        SetArm9IPCCommandHandler(IPC_COMMAND_SOUND, func_020d27fc);
        if (!func_020d28f0())
            return;
        while (!IsIPCCommandHandlerRegistered(IPC_COMMAND_SOUND, IPCSide_Arm7))
            func_020c976c(100);
    }

    // RequestCommandProc
    static void func_020d2880()
    {
        while (SendCommandToArm7(IPC_COMMAND_SOUND, 0, false) < 0)
        {
        }
    }

    // AllocCommand
    static SoundCommand* func_020d28a8()
    {
        SoundCommand* command;
        int lastState = DisableIRQInterrupts();
        if (sFreeList == NULL)
        {
            SetIRQInterruptState(lastState);
            return NULL;
        }
        command = sFreeList;
        sFreeList = sFreeList->next;
        if (sFreeList == NULL)
            sFreeListEnd = NULL;
        SetIRQInterruptState(lastState);
        return command;
    }

    // IsCommandAvailable: on an emulator, whether it emulates the ARM7's sound driver
    static int func_020d28f0()
    {
        unsigned long result;
        int lastState;
        if (!func_020c7dc4())
            return true;
        lastState = DisableIRQInterrupts();
        *(volatile unsigned long*)0x04fff200 = 0x10;
        result = *(volatile unsigned long*)0x04fff200;
        SetIRQInterruptState(lastState);
        return result != 0 ? true : false;
    }
}
