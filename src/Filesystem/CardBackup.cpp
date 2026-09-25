#include "Filesystem/CardBackup.h"
#include "Filesystem/FSInnerDefs.h"
#include "System/Cache.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include "System/ProcessorContext.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's card_backup.c: the backup's requests, which the card's context runs a page at a time

// SDK_USING_MIDDLEWARE(cardi_backup_assert): refers to the middleware's name in BuildInfo, "[SDK+NINTENDO:BACKUP]", so
// that the linker keeps it. The original has its address as a constant.
#define BACKUP_MIDDLEWARE ((const void*)0x02000bc4)

extern "C"
{
    // OSi_ReferSymbol: does nothing
    void func_02000b9c(const void* symbol);
    // OS_Terminate
    void func_020c9be0();
}

// CARDi_WaitTask: waits for the other request, and starts this one
static inline void WaitTask(CardReadManager* p, CardBackupCallback callback, void* arg)
{
    const int lastState = DisableIRQInterrupts();
    while (p->flags & CARD_STAT_BUSY)
        BlockCurrentContext(&p->ongoingReadBlock);
    p->flags |= CARD_STAT_BUSY;
    p->onComplete = (CardReadManager::CompletionCallback)callback;
    p->handle = (NitroHandle*)arg;
    SetIRQInterruptState(lastState);
}

// CARDi_EndTask: ends the request, wakes the contexts that wait for it, and calls its callback
static inline void EndTask(CardReadManager* p, int isOwnTask)
{
    const CardBackupCallback callback = (CardBackupCallback)p->onComplete;
    void* const arg = p->handle;
    {
        const int lastState = DisableIRQInterrupts();
        p->flags &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
        UnblockContexts(&p->ongoingReadBlock);
        if (p->flags & CARD_STAT_RECV)
            MarkContextReadyAndSwitch(&p->cartridgeReadContext);
        SetIRQInterruptState(lastState);
    }
    if (isOwnTask && callback)
        callback(arg);
}

extern "C"
{
    // CARDi_RequestStreamCommandCore
    static void func_020d03fc(CardReadManager* p)
    {
        const int reqType = p->reqType;
        const int reqMode = p->reqMode;
        const int retryCount = p->reqRetry;
        unsigned long size = sizeof(p->backupPageBuffer);
        func_02000b9c(BACKUP_MIDDLEWARE);
        if (reqType == CARD_REQ_ERASE_SECTOR_BACKUP)
            size = func_020d06e8();
        else if (reqType == CARD_REQ_ERASE_SUBSECTOR_BACKUP)
            size = data_021118e0.pSharedData->spec.subsect_size;
        do
        {
            const int len = (size < p->writeLength) ? size : p->writeLength;
            p->pSharedData->len = len;
            if (p->flags & CARD_STAT_CANCEL)
            {
                p->flags &= ~CARD_STAT_CANCEL;
                p->pSharedData->result = CARD_RESULT_CANCELED;
                break;
            }
            switch (reqMode)
            {
            case CARD_REQUEST_MODE_RECV:
                InvalidateDataCacheRange(p->backupPageBuffer, len);
                p->pSharedData->src = p->cartridgeReadOffset;
                p->pSharedData->dst = (unsigned long)p->backupPageBuffer;
                break;
            case CARD_REQUEST_MODE_SEND:
            case CARD_REQUEST_MODE_SEND_VERIFY:
                VectorizedInvertedMemcpy((const void*)p->cartridgeReadOffset, p->backupPageBuffer, len);
                CleanInvalidateCacheRange(p->backupPageBuffer, len);
                DrainWriteBuffer();
                p->pSharedData->src = (unsigned long)p->backupPageBuffer;
                p->pSharedData->dst = (unsigned long)p->writeDst;
                break;
            case CARD_REQUEST_MODE_SPECIAL:
                p->pSharedData->src = p->cartridgeReadOffset;
                p->pSharedData->dst = (unsigned long)p->writeDst;
                break;
            }
            if (!func_020d0fc4(p, reqType, retryCount))
                break;
            if (reqMode == CARD_REQUEST_MODE_SEND_VERIFY)
            {
                // With `if (!...) break;`, the compiler inverts the branches
                if (func_020d0fc4(p, CARD_REQ_VERIFY_BACKUP, 1))
                {
                }
                else
                    break;
            }
            else if (reqMode == CARD_REQUEST_MODE_RECV)
            {
                VectorizedInvertedMemcpy(p->backupPageBuffer, p->writeDst, len);
            }
            p->cartridgeReadOffset += len;
            p->writeDst += len;
            p->writeLength -= len;
        } while (p->writeLength > 0);
        EndTask(p, true);
    }

    // CARDi_RequestStreamCommand
    int func_020d05ec(unsigned long src, unsigned long dst, unsigned long len, CardBackupCallback callback, void* arg,
                      int isAsync, int reqType, int reqRetry, int reqMode)
    {
        CardReadManager* const p = &data_021118e0;
        func_02000b9c(BACKUP_MIDDLEWARE);
        WaitTask(p, callback, arg);
        p->cartridgeReadOffset = src;
        p->writeDst = (unsigned char*)dst;
        p->writeLength = len;
        p->reqType = reqType;
        p->reqRetry = reqRetry;
        p->reqMode = reqMode;
        if (isAsync)
        {
            SendTaskToReadContext(func_020d03fc);
            return true;
        }
        data_021118e0.currentTaskExecutionContext = data_02111304.activeContext;
        func_020d03fc(p);
        return p->pSharedData->result == CARD_RESULT_SUCCESS;
    }

    // CARD_GetCurrentBackupType
    int func_020d06d4()
    {
        return data_021118e0.pSharedData->type;
    }

    // CARD_GetBackupSectorSize
    unsigned long func_020d06e8()
    {
        return data_021118e0.pSharedData->spec.sect_size;
    }

    // CARD_IdentifyBackup
    int func_020d06fc(int type)
    {
        CardReadManager* const p = &data_021118e0;
        func_02000b9c(BACKUP_MIDDLEWARE);
        if (type == CARD_BACKUP_TYPE_NOT_USE)
            func_020c9be0();
        VerifyCardReadManagerInitialized();
        WaitTask(p, NULL, NULL);
        func_020d0078(type);
        data_021118e0.currentTaskExecutionContext = data_02111304.activeContext;
        func_020d0fc4(p, CARD_REQ_IDENTIFY, 1);
        p->pSharedData->src = 0;
        p->pSharedData->dst = (unsigned long)p->backupPageBuffer;
        p->pSharedData->len = 1;
        func_020d0fc4(p, CARD_REQ_READ_BACKUP, 1);
        EndTask(p, true);
        return p->pSharedData->result == CARD_RESULT_SUCCESS;
    }

    // CARD_WaitBackupAsync
    int func_020d0834()
    {
        return AwaitCardReadManagerIdle();
    }

    // CARD_TryWaitBackupAsync
    int func_020d0840()
    {
        return IsCardReadManagerIdle();
    }
}
