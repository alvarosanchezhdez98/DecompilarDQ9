#include "System/Cartridge.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's ctrdg_task.c: a thread that runs the cartridge's tasks. CTRDGi_IsTaskAvailable, CTRDGi_IsTaskBusy,
// CTRDGi_SetTask, CTRDGi_EndTaskThread and CTRDG_SetTaskThreadPriority aren't in the ROM.

// CTRDG_TASK_STACK_SIZE and CTRDG_TASK_PRIORITY_DEFAULT
#define TASK_STACK_SIZE 1024
#define TASK_PRIORITY 20

// ctrdgi_task_work: NULL when the thread ends
static CartridgeTaskWork* taskWork = NULL;
// ctrdgi_task_list
static CartridgeTask taskList;
// ctrdg_task_stack
unsigned long long cartridgeTaskStack[TASK_STACK_SIZE / sizeof(unsigned long long)];

// The NitroSDK's C copies a structure as a block, and C++ member by member
struct TaskCopy
{
    unsigned long words[sizeof(CartridgeTask) / 4];
};

extern "C"
{
    void func_020d19f4(void* arg);

    // usa: func_020d1954
    // CTRDGi_InitTaskThread
    void func_020d1954(CartridgeTaskWork* work)
    {
        int priorState = DisableIRQInterrupts();

        if (!taskWork)
        {
            CartridgeTaskWork* const p = work;

            taskWork = p;
            func_020d19e0(&p->endTask);
            func_020d19e0(&taskList);
            p->list = NULL;
            PopulateContext(&p->thread, (unsigned int)func_020d19f4, (unsigned int)p,
                (unsigned int)(cartridgeTaskStack + TASK_STACK_SIZE / sizeof(unsigned long long)), TASK_STACK_SIZE,
                TASK_PRIORITY);
            MarkContextReadyAndSwitch(&p->thread);
        }

        SetIRQInterruptState(priorState);
    }

    // usa: func_020d19e0
    // CTRDGi_InitTaskInfo
    void func_020d19e0(CartridgeTask* task)
    {
        VectorizedMemset(task, 0, sizeof(*task));
    }

    // usa: func_020d19f4
    // CTRDGi_TaskThread: runs the tasks
    void func_020d19f4(void* arg)
    {
        CartridgeTaskWork* const p = (CartridgeTaskWork*)arg;

        for (;;)
        {
            CartridgeTask task;

            VectorizedMemset(&task, 0, sizeof(CartridgeTask));
            {
                int priorState = DisableIRQInterrupts();
                while (!p->list)
                {
                    BlockCurrentContext(NULL);
                }
                *(TaskCopy*)&task = *(TaskCopy*)p->list;
                SetIRQInterruptState(priorState);
            }

            if (task.task)
            {
                task.result = task.task(&task);
            }

            {
                int priorState = DisableIRQInterrupts();
                CartridgeTaskFunction callback = task.callback;

                taskList.busy = false;
                if (callback)
                {
                    callback(&task);
                }
                if (taskWork == NULL)
                {
                    break;
                }
                p->list = NULL;
                SetIRQInterruptState(priorState);
            }
        }

        ContextExecutionReturnProc();
        return;
    }
}
