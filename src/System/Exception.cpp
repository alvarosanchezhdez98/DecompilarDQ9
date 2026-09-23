#include "System/DTCM.h"
#include "System/CP15.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_exception.c: the handler of exceptions (undefined instructions and aborts). It saves the registers
// and calls the game's handler, if it has set one; the game doesn't, so it stops there, or in the debugger.

// The NitroSDK's HW_EXCP_VECTOR_BUF_FOR_DEBUGGER: the handler that the debugger's exception vector calls
#define PTR_DEBUGGER_EXCEPTION_HANDLER ((unsigned long*)0x027ffd9c)

// The NitroSDK's OSiExContext: the registers when the exception happened
struct ExceptionContext
{
    // Like the start of ProcessorContext
    unsigned int programStatusRegister;
    unsigned int registers[15]; // r0-r14
    unsigned int resumeAddress; // pc + 4
    unsigned int supervisorStackPointer;
    ProcessorContext::MathRegisters mathRegisters;

    unsigned int cp15;
    unsigned int savedProgramStatusRegister;
    unsigned int exceptionInfo;
    unsigned int debug[4];
};

typedef void (*ExceptionHandler)(unsigned long context, void* userData);

static ExceptionContext exceptionContext;
static ExceptionHandler userExceptionHandler;
static void* userExceptionHandlerData;
static void* debuggerExceptionHandler = NULL;
// Not referenced
static unsigned long exceptionHookStack[8];

extern "C"
{
    void func_020c8aac();

    // usa: func_020c8a3c
    // OS_InitException: handles the exceptions, unless a debugger does
    void func_020c8a3c()
    {
        if (0x02600000 <= *PTR_DEBUGGER_EXCEPTION_HANDLER && *PTR_DEBUGGER_EXCEPTION_HANDLER < 0x02800000)
        {
            debuggerExceptionHandler = *(void**)PTR_DEBUGGER_EXCEPTION_HANDLER;
        }
        else
        {
            debuggerExceptionHandler = NULL;
        }

        if (debuggerExceptionHandler == NULL)
        {
            *PTR_DEBUGGER_EXCEPTION_HANDLER = (unsigned long)func_020c8aac;
            DTCM_DATA_EXCEPTION_HANDLER = (unsigned int)func_020c8aac;
        }

        userExceptionHandler = NULL;
        (void)exceptionHookStack;
    }

#ifdef __MWERKS__
    void func_020c8b30();

    // usa: func_020c8aac
    // OSi_ExceptionHandler. In the original, each conditional instruction became a conditional branch over an
    // unconditional one, which none of our compiler versions do, so the branches are written out.
    asm void func_020c8aac()
    {
        ldr r12, =debuggerExceptionHandler
        ldr r12, [r12, #0]
        cmp r12, #0
        bne @call_debugger
        b @skip_call_debugger
    @call_debugger:
        mov lr, pc
    @skip_call_debugger:
        bne @jump_debugger
        b @skip_jump_debugger
    @jump_debugger:
        bx r12
    @skip_jump_debugger:

        ldr r12, =0x02000000 // the ITCM's end
        stmdb r12!, {r0, r1, r2, r3, sp, lr}

        and r0, sp, #1
        mov sp, r12

        mrs r1, cpsr
        and r1, r1, #0x1f
        teq r1, #0x17 // abort mode
        bne @not_abort
        bl func_020c8b30
        b @stop
    @not_abort:
        teq r1, #0x1b // undefined mode
        bne @stop
        bl func_020c8b30

    @stop:
        ldr r12, =debuggerExceptionHandler
        ldr r12, [r12, #0]
        cmp r12, #0
    @loop_without_debugger:
        beq @loop_without_debugger
    @loop:
        nop
        b @loop

        ldmia sp!, {r0, r1, r2, r3, r12, lr}
        mov sp, r12
        bx lr
    }

    void func_020c8b44();
    void func_020c8bd4();

    // usa: func_020c8b30
    // OSi_GetAndDisplayContext
    asm void func_020c8b30()
    {
        stmdb sp!, {r0, lr}
        bl func_020c8b44
        bl func_020c8bd4
        ldmia sp!, {r0, lr}
        bx lr
    }

    // usa: func_020c8b44
    // OSi_SetExContext: saves the registers in exceptionContext, from the ones that the BIOS pushed on the stack
    asm void func_020c8b44()
    {
        ldr r1, =exceptionContext

        mrs r2, cpsr
        str r2, [r1, #0x74] // debug[1]

        str r0, [r1, #0x6c] // exceptionInfo
        ldr r0, [r12, #0]
        str r0, [r1, #0x4] // registers[0]
        ldr r0, [r12, #4]
        str r0, [r1, #0x8] // registers[1]
        ldr r0, [r12, #8]
        str r0, [r1, #0xc] // registers[2]
        ldr r0, [r12, #0xc]
        str r0, [r1, #0x10] // registers[3]
        ldr r2, [r12, #0x10]
        bic r2, r2, #1

        add r0, r1, #0x14 // registers[4]
        stmia r0, {r4, r5, r6, r7, r8, r9, r10, r11}

        str r12, [r1, #0x70] // debug[0]

        ldr r0, [r2, #0]
        str r0, [r1, #0x64] // cp15
        ldr r3, [r2, #4]
        str r3, [r1, #0] // programStatusRegister
        ldr r0, [r2, #8]
        str r0, [r1, #0x34] // registers[12]
        ldr r0, [r2, #0xc]
        str r0, [r1, #0x40] // resumeAddress

        // The stack pointer and the link register of the mode of the exception
        mrs r0, cpsr
        orr r3, r3, #0x80
        bic r3, r3, #0x20
        msr cpsr_fsxc, r3

        str sp, [r1, #0x38] // registers[13]
        str lr, [r1, #0x3c] // registers[14]
        mrs r2, spsr

        str r2, [r1, #0x7c] // debug[3]

        msr cpsr_fsxc, r0
        bx lr
    }
#endif

    // usa: func_020c8bd4
    // OSi_DisplayExContext: calls the game's exception handler, in system mode
    void func_020c8bd4()
    {
        if (userExceptionHandler)
        {
#ifdef __MWERKS__
            asm
            {
                mrs r2, cpsr
                mov r0, sp
                ldr r1, =0x9f // system mode, interrupts disabled
                msr cpsr_fsxc, r1
                mov r1, sp
                mov sp, r0
                stmdb sp!, {r1, r2}
                bl func_020c89f8
                ldr r0, =exceptionContext
                ldr r1, =userExceptionHandlerData
                ldr r1, [r1]
                ldr r12, =userExceptionHandler
                ldr r12, [r12]
                ldr lr, =@return
                bx r12
            @return:
                bl func_020c8a08
                ldmia sp!, {r1, r2}
                mov sp, r1
                msr cpsr_fsxc, r2
            }
#endif
        }
    }
}
