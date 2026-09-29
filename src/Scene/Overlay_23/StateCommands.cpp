// The commands of overlay 17's scripts that read the state of the game: the party members, the play time and the
// records of the game, the grottos... Main's func_0209fee4 gives them to a script engine with SetStateCommands()
#include "GameState/GameState.h"
#include "GameState/PartyMember.h"
#include "GameState/PlayRecords.h"
#include "GameState/Profile.h"
#include "Grotto/Main/ActiveGrottoClass.h"
#include "Resource/GameResources.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/RealTimeClock.h"
#include <globaldefs.h>
#include <std_library_functions.h>

// What func_0202ae18 returns
struct Unknown_0202ae18
{
    char unk_0[0x100d];
    unsigned char unk_100d;
};

// What the pointer at 8 of the current zone's data points to
struct Unknown_zone_8
{
    char unk_0[0xc];
    unsigned char unk_c_0 : 4;
    unsigned char unk_c_4 : 1;
    unsigned char unk_c_5 : 3;
};

// The data of the current zone, which func_02012fe4 returns
struct ZoneData
{
    unsigned short id_;
    char unk_2[6];
    Unknown_zone_8* unk_8;
    char unk_c[0x23ec - 0xc];
    ActiveGrottoClass grotto_;
};

// What func_020ac020 writes
struct Unknown_020ac020
{
    unsigned int unk_0 : 10;
    unsigned int unk_10 : 1;
    unsigned int unk_11 : 7;
    unsigned int unk_18 : 7;
    unsigned int unk_25 : 7;
};

// What func_ov017_021b8478 returns
struct Unknown_021b8478
{
    char unk_0[0x24];
    unsigned char unk_24;
    unsigned char unk_25;
};

// A command and the number that the scripts call it by
struct StateCommandEntry
{
    ScriptCommand command_;
    int id_;
};

extern "C"
{
    // ScriptValue::ToInt() and ScriptValue::Set() of overlay 17
    int func_ov017_021d60f4(const ScriptValue* value);
    void func_ov017_021d6134(ScriptValue* value, int result);
    // Sets the commands of a script engine
    void func_ov017_021d4cc0(ScriptEngine* engine, ScriptCommand* commands, int count);
    Unknown_021b8478* func_ov017_021b8478(int);

    // A party member by their number, the number of the leader(?), and the numbers of the members of the party
    PartyMember* func_0200ff1c(GameState* gameState, int member);
    int func_020100a8(GameState* gameState);
    int func_02011494(GameState* gameState, unsigned char* members);
    int func_020114ec(GameState* gameState, unsigned char* members);
    PartyMemberData* func_02053c6c(PartyMember* member);
    // Times to add to a play time
    void func_020103f0(GameState* gameState, unsigned short* hours, unsigned char* minutes, unsigned char* seconds);
    void func_020104cc(GameState* gameState, unsigned short* hours, unsigned char* minutes, unsigned char* seconds);
    int func_0201079c(GameState* gameState);
    int func_020107d0(GameState* gameState);
    int func_0201081c(GameState* gameState);
    void* func_02010828(GameState* gameState);
    ZoneData* func_02012fe4();
    bool func_0201b588(unsigned short zone);
    Unknown_0202ae18* func_0202ae18();
    int func_0202b7d8(Unknown_0202ae18*);
    int func_0202ba00(Unknown_0202ae18*);
    int func_0202c540(Unknown_0202ae18*);
    int func_02046b38(void*, void*);
    void* func_0205ec34();
    unsigned int func_0206e384(void*);
    int func_02086aec(void*, short);
    void* func_0209fe8c();
    void func_0209ffe0(void*, short);
    int func_020a0870(PlayRecords* records);
    int func_020a08a4(PlayRecords* records);
    int func_020a08d8(PlayRecords* records);
    int func_020a090c(PlayRecords* records);
    void func_020ac020(int, short*, Unknown_020ac020*, int);
    int func_020ac0b4(unsigned int*);
}

