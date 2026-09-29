// The files that the game downloads (overlay 31): "info", "mes", "sell", "auction" and "quest" files, each checked
// with a checksum and encrypted with RC4. The "mes", "auction" and "quest" ones are scripts, whose commands set the
// downloaded data of GameState
#include "GameState/GameState.h"
#include "Memory/SafeAllocator.h"
#include "Resource/PartNameTable.h"
#include "Resource/Script.h"
#include "Util/Random.h"
#include <std_library_functions.h>

// A downloaded file (0xb0 bytes)
struct DownloadEntry
{
    char unk_0[0x88];
    char name_[0x24];
    int size_;
};

// The state of the downloaded files' commands
struct DownloadState
{
    // The entries that the "auction" file chooses
    unsigned char count_;
    // The "k" command ran
    unsigned char checked_;
    // The "auction" file's second run, which sets the chosen entries
    unsigned char choosing_;
    // The "h" command's entry
    unsigned char index_;
    PartNameTable* items_;
    char* quest_;
    DownloadedData* data_;
    // The message of the game's language, which the "i" command sets
    const char* message_;
};

// What func_02012fe4 returns ("the zone struct"): only what the "m" command sets
struct ZoneData
{
    char unk_0[0x840];
    struct Unknown_840
    {
        char unk_0[0x1b48];
        unsigned int unk_1b48;
        unsigned int unk_1b4c;
        char unk_1b50[0x11];
        unsigned char unk_1b61;
    } unk_840;
};

// What ov031's RC4 functions use
struct RC4Context
{
    char unk_0[0x104];
};

extern "C"
{
    int func_0200fb08(GameState* gameState);
    void* func_02010828(GameState* gameState);
    ZoneData* func_02012fe4();
    char* func_0205ec34();
    void func_0206df6c(char* flags, char* values, int flag, int);
    void func_0206e2a0(char* flags, int flag);
    int func_0206e2dc(char* flags, int flag);
    const PartEntry* func_020dedd0(PartNameTable* items, short id);
    GameResources* func_ov017_0218b5b0();
    void func_ov031_022118a8(RC4Context* context, const char* key, int length);
    void func_ov031_02211938(RC4Context* context, const void* input, int size, void* output);
}

static int Command_64(Script::Parameter* params, int count);
static int Command_65(Script::Parameter* params, int count);
static int Command_66(Script::Parameter* params, int count);
static int Command_67(Script::Parameter* params, int count);
static int Command_68(Script::Parameter* params, int count);
static int Command_69(Script::Parameter* params, int count);
static int Command_6a(Script::Parameter* params, int count);
static int Command_6b(Script::Parameter* params, int count);
static int Command_6c(Script::Parameter* params, int count);
static int Command_6d(Script::Parameter* params, int count);
static int Command_6e(Script::Parameter* params, int count);

static DownloadState sState;

static Script::OpcodeLookupEntry sCommands[] = {
    {'d', Command_64}, {'e', Command_65}, {'f', Command_66}, {'g', Command_67}, {'h', Command_68}, {'i', Command_69},
    {'j', Command_6a}, {'k', Command_6b}, {'l', Command_6c}, {'m', Command_6d}, {'n', Command_6e}, {0, NULL},
};

void SetDownloadItems(PartNameTable* items)
{
    sState.items_ = items;
}

// The entries that the "auction" file chooses, by their order in the file
static unsigned char sChosen[6];

// The strings of the functions, which the compiler pools in this order. ReadQuest() is in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for it
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] = "info\0mes\0sell\0auction\0quest\0XENLONPROJECTKEY";
#define STRING(offset, text) (sStrings + (offset))
#endif

static int Command_64(Script::Parameter* params, int count)
{
    return 1;
}

static int Command_65(Script::Parameter* params, int count)
{
    return 1;
}

static int Command_66(Script::Parameter* params, int count)
{
    if (sState.choosing_)
        sState.data_->unk_0 = params[0].ToInt();
    return 1;
}

static int Command_67(Script::Parameter* params, int count)
{
    if (!sState.choosing_)
        return 1;
    sState.data_->start_.year_ = params[0].ToInt();
    sState.data_->start_.month_ = params[1].ToInt();
    sState.data_->start_.day_ = params[2].ToInt();
    return 1;
}

