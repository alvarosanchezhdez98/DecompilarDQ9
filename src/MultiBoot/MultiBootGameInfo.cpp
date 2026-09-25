#include "MultiBoot/MultiBoot.h"
#include "Filesystem/FileAccessor.h"
#include "Filesystem/LowNitroHandle.h"
#include "Filesystem/NitroVM.h"
#include <globaldefs.h>

// The NitroSDK's mb_gameinfo.c: the information of the games, which the parent sends in beacons

#pragma optimize_for_size off
#pragma optimization_level 4

// The beacon's data: the fixed part (the icon, the names) in pieces, then the volatile part (the members)
struct MbBeacon
{
    unsigned long ggid;
    unsigned char dataAttr : 2;
    unsigned char fileNo : 6;
    unsigned char seqNoFixed;
    unsigned char seqNoVolat;
    unsigned char beaconNo;
    unsigned short sum;
    union
    {
        struct
        {
            unsigned char seqNo;
            unsigned char sendNum;
            unsigned char size;
            unsigned char reserved;
            unsigned char data[0x62];
        } fixed;
        struct
        {
            unsigned char nowPlayerNum;
            char unk_1;
            unsigned short nowPlayerFlag;
            unsigned short changePlayerFlag;
            unsigned short member[4][0xb];
            unsigned char userVolatData[8];
        } volat;
    } data;
};

// What the parent sends
struct MbSendStatus
{
    char unk_0[0x10];
    int timing;
    void (*callback)(unsigned long ggid);
    MBGameInfo* list;
    MBGameInfo* now;
    const unsigned char* data;
    unsigned char state;
    unsigned char unk_25;
    unsigned char seqNoVolat;
    unsigned char seqNo;
    unsigned char sendNum;
    unsigned char beaconNo;
    char unk_2a[0x16];
    MbBeacon beacon;
};

enum
{
    STATE_NONE,
    STATE_READY,
    STATE_INIT_FIXED,
    STATE_SEND_FIXED,
    STATE_INIT_VOLAT,
    STATE_SEND_VOLAT,
    STATE_END,
};

static MbSendStatus mbss;
// What a child receives (MbBeaconRecvStatus): the parent's code doesn't use it
static unsigned char mbrs[0x59f0];