// A party member: 0 to 3 are the members' numbers, -1 is the leader(?), and -2 and less the members of the party
static PartyMember* GetMember(int index)
{
    GameState* gameState = GameState::GetInstance();
    PartyMember* member = NULL;
    if (index >= 0)
    {
        if (index >= 0 && index <= 3 ? 1 : 0)
            member = func_0200ff1c(gameState, index);
    }
    else if (index == -1)
    {
        member = func_0200ff1c(gameState, func_020100a8(gameState));
    }
    else
    {
        unsigned char members[4] = {};
        int count = func_02011494(gameState, members);
        int i = -1 - index;
        if (i < count)
            member = func_0200ff1c(gameState, members[i]);
    }
    return member;
}

// A play time plus the time played since it was saved (type 0), or since what type 1 counts
static PlayTime AddTime(PlayTime time, int type)
{
    PlayTime result;
    unsigned short hours;
    unsigned char minutes;
    unsigned char seconds;
    GameState* gameState = GameState::GetInstance();
    hours = 0;
    minutes = 0;
    seconds = 0;
    result.hours_ = 0;
    result.minutes_ = 0;
    result.seconds_ = 0;
    if (type == 0)
    {
        func_020103f0(gameState, &hours, &minutes, &seconds);
    }
    else
    {
        Unknown_0202ae18* unknown = func_0202ae18();
        int mode = func_0202ba00(unknown);
        int players = unknown->unk_100d;
        if ((mode == 5 && players > 1) || mode == 6)
        {
            func_020104cc(gameState, &hours, &minutes, &seconds);
        }
        else
        {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }
    }
    func_020ac614(&result, time.hours_ + hours);
    func_020ac644(&result, time.minutes_ + minutes);
    result.seconds_ += (unsigned char)(time.seconds_ + seconds);
    if (result.seconds_ > 59)
    {
        unsigned char added = result.seconds_ / 60;
        if (result.hours_ == 9999 && result.minutes_ + added > 59)
        {
            result.hours_ = 9999;
            result.minutes_ = 59;
            result.seconds_ = 59;
        }
        else
        {
            func_020ac644(&result, added);
            result.seconds_ %= 60;
        }
    }
    return result;
}

static int StateCommand_00(ScriptValue* params, int count)
{
    void* unknown = func_0209fe8c();
    if (unknown != NULL)
        func_0209ffe0(unknown, func_ov017_021d60f4(&params[0]));
    return 1;
}

// Writes whether a flag of the game is set
static int StateCommand_01(ScriptValue* params, int count)
{
    GameFlags flags;
    func_020ac460(&flags);
    int set = 0;
    int flag = func_ov017_021d60f4(&params[0]);
    if (flags.flags_[flag / 32] & (1 << (flag % 32)))
        set = 1;
    if (set)
        func_ov017_021d6134(&params[1], 1);
    else
        func_ov017_021d6134(&params[1], 0);
    return 1;
}

static int StateCommand_02(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    func_ov017_021d6134(&params[0], func_0201079c(gameState));
    func_ov017_021d6134(&params[1], func_020107d0(gameState));
    return 1;
}

static int StateCommand_32(ScriptValue* params, int count)
{
    void* unknown = func_0209fe8c();
    if (unknown != NULL)
        func_0209ffe0(unknown, func_ov017_021d60f4(&params[0]));
    return 1;
}

// Writes whether a flag of the records is set
static int StateCommand_33(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    int set = 0;
    int flag = func_ov017_021d60f4(&params[0]);
    unsigned int word = records.flags_[flag / 32];
    if (word & (1 << (flag % 32)))
        set = 1;
    if (set)
        func_ov017_021d6134(&params[1], 1);
    else
        func_ov017_021d6134(&params[1], 0);
    return 1;
}

// Sets a flag of the records
static int StateCommand_34(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    int flag = func_ov017_021d60f4(&params[0]);
    records.flags_[flag / 32] |= 1 << (flag % 32);
    func_020ac494(&records);
    return 1;
}

static int StateCommand_35(ScriptValue* params, int count)
{
    func_ov017_021d6134(&params[0], func_0201081c(GameState::GetInstance()));
    return 1;
}

// Writes a member's vocation, and their level and unk_b0 in it
static int StateCommand_65(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    func_ov017_021d6134(&params[1], member->data_->vocation_);
    func_ov017_021d6134(&params[2], member->data_->details_.levels_[member->data_->vocation_]);
    func_ov017_021d6134(&params[3], member->data_->details_.unk_b0[member->data_->vocation_]);
    return 1;
}

