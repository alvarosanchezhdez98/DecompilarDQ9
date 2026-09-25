#pragma once

#include "System/ProcessorContext.h"
#include "LowNitroHandle.h"
#include "NitroVM.h"

// The NitroSDK's CARDBackupType: the backup's device, its size, and its vendor
#define CARD_BACKUP_TYPE_DEVICE_SHIFT 0
#define CARD_BACKUP_TYPE_SIZEBIT_SHIFT 8
#define CARD_BACKUP_TYPE_VENDER_SHIFT 16
#define CARD_BACKUP_TYPE_NOT_USE 0
#define CARD_BACKUP_TYPE_DEVICE_EEPROM 1
#define CARD_BACKUP_TYPE_DEVICE_FLASH 2
#define CARD_BACKUP_TYPE_DEVICE_FRAM 3

// The backup device's parameters: sizes, and the times that its commands take (the NitroSDK's CARDBackupSpec? in
// CARDiCommandArg)
struct CardBackupSpec
{
    unsigned long total_size;
    unsigned long sect_size;
    unsigned long subsect_size;
    unsigned long page_size;
    unsigned long addr_width;
    unsigned long program_page;
    unsigned long write_page;
    unsigned long write_page_total;
    unsigned long erase_chip;
    unsigned long erase_chip_total;
    unsigned long erase_sector;
    unsigned long erase_sector_total;
    unsigned long erase_subsector;
    unsigned long erase_subsector_total;
    unsigned long erase_page;
    unsigned char initial_status;
    unsigned char padding1[3];
    // The requests that the device supports, a bit for each CARD_REQ_*
    unsigned long caps;
    unsigned char padding2[4];
};

// sizeof == 0x60: the request that the ARM7 runs, and its result (the NitroSDK's CARDiCommandArg)
struct Arm7CardReadData
{
    int result;
    // The backup's CARDBackupType
    int type;
    unsigned long id;
    unsigned long src;
    unsigned long dst;
    unsigned long len;
    CardBackupSpec spec;
};

// sizeof <= 0x620
#define CARTRIDGE_READ_CONTEXT_FLAG_0 0
#define READ_MANAGER_FLAG_HARDWARE_READ_IN_PROGRESS 2
#define READ_MANAGER_FLAG_CONTEXT_HAS_TASK_PENDING 3
#define CARTRIDGE_READ_CONTEXT_FLAG_4 4
#define READ_MANAGER_FLAG_AWAITING_ARM7_ACTION 5
#define CARTRIDGE_READ_CONTEXT_FLAG_6 6

struct CardReadManager
{
    typedef void (*ReadProc)(CardReadManager*);
    typedef void (*CompletionCallback)(NitroHandle*);

    Arm7CardReadData* pSharedData;
    int unknown_4;
    struct CardReadManagerLock {
        // two of {owner, multiplicity, taskType} should probably be volatile,
        // but not all three. see the lock & initialize functions
        volatile int owner;
        int multiplicity;
        BlockedContextList waitingContexts;
        int taskType;
    } lock;
    unsigned int cartridgeReadOffset;
    unsigned char* writeDst;
    unsigned int writeLength;
    unsigned int dmaChannel;
    // The backup's request (CARD_REQ_*), how many times it's retried, and how its data is copied (CARDRequestMode)
    int reqType;
    int reqRetry;
    int reqMode;
    CompletionCallback onComplete;
    NitroHandle* handle;
    ReadProc cartridgeReadProc;
    // cartridgeReadContext runs a loop that handles incoming tasks, but
    // if you request a synchronous task then execution can occur on a different
    // context in the meantime
    ProcessorContext cartridgeReadContext;
    ProcessorContext* currentTaskExecutionContext;
    // Set to 4 and 8 in different places
    unsigned int contextPriority_108;
    BlockedContextList ongoingReadBlock; 
    volatile unsigned int flags;
    // if you need to clean more than this amount of the cache, then just
    // clean the whole thing instead
    unsigned int instructionCacheCleanThreshold;
    unsigned int dataCacheCleanThreshold;

    // The backup's data is copied through this buffer, a page at a time (the NitroSDK's backup_cache_page_buf)
    unsigned char backupPageBuffer[0x100];
    char readContextStack[0x400];
};

void SendTaskToReadContext(CardReadManager::ReadProc task);

void LockCardReadManager(unsigned short ownerID, int taskType);
void UnlockCardReadManager(unsigned short ownerID, int taskType);

void InitializeCardReadManager();
int IsCardReadManagerInitialized();
void VerifyCardReadManagerInitialized();

bool AwaitCardReadManagerIdle();
bool IsCardReadManagerIdle();
int GetCardReadManagerSharedStatus();

unsigned int SetReadContextPriority(unsigned int priority);
void NitroVM_Command_AcquireCardReadResources(unsigned short ownerID);
void NitroVM_Command_ReleaseCardReadResources(unsigned short ownerID);

#if defined(jpn)
#define func_020d0f28 func_020d29f4
#endif

void SendGamecardBusCommand(unsigned int firstWord, unsigned int secondWord);
unsigned int SetupNormalGamecardBusCommandMode();
// note: even if set to async, you'll still have to wait for any ongoing operation
// to finish before this one can be dispatched
void LoadDataFromCartridgeToMemory(unsigned int dmaChannel,
    unsigned int cartridgeOffset, void* dest, unsigned int length,
    CardReadManager::CompletionCallback onComplete, NitroHandle* handle, CBool async);

void InitializeCardReading();

void IPCCommand11Proc(unsigned int command, unsigned int argument, unsigned int flag);
void CartridgeReadContextLoop();