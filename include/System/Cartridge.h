#pragma once

#include "System/ProcessorContext.h"

// The NitroSDK's cartridge library (CTRDG): what's in the GBA slot

// CTRDGHeader: the header of a GBA cartridge
struct GBACartridgeHeader
{
    unsigned long startAddress; // 0
    unsigned char nintendoLogo[0x9c]; // 4
    char title[12]; // a0
    unsigned long gameCode; // ac
    unsigned short makerCode; // b0
    unsigned char isRomCode; // b2, CARTRIDGE_IS_ROM_CODE for the cartridges with a program
    unsigned char machineCode; // b3
    unsigned char deviceType; // b4
    unsigned char exLsiID[3]; // b5
    unsigned char reserved[4]; // b8
    unsigned char softVersion; // bc
    unsigned char complement; // bd
    unsigned short moduleID; // be
};

#define CARTRIDGE_IS_ROM_CODE 0x96

// CTRDGModuleInfo: what the system found in the slot at boot, at 0x027ffc30 (HW_CTRDG_MODULE_INFO_BUF)
struct CartridgeModuleInfo
{
    unsigned short moduleID; // 0, 0xffff if there's none
    unsigned char exLsiID[3]; // 2
    unsigned char isAgbCartridge : 1; // 5
    unsigned char detectPullOut : 1;
    unsigned short makerCode; // 6
    unsigned long gameCode; // 8
};

#define CARTRIDGE_MODULE_INFO ((CartridgeModuleInfo*)0x027ffc30)

// CTRDGWork
struct CartridgeWork
{
    volatile unsigned short subProcessorInitialized; // 0, the ARM7 read the module's information
    unsigned short lockID; // 2
};

// CTRDGRomCycle: the access cycles of the GBA slot
struct CartridgeRomCycle
{
    int first; // MICartridgeRomCycle1st
    int second; // MICartridgeRomCycle2nd
};

// CTRDGLockByProc
struct CartridgeLock
{
    int locked; // 0, the ARM9 already had the slot
    int priorState; // 4
};

struct CartridgeTask;

// CTRDG_TASK_FUNC
typedef unsigned long (*CartridgeTaskFunction)(CartridgeTask* task);

// CTRDGTaskInfo: a task for the cartridge's thread
struct CartridgeTask
{
    CartridgeTaskFunction task; // 0
    CartridgeTaskFunction callback; // 4
    unsigned long result; // 8
    unsigned char* data; // c
    unsigned char* address; // 10
    unsigned long offset; // 14
    unsigned long size; // 18
    unsigned char* dst; // 1c
    unsigned short sectorCount; // 20
    unsigned char busy; // 22
    unsigned char param[1]; // 23
};

// CTRDGiTaskWork
struct CartridgeTaskWork
{
    ProcessorContext thread; // 0
    CartridgeTask* volatile list; // c0, the task to run
    CartridgeTask endTask; // c4
};

// The IPC command of the cartridge (the NitroSDK's PXI_FIFO_TAG_CTRDG), and its commands (CTRDG_PXI_COMMAND_*)
#define IPC_COMMAND_CARTRIDGE 13
#define CARTRIDGE_COMMAND_MASK 0x3f
#define CARTRIDGE_COMMAND_PARAM_SHIFT 6
#define CARTRIDGE_COMMAND_INIT_MODULE_INFO 0x01
#define CARTRIDGE_COMMAND_TERMINATE 0x02
#define CARTRIDGE_COMMAND_PULLED_OUT 0x11

// CTRDGi_Work
extern CartridgeWork cartridgeWork;

extern "C"
{
    // usa: func_020d12e4
    // CTRDGi_InitCommon
    void func_020d12e4();
    // usa: func_020d131c
    // CTRDG_IsOptionCartridge
    int func_020d131c();
    // usa: func_020d1344
    // CTRDGi_IsAgbCartridgeAtInit
    int func_020d1344();
    // usa: func_020d135c
    // CTRDG_IsExisting
    int func_020d135c();
    // usa: func_020d1468
    // CTRDGi_ChangeLatestAccessCycle
    void func_020d1468(CartridgeRomCycle* cycle);
    // usa: func_020d14b0
    // CTRDGi_RestoreAccessCycle
    void func_020d14b0(CartridgeRomCycle* cycle);
    // usa: func_020d14e4
    // CTRDGi_LockByProcessor
    void func_020d14e4(unsigned short lockID, CartridgeLock* lock);
    // usa: func_020d1540
    // CTRDGi_UnlockByProcessor
    void func_020d1540(unsigned short lockID, CartridgeLock* lock);
    // usa: func_020d1564
    // CTRDGi_SendtoPxi
    void func_020d1564(unsigned long data);
    // usa: func_020d15b4
    // CTRDG_Enable
    void func_020d15b4(int enable);

    // usa: func_020d1954
    // CTRDGi_InitTaskThread
    void func_020d1954(CartridgeTaskWork* work);
    // usa: func_020d19e0
    // CTRDGi_InitTaskInfo
    void func_020d19e0(CartridgeTask* task);
}