// Writes whether a member is a woman
static int StateCommand_66(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    func_ov017_021d6134(&params[1], member->data_->details_.appearance_.female_);
    return 1;
}

// Writes whether a member has the pieces of equipment of the parameters (pairs of a slot and an item)
// NONMATCHING: the C matches 47.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original colors the loop's limit and a zero last (r9, r10); tried declaration orders, a local copy of params and
// the permuter
#ifdef NONMATCHING
static int StateCommand_67(ScriptValue* params, int count)
{
    int slot;
    PartyMember* member;
    int equipped;
    int i;
    GameState::GetInstance();
    member = GetMember(func_ov017_021d60f4(params++));
    if (member == NULL)
        return 0;
    equipped = 1;
    for (i = 0; i < count - 2; i += 2)
    {
        slot = func_ov017_021d60f4(params++);
        if (((PartEntry*)((char*)member->data_ + 0x194))[(unsigned char)slot].unk_18 != func_ov017_021d60f4(params++))
            equipped = 0;
    }
    if (equipped)
        func_ov017_021d6134(params, 1);
    else
        func_ov017_021d6134(params, 0);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

static asm int StateCommand_67(ScriptValue* params, int count)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    mov r8, r0
    mov r4, r1
    bl _ZN9GameState11GetInstanceEv
    mov r0, r8
    bl func_ov017_021d60f4
    add r8, r8, #0x8
    bl GetMember
    movs r5, r0
    moveq r0, #0x0
    ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    mov r7, #0x0
    mov r6, #0x1
    sub r9, r4, #0x2
    mov r10, r7
    b @L021e949c
@L021e9464:
    mov r0, r8
    bl func_ov017_021d60f4
    mov r4, r0
    add r0, r8, #0x8
    add r8, r8, #0x10
    bl func_ov017_021d60f4
    ldr r2, [r5, #0x150]
    and r1, r4, #0xff
    add r2, r2, #0x194
    add r1, r2, r1, lsl #0x5
    ldrsh r1, [r1, #0x18]
    add r7, r7, #0x2
    cmp r1, r0
    movne r6, r10
@L021e949c:
    cmp r7, r9
    blt @L021e9464
    cmp r6, #0x0
    mov r0, r8
    beq @L021e94bc
    mov r1, #0x1
    bl func_ov017_021d6134
    b @L021e94c4
@L021e94bc:
    mov r1, #0x0
    bl func_ov017_021d6134
@L021e94c4:
    mov r0, #0x1
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

// Writes a statistic of a member
static int StateCommand_68(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    switch (func_ov017_021d60f4(&params[1]))
    {
    case 0:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_0_0);
        break;
    case 1:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_0_10);
        break;
    case 2:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_0_20);
        break;
    case 3:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_4_0);
        break;
    case 4:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_4_10);
        break;
    case 5:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_4_20);
        break;
    case 6:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_8_0);
        break;
    case 7:
        func_ov017_021d6134(&params[2], member->status_->unk_30);
        break;
    case 8:
        func_ov017_021d6134(&params[2], member->status_->unk_32);
        break;
    case 9:
        func_ov017_021d6134(&params[2], member->status_->unk_34);
        break;
    case 10:
        func_ov017_021d6134(&params[2], member->status_->unk_36);
        break;
    case 11:
        func_ov017_021d6134(&params[2], (unsigned short)member->data_->unk_c_0);
        break;
    }
    return 1;
}

// Writes a sum of the bonuses of a member's equipment
static int StateCommand_69(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    int bonuses[6] = {};
    for (int i = 0; i < 11; i++)
    {
        PartEntry* entry = &member->data_->details_.equipment_[(unsigned char)i];
        PartModelInfo* info;
        if (entry != NULL && (info = entry->model_) != NULL)
        {
            bonuses[0] += info->unk_18_0;
            bonuses[1] += info->unk_18_10;
            bonuses[2] += info->unk_18_20;
            bonuses[3] += info->unk_1c_0;
            bonuses[4] += info->unk_1c_10;
            bonuses[5] += info->unk_1c_20;
        }
    }
    switch (func_ov017_021d60f4(&params[1]))
    {
    case 0:
        func_ov017_021d6134(&params[2], bonuses[4]);
        break;
    case 1:
        func_ov017_021d6134(&params[2], bonuses[0]);
        break;
    case 2:
        func_ov017_021d6134(&params[2], bonuses[1]);
        break;
    case 3:
        func_ov017_021d6134(&params[2], bonuses[2]);
        break;
    case 4:
        func_ov017_021d6134(&params[2], bonuses[3]);
        break;
    case 5:
        func_ov017_021d6134(&params[2], bonuses[5]);
        break;
    }
    return 1;
}

