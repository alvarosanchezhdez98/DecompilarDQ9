#include "System/Cache.h"
#include "System/DTCM.h"
#include "System/Interrupts.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_reset.c, the part in the ITCM (see Reset.cpp): once the ARM7 is ready, it reloads the program
// from the card and boots it again. The functions that the NitroSDK wrote in assembly are in assembly.

// HW_ROM_BASE_OFFSET_BUF: where the program is in the card, for a program that another one booted
#define ROM_BASE_OFFSET (*(unsigned long*)0x027ffc2c)
// HW_ROM_HEADER_BUF
#define ROM_HEADER 0x027ffe00
// The start of the card, which can't be read with the normal command (the secure area)
#define CARD_SECURE_AREA_END 0x8000

// The card's registers
#define REG_CARD_MASTERCNT (*(volatile unsigned char*)0x040001a1)
#define REG_CARD_CNT (*(volatile unsigned long*)0x040001a4)
#define REG_CARD_CMD ((volatile unsigned char*)0x040001a8)
#define REG_CARD_DATA (*(volatile unsigned long*)0x04100010)
#define REG_IME (*(volatile unsigned short*)0x04000208)

#define CARD_MASTER_ENABLE 0x80
#define CARD_CMD_READ_PAGE 0xb7
#define CARD_CTRL_CMD_MASK 0x07000000
#define CARD_CTRL_CMD_PAGE 0x01000000
#define CARD_CTRL_RESET_HI 0x20000000
#define CARD_CTRL_START 0x80000000
#define CARD_CTRL_READY 0x00800000

// OSi_IsResetOccurred, in Reset.cpp
extern volatile unsigned short isResetOccurred;

extern "C"
{
    void func_01ff8218();
    void func_01ff82e4();
    static void func_01ff8300();
    static void func_01ff83a8(unsigned long src, void* dst, int len);

    // OSi_DoResetSystem
    void func_01ff81e4()
    {
        while (!isResetOccurred)
        {
        }
        REG_IME = 0;
        func_01ff8300();
        func_01ff8218();
    }

    // OSi_DoBoot: clears the system's shared memory and boots the program that it reloaded
    asm void func_01ff8218()
    {
        mov r12, #0x4000000
        str r12, [r12, #0x208]
        ldr r1, =data_027e0000
        add r1, r1, #0x3fc0
        add r1, r1, #0x3c
        mov r0, #0x0
        str r0, [r1, #0x0]
        ldr r1, =0x4000180
    @L01ff8238:
        ldrh r0, [r1, #0x0]
        and r0, r0, #0xf
        cmp r0, #0x1
        bne @L01ff8238
        mov r0, #0x100
        strh r0, [r1, #0x0]
        mov r0, #0x0
        ldr r3, =0x27ffd9c
        ldr r4, [r3, #0x0]
        ldr r1, =0x27ffd80
        mov r2, #0x80
        bl func_01ff82e4
        str r4, [r3, #0x0]
        ldr r1, =0x27fff80
        mov r2, #0x18
        bl func_01ff82e4
        ldr r1, =0x27fff98
        strh r0, [r1, #0x0]
        ldr r1, =0x27fff9c
        mov r2, #0x64
        bl func_01ff82e4
        ldr r1, =0x4000180
    @L01ff8290:
        ldrh r0, [r1, #0x0]
        and r0, r0, #0xf
        cmp r0, #0x1
        beq @L01ff8290
        mov r0, #0x0
        strh r0, [r1, #0x0]
        ldr r3, =0x27ffe00
        ldr r12, [r3, #0x24]
        mov lr, r12
        ldr r11, =0x27fff80
        ldmia r11, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
        mov r11, #0x0
        bx r12
    }

    // OSi_CpuClear32
    asm void func_01ff82e4()
    {
        add r12, r1, r2
    @L01ff82e8:
        cmp r1, r12
        blt @L01ff82f4
        b @L01ff82f8
    @L01ff82f4:
        stmia r1!, {r0}
    @L01ff82f8:
        blt @L01ff82e8
        bx lr
    }

    // OSi_ReloadRomData: reads the ARM9's and the ARM7's programs from the card again
    static void func_01ff8300()
    {
        const unsigned long base = ROM_BASE_OFFSET;
        unsigned long arm9Src;
        unsigned long arm9Dst;
        unsigned long arm9Size;
        unsigned long arm7Src;
        unsigned long arm7Dst;
        unsigned long arm7Size;
        int lastState;
        if (base >= CARD_SECURE_AREA_END)
            func_01ff83a8(base, (void*)ROM_HEADER, 0x160);
        arm9Src = *(unsigned long*)(ROM_HEADER + 0x20);
        arm9Dst = *(unsigned long*)(ROM_HEADER + 0x28);
        arm9Size = *(unsigned long*)(ROM_HEADER + 0x2c);
        arm7Src = *(unsigned long*)(ROM_HEADER + 0x30);
        arm7Dst = *(unsigned long*)(ROM_HEADER + 0x38);
        arm7Size = *(unsigned long*)(ROM_HEADER + 0x3c);
        lastState = DisableIRQInterrupts();
        CleanDataCache();
        InvalidateDataCache();
        SetIRQInterruptState(lastState);
        InvalidateInstructionCache();
        DrainWriteBuffer();
        arm9Src += base;
        if (arm9Src < CARD_SECURE_AREA_END)
        {
            const unsigned long diff = CARD_SECURE_AREA_END - arm9Src;
            arm9Dst += diff;
            arm9Size -= diff;
            arm9Src = CARD_SECURE_AREA_END;
        }
        func_01ff83a8(arm9Src, (void*)arm9Dst, arm9Size);
        func_01ff83a8(arm7Src + base, (void*)arm7Dst, arm7Size);
    }

    // OSi_ReadCardRom32: reads the card in pages of 512 bytes
    static void func_01ff83a8(unsigned long src, void* dst, int len)
    {
        // The header's control of the card for the normal commands
        const unsigned long ctrlStart = (*(volatile unsigned long*)(ROM_HEADER + 0x60) & ~CARD_CTRL_CMD_MASK) |
                                        (CARD_CTRL_CMD_PAGE | CARD_CTRL_START | CARD_CTRL_RESET_HI);
        long pos = -(long)(src & (512 - 1));
        while (REG_CARD_CNT & CARD_CTRL_START)
        {
        }
        REG_CARD_MASTERCNT = CARD_MASTER_ENABLE;
        for (src += pos; pos < len; src += 512)
        {
            REG_CARD_CMD[0] = CARD_CMD_READ_PAGE;
            REG_CARD_CMD[1] = src >> 24;
            REG_CARD_CMD[2] = src >> 16;
            REG_CARD_CMD[3] = src >> 8;
            REG_CARD_CMD[4] = src;
            REG_CARD_CMD[5] = 0;
            REG_CARD_CMD[6] = 0;
            REG_CARD_CMD[7] = 0;
            REG_CARD_CNT = ctrlStart;
            for (;;)
            {
                const unsigned long ctrl = REG_CARD_CNT;
                if (ctrl & CARD_CTRL_READY)
                {
                    const unsigned long data = REG_CARD_DATA;
                    if (pos >= 0 && pos < len)
                        *(unsigned long*)((unsigned long)dst + pos) = data;
                    pos += sizeof(unsigned long);
                }
                if (!(ctrl & CARD_CTRL_START))
                    break;
            }
        }
    }
}