static int Command_68(Script::Parameter* params, int count)
{
    if (!sState.choosing_)
    {
        sState.index_++;
        return 1;
    }
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    int minimum = params[2].ToInt();
    int maximum = params[3].ToInt();
    for (int i = 0; i < sState.count_; i++)
    {
        if (sState.index_ == sChosen[i])
        {
            Random* random = GetBTRandom();
            sState.data_->entries_[i].id_ = id;
            sState.data_->entries_[i].unk_4_7 = value;
            sState.data_->entries_[i].value_ = NextRandomBetween(random, minimum, maximum);
        }
    }
    sState.index_++;
    return 1;
}

static int Command_69(Script::Parameter* params, int count)
{
    int language = params[0].ToInt();
    if (language == func_0200fb08(GameState::GetInstance()))
        sState.message_ = params[1].ToString();
    return 1;
}

static int Command_6a(Script::Parameter* params, int count)
{
    sState.data_->end_.year_ = params[0].ToInt();
    sState.data_->end_.month_ = params[1].ToInt();
    sState.data_->end_.day_ = params[2].ToInt();
    return 1;
}

static int Command_6b(Script::Parameter* params, int count)
{
    if (sState.checked_)
        return 1;
    int id = params[0].ToInt();
    if (id == sState.data_->itemId_)
    {
        if (sState.items_ == NULL)
        {
            sState.checked_ = 1;
            sState.data_->flags_ |= 2;
            return 0;
        }
        const PartEntry* item = func_020dedd0(sState.items_, id);
        if (item == NULL)
        {
            sState.checked_ = 1;
            sState.data_->flags_ |= 2;
            return 0;
        }
        func_02010828(GameState::GetInstance());
        float minimum = params[1].ToFloat();
        float maximum = params[2].ToFloat();
        Random* random = GetBTRandom();
        unsigned short itemPrice = item->price_;
        int price = itemPrice * NextRandomFloatBetween(random, minimum, maximum);
        if (price >= sState.data_->price_ || (sState.data_->flags_ & 4))
            sState.data_->flags_ |= 1;
        else
            sState.data_->flags_ |= 2;
        sState.checked_ = 1;
    }
    return 1;
}

static int Command_6c(Script::Parameter* params, int count)
{
    char* flags = func_0205ec34();
    for (int i = 0; i < count; i++)
    {
        int flag = params->ToInt();
        params++;
        if (!func_0206e2dc(flags, flag))
        {
            func_0206e2a0(flags, flag);
            sState.data_->flags_ |= 0x40;
            func_0206df6c(flags, flags + 0x8c, 0x797, 1);
        }
    }
    return 1;
}

static int Command_6d(Script::Parameter* params, int count)
{
    ZoneData::Unknown_840* zones = &func_02012fe4()->unk_840;
    for (int i = 0; i < count; i++)
    {
        int zone = params->ToInt();
        params++;
        if (!(zones->unk_1b48 & (1 << zone)))
        {
            zones->unk_1b48 |= 1 << zone;
            zones->unk_1b4c |= 1 << zone;
            zones->unk_1b61 = 1;
            sState.data_->flags_ |= 0x200;
        }
    }
    return 1;
}

static int Command_6e(Script::Parameter* params, int count)
{
    return 1;
}

static int ReadInfo(unsigned char* data, int size, void* buffer);
static int ReadMessage(unsigned char* data, int size, void* buffer);
static int ReadAuction(unsigned char* data, int size, void* buffer);
static int ReadQuest(unsigned char* data, int size, void* buffer);
static unsigned long long GetChecksum(int size, const unsigned char* data);