// Writes the points that a member spent on a skill
static int StateCommand_6a(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    int skill = func_ov017_021d60f4(&params[1]);
    func_ov017_021d6134(&params[2], member->data_->details_.skillPoints_[(unsigned char)skill]);
    return 1;
}

// Writes a member's HP
static int StateCommand_6b(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    func_ov017_021d6134(&params[1], member->unk_130[2]);
    return 1;
}

// Writes a member's MP(?)
static int StateCommand_6c(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    func_ov017_021d6134(&params[1], member->unk_130[3]);
    return 1;
}

static int StateCommand_6d(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_10_9);
    return 1;
}

static int StateCommand_6e(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_c_14);
    return 1;
}

static int StateCommand_6f(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_8_24);
    return 1;
}

static int StateCommand_70(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_10_0);
    return 1;
}

static int StateCommand_72(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], func_020a0870(&records));
    return 1;
}

static int StateCommand_71(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], func_020a090c(&records));
    return 1;
}

static int StateCommand_73(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], func_020a08a4(&records));
    return 1;
}

static int StateCommand_74(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], func_020a08d8(&records));
    return 1;
}

static int StateCommand_75(ScriptValue* params, int count)
{
    func_ov017_021d6134(&params[0], *(int*)((char*)func_02010828(GameState::GetInstance()) + 0xf68));
    return 1;
}

// Writes whether today is the player's birthday
static int StateCommand_76(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    RealTimeClockDate date;
    func_020cf0fc(&date);
    ProfileData* profile = GetProfile(gameState);
    if (date.month == profile->month_ && date.day == profile->day_)
        func_ov017_021d6134(&params[0], 1);
    else
        func_ov017_021d6134(&params[0], 0);
    return 1;
}

// Writes the number of bits set of func_0206e384's value, plus 16
static int StateCommand_77(ScriptValue* params, int count)
{
    unsigned int bits = 0xffff | (func_0206e384(func_0205ec34()) << 16);
    int set = 0;
    while (bits != 0)
    {
        set += bits & 1;
        bits >>= 1;
    }
    func_ov017_021d6134(&params[0], set);
    return 1;
}

static int StateCommand_78(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_18_0);
    return 1;
}

static int StateCommand_79(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_18_9);
    return 1;
}

static int StateCommand_7a(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_18_16);
    return 1;
}

// Writes the hours and the minutes played
static int StateCommand_7b(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime time = AddTime(records.playTime_, 0);
    func_ov017_021d6134(&params[0], time.hours_);
    func_ov017_021d6134(&params[1], time.minutes_);
    return 1;
}

static int StateCommand_7c(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime time = AddTime(records.unk_4, 1);
    func_ov017_021d6134(&params[0], time.hours_);
    func_ov017_021d6134(&params[1], time.minutes_);
    return 1;
}

static int StateCommand_7d(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_2c_0);
    return 1;
}

static int StateCommand_7e(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_30_0);
    return 1;
}

static int StateCommand_7f(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_34_0);
    return 1;
}

static int StateCommand_80(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_38_0);
    return 1;
}

static int StateCommand_81(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_3c_0);
    return 1;
}

static int StateCommand_82(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_8_0);
    return 1;
}

static int StateCommand_83(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_28_12);
    return 1;
}

static int StateCommand_84(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_28_0);
    return 1;
}

static int StateCommand_85(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_1c_0);
    return 1;
}

static int StateCommand_86(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_40_0);
    return 1;
}

static int StateCommand_87(ScriptValue* params, int count)
{
    unsigned int value = 0;
    func_020ac0b4(&value);
    func_ov017_021d6134(&params[0], value);
    return 1;
}

static int StateCommand_88(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_28_22);
    return 1;
}

static int StateCommand_89(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_24_0);
    return 1;
}

static int StateCommand_8a(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    unsigned int value = records.unk_44;
    if (value > 0x7fffffff)
        value = 0x7fffffff;
    func_ov017_021d6134(&params[0], value);
    return 1;
}

