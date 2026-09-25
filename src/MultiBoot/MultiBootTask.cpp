#include "MultiBoot/MultiBoot.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include "System/ProcessorContext.h"
#include <globaldefs.h>

// The NitroSDK's mb_task.c: a thread that runs the MB library's tasks by priority

#pragma optimize_for_size off
#pragma optimization_level 4

// OS_THREAD_PRIORITY_MAX, the lowest priority
#define PRIORITY_LOWEST 31
// MB_TASK_PRIORITY_ABOVE, MB_TASK_PRIORITY_BELOW and MB_TASK_PRIORITY_NORMAL: relative to the thread's priority
#define PRIORITY_ABOVE 32
#define PRIORITY_BELOW 33
#define PRIORITY_NORMAL 34

extern "C"
{
    static MBiTaskWork* mbi_task_work = NULL;

    static void MBi_TaskThread(void* arg)
    {
        MBiTaskWork* const p = (MBiTaskWork*)arg;
        for (;;)
        {
            MBiTaskInfo* info;
            int lastState = DisableIRQInterrupts();
            while (p->list == NULL)
            {
                ChangeContextPriority(&p->thread, 0);
                BlockCurrentContext(NULL);
            }
            info = p->list;
            p->list = p->list->next;
            ChangeContextPriority(&p->thread, info->priority);
            SetIRQInterruptState(lastState);

            if (info->task != NULL)
                info->task(info);

            {
                int lastState2 = DisableIRQInterrupts();
                MBTaskFunc callback = info->callback;
                unsigned long current = GetContextPriority(&p->thread);
                unsigned long next = p->list == NULL ? 0 : (current < p->list->priority ? (unsigned long)p->list->priority : current);
                if (next != current)
                    ChangeContextPriority(&p->thread, next);
                info->next = NULL;
                info->busy = false;
                if (callback != NULL)
                    callback(info);
                if (info == &p->endTask)
                    break;
                SetIRQInterruptState(lastState2);
            }
        }
        ContextExecutionReturnProc();
    }

    void MBi_InitTaskThread(MBiTaskWork* p, unsigned long size)
    {
        int lastState = DisableIRQInterrupts();
        if (mbi_task_work == NULL)
        {
            mbi_task_work = p;
            MBi_InitTaskInfo(&p->endTask);
            p->list = NULL;
            {
                const unsigned long stackSize = (size - sizeof(MBiTaskWork)) & ~3;
                PopulateContext(&p->thread, (unsigned int)MBi_TaskThread, (unsigned int)p,
                                (unsigned int)((unsigned char*)(p + 1) + stackSize), stackSize, 0);
                MarkContextReadyAndSwitch(&p->thread);
            }
        }
        SetIRQInterruptState(lastState);
    }

    int MBi_IsTaskAvailable()
    {
        return mbi_task_work != NULL;
    }

    void MBi_InitTaskInfo(MBiTaskInfo* info)
    {
        VectorizedMemset(info, 0, sizeof(*info));
    }

    int MBi_IsTaskBusy(volatile const MBiTaskInfo* info)
    {
        return info->busy != false;
    }

    void MBi_SetTask(MBiTaskInfo* info, MBTaskFunc task, MBTaskFunc callback, unsigned long priority)
    {
        MBiTaskWork* const p = mbi_task_work;
        if (!MBi_IsTaskAvailable())
            return;
        if (info->busy)
            return;
        if (priority > PRIORITY_LOWEST)
        {
            const unsigned long current = GetContextPriority(&p->thread);
            if (priority == PRIORITY_ABOVE)
                priority = current != 0 ? current - 1 : 0;
            else if (priority == PRIORITY_BELOW)
                priority = current < PRIORITY_LOWEST ? current + 1 : PRIORITY_LOWEST;
            else if (priority == PRIORITY_NORMAL)
                priority = current;
            else
                priority = PRIORITY_LOWEST;
        }
        {
            int lastState = DisableIRQInterrupts();
            info->busy = true;
            info->priority = priority;
            info->task = task;
            info->callback = callback;
            if (p->list == NULL)
            {
                if (info == &p->endTask)
                    mbi_task_work = NULL;
                p->list = info;
                MarkContextReadyAndSwitch(&p->thread);
            }
            else
            {
                MBiTaskInfo* position = p->list;
                if (info == &p->endTask)
                {
                    while (position->next != NULL)
                        position = position->next;
                    position->next = info;
                    mbi_task_work = NULL;
                }
                else if (priority < position->priority)
                {
                    p->list = info;
                    info->next = position;
                }
                else
                {
                    while (position->next != NULL && priority >= position->next->priority)
                        position = position->next;
                    info->next = position->next;
                    position->next = info;
                }
            }
            SetIRQInterruptState(lastState);
        }
    }

    void MBi_EndTaskThread(MBTaskFunc callback)
    {
        int lastState = DisableIRQInterrupts();
        if (MBi_IsTaskAvailable())
            MBi_SetTask(&mbi_task_work->endTask, NULL, callback, 0);
        SetIRQInterruptState(lastState);
    }
}
