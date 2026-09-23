#include "System/DMA.h"
#include "System/GamecardBusOwnership.h"
#include "System/Graphics.h"
#include "System/Interrupts.h"
#include "System/VRAM.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's gx.c: initializes the graphics and turns the displays on and off. GX_HBlankIntr and GX_IsDispOn
// aren't in the ROM.

// The NitroSDK's GX_DMA_NOT_USE
#define NO_DMA_CHANNEL -1
// The NitroSDK's OS_LOCK_ID_ERROR
#define LOCK_ID_ERROR -3

// POWCNT's bits: the LCDs, the 2D engine A, the 3D rendering and geometry engines, the 2D engine B, and the main
// engine on the top screen
#define POWER_LCD 0x0001
#define POWER_ALL 0x020e
#define POWER_SWAP_SCREENS 0x8000

// DISPCNT's display mode (0 to turn the display off), and the settings of the BG modes and VRAM
#define DISPLAY_MODE_MASK 0x30000
#define DISPLAY_MODE_SHIFT 16
#define DISPLAY_MODE_GRAPHICS 1
#define GRAPHICS_MODE_MASK 0x000f000f

// MASTER_BRIGHT's modes
#define BRIGHTNESS_MODE_MASK 0xc000
#define BRIGHTNESS_MODE_UP 0x4000
#define BRIGHTNESS_MODE_DOWN 0x8000
#define BRIGHTNESS_VALUE_MASK 0x1f

// The NitroSDK's GXi_DmaId: the DMA channel that the graphics functions use, NO_DMA_CHANNEL to copy with the CPU
int data_020f2270 = 3;
// The NitroSDK's sDispMode: the display mode while the display is off
static unsigned short displayMode = 0;
// The NitroSDK's GXi_VRamLockId: the lock ID of the VRAM (VRAM.cpp uses it too)
volatile unsigned short data_02111222 = 0;
// The NitroSDK's sIsDispOn
static unsigned short isDisplayOn = 1;