static int StateCommand_8b(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    unsigned int value = records.unk_48;
    if (value > 0x7fffffff)
        value = 0x7fffffff;
    func_ov017_021d6134(&params[0], value);
    return 1;
}

static int StateCommand_8c(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime time = AddTime(records.unk_68, 0);
    func_ov017_021d6134(&params[0], time.hours_);
    func_ov017_021d6134(&params[1], time.minutes_);
    return 1;
}

static int StateCommand_8d(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime time = AddTime(records.unk_6c, 1);
    func_ov017_021d6134(&params[0], time.hours_);
    func_ov017_021d6134(&params[1], time.minutes_);
    return 1;
}

static int StateCommand_8e(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_70_0);
    return 1;
}

static int StateCommand_8f(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_70_16);
    return 1;
}

static int StateCommand_90(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_74_0);
    return 1;
}

static int StateCommand_91(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_74_16);
    return 1;
}

static int StateCommand_92(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_78_0);
    return 1;
}

static int StateCommand_93(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_78_16);
    return 1;
}

static int StateCommand_94(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_7c_0);
    return 1;
}

static int StateCommand_95(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_7c_10);
    return 1;
}

static int StateCommand_96(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_7c_20);
    return 1;
}

static int StateCommand_97(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_80_0);
    return 1;
}

static int StateCommand_98(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_80_16);
    return 1;
}

static int StateCommand_99(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_84_0);
    return 1;
}

static int StateCommand_9a(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_84_10);
    return 1;
}

static int StateCommand_9b(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_88_0);
    return 1;
}

static int StateCommand_9c(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_8c_0);
    return 1;
}

// Writes the number of members in the party but the leader(?)
static int StateCommand_9d(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    func_ov017_021d6134(&params[0], func_02011494(gameState, members) - 1);
    return 1;
}

// Writes the number of members of the party, but the first, who are down
static int StateCommand_9e(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    int numMembers = func_02011494(gameState, members);
    int down = 0;
    for (int i = 1; i < numMembers; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, members[i]);
        if (member != NULL && (int)member->unk_130[2] <= 0)
            down++;
    }
    func_ov017_021d6134(&params[0], down);
    return 1;
}

// Writes the number of members of the party whose vocation is 1, 4, 7 or 9
static int StateCommand_9f(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    int numMembers = func_02011494(gameState, members);
    int found = 0;
    for (int i = 0; i < numMembers; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, members[i]);
        if (member != NULL)
        {
            switch (member->data_->vocation_)
            {
            case 1:
            case 4:
            case 7:
            case 9:
                found++;
                break;
            }
        }
    }
    func_ov017_021d6134(&params[0], found);
    return 1;
}

// Writes the number of members of the party whose vocation is 2, 3 or 10
static int StateCommand_a0(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    int numMembers = func_02011494(gameState, members);
    int found = 0;
    for (int i = 0; i < numMembers; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, members[i]);
        if (member != NULL)
        {
            int vocation = member->data_->vocation_;
            if (vocation == 2 || vocation == 3 || vocation == 10)
                found++;
        }
    }
    func_ov017_021d6134(&params[0], found);
    return 1;
}

static int StateCommand_a1(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    int numMembers = func_020114ec(gameState, members);
    int found = 0;
    for (int i = 0; i < numMembers; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, members[i]);
        if (member != NULL && !(*(unsigned short*)member & 0x1000) && (int)member->unk_130[2] > 0)
            found++;
    }
    func_ov017_021d6134(&params[0], found);
    return 1;
}

static int StateCommand_a2(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    unsigned char members[4] = {};
    int numMembers = func_020114ec(gameState, members);
    int found = 0;
    for (int i = 0; i < numMembers; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, members[i]);
        if (member != NULL && !(*(unsigned short*)member & 0x1000) && (int)member->unk_130[2] <= 0)
            found++;
    }
    func_ov017_021d6134(&params[0], found);
    return 1;
}

// Writes the sum of a member's unk_fe
static int StateCommand_a3(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    int sum = 0;
    for (int i = 0; i < 13; i++)
        sum += member->data_->details_.unk_fe[(unsigned char)i];
    func_ov017_021d6134(&params[1], sum);
    return 1;
}