extern "C"
{
    // MIi_CpuClear16
    void func_020ca390(unsigned short value, void* dst, unsigned long size);
    // MI_CpuCopy16
    void func_020ca3b8(const void* src, void* dst, unsigned long size);
    // MIi_CpuClearFast
    void func_020ca458(unsigned long value, void* dst, unsigned long size);
    // WM_SetGameInfo
    void func_020d69cc(void* callback, const void* userGameInfo, unsigned short size, unsigned long ggid,
                       unsigned short tgid, unsigned char attr);
    // WM_GetAllowedChannel
    unsigned short func_020d4aa8();

    unsigned long MBi_GetGgid();
    unsigned short MBi_GetTgid();
    unsigned short MBi_calc_cksum(const unsigned short* buffer, int length);

    static int MBi_ReadIconInfo(const char* path, MBGameInfo* gameInfo, int isChar);
    int mystrlen(const unsigned short* string);
    static void MBi_ClearSendStatus();
    static int MBi_ReadyBeaconSendStatus();
    static void MBi_InitSendFixedBeacon();
    static void MBi_SendFixedBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr);
    static void MBi_InitSendVolatBeacon();
    static void MBi_SendVolatBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr);

    void MBi_MakeGameInfo(MBGameInfo* gameInfo, const MBGameRegistry* gameReg, const unsigned short* user)
    {
        func_020ca390(0, gameInfo, sizeof(MBGameInfo));
        gameInfo->dataAttr = 0;
        if (!MBi_ReadIconInfo(gameReg->iconCharPathp, gameInfo, true) |
            !MBi_ReadIconInfo(gameReg->iconPalettePathp, gameInfo, false))
        {
            gameInfo->dataAttr = 1;
            func_020ca458(0, gameInfo, 0x220);
        }
        gameInfo->ggid = gameReg->ggid;
        if (user != NULL)
            func_020ca3b8(user, gameInfo->parent, sizeof(gameInfo->parent));
        gameInfo->maxPlayerNum = gameReg->maxPlayerNum;
        func_020ca3b8(gameReg->gameNamep, gameInfo->gameName, (unsigned short)(mystrlen(gameReg->gameNamep) * 2));
        func_020ca3b8(gameReg->gameIntroductionp, gameInfo->gameIntroduction, sizeof(gameInfo->gameIntroduction));
        gameInfo->nowPlayerNum = 1;
        gameInfo->nowPlayerFlag = 1;
        gameInfo->sentPlayerFlag = 1;
    }

    static int MBi_ReadIconInfo(const char* path, MBGameInfo* gameInfo, int isChar)
    {
        NitroVM file;
        int size = isChar ? 0x200 : 0x20;
        void* dst = gameInfo->iconPalette;
        if (isChar)
            dst = gameInfo->iconChar;
        if (path == NULL)
            return false;
        NitroVM_Initialize(&file);
        if (!NitroVM_PrepareReadFileByPath(&file, path))
            return false;
        if (size != file.fileInfo.endOffset - file.fileInfo.startOffset)
        {
            NitroVM_FinishRead(&file);
            return false;
        }
        NitroVM_ReadSync(&file, dst, size);
        NitroVM_FinishRead(&file);
        return true;
    }

    void MB_UpdateGameInfoMember(MBGameInfo* gameInfo, const unsigned short* member, unsigned short nowPlayerFlag,
                                 unsigned short changePlayerFlag)
    {
        unsigned char playerNum = 1;
        func_020ca3b8(member, gameInfo->member, sizeof(gameInfo->member));
        for (int i = 0; i < 15; i++)
        {
            if (nowPlayerFlag & (2 << i))
                playerNum++;
        }
        gameInfo->nowPlayerNum = playerNum;
        gameInfo->nowPlayerFlag = nowPlayerFlag | 1;
        gameInfo->changePlayerFlag = changePlayerFlag;
        gameInfo->seqNoVolat++;
    }

    int mystrlen(const unsigned short* string)
    {
        int length = 0;
        while (*string++ != 0)
            length++;
        return length;
    }

    void MB_AddGameInfo(MBGameInfo* newGameInfo)
    {
        MBGameInfo* gameInfo = mbss.list;
        if (gameInfo == NULL)
        {
            mbss.list = newGameInfo;
        }
        else
        {
            while (gameInfo->next != NULL)
                gameInfo = gameInfo->next;
            gameInfo->next = newGameInfo;
        }
        newGameInfo->next = NULL;
    }

    void MB_InitSendGameInfoStatus()
    {
        mbss.list = NULL;
        mbss.now = NULL;
        mbss.state = STATE_READY;
        mbss.callback = NULL;
        MBi_ClearSendStatus();
    }

    static void MBi_ClearSendStatus()
    {
        mbss.unk_25 = 0;
        mbss.seqNoVolat = 0;
        mbss.seqNo = 0;
        mbss.sendNum = 0;
        mbss.beaconNo = 0;
    }

    void MB_SendGameInfoBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        while (true)
        {
            switch (mbss.state)
            {
            case STATE_NONE:
            case STATE_READY:
                if (!MBi_ReadyBeaconSendStatus())
                    return;
                break;
            case STATE_INIT_FIXED:
                MBi_InitSendFixedBeacon();
                break;
            case STATE_SEND_FIXED:
                MBi_SendFixedBeacon(ggid, tgid, attr);
                return;
            case STATE_INIT_VOLAT:
                MBi_InitSendVolatBeacon();
                break;
            case STATE_SEND_VOLAT:
                MBi_SendVolatBeacon(ggid, tgid, attr);
                return;
            case STATE_END:
                break;
            }
        }
    }

    // NONMATCHING: the C matches 66.7 %: the original reads mbss.list again to choose the next game, where the compiler
    // keeps it from the first test.
