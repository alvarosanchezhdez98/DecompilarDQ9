#include "World/Overlay_10/PitEvent.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Resource/GameResources.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>

// What the zone allows, returned by func_02099950 and in CurrentZone
struct ZoneInfo
{
    char unk_0[0xc];
    unsigned char type_ : 4;
    char unk_d;
    unsigned char unk_e_0 : 2;
    unsigned char unk_e_2 : 4;
    unsigned char unk_e_6 : 1;
};

// The zone struct that func_02012fe4 returns
struct CurrentZone
{
    unsigned short zoneID_;
    char unk_2[6];
    ZoneInfo* info_;
};

// A zone and position saved for each of the 4 players, returned by func_020120a0
struct SavedPosition
{
    unsigned short zoneID_;
    Vector3fix16 position_;
};

// The argument of a message: the party member's name
struct TextArgument
{
    char unk_0[0xc];
};

struct PartySelection
{
    char unk_0[0xc];
    unsigned char memberIndex_;
};

// What func_02057fb4 creates a game object with. Its callers set every member with the same stores, in the same
// order, and a constructor with them isn't inlined, so they're written at each call
struct GameObjectParams
{
    unsigned char unk_0;
    char unk_1[0xf];
    unsigned char unk_10;
    unsigned char unk_11_0 : 1;
    unsigned char unk_11_1 : 1;
    unsigned char unk_11_2 : 1;
    unsigned char unk_11_3 : 1;
    unsigned char unk_11_4 : 1;
    unsigned char unk_11_5 : 1;
    unsigned char unk_11_6 : 1;
    unsigned char unk_11_7 : 1;
    short unk_12;
    short unk_14[4];
    short unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    Vector3fix position_;
    Vector3fix rotation_;
    Vector3fix scale_;
};

struct Unknown_02079e2c
{
    char unk_0[8];
    unsigned int unk_8 : 8;
};

extern "C"
{
    // The game's heap
    extern AllocatorUnion data_02114e20;
    // The sound player
    extern char data_02108760[];

    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);
    void func_02012da4(AllocatorUnion* allocator, void* data);
    int func_020100a8(GameState* gameState);
    unsigned char func_020100b0(GameState* gameState);
    void* func_02011584(GameState* gameState);
    SavedPosition* func_020120a0(GameState* gameState, int player);
    CurrentZone* func_02012fe4();
    void* func_0202ae18();
    bool func_0202c508(void*);
    void* func_02033fa0(GameObject* object);
    void func_020340b4(GameObject* object);
    void func_020397c0(GameObject* object);
    void func_020397cc(GameObject* object, int);
    MessageSystem* func_020421a0();
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    int func_020457e0(MessageSystem* messages);
    void func_02046380(MessageSystem* messages);
    void func_02048350(GameObject* object, int);
    int func_0204bd7c(void*);
    // The models of the game objects
    void* func_02057924();
    void func_02057de0(void* models, int slot, SafeAllocator* allocator, void* file, unsigned int size);
    void func_02057f00(void* models, int slot);
    // Creates a game object with a model and returns its index
    int func_02057fb4(void* models, int slot, GameObjectParams* params);
    // Plays a sound effect
    void func_0205eaa0(void* sound, int id, int);
    void func_0205ebc0(void* sound, int, int);
    void func_0205ebec(void* sound);
    void func_0205ebfc(void* sound, int, int);
    void func_020727d8(TextList* texts);
    void func_020728ac(TextList* texts, SafeAllocator* allocator, void* file, unsigned int size, int, int, int);
    // Returns the text with an ID
    const char* func_02072a68(TextList* texts, short id);
    void* func_020797dc();
    Unknown_02079e2c* func_02079e2c(void*, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    ZoneInfo* func_02099950(void* table, int id);
    // Writes the name of a party member
    void func_020e4bf4(TextArgument* argument, int member);
    void func_ov017_021d360c(int, unsigned char player, unsigned short zoneID, Vector3fix16 position);
}

#define PIT_EFFECT_SLOT 0x11

void PitEvent::Initialize()
{
    state_ = State_LoadTexts;
    ticks_ = 0;
    taskID_ = -1;
    func_020727d8(&texts_);
    allocator_.ResetAllocatorPointer();
    createEffect_ = false;
}