static int StateCommand_a4(ScriptValue* params, int count)
{
    GameState::GetInstance();
    PartyMember* member = GetMember(func_ov017_021d60f4(&params[0]));
    if (member == NULL)
        return 0;
    int set = 0;
    if (*(unsigned int*)member->unk_130 & 2)
        set = 1;
    if (set)
        func_ov017_021d6134(&params[1], 1);
    else
        func_ov017_021d6134(&params[1], 0);
    return 1;
}

// Writes whether the leader(?) isn't down
static int StateCommand_a5(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    PartyMember* member = func_0200ff1c(gameState, func_020100a8(gameState));
    int alive = 0;
    if (member != NULL)
        alive = (int)member->unk_130[2] > 0;
    if (alive)
        func_ov017_021d6134(&params[0], 1);
    else
        func_ov017_021d6134(&params[0], 0);
    return 1;
}

// Writes the sum of the leader's(?) unk_b0, up to 0x7fffffff
static int StateCommand_a6(ScriptValue* params, int count)
{
    GameState* gameState = GameState::GetInstance();
    PartyMember* member = func_0200ff1c(gameState, func_020100a8(gameState));
    unsigned int sum = 0;
    if (member != NULL)
    {
        PartyMemberData* data = func_02053c6c(member);
        int* values = data->details_.unk_b0;
        for (int i = 0; i < 13; i++)
        {
            sum += values[i];
            if (sum > 0x7fffffff)
            {
                sum = 0x7fffffff;
                break;
            }
        }
    }
    func_ov017_021d6134(&params[0], sum);
    return 1;
}

static int StateCommand_a7(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_1c_16);
    return 1;
}

static int StateCommand_a8(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_20_0);
    return 1;
}

static int StateCommand_a9(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_20_16);
    return 1;
}

static int StateCommand_aa(ScriptValue* params, int count)
{
    if (func_0202b7d8(func_0202ae18()))
        func_ov017_021d6134(&params[0], 1);
    else
        func_ov017_021d6134(&params[0], 0);
    return 1;
}

static int StateCommand_ab(ScriptValue* params, int count)
{
    if (func_0202c540(func_0202ae18()))
        func_ov017_021d6134(&params[0], 1);
    else
        func_ov017_021d6134(&params[0], 0);
    return 1;
}

// Writes the current zone
static int StateCommand_ac(ScriptValue* params, int count)
{
    func_ov017_021d6134(&params[0], func_02012fe4()->id_);
    return 1;
}

// Writes the current zone rounded down to a hundred
static int StateCommand_ad(ScriptValue* params, int count)
{
    short zone = func_02012fe4()->id_;
    func_ov017_021d6134(&params[0], (short)(zone - zone % 100));
    return 1;
}

static int StateCommand_ae(ScriptValue* params, int count)
{
    func_ov017_021d6134(&params[0], func_02012fe4()->unk_8->unk_c_4);
    return 1;
}

static int StateCommand_af(ScriptValue* params, int count)
{
    func_ov017_021d6134(&params[0], *(int*)((char*)func_02010828(GameState::GetInstance()) + 0xf6c));
    return 1;
}

static int StateCommand_b0(ScriptValue* params, int count)
{
    void* unknown = func_02010828(GameState::GetInstance());
    int sum = 0;
    sum += func_02086aec(unknown, 0x5619);
    sum += func_02086aec(unknown, 0x561d);
    sum += func_02086aec(unknown, 0x561e);
    sum += func_02086aec(unknown, 0x561f);
    sum += func_02086aec(unknown, 0x5620);
    sum += func_02086aec(unknown, 0x5621);
    sum += func_02086aec(unknown, 0x5622);
    sum += func_02086aec(unknown, 0x5623);
    sum += func_02086aec(unknown, 0x5624);
    func_ov017_021d6134(&params[0], sum + func_02086aec(unknown, 0x5625));
    return 1;
}

static int StateCommand_b1(ScriptValue* params, int count)
{
    void* unknown = func_02010828(GameState::GetInstance());
    func_ov017_021d6134(&params[1], func_02086aec(unknown, func_ov017_021d60f4(&params[0])));
    return 1;
}

static int StateCommand_c9(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime* time = &records.unk_90;
    func_ov017_021d6134(&params[0], time->hours_);
    func_ov017_021d6134(&params[1], time->minutes_);
    return 1;
}

