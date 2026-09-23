#include "System/GamecardBusOwnership.h"
#include "System/Interrupts.h"
#include <globaldefs.h>
#include <asmhacks.h>
#include "std_library_functions.h"

#define REG_EXTMEMCTRL (*(volatile unsigned short*)0x04000204)
#define EXTMEMCTRL_FLAG_RELINQUISH_GBA_BUS (1 << 7)
#define EXTMEMCTRL_FLAG_RELINQUISH_NDS_BUS (1 << 11)

#define ADDR_REGISTERED_OWNERS_LOW 0x027fffb0
#define REGISTERED_OWNER_FLAGS ((unsigned int*)ADDR_REGISTERED_OWNERS_LOW)


#define PTR_NDS_BUS_LOCK ((GamecardBusLock*)0x027fffe0)
#define PTR_GBA_BUS_LOCK ((GamecardBusLock*)0x027fffe8)
#define PTR_UNKNOWN_BUS_LOCK ((GamecardBusLock*)0x027ffff0)

#pragma optimize_for_size off

#if defined(jpn)
#define func_020ca7e0 func_020cc2ac
#endif

extern "C"
{
    void WaitByLoop(int);

    // aligned memset clone
    void func_020ca3ec(int val, void* dst, unsigned len);

    // Performs an atomic swap
    unsigned int func_020ca7e0(unsigned int newValue, volatile unsigned int* atomic);
}

int TryLockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onLock)(), bool strict);
int WeakLockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onLock)());
int WeakUnlockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onUnlock)());

void MarkGBABusAcquired(); // acquire gba bus
void MarkGBABusReleased(); // release gba bus

void MarkNDSBusAcquired();
void MarkNDSBusReleased();

// The NitroSDK's OS_InitLock
void InitializeGamecardBusOwnership()
{
    // A local static like in the NitroSDK: with a global variable, the compiler schedules the first stores differently
    static int isInitialized = false;
    if (isInitialized)
    {
        return;
    }
    
    GamecardBusLock* ndsLock = PTR_UNKNOWN_BUS_LOCK;
    isInitialized = true;
    ndsLock->atomic = 0;
    
    WeakLockGamecardBusLock(126, ndsLock, NULL);

    if (ndsLock->unknown_6)
    {
        do
        {
            WaitByLoop(0x400);
        } while (ndsLock->unknown_6);
    }

    REGISTERED_OWNER_FLAGS[0] = 0xffffffff;
    REGISTERED_OWNER_FLAGS[1] = 0xffff0000;

    func_020ca3ec(0, (void*)0x027fffc0, 0x28);
    REG_EXTMEMCTRL |= EXTMEMCTRL_FLAG_RELINQUISH_NDS_BUS;
    REG_EXTMEMCTRL |= EXTMEMCTRL_FLAG_RELINQUISH_GBA_BUS;

    WeakUnlockGamecardBusLock(126, ndsLock, NULL);
    WeakLockGamecardBusLock(127, ndsLock, NULL);
}

// can be static
int LockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onLock)(), bool strict)
{
    if (TryLockGamecardBusLock(owner, lock, onLock, strict) > 0)
    {
        do {
            WaitByLoop(0x400);
        } while (TryLockGamecardBusLock(owner, lock, onLock, strict) > 0);
    }
}

// can be static
int WeakLockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onLock)())
{
    return LockGamecardBusLock(owner, lock, onLock, false);
}

// can be static
int UnlockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onUnlock)(), bool strict)
{
    if (owner != lock->ownerID)
        return -2;
    
    int priorState;
    if (strict)
        priorState = DisableIRQAndFIQInterrupts();
    else
        priorState = DisableIRQInterrupts();

    lock->ownerID = 0;
    if (onUnlock != NULL)
        onUnlock();

    lock->atomic = 0;

    if (strict)
        SetIRQAndFIQInterruptState(priorState);
    else
        SetIRQInterruptState(priorState);
    return 0;
}

// can be static
int WeakUnlockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onUnlock)())
{
    return UnlockGamecardBusLock(owner, lock, onUnlock, false);
}

// can be static
int TryLockGamecardBusLock(unsigned short owner, GamecardBusLock* lock, void (*onLock)(), bool strict)
{
    int priorState;
    if (strict)
        priorState = DisableIRQAndFIQInterrupts();
    else
        priorState = DisableIRQInterrupts();

    int oldAtomic = func_020ca7e0(owner, &lock->atomic);
    if (oldAtomic == 0)
    {
        if (onLock != NULL)
            onLock();
        lock->ownerID = owner;
    }

    if (strict)
        SetIRQAndFIQInterruptState(priorState);
    else
        SetIRQInterruptState(priorState);
    return oldAtomic;
}

// can be static
int InternalReleaseGBABus(unsigned short owner)
{
    return UnlockGamecardBusLock(owner, PTR_GBA_BUS_LOCK, &MarkGBABusReleased, true);
}

