#include "Filesystem/CardReadManager.h"
#include "Filesystem/FSInnerDefs.h"
#include "System/Interrupts.h"
#include "System/GamecardBusOwnership.h"

#pragma optimize_for_size off

unsigned int SetReadContextPriority(unsigned int priority)
{
    CardReadManager* manager = (CardReadManager*)&data_021118e0;
    int priorState = DisableIRQInterrupts();
    unsigned int oldPrio = manager->contextPriority_108;
    manager->contextPriority_108 = priority;
    ChangeContextPriority(&manager->cartridgeReadContext, priority);
    SetIRQInterruptState(priorState);
    return oldPrio;
}

void NitroVM_Command_AcquireCardReadResources(unsigned short ownerID)
{
    LockCardReadManager(ownerID, 1);
    AcquireNDSBus(ownerID);
}

void NitroVM_Command_ReleaseCardReadResources(unsigned short ownerID)
{
    ReleaseNDSBus(ownerID);
    UnlockCardReadManager(ownerID, 1);
}
// The NitroSDK's CARD_TARGET_BACKUP: the lock of the backup
#define CARD_TARGET_BACKUP 2

extern "C"
{
    // CARD_WaitBackupAsync and CARD_TryWaitBackupAsync
    int func_020d0834();
    int func_020d0840();

    // CARD_LockBackup
    void func_020d0040(unsigned short ownerID)
    {
        LockCardReadManager(ownerID, CARD_TARGET_BACKUP);
    }

    // CARD_UnlockBackup: waits for the backup's asynchronous request first
    void func_020d0050(unsigned short ownerID)
    {
        if (!func_020d0840())
            func_020d0834();
        UnlockCardReadManager(ownerID, CARD_TARGET_BACKUP);
    }
}