void ReadDownloadedFiles(unsigned char* data, DownloadEntry* entries, int count, SafeAllocator* allocator)
{
    DownloadEntry* entry;
    void* buffer = allocator->Allocate(0xc800);
    for (int i = 0; i < count; i++)
    {
        entry = &entries[i];
        int info = 0;
        if (strstr(entry->name_, STRING(0, "info")) != NULL)
        {
            info = 1;
            if (!ReadInfo(data, entry->size_, buffer))
                entry->name_[0] = 0;
        }
        else if (strstr(entry->name_, STRING(0x5, "mes")) != NULL)
            ReadMessage(data, entry->size_, buffer);
        else if (strstr(entry->name_, STRING(0x9, "sell")) != NULL)
        {
        }
        else if (strstr(entry->name_, STRING(0xe, "auction")) != NULL)
            ReadAuction(data, entry->size_, buffer);
        else if (strstr(entry->name_, STRING(0x16, "quest")) != NULL)
            ReadQuest(data, entry->size_, buffer);
        data += entry->size_;
        if (info)
            entry->size_ -= 4;
    }
    sState.items_ = NULL;
}

static int ReadInfo(unsigned char* data, int size, void* buffer)
{
    if (GetChecksum(size, data) != 0)
        return 0;
    RC4Context context;
    const char* key = STRING(0x1c, "XENLONPROJECTKEY");
    func_ov031_022118a8(&context, key, strlen(key));
    func_ov031_02211938(&context, data, size - 4, buffer);
    memcpy(data, buffer, size - 4);
    return 1;
}

static int ReadMessage(unsigned char* data, int size, void* buffer)
{
    Script script;
    if (GetChecksum(size, data) != 0)
        return 0;
    RC4Context context;
    const char* key = STRING(0x1c, "XENLONPROJECTKEY");
    func_ov031_022118a8(&context, key, strlen(key));
    func_ov031_02211938(&context, data, size - 4, buffer);
    GameState* gameState = GameState::GetInstance();
    sState.data_ = &gameState->downloadedData_;
    sState.message_ = NULL;
    script.Initialize();
    script.SetOpcodeLookup(sCommands);
    script.Load(buffer, size - 4);
    script.Execute();
    if (sState.message_ == NULL)
        return 0;
    memset(gameState->downloadedMessage_, 0, sizeof(gameState->downloadedMessage_));
    const char* message = sState.message_;
    memcpy(gameState->downloadedMessage_, message, strlen(message));
    return 1;
}

static int ReadAuction(unsigned char* data, int size, void* buffer)
{
    Script counter;
    Script script;
    if (GetChecksum(size, data) != 0)
        return 0;
    int i;
    RC4Context context;
    const char* key = STRING(0x1c, "XENLONPROJECTKEY");
    func_ov031_022118a8(&context, key, strlen(key));
    func_ov031_02211938(&context, data, size - 4, buffer);
    data = (unsigned char*)buffer;
    DownloadedData* downloaded = &GameState::GetInstance()->downloadedData_;
    sState.choosing_ = 0;
    sState.index_ = 0;
    sState.data_ = downloaded;
    counter.Initialize();
    counter.SetOpcodeLookup(sCommands);
    int length = size - 4;
    counter.Load(buffer, length);
    counter.Execute();
    if (sState.index_ == 0)
        return 0;
    for (i = 0; i < 6; i++)
    {
        downloaded->entries_[i].id_ = -1;
        sChosen[i] = 0xff;
    }
    sState.count_ = sState.index_;
    if (sState.count_ > 6)
        sState.count_ = 6;
    for (i = 0; i < sState.count_; i++)
    {
        short chosen = rand() % sState.index_;
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            if (chosen == sChosen[j])
                break;
        }
        if (j >= 0)
            i--;
        else
            sChosen[i] = chosen;
    }
    sState.choosing_ = 1;
    sState.index_ = 0;
    sState.data_ = downloaded;
    script.Initialize();
    script.SetOpcodeLookup(sCommands);
    script.Load(data, length);
    script.Execute();
    return 1;
}