// must be exposed
#ifdef __MWERKS__
asm int ReleaseGBABus(unsigned short owner)
{
    ldr r1, =InternalReleaseGBABus
    bx r1
}
#else
int ReleaseGBABus(unsigned short owner)
{
    return InternalReleaseGBABus(owner);
}
#endif

// must be exposed
int TryAcquireGBABus(unsigned short owner)
{
    return TryLockGamecardBusLock(owner, PTR_GBA_BUS_LOCK, &MarkGBABusAcquired, true);
}

// can be static
void MarkGBABusAcquired()
{
    REG_EXTMEMCTRL &= ~EXTMEMCTRL_FLAG_RELINQUISH_GBA_BUS;
}

// can be static
void MarkGBABusReleased()
{
    REG_EXTMEMCTRL |= EXTMEMCTRL_FLAG_RELINQUISH_GBA_BUS;
}

// must be exposed
int AcquireNDSBus(unsigned short owner)
{
    return WeakLockGamecardBusLock(owner, PTR_NDS_BUS_LOCK, &MarkNDSBusAcquired);
}

// must be exposed
int ReleaseNDSBus(unsigned short owner)
{
    return WeakUnlockGamecardBusLock(owner, PTR_NDS_BUS_LOCK, &MarkNDSBusReleased);
}

// can be static
void MarkNDSBusAcquired()
{
    REG_EXTMEMCTRL &= ~EXTMEMCTRL_FLAG_RELINQUISH_NDS_BUS;
}

// can be static
void MarkNDSBusReleased()
{
    REG_EXTMEMCTRL |= EXTMEMCTRL_FLAG_RELINQUISH_NDS_BUS;
}

// must be exposed
unsigned short GetLockOwner(GamecardBusLock* lock)
{
    return lock->ownerID;
}

inline int leadZeroCount(unsigned int what)
{
    int ret;
    __asm("clz %[output], %[input]" : : [output] "=r" (ret), [input] "r" (what));
    return ret;
}

// GenerateLockOwnerID and ReleaseLockOwnerID are written in assembly, like the NitroSDK's OS_GetLockID and
// OS_ReleaseLockID. In the original, each conditional instruction (e.g. movne) became a conditional branch over an
// unconditional one, which none of our compiler versions do, so the branches are written out.
#ifdef __MWERKS__
asm unsigned int GenerateLockOwnerID()
{
    ldr r3, =ADDR_REGISTERED_OWNERS_LOW
    ldr r1, [r3, #0]
    clz r2, r1 // number of the first free ID among 0x40-0x5f
    cmp r2, #32
    bne @movne
    b @skip_movne
@movne:
    mov r0, #0x40
@skip_movne:
    bne @found
    add r3, r3, #4
    ldr r1, [r3, #0]
    clz r2, r1 // number of the first free ID among 0x60-0x7f
    cmp r2, #32
    ldr r0, =0xfffffffd // no free ID
    beq @bxeq
    b @skip_bxeq
@bxeq:
    bx lr
@skip_bxeq:
    mov r0, #0x60
@found:
    add r0, r0, r2
    mov r1, #0x80000000
    mov r1, r1, lsr r2
    ldr r2, [r3, #0]
    bic r2, r2, r1
    str r2, [r3, #0]
    bx lr
}

asm void ReleaseLockOwnerID(register unsigned short id)
{
    ldr r3, =ADDR_REGISTERED_OWNERS_LOW
    cmp r0, #0x60
    bpl @addpl
    b @skip_addpl
@addpl:
    add r3, r3, #4
@skip_addpl:
    bpl @subpl
    b @skip_subpl
@subpl:
    sub r0, r0, #0x60
@skip_subpl:
    bmi @submi
    b @skip_submi
@submi:
    sub r0, r0, #0x40
@skip_submi:
    mov r1, #0x80000000
    mov r1, r1, lsr r0
    ldr r2, [r3, #0]
    orr r2, r2, r1
    str r2, [r3, #0]
    bx lr
}
#else
// The IDs 0x40-0x7f are free when their bit (from the highest) is set in REGISTERED_OWNER_FLAGS[0] or [1]
unsigned int GenerateLockOwnerID()
{
    for (int word = 0; word < 2; word++)
    {
        int bit = leadZeroCount(REGISTERED_OWNER_FLAGS[word]);
        if (bit != 32)
        {
            REGISTERED_OWNER_FLAGS[word] &= ~(0x80000000 >> bit);
            return 0x40 + word * 32 + bit;
        }
    }
    return 0xfffffffd;
}

void ReleaseLockOwnerID(unsigned short id)
{
    if (id >= 0x60)
        REGISTERED_OWNER_FLAGS[1] |= 0x80000000 >> (id - 0x60);
    else
        REGISTERED_OWNER_FLAGS[0] |= 0x80000000 >> (id - 0x40);
}
#endif