#ifdef NONMATCHING
    static int MBi_ReadyBeaconSendStatus()
    {
        MBGameInfo* next;
        if (mbss.list == NULL)
        {
            func_020d69cc(NULL, &mbss.beacon, sizeof(MbBeacon), MBi_GetGgid(), MBi_GetTgid(), 8);
            return false;
        }
        mbss.now = mbss.now != NULL && (next = mbss.now->next) != NULL ? next : mbss.list;
        MBi_ClearSendStatus();
        mbss.seqNoVolat = mbss.now->seqNoVolat;
        mbss.state = STATE_INIT_FIXED;
        return true;
    }
#else
    asm static int MBi_ReadyBeaconSendStatus()
    {
        stmdb sp!, {r4, lr}
        sub sp, sp, #0x8
        ldr r0, =mbss
        ldr r1, [r0, #0x18]
        cmp r1, #0x0
        bne @L021daf1c
        bl MBi_GetGgid
        mov r4, r0
        bl MBi_GetTgid
        str r0, [sp, #0x0]
        mov r12, #0x8
        ldr r1, =mbss+0x40
        mov r3, r4
        mov r0, #0x0
        mov r2, #0x70
        str r12, [sp, #0x4]
        bl func_020d69cc
        add sp, sp, #0x8
        mov r0, #0x0
        ldmia sp!, {r4, pc}
    @L021daf1c:
        ldr r0, [r0, #0x1c]
        cmp r0, #0x0
        ldrne r1, [r0, #0x4bc]
        cmpne r1, #0x0
        ldreq r0, =mbss
        ldreq r1, [r0, #0x18]
        ldr r0, =mbss
        str r1, [r0, #0x1c]
        bl MBi_ClearSendStatus
        ldr r1, =mbss
        mov r2, #0x2
        ldr r3, [r1, #0x1c]
        mov r0, #0x1
        ldrb r3, [r3, #0x4b4]
        strb r3, [r1, #0x26]
        strb r2, [r1, #0x24]
        add sp, sp, #0x8
        ldmia sp!, {r4, pc}
    }
#endif

    static void MBi_InitSendFixedBeacon()
    {
        if (mbss.state != STATE_INIT_FIXED)
            return;
        if (mbss.now->dataAttr == 0)
        {
            mbss.sendNum = 9;
            mbss.data = (const unsigned char*)mbss.now;
        }
        else
        {
            mbss.sendNum = 4;
            mbss.data = (const unsigned char*)mbss.now->parent;
        }
        mbss.state = STATE_SEND_FIXED;
    }

    // NONMATCHING: the C matches 93.3 %: the compiler gives the game and the data being sent each other's registers.
#ifdef NONMATCHING
    static void MBi_SendFixedBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        if (mbss.data + sizeof(mbss.beacon.data.fixed.data) <= &mbss.now->nowPlayerNum)
        {
            mbss.beacon.data.fixed.size = sizeof(mbss.beacon.data.fixed.data);
        }
        else
        {
            mbss.beacon.data.fixed.size = &mbss.now->nowPlayerNum - mbss.data;
            func_020ca390(0, mbss.beacon.data.fixed.data + mbss.beacon.data.fixed.size,
                          sizeof(mbss.beacon.data.fixed.data) - mbss.beacon.data.fixed.size);
        }
        func_020ca3b8(mbss.data, mbss.beacon.data.fixed.data, mbss.beacon.data.fixed.size);
        mbss.beacon.data.fixed.seqNo = mbss.seqNo;
        mbss.beacon.data.fixed.sendNum = mbss.sendNum;
        mbss.beacon.dataAttr = mbss.now->dataAttr;
        mbss.beacon.seqNoFixed = mbss.now->seqNoFixed;
        mbss.beacon.seqNoVolat = mbss.seqNoVolat;
        mbss.beacon.ggid = mbss.now->ggid;
        mbss.beacon.fileNo = mbss.now->fileNo;
        mbss.beacon.beaconNo = mbss.beaconNo++;
        mbss.beacon.sum = 0;
        mbss.beacon.sum = MBi_calc_cksum(&mbss.beacon.sum, 0x68);
        if (++mbss.seqNo < mbss.sendNum)
            mbss.data += sizeof(mbss.beacon.data.fixed.data);
        else
            mbss.state = STATE_INIT_VOLAT;
        func_020d69cc(NULL, &mbss.beacon, sizeof(MbBeacon), ggid, tgid, attr | 3);
    }
#else
    asm static void MBi_SendFixedBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, lr}
        sub sp, sp, #0x8
        ldr r3, =mbss
        mov r6, r0
        ldr r4, [r3, #0x1c]
        ldr r0, [r3, #0x20]
        add r12, r4, #0x358
        add r7, r0, #0x62
        cmp r7, r12
        movls r0, #0x62
        mov r5, r1
        mov r4, r2
        strlsb r0, [r3, #0x4c]
        bls @L021db018
        sub r7, r12, r0
        and r1, r7, #0xff
        ldr r0, =mbss+0x4e
        rsb r2, r1, #0x62
        add r1, r0, r1
        mov r0, #0x0
        strb r7, [r3, #0x4c]
        bl func_020ca390
    @L021db018:
        ldr r0, =mbss
        ldr r1, =mbss+0x4e
        ldrb r2, [r0, #0x4c]
        ldr r0, [r0, #0x20]
        bl func_020ca3b8
        ldr r2, =mbss
        ldr r0, =mbss+0x48
        ldrb r7, [r2, #0x27]
        mov r3, #0x0
        mov r1, #0x68
        strb r7, [r2, #0x4a]
        ldrb r7, [r2, #0x28]
        strb r7, [r2, #0x4b]
        ldr r7, [r2, #0x1c]
        ldrb lr, [r2, #0x44]
        ldrb r12, [r7, #0x4b2]
        bic lr, lr, #0x3
        and r12, r12, #0x3
        orr r12, lr, r12
        strb r12, [r2, #0x44]
        ldrb r12, [r7, #0x4b3]
        strb r12, [r2, #0x45]
        ldrb r12, [r2, #0x26]
        strb r12, [r2, #0x46]
        ldr r12, [r7, #0x4b8]
        str r12, [r2, #0x40]
        ldrb lr, [r2, #0x44]
        ldrb r12, [r7, #0x4b5]
        bic lr, lr, #0xfc
        mov r12, r12, lsl #0x1a
        orr r12, lr, r12, lsr #0x18
        strb r12, [r2, #0x44]
        ldrb lr, [r2, #0x29]
        add r12, lr, #0x1
        strb r12, [r2, #0x29]
        strb lr, [r2, #0x47]
        strh r3, [r2, #0x48]
        bl MBi_calc_cksum
        ldr r1, =mbss
        strh r0, [r1, #0x48]
        ldrb r0, [r1, #0x27]
        add r2, r0, #0x1
        strb r2, [r1, #0x27]
        ldrb r0, [r1, #0x28]
        and r2, r2, #0xff
        cmp r2, r0
        movhs r0, #0x4
        strhsb r0, [r1, #0x24]
        bhs @L021db0e8
        ldr r0, [r1, #0x20]
        add r0, r0, #0x62
        str r0, [r1, #0x20]
    @L021db0e8:
        orr r0, r4, #0x3
        ldr r1, =mbss+0x40
        mov r3, r6
        str r5, [sp, #0x0]
        and r4, r0, #0xff
        mov r0, #0x0
        mov r2, #0x70
        str r4, [sp, #0x4]
        bl func_020d69cc
        add sp, sp, #0x8
        ldmia sp!, {r3, r4, r5, r6, r7, pc}
    }
#endif

    static void MBi_InitSendVolatBeacon()
    {
        mbss.now->sentPlayerFlag = 1;
        mbss.seqNoVolat = mbss.now->seqNoVolat;
        mbss.state = STATE_SEND_VOLAT;
    }

    // NONMATCHING: the C matches 72.3 %: the original computes the addresses of the members with a multiplication in each
    // iteration of the loops, where the compiler increments pointers.
#ifdef NONMATCHING
    static void MBi_SendVolatBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        int i;
        unsigned long count;
        if (mbss.seqNoVolat != mbss.now->seqNoVolat)
            MBi_InitSendVolatBeacon();
        mbss.beacon.dataAttr = 2;
        mbss.beacon.seqNoFixed = mbss.now->seqNoFixed;
        mbss.beacon.seqNoVolat = mbss.seqNoVolat;
        mbss.beacon.ggid = mbss.now->ggid;
        mbss.beacon.fileNo = mbss.now->fileNo;
        mbss.beacon.beaconNo = mbss.beaconNo++;
        mbss.beacon.data.volat.nowPlayerNum = mbss.now->nowPlayerNum;
        mbss.beacon.data.volat.nowPlayerFlag = mbss.now->nowPlayerFlag;
        mbss.beacon.data.volat.changePlayerFlag = mbss.now->changePlayerFlag;
        if (mbss.timing == 0 && mbss.callback != NULL)
            mbss.callback(mbss.now->ggid);
        for (i = 0; i < 8; i++)
            mbss.beacon.data.volat.userVolatData[i] = mbss.now->userVolatData[i];
        func_020ca390(0, mbss.beacon.data.volat.member, sizeof(mbss.beacon.data.volat.member));
        count = 0;
        {
            const unsigned short remain = mbss.now->sentPlayerFlag ^ mbss.now->nowPlayerFlag;
            for (i = 0; i < 15; i++)
            {
                if (remain & (2 << i))
                {
                    func_020ca3b8(mbss.now->member[i], mbss.beacon.data.volat.member[count], 0x16);
                    count++;
                    mbss.now->sentPlayerFlag |= 2 << i;
                    if (count == 4)
                        break;
                }
            }
        }
        if (count < 4)
            *(unsigned char*)mbss.beacon.data.volat.member[count] &= ~0xf0;
        mbss.beacon.sum = 0;
        mbss.beacon.sum = MBi_calc_cksum(&mbss.beacon.sum, 0x68);
        if (mbss.now->sentPlayerFlag == mbss.now->nowPlayerFlag)
            mbss.state = STATE_READY;
        func_020d69cc(NULL, &mbss.beacon, sizeof(MbBeacon), ggid, tgid, attr | 3);
        if (mbss.timing == 1 && mbss.callback != NULL)
            mbss.callback(mbss.now->ggid);
    }
#else
    asm static void MBi_SendVolatBeacon(unsigned long ggid, unsigned short tgid, unsigned char attr)
    {
        stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
        sub sp, sp, #0x14
        ldr r3, =mbss
        str r0, [sp, #0x8]
        ldr r0, [r3, #0x1c]
        ldrb r3, [r3, #0x26]
        ldrb r0, [r0, #0x4b4]
        str r1, [sp, #0xc]
        str r2, [sp, #0x10]
        cmp r3, r0
        beq @L021db184
        bl MBi_InitSendVolatBeacon
    @L021db184:
        ldr r2, =mbss
        ldrb r0, [r2, #0x44]
        bic r0, r0, #0x3
        orr r0, r0, #0x2
        strb r0, [r2, #0x44]
        ldr r0, [r2, #0x1c]
        ldrb r3, [r0, #0x4b3]
        add r1, r0, #0x300
        strb r3, [r2, #0x45]
        ldrb r3, [r2, #0x26]
        strb r3, [r2, #0x46]
        ldr r3, [r0, #0x4b8]
        str r3, [r2, #0x40]
        ldrb r4, [r2, #0x44]
        ldrb r3, [r0, #0x4b5]
        bic r4, r4, #0xfc
        mov r3, r3, lsl #0x1a
        orr r3, r4, r3, lsr #0x18
        strb r3, [r2, #0x44]
        ldrb r4, [r2, #0x29]
        add r3, r4, #0x1
        strb r3, [r2, #0x29]
        strb r4, [r2, #0x47]
        ldrb r3, [r0, #0x358]
        strb r3, [r2, #0x4a]
        ldrh r3, [r1, #0x5a]
        strh r3, [r2, #0x4c]
        ldrh r1, [r1, #0x5c]
        strh r1, [r2, #0x4e]
        ldr r1, [r2, #0x10]
        cmp r1, #0x0
        bne @L021db218
        ldr r1, [r2, #0x14]
        cmp r1, #0x0
        beq @L021db218
        ldr r0, [r0, #0x4b8]
        blx r1
    @L021db218:
        ldr r0, =mbss
        mov r9, #0x0
        ldr r1, =mbss+0xa8
        ldr r2, [r0, #0x1c]
        b @L021db23c
    @L021db22c:
        add r0, r2, r9
        ldrb r0, [r0, #0x4a8]
        strb r0, [r1, r9]
        add r9, r9, #0x1
    @L021db23c:
        cmp r9, #0x8
        blt @L021db22c
        ldr r1, =mbss+0x50
        mov r0, #0x0
        mov r2, #0x58
        bl func_020ca390
        ldr r5, =mbss
        mov r10, #0x0
        ldr r1, [r5, #0x1c]
        mov r6, #0x2
        add r0, r1, #0x400
        add r1, r1, #0x300
        ldrh r2, [r0, #0xb0]
        ldrh r0, [r1, #0x5a]
        mov r9, r10
        ldr r7, =mbss+0x50
        eor r0, r2, r0
        mov r4, r0, lsl #0x10
        mov r8, r6
        mov r11, #0x16
        b @L021db2e0
    @L021db290:
        mov r0, r8, lsl r9
        tst r0, r4, lsr #0x10
        beq @L021db2dc
        ldr r0, [r5, #0x1c]
        mla r1, r10, r11, r7
        add r0, r0, #0x5e
        add r2, r0, #0x300
        mov r0, #0x16
        mla r0, r9, r0, r2
        mov r2, #0x16
        bl func_020ca3b8
        ldr r0, [r5, #0x1c]
        add r10, r10, #0x1
        add r0, r0, #0x400
        ldrh r1, [r0, #0xb0]
        cmp r10, #0x4
        orr r1, r1, r6, lsl r9
        strh r1, [r0, #0xb0]
        beq @L021db2e8
    @L021db2dc:
        add r9, r9, #0x1
    @L021db2e0:
        cmp r9, #0xf
        blt @L021db290
    @L021db2e8:
        cmp r10, #0x4
        bhs @L021db308
        mov r0, #0x16
        mul r1, r10, r0
        ldr r2, =mbss+0x50
        ldrb r0, [r2, r1]
        bic r0, r0, #0xf0
        strb r0, [r2, r1]
    @L021db308:
        ldr r2, =mbss
        mov r3, #0x0
        ldr r0, =mbss+0x48
        mov r1, #0x68
        strh r3, [r2, #0x48]
        bl MBi_calc_cksum
        ldr r2, =mbss
        strh r0, [r2, #0x48]
        ldr r1, [r2, #0x1c]
        add r0, r1, #0x400
        add r1, r1, #0x300
        ldrh r3, [r0, #0xb0]
        ldrh r0, [r1, #0x5a]
        ldr r1, =mbss+0x40
        cmp r3, r0
        moveq r0, #0x1
        streqb r0, [r2, #0x24]
        ldr r0, [sp, #0x10]
        ldr r3, [sp, #0x8]
        orr r2, r0, #0x3
        ldr r0, [sp, #0xc]
        and r4, r2, #0xff
        str r0, [sp, #0x0]
        mov r0, #0x0
        mov r2, #0x70
        str r4, [sp, #0x4]
        bl func_020d69cc
        ldr r0, =mbss
        ldr r1, [r0, #0x10]
        cmp r1, #0x1
        addne sp, sp, #0x14
        ldmneia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r1, [r0, #0x14]
        cmp r1, #0x0
        addeq sp, sp, #0x14
        ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
        ldr r0, [r0, #0x1c]
        ldr r0, [r0, #0x4b8]
        blx r1
        add sp, sp, #0x14
        ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
    }
#endif

    int changeScanChannel(WMScanParam* param)
    {
        unsigned short allowed;
        unsigned short channel;
        unsigned short i;
        allowed = func_020d4aa8();
        if (allowed == 0)
            return false;
        for (i = 0, channel = param->channel; i < 16; i++, channel = channel == 16 ? 1 : channel + 1)
        {
            if ((allowed & (1 << (channel - 1))) && param->channel != channel)
            {
                param->channel = channel;
                break;
            }
        }
        return true;
    }
}
