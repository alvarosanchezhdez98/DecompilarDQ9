#include "System/Cartridge.h"
#include "System/CP15.h"
#include "System/GamecardBusOwnership.h"
#include "System/IPC.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's ctrdg.c: the cartridge in the GBA slot. Only the functions that the game uses are in the ROM.

// HW_CTRDG_ROM: the GBA slot's ROM, and the module ID at its end
#define CARTRIDGE_ROM 0x08000000
#define CARTRIDGE_HEADER ((GBACartridgeHeader*)CARTRIDGE_ROM)
#define CARTRIDGE_MODULE_ID (*(unsigned short*)(CARTRIDGE_ROM + 0x1fffe))

// EXMEMCNT: the GBA slot's access cycles (MI_CTRDG_ROMCYCLE1_18 and MI_CTRDG_ROMCYCLE2_6 are the slowest)
#define EXMEMCNT (*(volatile unsigned short*)0x04000204)
#define ROM_CYCLE_FIRST_MASK 0xc
#define ROM_CYCLE_FIRST_SHIFT 2
#define ROM_CYCLE_FIRST_18 3
#define ROM_CYCLE_SECOND_MASK 0x10
#define ROM_CYCLE_SECOND_SHIFT 4
#define ROM_CYCLE_SECOND_6 0

// HW_CTRDG_LOCK_BUF, and the owner's flag of the ARM9 (OS_MAINP_LOCKED_FLAG)
#define CARTRIDGE_LOCK ((GamecardBusLock*)0x027fffe8)
#define LOCKED_BY_ARM9 0x40

// The protection region 3 (the GBA slot): read and write, or read only (OS_PR3_ACCESS_*)
#define REGION3_ACCESS_MASK 0xf000
#define REGION3_ACCESS_READ_WRITE 0x1000
#define REGION3_ACCESS_READ_ONLY 0x5000

// CTRDGi_EnableFlag
static int isEnabled = false;
// CTRDGi_Work
CartridgeWork cartridgeWork;

unsigned short GetLockOwner(GamecardBusLock* lock);

// MI_SetCartridgeRomCycle1st and MI_SetCartridgeRomCycle2nd
static inline void SetRomCycleFirst(int cycle)
{
    EXMEMCNT = (unsigned short)((cycle << ROM_CYCLE_FIRST_SHIFT) | (EXMEMCNT & ~ROM_CYCLE_FIRST_MASK));
}

static inline void SetRomCycleSecond(int cycle)
{
    EXMEMCNT = (unsigned short)((cycle << ROM_CYCLE_SECOND_SHIFT) | (EXMEMCNT & ~ROM_CYCLE_SECOND_MASK));
}