static int StateCommand_ca(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    PlayTime* time = &records.unk_94;
    func_ov017_021d6134(&params[0], time->hours_);
    func_ov017_021d6134(&params[1], time->minutes_);
    return 1;
}

static int StateCommand_cb(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_98_0);
    return 1;
}

static int StateCommand_cc(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_98_17);
    return 1;
}

static int StateCommand_cd(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_98_24);
    return 1;
}

static int StateCommand_ce(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_9c_0);
    return 1;
}

static int StateCommand_cf(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_9c_17);
    return 1;
}

static int StateCommand_d0(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_9c_24);
    return 1;
}

static int StateCommand_d1(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a0_0);
    return 1;
}

static int StateCommand_d2(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a4_0);
    return 1;
}

static int StateCommand_d3(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a0_9);
    return 1;
}

static int StateCommand_d4(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a4_8);
    return 1;
}

static int StateCommand_d5(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a8_0);
    return 1;
}

static int StateCommand_d6(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_a4_22);
    return 1;
}

static int StateCommand_d7(ScriptValue* params, int count)
{
    PlayRecords records;
    func_020ac4c0(&records);
    func_ov017_021d6134(&params[0], records.unk_ac);
    return 1;
}

static int StateCommand_fb(ScriptValue* params, int count)
{
    Unknown_020ac020 value;
    short id;
    value.unk_0 = 0;
    value.unk_10 = 0;
    value.unk_11 = 0;
    value.unk_18 = 0;
    id = func_ov017_021d60f4(&params[0]);
    func_020ac020(0, &id, &value, 1);
    func_ov017_021d6134(&params[1], value.unk_0);
    return 1;
}

// Writes unk_c_0 of the records in a grotto of a regular treasure map
static int StateCommand_fc(ScriptValue* params, int count)
{
    unsigned int value = 0;
    GameResources* resources = func_ov017_0218b5b0();
    void* unk36fc;
    void* unk3718 = resources->unknown_ptr_3718;
    unk36fc = resources->unknown_ptr_36fc;
    Unknown_021b8478* unknown = func_ov017_021b8478((int)unk3718);
    if (func_02046b38(unk36fc, unk3718))
    {
        ZoneData* zone = func_02012fe4();
        DetailedTreasureMapData* map = zone->grotto_.GetDetailedData();
        if (unknown->unk_24 != 0)
        {
            if (func_0201b588(zone->id_) && map != NULL)
            {
                if (map->mapType_ == 1)
                {
                    PlayRecords records;
                    func_020ac4c0(&records);
                    value = records.unk_c_0;
                }
            }
        }
    }
    func_ov017_021d6134(&params[0], value);
    return 1;
}

// Writes unk_c_7 of the records in a grotto of a legacy boss's map
static int StateCommand_fd(ScriptValue* params, int count)
{
    unsigned int value = 0;
    GameResources* resources = func_ov017_0218b5b0();
    void* unk36fc;
    void* unk3718 = resources->unknown_ptr_3718;
    unk36fc = resources->unknown_ptr_36fc;
    Unknown_021b8478* unknown = func_ov017_021b8478((int)unk3718);
    if (func_02046b38(unk36fc, unk3718))
    {
        ZoneData* zone = func_02012fe4();
        DetailedTreasureMapData* map = zone->grotto_.GetDetailedData();
        if (unknown->unk_25 != 0)
        {
            if (func_0201b588(zone->id_) && map != NULL)
            {
                if (map->mapType_ == 2)
                {
                    PlayRecords records;
                    func_020ac4c0(&records);
                    value = records.unk_c_7;
                }
            }
        }
    }
    func_ov017_021d6134(&params[0], value);
    return 1;
}

