#pragma once
#include "Filesystem/CardReadManager.h"

// The NitroSDK's backup (card_backup.c and card_spi.c): the save memory of the card, which the ARM7 reads and writes
// with requests that the ARM9 sends through CardReadManager

// The requests to the ARM7 (CARD_REQ_*)
#define CARD_REQ_INIT 0
#define CARD_REQ_ACK 1
#define CARD_REQ_IDENTIFY 2
#define CARD_REQ_READ_ID 3
#define CARD_REQ_READ_ROM 4
#define CARD_REQ_WRITE_ROM 5
#define CARD_REQ_READ_BACKUP 6
#define CARD_REQ_WRITE_BACKUP 7
#define CARD_REQ_PROGRAM_BACKUP 8
#define CARD_REQ_VERIFY_BACKUP 9
#define CARD_REQ_ERASE_PAGE_BACKUP 10
#define CARD_REQ_ERASE_SECTOR_BACKUP 11
#define CARD_REQ_ERASE_CHIP_BACKUP 12
#define CARD_REQ_READ_STATUS 13
#define CARD_REQ_WRITE_STATUS 14
#define CARD_REQ_ERASE_SUBSECTOR_BACKUP 15

// The requests that a backup device supports (CARD_BACKUP_CAPS_*), in CardBackupSpec's caps
#define CARD_BACKUP_CAPS_AVAILABLE ((1 << CARD_REQ_READ_BACKUP) - 1 | 1 << CARD_REQ_READ_STATUS)
#define CARD_BACKUP_CAPS_READ (1 << CARD_REQ_READ_BACKUP)
#define CARD_BACKUP_CAPS_WRITE (1 << CARD_REQ_WRITE_BACKUP)
#define CARD_BACKUP_CAPS_PROGRAM (1 << CARD_REQ_PROGRAM_BACKUP)
#define CARD_BACKUP_CAPS_VERIFY (1 << CARD_REQ_VERIFY_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_PAGE (1 << CARD_REQ_ERASE_PAGE_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_SECTOR (1 << CARD_REQ_ERASE_SECTOR_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_CHIP (1 << CARD_REQ_ERASE_CHIP_BACKUP)
#define CARD_BACKUP_CAPS_READ_STATUS (1 << CARD_REQ_READ_STATUS)
#define CARD_BACKUP_CAPS_WRITE_STATUS (1 << CARD_REQ_WRITE_STATUS)
#define CARD_BACKUP_CAPS_ERASE_SUBSECTOR (1 << CARD_REQ_ERASE_SUBSECTOR_BACKUP)

// How a request's data is copied (CARDRequestMode)
#define CARD_REQUEST_MODE_RECV 0
#define CARD_REQUEST_MODE_SEND 1
#define CARD_REQUEST_MODE_SEND_VERIFY 2
#define CARD_REQUEST_MODE_SPECIAL 3

// The requests' results (CARDResult)
#define CARD_RESULT_SUCCESS 0
#define CARD_RESULT_UNSUPPORTED 3
#define CARD_RESULT_CANCELED 7

// The flags of CardReadManager (CARD_STAT_*) that the backup uses: the request is waited for, the card's context
// waits for it, and it was canceled
#define CARD_STAT_BUSY (1 << READ_MANAGER_FLAG_HARDWARE_READ_IN_PROGRESS)
#define CARD_STAT_TASK (1 << READ_MANAGER_FLAG_CONTEXT_HAS_TASK_PENDING)
#define CARD_STAT_RECV (1 << CARTRIDGE_READ_CONTEXT_FLAG_4)
#define CARD_STAT_CANCEL (1 << CARTRIDGE_READ_CONTEXT_FLAG_6)

// What a backup's request calls when it ends (MIDmaCallback)
typedef void (*CardBackupCallback)(void* arg);

extern "C"
{
    // CARDi_Request
    int func_020d0fc4(CardReadManager* manager, int request, int retries);

    // CARD_LockBackup and CARD_UnlockBackup
    void func_020d0040(unsigned short ownerID);
    void func_020d0050(unsigned short ownerID);
    // CARDi_IdentifyBackupCore: sets the parameters of the backup device
    void func_020d0078(int type);
    // CARDi_RequestStreamCommand: reads, writes or erases the backup
    int func_020d05ec(unsigned long src, unsigned long dst, unsigned long len, CardBackupCallback callback, void* arg,
                      int isAsync, int reqType, int reqRetry, int reqMode);
    // CARD_GetCurrentBackupType and CARD_GetBackupSectorSize
    int func_020d06d4();
    unsigned long func_020d06e8();
    // CARD_IdentifyBackup
    int func_020d06fc(int type);
    // CARD_WaitBackupAsync and CARD_TryWaitBackupAsync
    int func_020d0834();
    int func_020d0840();
}