// NONMATCHING: the C matches 96.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original computes quest_'s address before storing data_, and stores data_ first; ours stores in the order of the
// source
#ifdef NONMATCHING
static int ReadQuest(unsigned char* data, int size, void* buffer)
{
    Script script;
    if (GetChecksum(size, data) != 0)
        return 0;
    RC4Context context;
    const char* key = STRING(0x1c, "XENLONPROJECTKEY");
    func_ov031_022118a8(&context, key, strlen(key));
    func_ov031_02211938(&context, data, size - 4, buffer);
    GameState* gameState = GameState::GetInstance();
    DownloadedData* downloaded = &gameState->downloadedData_;
    sState.quest_ = gameState->unk_6380;
    sState.data_ = downloaded;
    downloaded->flags_ &= ~0x240;
    script.Initialize();
    script.SetOpcodeLookup(sCommands);
    script.Load(buffer, size - 4);
    script.Execute();
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN6Script10InitializeEv(); // Script::Initialize
    void _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE(); // Script::SetOpcodeLookup
    void _ZN6Script4LoadEPKvj(); // Script::Load
    void _ZN6Script7ExecuteEv(); // Script::Execute
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

static asm int ReadQuest(unsigned char* data, int size, void* buffer)
{
    stmdb sp!, {r4, r5, r6, r7, lr}
    sub sp, sp, #0x134
    sub sp, sp, #0x400
    mov r7, r0
    mov r5, r1
    mov r0, r5
    mov r1, r7
    mov r4, r2
    bl GetChecksum
    cmp r1, #0x0
    cmpeq r0, #0x0
    mov r0, #0x0
    bne @L021f6140
    ldr r6, =sStrings+0x1c
    mov r0, r6
    bl strlen
    mov r2, r0
    add r0, sp, #0x0
    mov r1, r6
    bl func_ov031_022118a8
    add r0, sp, #0x0
    mov r1, r7
    mov r3, r4
    sub r2, r5, #0x4
    bl func_ov031_02211938
    bl _ZN9GameState11GetInstanceEv
    add r1, r0, #0x26c
    add r3, r1, #0x5c00
    add r0, r0, #0x2380
    add r1, r0, #0x4000
    ldr r0, =sState
    add r2, r3, #0x100
    str r3, [r0, #0xc]
    str r1, [r0, #0x8]
    mov r0, #0x2000
    ldrh r1, [r2, #0xc]
    rsb r0, r0, #0x0
    and r3, r1, r0
    mov r1, r1, lsl #0x13
    mov r1, r1, lsr #0x13
    bic r1, r1, #0x240
    mov r1, r1, lsl #0x10
    mov r0, r0, lsr #0x13
    and r0, r0, r1, lsr #0x10
    orr r0, r3, r0
    strh r0, [r2, #0xc]
    add r0, sp, #0x104
    bl _ZN6Script10InitializeEv
    ldr r1, =sCommands
    add r0, sp, #0x104
    bl _ZN6Script15SetOpcodeLookupEPNS_17OpcodeLookupEntryE
    mov r1, r4
    sub r2, r5, #0x4
    add r0, sp, #0x104
    bl _ZN6Script4LoadEPKvj
    add r0, sp, #0x104
    bl _ZN6Script7ExecuteEv
    mov r0, #0x1
@L021f6140:
    add sp, sp, #0x134
    add sp, sp, #0x400
    ldmia sp!, {r4, r5, r6, r7, pc}
}
#endif

// Moves the date forward by 2 hours, up to the current hour
void AdvanceDownloadDate(DownloadDate* date)
{
    Unknown_22b4* clock = func_ov017_0218b5b0()->unknown_ptr_3b48;
    int nextDay = 0;
    if (clock->unknown_33 <= date->hour_)
    {
        date->hour_ = clock->unknown_33;
        date->unk_26 = 0;
        nextDay = 1;
    }
    else
    {
        int limit = clock->unknown_33 - 2;
        if (limit < 0)
            limit += 24;
        if (date->hour_ < limit)
        {
            date->unk_26 = 0;
            date->hour_ = clock->unknown_33;
        }
        else
        {
            date->hour_ += 2;
            if (date->hour_ >= 24)
            {
                date->hour_ -= 24;
                nextDay = 1;
            }
        }
    }
    if (nextDay)
    {
        date->day_++;
        unsigned int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((date->year_ & 3) == 0)
            days[1] = 29;
        if (*(days + date->month_ - 1) < date->day_ || date->day_ == 0)
        {
            date->day_ = 1;
            date->month_++;
            if (date->month_ > 12)
            {
                date->month_ = 1;
                date->year_++;
            }
        }
    }
}

static unsigned long long GetChecksum(int size, const unsigned char* data)
{
    unsigned long long checksum = 0;
    while (size-- > 0)
        checksum = ((checksum << 8) + *data++) % 0xc2a030d4ULL;
    return checksum;
}