void PitEvent::Finish()
{
    func_02057f00(func_02057924(), PIT_EFFECT_SLOT);
    SignedAllocatorHeader* buffer = allocator_.GetSignedAllocator();
    if (buffer != NULL)
    {
        allocator_.Destroy();
        func_02012da4(&data_02114e20, buffer);
    }
    if (taskID_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(taskID_);
        taskID_ = -1;
    }
    GameObject* object = GameState::GetInstance()->GetUnknownGameObject();
    if (object != NULL)
    {
        func_020397c0(object);
    }
    Initialize();
}

bool PitEvent::Update()
{
    BackgroundLoader* loader;
    MessageSystem* messages;
    GameState* gameState;
    GameObject* member;
    GameObject* leader;
    void* unknown;
    GameResources* resources;
    CurrentZone* zone;
    PartySelection* selection;
    loader = BackgroundLoader::GetInstance();
    messages = func_020421a0();
    gameState = GameState::GetInstance();
    selection = (PartySelection*)func_ov017_0218b5b0()->unknown_ptr_array_3afc[0x2b];
    member = gameState->GetPartyMemberByIndex(selection->memberIndex_);
    leader = gameState->GetPartyMemberByIndex(func_020100b0(gameState));
    unknown = func_0202ae18();
    resources = func_ov017_0218b5b0();
    zone = func_02012fe4();
    if (member == NULL || leader == NULL)
    {
        Finish();
        return true;
    }

    if (state_ == State_LoadTexts)
    {
        func_020397cc(leader, 1);
        void* buffer = func_02012d88(&data_02114e20, 0x7800);
        if (buffer == NULL)
        {
            Finish();
            return true;
        }
        allocator_.CreateTypeA(buffer, 0x7800);
        taskID_ = loader->QueueLoadFileInGP2("data/bin/str_pit.gp2", "str_pit_<LG>.bin", NULL);
        state_ = State_ShowMessage;
    }
    else if (state_ == State_ShowMessage)
    {
        if (loader->GetTaskStatus(taskID_) == 0)
        {
            return false;
        }
        if (loader->GetDetailedTaskStatus(taskID_) != BackgroundLoader::TaskStatus_Complete)
        {
            Finish();
            return true;
        }
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(taskID_, &file, &size);
        func_020727d8(&texts_);
        func_020728ac(&texts_, &allocator_, file, size, 0, 0, 0);
        loader->RemoveTask(taskID_);
        SavedPosition* saved = func_020120a0(gameState, func_020100a8(gameState));
        if (saved == NULL)
        {
            Finish();
            return true;
        }
        ZoneInfo* info = zone->info_;
        if (info == NULL)
        {
            Finish();
            return true;
        }
        createEffect_ = true;
        if (info->type_ == 0)
        {
            void* unknown2 = func_02033fa0(member);
            if (unknown2 != NULL)
            {
                void* table = func_02011584(gameState);
                ZoneInfo* info2 = func_02099950(table, func_0204bd7c(unknown2));
                if (info2 != NULL && info2->unk_e_2 != 0)
                {
                    createEffect_ = false;
                }
            }
        }
        else if (zone->info_ != NULL)
        {
            createEffect_ = zone->info_->unk_e_6;
        }
        int message;
        if (!createEffect_)
        {
            state_ = State_WaitForEnd;
            message = 2;
        }
        else if (saved->zoneID_ != 0)
        {
            state_ = State_WaitForAnswer;
            message = 1;
        }
        else
        {
            message = 0;
            state_ = State_LoadEffect;
            func_0205eaa0(data_02108760, 100, 0);
        }
        const char* text = func_02072a68(&texts_, message);
        TextArgument argument;
        func_020e4bf4(&argument, selection->memberIndex_);
        func_02046380(messages);
        messages->arguments_ = &argument;
        func_0204500c(messages, text, 0, 0xe3);
        messages->busy_ = 1;
    }
    else if (state_ == State_WaitForAnswer)
    {
        if (messages->busy_ != 0)
        {
            return false;
        }
        if (func_020457e0(messages) == 0)
        {
            const char* text = func_02072a68(&texts_, 0);
            TextArgument argument;
            func_020e4bf4(&argument, selection->memberIndex_);
            func_02046380(messages);
            messages->arguments_ = &argument;
            func_0204500c(messages, text, 0, 0xe3);
            messages->busy_ = 1;
            func_0205eaa0(data_02108760, 100, 0);
            SavedPosition* saved = func_020120a0(gameState, func_020100a8(gameState));
            if (saved != NULL)
            {
                saved->zoneID_ = 0;
            }
            state_ = State_LoadEffect;
        }
        else
        {
            Finish();
            return true;
        }
    }
    else if (state_ == State_LoadEffect)
    {
        taskID_ = loader->QueueLoadFile("data/effect/ana.chr", NULL);
        state_ = State_CreateEffect;
        ticks_ = 0;
    }
    else if (state_ == State_CreateEffect)
    {
        if (loader->GetTaskStatus(taskID_) == 0)
        {
            return false;
        }
        if (loader->GetDetailedTaskStatus(taskID_) != BackgroundLoader::TaskStatus_Complete)
        {
            Finish();
            return true;
        }
        if (ticks_ < 15)
        {
            ticks_++;
            return false;
        }
        func_0205ebc0(data_02108760, 0x74, 0x74);
        func_0205ebfc(data_02108760, 0, 0);
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(taskID_, &file, &size);
        Vector3fix position = member->obj3D_.position_;
        char* unknown3 = resources->unknown_2cc;
        func_0207df50(unknown3 + 0xc40);
        func_0207df90(unknown3 + 0xc40);
        void* models = func_02057924();
        func_02057de0(models, PIT_EFFECT_SLOT, &allocator_, file, size);
        func_0207dfac(unknown3 + 0xc40);
        Vector3fix scale;
        scale.x = 0x10a;
        scale.y = 0x10a;
        scale.z = 0x10a;
        GameObjectParams params;
        params.unk_0 = 0;
        params.unk_10 = 1;
        params.unk_12 = 0;
        params.unk_14[0] = -1;
        params.unk_14[1] = -1;
        params.unk_14[2] = -1;
        params.unk_14[3] = -1;
        params.unk_1c = -0x1000;
        params.unk_20 = 0;
        params.unk_24 = 0;
        params.unk_28 = 0;
        params.position_.x = 0;
        params.position_.y = 0;
        params.position_.z = 0;
        params.rotation_.x = 0;
        params.rotation_.y = 0;
        params.rotation_.z = 0;
        params.scale_.x = 0x1000;
        params.scale_.y = 0x1000;
        params.scale_.z = 0x1000;
        params.unk_11_0 = 0;
        params.unk_11_1 = 0;
        params.unk_11_2 = 1;
        params.unk_11_3 = 0;
        params.unk_11_4 = 0;
        params.unk_11_5 = 0;
        params.unk_11_6 = 0;
        params.unk_11_7 = 0;
        params.position_ = position;
        params.scale_ = scale;
        effectIndex_ = func_02057fb4(models, PIT_EFFECT_SLOT, &params);
        Vector3fix16 tile;
        tile.x = position.x >> 4;
        tile.y = position.y >> 4;
        tile.z = position.z >> 4;
        if (func_0202c508(unknown))
        {
            SavedPosition* saved = func_020120a0(gameState, func_020100a8(gameState));
            if (saved != NULL)
            {
                saved->zoneID_ = zone->zoneID_;
                saved->position_.x = tile.x;
                saved->position_.y = tile.y;
                saved->position_.z = tile.z;
            }
        }
        Unknown_02079e2c* unknown4 = func_02079e2c(func_020797dc(), 0xd2);
        if (unknown4 != NULL)
        {
            func_02048350(member, unknown4->unk_8);
        }
        GameObject* object = gameState->GetUnknownGameObject();
        if (object != NULL)
        {
            func_020340b4(object);
        }
        func_ov017_021d360c(0, func_020100a8(gameState), zone->zoneID_, tile);
        state_ = State_WaitForEnd;
    }
    else if (state_ == State_WaitForEnd)
    {
        GameState* gameState2 = GameState::GetInstance();
        bool done = false;
        if (createEffect_)
        {
            if (gameState2->GetGameObjectByIndex(effectIndex_) == NULL && messages->busy_ == 0)
            {
                done = true;
            }
        }
        else if (messages->busy_ == 0)
        {
            done = true;
        }
        if (done)
        {
            Finish();
            func_0205ebec(data_02108760);
            return true;
        }
    }
    return false;
}