extern "C"
{
    // usa: func_020ca3ec
    // The NitroSDK's MIi_CpuClear32: fills memory with a 32-bit value
    void func_020ca3ec(int value, void* dst, unsigned int len);
    // usa: func_020c9be0
    // The NitroSDK's OS_Terminate: stops the program
    void func_020c9be0();

    // usa: func_020c36f0
    // GX_Init
    void func_020c36f0()
    {
        const unsigned short bgMatrixOne = 1 << 8;

        POWCNT |= POWER_SWAP_SCREENS;
        // GX_SetPower
        POWCNT = (POWCNT & ~POWER_ALL) | POWER_ALL;
        // GXi_PowerLCD
        POWCNT |= POWER_LCD;
        // GX_InitGXState
        InitializeVRAM();

        {
            long lockResult;

            while (data_02111222 == 0)
            {
                lockResult = GenerateLockOwnerID();
                if (lockResult == LOCK_ID_ERROR)
                {
                    // OS_Panic, which only terminates in a final ROM
                    func_020c9be0();
                }
                data_02111222 = (unsigned short)lockResult;
            }
        }

        // The main engine's registers
        DISPSTAT = 0;
        DISPCNT = 0;
        if (data_020f2270 != NO_DMA_CHANNEL)
        {
            DMAMemsetSynchronous(data_020f2270, 0x04000008, 0, 0x04000068 - 0x04000008);
            MASTER_BRIGHT = 0;

            // The sub engine's registers
            DMAMemsetSynchronous(data_020f2270, 0x04001000, 0, 0x0400106c - 0x04001000 + 4);
        }
        else
        {
            func_020ca3ec(0, (void*)0x04000008, 0x04000068 - 0x04000008);
            MASTER_BRIGHT = 0;

            // The sub engine's registers
            func_020ca3ec(0, (void*)0x04001000, 0x0400106c - 0x04001000 + 4);
        }

        BG2PA = bgMatrixOne;
        BG2PD = bgMatrixOne;
        BG3PA = bgMatrixOne;
        BG3PD = bgMatrixOne;
        BG2PASUB = bgMatrixOne;
        BG2PDSUB = bgMatrixOne;
        BG3PASUB = bgMatrixOne;
        BG3PDSUB = bgMatrixOne;
    }

    // usa: func_020c383c
    // GX_SetVCountEqVal: sets the line of the V-count match interrupt
    void func_020c383c(long line)
    {
        DISPSTAT = (unsigned short)((DISPSTAT & 0x3f) | ((line & 0xff) << 8) | ((line & 0x100) >> 1));
    }

    // usa: func_020c3864
    // GX_VBlankIntr: enables or disables the V-blank interrupt, and returns whether it was enabled
    long func_020c3864(int enable)
    {
        long previous = DISPSTAT & 8;
        if (enable)
        {
            DISPSTAT |= 8;
        }
        else
        {
            DISPSTAT &= ~8;
        }
        return previous;
    }

    // usa: func_020c3898
    // GX_DispOff
    void func_020c3898()
    {
        unsigned long displayControl = DISPCNT;

        isDisplayOn = 0;
        displayMode = (unsigned short)((displayControl & DISPLAY_MODE_MASK) >> DISPLAY_MODE_SHIFT);

        DISPCNT = displayControl & ~DISPLAY_MODE_MASK;
    }

    // usa: func_020c38d4
    // GX_DispOn
    void func_020c38d4()
    {
        isDisplayOn = 1;
        if (displayMode != 0)
        {
            // Restore the display mode
            DISPCNT = (DISPCNT & ~DISPLAY_MODE_MASK) | (displayMode << DISPLAY_MODE_SHIFT);
        }
        else
        {
            DISPCNT = DISPCNT | (DISPLAY_MODE_GRAPHICS << DISPLAY_MODE_SHIFT);
        }
    }

    // usa: func_020c391c
    // GX_SetGraphicsMode: sets the main engine's display mode, BG mode and whether BG 0 is 3D
    void func_020c391c(int mode, int bgMode, int bg0Is3D)
    {
        unsigned long displayControl = DISPCNT;

        displayMode = (unsigned short)mode;
        if (!isDisplayOn)
        {
            mode = 0;
        }

        displayControl &= ~GRAPHICS_MODE_MASK;

        DISPCNT = (unsigned long)(displayControl | (mode << DISPLAY_MODE_SHIFT) | bgMode | (bg0Is3D << 3));

        if (displayMode == 0)
        {
            isDisplayOn = 0;
        }
    }

    // usa: func_020c3984
    // GXS_SetGraphicsMode: sets the sub engine's BG mode
    void func_020c3984(int bgMode)
    {
        DISPCNTSUB = (DISPCNTSUB & ~7) | bgMode;
    }

    // usa: func_020c39a0
    // GXx_SetMasterBrightness_: from -16 (black) to 16 (white)
    void func_020c39a0(volatile unsigned short* reg, int brightness)
    {
        if (brightness == 0)
        {
            *reg = 0;
        }
        else if (brightness > 0)
        {
            *reg = (unsigned short)(BRIGHTNESS_MODE_UP | brightness);
        }
        else
        {
            *reg = (unsigned short)(BRIGHTNESS_MODE_DOWN | -brightness);
        }
    }

    // usa: func_020c39c8
    // GXx_GetMasterBrightness_
    int func_020c39c8(volatile unsigned short* reg)
    {
        unsigned short mode = (unsigned short)(*reg & BRIGHTNESS_MODE_MASK);

        if (mode == 0)
        {
            return 0;
        }
        else if (mode == BRIGHTNESS_MODE_UP)
        {
            return *reg & BRIGHTNESS_VALUE_MASK;
        }
        else if (mode == BRIGHTNESS_MODE_DOWN)
        {
            return -(*reg & BRIGHTNESS_VALUE_MASK);
        }
        else
        {
            return 0;
        }
    }

    // usa: func_020c3a0c
    // GX_SetDefaultDMA: sets the DMA channel of the graphics functions, and returns the previous one
    int func_020c3a0c(int channel)
    {
        int previous = data_020f2270;
        int priorState;

        if (data_020f2270 != NO_DMA_CHANNEL)
        {
            AwaitDMACompletion(data_020f2270);
        }

        priorState = DisableIRQInterrupts();

        data_020f2270 = channel;

        SetIRQInterruptState(priorState);

        return previous;
    }
}