extern "C"
{
    // BIOS: copies or fills memory
    void CpuSet(const void* src, void* dst, unsigned long control);
    // BIOS: waits for a number of loops of 4 cycles
    void WaitByLoop(int count);

    // usa: func_020d12e4
    // CTRDGi_InitCommon
    void func_020d12e4()
    {
        // SVC_CpuClear: fills 32-bit words
        unsigned long zero = 0;
        CpuSet(&zero, &cartridgeWork, (1 << 24) | (1 << 26) | (sizeof(cartridgeWork) / 4));
        cartridgeWork.lockID = (unsigned short)GenerateLockOwnerID();
    }

    // usa: func_020d131c
    // CTRDG_IsOptionCartridge: whether there's a cartridge that isn't a GBA game
    int func_020d131c()
    {
        return func_020d135c() && !func_020d1344();
    }

    // usa: func_020d1344
    // CTRDGi_IsAgbCartridgeAtInit
    int func_020d1344()
    {
        CartridgeModuleInfo* info = CARTRIDGE_MODULE_INFO;
        return info->isAgbCartridge;
    }

    // CTRDG_IsPulledOut: it isn't in the ROM, but CTRDG_CheckPulledOut (in CartridgeInit.cpp) calls it
    int CTRDG_IsPulledOut()
    {
        CartridgeModuleInfo* info = CARTRIDGE_MODULE_INFO;

        if (info->moduleID == 0xffff)
        {
            return false;
        }
        if (!info->detectPullOut)
        {
            func_020d135c();
        }
        return info->detectPullOut;
    }

    // usa: func_020d135c
    // CTRDG_IsExisting: whether the cartridge that was there at boot is still there
    int func_020d135c()
    {
        int result = true;
        CartridgeLock lock;
        GBACartridgeHeader* header = CARTRIDGE_HEADER;
        CartridgeModuleInfo* info = CARTRIDGE_MODULE_INFO;

        if (info->moduleID == 0xffff)
        {
            return false;
        }
        if (info->detectPullOut == true)
        {
            return false;
        }

        func_020d14e4(cartridgeWork.lockID, &lock);
        {
            CartridgeRomCycle cycle;
            unsigned char isRomCode;

            func_020d1468(&cycle);
            isRomCode = header->isRomCode;
            if (isRomCode == CARTRIDGE_IS_ROM_CODE && info->moduleID != header->moduleID ||
                isRomCode != CARTRIDGE_IS_ROM_CODE && info->moduleID != CARTRIDGE_MODULE_ID ||
                info->gameCode != header->gameCode && info->isAgbCartridge)
            {
                info->detectPullOut = true;
                result = false;
            }
            func_020d14b0(&cycle);
        }
        func_020d1540(cartridgeWork.lockID, &lock);
        return result;
    }

    // usa: func_020d1468
    // CTRDGi_ChangeLatestAccessCycle: saves the access cycles, and sets the slowest ones
    void func_020d1468(CartridgeRomCycle* cycle)
    {
        cycle->first = (EXMEMCNT & ROM_CYCLE_FIRST_MASK) >> ROM_CYCLE_FIRST_SHIFT;
        cycle->second = (EXMEMCNT & ROM_CYCLE_SECOND_MASK) >> ROM_CYCLE_SECOND_SHIFT;
        SetRomCycleFirst(ROM_CYCLE_FIRST_18);
        SetRomCycleSecond(ROM_CYCLE_SECOND_6);
    }

    // usa: func_020d14b0
    // CTRDGi_RestoreAccessCycle
    void func_020d14b0(CartridgeRomCycle* cycle)
    {
        SetRomCycleFirst(cycle->first);
        SetRomCycleSecond(cycle->second);
    }

    // usa: func_020d14e4
    // CTRDGi_LockByProcessor: gets the GBA slot, with the interrupts disabled
    void func_020d14e4(unsigned short lockID, CartridgeLock* lock)
    {
        while (true)
        {
            lock->priorState = DisableIRQInterrupts();
            if ((lock->locked = GetLockOwner(CARTRIDGE_LOCK) & LOCKED_BY_ARM9) != 0 || TryAcquireGBABus(lockID) == 0)
            {
                break;
            }
            SetIRQInterruptState(lock->priorState);
            WaitByLoop(1);
        }
    }

    // usa: func_020d1540
    // CTRDGi_UnlockByProcessor
    void func_020d1540(unsigned short lockID, CartridgeLock* lock)
    {
        if (!lock->locked)
        {
            ReleaseGBABus(lockID);
        }
        SetIRQInterruptState(lock->priorState);
    }

    // usa: func_020d1564
    // CTRDGi_SendtoPxi
    void func_020d1564(unsigned long data)
    {
        while (SendCommandToArm7(IPC_COMMAND_CARTRIDGE, data, false) != IPCResult_Success)
        {
            WaitByLoop(1);
        }
    }

    // usa: func_020d15b4
    // CTRDG_Enable: allows writing to the GBA slot, if the cartridge isn't a GBA game
    void func_020d15b4(int enable)
    {
        int priorState = DisableIRQInterrupts();

        isEnabled = enable;
        if (!func_020d131c())
        {
            unsigned long access = enable ? REGION3_ACCESS_READ_WRITE : REGION3_ACCESS_READ_ONLY;
            func_020c8a18(REGION3_ACCESS_MASK, access);
        }

        SetIRQInterruptState(priorState);
    }
}