static StateCommandEntry sCommandTable[] = {
    {StateCommand_00, 0x00}, {StateCommand_01, 0x01}, {StateCommand_02, 0x02}, {StateCommand_32, 0x32}, {StateCommand_33, 0x33},
    {StateCommand_34, 0x34}, {StateCommand_35, 0x35}, {StateCommand_65, 0x65}, {StateCommand_66, 0x66}, {StateCommand_67, 0x67},
    {StateCommand_68, 0x68}, {StateCommand_69, 0x69}, {StateCommand_6a, 0x6a}, {StateCommand_6b, 0x6b}, {StateCommand_6c, 0x6c},
    {StateCommand_6d, 0x6d}, {StateCommand_6e, 0x6e}, {StateCommand_6f, 0x6f}, {StateCommand_70, 0x70}, {StateCommand_71, 0x71},
    {StateCommand_72, 0x72}, {StateCommand_73, 0x73}, {StateCommand_74, 0x74}, {StateCommand_75, 0x75}, {StateCommand_76, 0x76},
    {StateCommand_77, 0x77}, {StateCommand_78, 0x78}, {StateCommand_79, 0x79}, {StateCommand_7a, 0x7a}, {StateCommand_7b, 0x7b},
    {StateCommand_7c, 0x7c}, {StateCommand_7d, 0x7d}, {StateCommand_7e, 0x7e}, {StateCommand_7f, 0x7f}, {StateCommand_80, 0x80},
    {StateCommand_81, 0x81}, {StateCommand_82, 0x82}, {StateCommand_83, 0x83}, {StateCommand_84, 0x84}, {StateCommand_85, 0x85},
    {StateCommand_86, 0x86}, {StateCommand_87, 0x87}, {StateCommand_88, 0x88}, {StateCommand_89, 0x89}, {StateCommand_8a, 0x8a},
    {StateCommand_8b, 0x8b}, {StateCommand_8c, 0x8c}, {StateCommand_8d, 0x8d}, {StateCommand_8e, 0x8e}, {StateCommand_8f, 0x8f},
    {StateCommand_90, 0x90}, {StateCommand_91, 0x91}, {StateCommand_92, 0x92}, {StateCommand_93, 0x93}, {StateCommand_94, 0x94},
    {StateCommand_95, 0x95}, {StateCommand_96, 0x96}, {StateCommand_97, 0x97}, {StateCommand_98, 0x98}, {StateCommand_99, 0x99},
    {StateCommand_9a, 0x9a}, {StateCommand_9b, 0x9b}, {StateCommand_9c, 0x9c}, {StateCommand_9d, 0x9d}, {StateCommand_9e, 0x9e},
    {StateCommand_9f, 0x9f}, {StateCommand_a0, 0xa0}, {StateCommand_a1, 0xa1}, {StateCommand_a2, 0xa2}, {StateCommand_a3, 0xa3},
    {StateCommand_a4, 0xa4}, {StateCommand_a5, 0xa5}, {StateCommand_a6, 0xa6}, {StateCommand_a7, 0xa7}, {StateCommand_a8, 0xa8},
    {StateCommand_a9, 0xa9}, {StateCommand_aa, 0xaa}, {StateCommand_ab, 0xab}, {StateCommand_ac, 0xac}, {StateCommand_ad, 0xad},
    {StateCommand_ae, 0xae}, {StateCommand_af, 0xaf}, {StateCommand_b0, 0xb0}, {StateCommand_b1, 0xb1}, {StateCommand_c9, 0xc9},
    {StateCommand_ca, 0xca}, {StateCommand_cb, 0xcb}, {StateCommand_cc, 0xcc}, {StateCommand_cd, 0xcd}, {StateCommand_ce, 0xce},
    {StateCommand_cf, 0xcf}, {StateCommand_d0, 0xd0}, {StateCommand_d1, 0xd1}, {StateCommand_d2, 0xd2}, {StateCommand_d3, 0xd3},
    {StateCommand_d4, 0xd4}, {StateCommand_d5, 0xd5}, {StateCommand_d6, 0xd6}, {StateCommand_d7, 0xd7}, {StateCommand_fb, 0xfb},
    {StateCommand_fc, 0xfc}, {StateCommand_fd, 0xfd}, {NULL, -1},
};

// The commands by their numbers
static ScriptCommand sCommands[0x12c];

void SetStateCommands(ScriptEngine* engine)
{
    memset(sCommands, 0, sizeof(sCommands));
    for (StateCommandEntry* entry = sCommandTable; entry != NULL; entry++)
    {
        ScriptCommand command = entry->command_;
        if (command == NULL)
            break;
        int id = entry->id_;
        if (id >= 0 && id < 0x12c)
        {
            if (sCommands[id] != NULL)
            {
                while (true)
                {
                }
            }
            sCommands[id] = command;
        }
    }
    func_ov017_021d4cc0(engine, sCommands, 0x12c);
}
