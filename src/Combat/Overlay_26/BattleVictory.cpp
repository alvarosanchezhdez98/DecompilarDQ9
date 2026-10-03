// Overlay 26: the victory of a battle, before the results of overlay 23 (BattleScene::End_Start()): the camera on the
// last action, the party walking to the formation's places of a stage (mp0200, its bones f1-f4 and b1-b4), the
// messages of the victory, the special scenes of some battles, and the members of a multiplayer battle who leave

#include "Scene/Overlay_23/BattleEnd.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Filesystem/GPC.h"
#include "GameState/GameState.h"
#include "GameState/Party.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "Text/MessageSystem.h"
#include "Util/Random.h"
#include "World/GameObjectParams.h"
#include <std_library_functions.h>

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // Vector3i::operator=, which the game calls
    void _ZN8Vector3iaSERKS_(Vector3i* to, const Vector3i* from);

    extern char data_02108760[];

    GameResources* func_0200fb8c(GameState* gameState);
    void func_0200fd38(GameState* gameState, int object, GameObject* model);
    void func_0200fd48(GameState* gameState, int object);
    GameObject* func_0200fea4(GameState* gameState, int object);
    GameObject* func_0200ff1c(GameState* gameState, unsigned int member);
    int func_0200ff58(GameState* gameState, int member);
    signed char func_02010088(GameObject* object);
    unsigned int func_020100a8(GameState* gameState);
    BattleCamera* func_020100bc(GameState* gameState);
    void func_020100c4(GameState* gameState, BattleCamera* camera);
    Party* func_02010828(GameState* gameState);
    int func_020114ec(GameState* gameState, signed char* members);
    void func_02012050(GameState* gameState);
    int func_02012060(GameState* gameState);
    void func_02012fe4();
    void* func_0202ae18();
    void* func_0202ae24();
    int func_0202b7d8(void* link);
    int func_0202c1c0(void* link, int member);
    int func_0202c508(void* link);
    int func_0202c540(void* link);
    void func_0202e694(BattleCamera* camera, const Vector3i* target);
    void func_0203232c(int* objects, int count);
    int func_02032370(int maximum);
    void func_02033874(GameObject* object, int angle);
    void func_02033b88(GameObject* object, int);
    void func_02033fdc(GameObject* object);
    void func_0203409c(GameObject* object);
    void func_02039894(GameObject* object);
    void func_02039d58(GameObject* object);
    void func_02039d84(GameObject* object);
    void func_0203b4a0(GameResources* resources, int);
    void func_0203b4b0(GameResources* resources, int);
    void func_0203b4d8(GameResources* resources, int);
    void func_0203b4e8(GameResources* resources, int);
    int func_0203b5e0(GameResources* resources, int);
    void func_0203c108(BattleMenuName* name, const char* text);
    void func_0203dafc(ObjectArchiveLoadInfo* info);
    void func_020407b4(Object3D* object, int, int, int);
    MessageSystem* func_020421a0();
    void func_02042b98(MessageSystem* messages, int, int, int, int);
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    void func_02046380(MessageSystem* messages);
    void func_02046574(MessageSystem* messages, int index, const void* name);
    void func_020465c0(MessageSystem* messages, int index, int value);
    void func_02046608(MessageSystem* messages, int, const char* input, char* output, int size, int, int);
    void func_020466e4(void* flags, int flag);
    void func_020466f4(void* flags, int flag);
    int func_02046708(void* flags, int flag);
    int func_0204671c();
    int func_02046b08(void*);
    void func_02049390(GameObject* object, int place);
    int func_020493a4(GameObject* object);
    Vector3i func_02049b54(GameObject* object);
    void func_02049bac(GameObject* object, Vector3i* rotation);
    void func_02049bd4(GameObject* object, Vector3i* position);
    void func_02049c88(GameObject* object, void*);
    void func_02049f50(GameObject* object, int, int);
    void func_0204a120(void* camera);
    void func_0204a3f0(void* camera, Object3D* model);
    GameObject* func_0204a438();
    void func_0204a440(void* camera, const char* bone);
    void func_0204a464(void* camera, const char* bone);
    void func_020531f0(GameObject* object);
    PartyMemberData* func_02053c6c(GameObject* object);
    void func_02053da0(GameObject* object, Vector3i* position);
    void* func_02053dc0(GameObject* object);
    void func_02053dd0(GameObject* object);
    void func_02053ec8(GameObject* object, int);
    int func_020546a8(int member);
    void* func_02057924();
    void func_02057e6c(void* models, int slot, SafeAllocator* allocator, void* file, unsigned int size,
        VRAMManagerState* vram);
    void func_02057f00(void* models, int slot);
    short func_02057fb4(void* models, int slot, void* params);
    int func_0205e488(void*);
    int func_0205e4f8(void*, int);
    void func_0205eaa0(void* sound, int id);
    void func_0205eb54(void* sound, int, int);
    void func_0205eb80(void* sound);
    void func_0205eb90(void* sound, int, int);
    void func_02072c9c(int member, char* name);
    void func_02078484(void* params);
    void* func_020797dc();
    void* func_02079e2c(void*, short id);
    void* func_0207d78c();
    void func_0207da94(void*, unsigned char member);
    int func_0207db58(void*, unsigned short, unsigned int);
    void func_0207df50(VRAMManagerState* state);
    void func_0207dfc8(VRAMManagerState* state, VRAMManagerState* copy);
    unsigned short func_02083554(PartyMemberData* data, unsigned short item);
    int func_02083960(PartyMemberData* data);
    int func_020839dc(PartyMemberData* data, unsigned char* skills, int count);
    void func_02083acc();
    int func_02083b00(PartyMemberData* data, int);
    void func_02083b28();
    int func_020882f8(ModifiableCombatStats* stats);
    void func_02088e64(ModifiableCombatStats* stats);
    void func_0208936c(ModifiableCombatStats* stats, unsigned short* unk130, BaseCombatStats* base);
    void func_0209a338(void* table);
    void func_0209a470(void* table, SafeAllocator* allocator, void* file, unsigned int size);
    void* func_0209a594(void* table, unsigned short id);
    void func_0209a804(void* table);
    void func_0209a8b4(void* table, SafeAllocator* allocator, void* file, unsigned int size);
    void* func_0209a9dc(void* table, unsigned char id);
    int func_0209ab7c(void* table, GameObject* object, unsigned char* spells);
    void func_020a0068(void*, int);
    void func_020a00a4(void*, int);
    void func_020a0780(void*, int);
    void func_020a07b0(void*, int);
    void func_020a35cc(BattleInfo* info, unsigned char member);
    int func_020a35e0(BattleInfo* info, unsigned char member);
    int func_020a35f8(BattleInfo* info);
    void func_020a367c(BattleInfo* info, unsigned char member);
    int func_020a36a8(BattleInfo* info);
    void func_020ac494(void* records);
    void func_020ac4c0(void* records);
    void* func_020d6c00();
    void func_020d6f44();
    void func_020d738c(void*);
    void func_020dd0b0(int id, char* text);
    PartEntry* func_020dedd0(void* names, short id);
    const char* func_020e0434(void* texts, int id);
    void* func_020e3580();
    void func_020e36f0(void*);
    void func_020e3798(void*);
    int func_020e37e8(void*);
    void* func_020e3808();
    void* func_020e385c(void*, int, int);
    void func_020e3994(void*, int, int);
    int func_020e3ad0(void*, int, int);
    void func_020e4864(const void* input, char* output, int, int, int, int);
    void func_020e4c74(MessageName* name, GameObject* object);
    void func_020e4ce8(MessageName* name, GameObject* object, int);

    void func_ov000_0215d588(BattleData* data);
    int func_ov000_0215e8e8(BattleData* data);
    int func_ov000_0215e9fc(BattleData* data, short* objects, int count, int);
    int func_ov000_0215eb1c(BattleData* data, short* objects, int count, int);
    int func_ov000_0215ec1c(BattleData* data, short* objects, int count, int);
    int func_ov000_0215f7a8(BattleData* data, short* members, int count);
    int func_ov000_0215fad4(BattleData* data);
    void func_ov000_0215fb04(BattleData* data, int member);
    int func_ov000_0215fc60(BattleData* data);
    int func_ov000_0215fc8c(BattleData* data, short action);
    void func_ov000_02160130();
    void func_ov000_02160d80(BattleScene* scene, int);
    void func_ov000_02160da0(BattleScene* scene);
    BattleMenu* func_ov000_02160f08();
    BattleCamera* func_ov000_02160f14(BattleScene* scene);
    void func_ov000_02160fa8(BattleScene* scene, int flag);
    void func_ov000_02160fbc(BattleScene* scene, int flag);
    int func_ov000_02160fd4(BattleScene* scene, int flag);
    void func_ov000_0216118c(BattleScene* scene, int);
    void func_ov000_0216258c(BattleScene* scene);
    void func_ov000_021626a0(BattleScene* scene, int, int);
    void func_ov000_021629ec(BattleScene* scene);
    void func_ov000_02162c14(BattleScene* scene, int member, BattleMemberState* state);
    void func_ov000_02162c90(BattleScene* scene, int member, int);
    void func_ov000_02162cbc(BattleScene* scene);
    void* func_ov000_02163524(BattleScene* scene);
    void func_ov000_021636ac(BattleScene* scene);
    void func_ov000_02163710(BattleScene* scene, int);
    void func_ov000_0216377c(BattleScene* scene, int);
    void func_ov000_021637c8(BattleScene* scene);
    void func_ov000_021637fc(BattleScene* scene, int member);
    void func_ov000_02163894(BattleScene* scene);
    void func_ov000_02163928(BattleScene* scene);
    void func_ov000_02163a7c(BattleScene* scene);
    void func_ov000_021675a0(BattleScene* scene);
    void func_ov000_021676a8(BattleScene* scene);
    void func_ov000_02167e6c(BattleScene* scene);
    void func_ov000_02167fb0(BattleScene* scene, GameObject* object);
    void func_ov000_02168144(BattleScene* scene);
    void func_ov000_02168644(BattleScene* scene, int member);
    int func_ov000_02168720(BattleScene* scene);
    void func_ov000_0216d370(BattleCamera* camera, int, int, int);
    void* func_ov000_0216f208(BattleCamera* camera);
    void func_ov000_0216f74c(Vector3i* position, int* place);
    void func_ov000_02171614(BattleMenuMember* member);
    void func_ov000_0217193c();
    void func_ov000_02171640(BattleMenuMember* member, int index);
    void func_ov000_02171968(BattleMenuMember* member, int index);
    void func_ov000_02171b3c(BattleMenuMember* member);
    void func_ov000_02171b68(BattleMenuMember* member, int index, PartEntry* entry);
    void func_ov000_021744f4(BattleMenu* menu, int count);
    void func_ov000_02174514(BattleMenu* menu);
    void func_ov000_0217457c(BattleMenu* menu, int);
    void func_ov000_02174614(BattleMenu* menu, int);
    void func_ov000_02174738(BattleMenu* menu, int member);
    void func_ov000_02174a50(BattleMenu* menu, int member);
    void func_ov000_02174b14(BattleMenu* menu);
    void func_ov000_02174c14(BattleMenu* menu);
    void func_ov000_02174dc0(BattleMenu* menu);
    void func_ov000_02175258(BattleMenu* menu);
    int func_ov000_021759f4(BattleMenu* menu);
    void func_ov000_02175808(BattleMenu* menu);
    void func_ov000_02175be4(BattleMenu* menu);
    void func_ov000_02176038(BattleMenu* menu);
    void func_ov000_02176054(BattleMenu* menu);
    void func_ov000_0217a8f4(BattleMenu* menu);
    void func_ov000_0217f518();
    void func_ov000_0217f5d0();
    void func_ov000_0217fa60(BattleMenu* menu);
    int func_ov000_0217fb98(BattleMenu* menu);
    void func_ov000_0217fbf4(BattleMenu* menu, int);
    void func_ov000_0217fcc4(BattleMenu* menu, int);
    void func_ov000_0218048c(BattleMenu* menu);
    void func_ov000_02180b3c(BattleMenu* menu);
    void func_ov000_02181364(BattleMenu* menu);
    void func_ov000_021813d4(BattleMenu* menu);
    void func_ov000_021814bc(BattleMenu* menu);
    void func_ov000_02181608(BattleMenu* menu);
    void func_ov000_02181694(BattleMenu* menu, int);
    void func_ov000_021816e8(BattleMenu* menu, int);
    void func_ov000_0218173c(BattleMenu* menu);

    void func_ov017_021917f0(int member, int);
    void func_ov017_02191b40(GameResources* resources, int member);
    int func_ov017_02195658(GameResources* resources);
    void func_ov017_0219c774(unsigned short, int, int);
    void func_ov017_021a23b0(GameResources* resources, unsigned short);
    void func_ov017_021b8468(void*);
    void* func_ov017_021b8478(void*);
    void func_ov017_021c6814(unsigned short link, unsigned short member, BattleMemberState* state, unsigned char, int, int);
    void func_ov017_021c847c();
    void func_ov017_021c8654();
    void func_ov017_021c8758(unsigned short);
    void func_ov017_021c894c(unsigned short);
    void func_ov017_021c9ad4(unsigned short);
    void func_ov017_021c9b90(unsigned short, int member);
    void func_ov017_021ca174(unsigned short);
    void func_ov017_021cbc48(void*);
    void func_ov017_021cc050(unsigned short);
    void func_ov017_021cdf80(BattleData* data, int);
    void func_ov017_021cefe0(unsigned short, int, int);
    void func_ov017_021cf650(unsigned short, int, int);
}

// The camera of the victory for an action (0x1c bytes): where it looks at and from
struct VictoryCamera
{
    int action_;
    Vector3i target_;
    Vector3i position_;
};

// The bones of mp0200 where the party members stand: the front row's and the back row's
static char sF4[] = "f4";
static char sF3[] = "f3";
static char sF1[] = "f1";
static char sF2[] = "f2";
static char sB4[] = "b4";
static char sB1[] = "b1";
static char sB2[] = "b2";
static char sB3[] = "b3";
// The task that loads skilltable.bin and spelltable.bin
static int sTask = -1;
static char* sBones[8] = {sF1, sF2, sF3, sF4, sB1, sB2, sB3, sB4};
// The cameras of the victory for the actions that end battles (0: any other action; three for 0x115), until -1
static VictoryCamera sCameras[] = {
    {0x101, {0x0, 0x10f5, 0x2451}, {0x0, 0x1147, 0x0}},
    {0x102, {-0x451, 0x15c2, 0x25c2}, {-0x451, 0x15eb, 0x0}},
    {0x120, {-0x451, 0x15c2, 0x25c2}, {-0x451, 0x15eb, 0x0}},
    {0x103, {0x0, 0x130a, 0x1a14}, {0x0, 0x130a, 0x0}},
    {0x104, {0x0, 0x1ccc, 0x26b8}, {0x0, 0x1b85, 0x0}},
    {0x105, {0x214, 0x1451, 0x2e66}, {0x214, 0x16b8, 0x0}},
    {0x125, {0x214, 0x1451, 0x2e66}, {0x214, 0x16b8, 0x0}},
    {0x116, {0x214, 0x1451, 0x2e66}, {0x214, 0x16b8, 0x0}},
    {0x106, {0x0, 0x2b5c, 0x9428}, {0x0, 0x3451, 0x0}},
    {0xd5, {0x0, 0x2b5c, 0x9428}, {0x0, 0x3451, 0x0}},
    {0xff, {0x0, 0x2b5c, 0x9428}, {0x0, 0x3451, 0x0}},
    {0x107, {0x0, 0x1400, 0x28f5}, {0x0, 0x15eb, 0x0}},
    {0x109, {0x0, 0xdeb, 0x2ccc}, {0x0, 0x1451, 0x0}},
    {0x108, {0x0, 0x151e, 0x2970}, {0x0, 0x1400, 0x0}},
    {0x10a, {0x0, 0xf0a, 0x2428}, {0x0, 0x123d, 0x0}},
    {0x119, {0x0, 0xf0a, 0x2428}, {0x0, 0x123d, 0x0}},
    {0x10b, {0x0, 0x1385, 0x2051}, {0x0, 0x13d7, 0x0}},
    {0x11f, {0x0, 0x1385, 0x2051}, {0x0, 0x13d7, 0x0}},
    {0x10c, {0x0, 0x14a3, 0x2999}, {0x0, 0x16e1, 0x0}},
    {0x10d, {0x0, 0x13ae, 0x56e1}, {0x0, 0x18f5, 0x0}},
    {0x10e, {-0x3ae, 0x1800, 0x3214}, {-0x3ae, 0x16b8, 0x0}},
    {0x122, {-0x3ae, 0x1800, 0x3214}, {-0x3ae, 0x16b8, 0x0}},
    {0x110, {0x0, 0x14f5, 0x1d1e}, {0x0, 0x14f5, 0x0}},
    {0x124, {0x0, 0x14f5, 0x1d1e}, {0x0, 0x14f5, 0x0}},
    {0x111, {0x0, 0x107a, 0x1f0a}, {0x0, 0x11eb, 0x0}},
    {0x118, {0x0, 0x107a, 0x1f0a}, {0x0, 0x11eb, 0x0}},
    {0x112, {-0x51e, 0x1f85, 0x311e}, {-0x51e, 0x1ee1, 0x0}},
    {0x114, {0x0, 0x1028, 0x1570}, {0x0, 0x1170, 0x0}},
    {0x0, {0x0, 0x1028, 0x1570}, {0x0, 0x1170, 0x0}},
    {0x113, {-0x8cc, 0x1028, 0x5d1e}, {-0x8cc, 0x270a, 0x0}},
    {0x126, {-0x8cc, 0x1028, 0x5d1e}, {-0x8cc, 0x270a, 0x0}},
    {0x127, {0x0, 0x1a66, 0x3fae}, {0x0, 0x1dc2, 0x0}},
    {0x128, {0x0, 0x1800, 0x391e}, {0x0, 0x1ee1, 0x0}},
    {0x129, {0x0, 0x17ae, 0x38f5}, {0x0, 0x1800, 0x0}},
    {0x12a, {0x0, 0x1147, 0x3ee1}, {0x0, 0x1947, 0x0}},
    {0x12b, {0x0, 0x9eb, 0x3ab8}, {0x0, 0x163d, 0x0}},
    {0x12c, {0x0, 0x16b8, 0x40cc}, {0x0, 0x1d47, 0x0}},
    {0x12d, {0x0, 0x70a, 0x3bae}, {0x0, 0x151e, 0x0}},
    {0x12e, {0x0, 0x1385, 0x2451}, {0x0, 0x135c, 0x0}},
    {0x12f, {0x0, 0xdeb, 0x35c2}, {0x0, 0x1547, 0x0}},
    {0x131, {0x0, 0x22b8, 0x4a66}, {0x0, 0x24f5, 0x0}},
    {0x132, {0x0, 0x17ae, 0x41eb}, {0x0, 0x1c51, 0x0}},
    {0x133, {0x0, 0x1970, 0x5785}, {0x0, 0x2828, 0x0}},
    {0x130, {0x0, 0x1828, 0x2570}, {0x0, 0x187a, 0x0}},
    {0x115, {0x0, 0xe14, 0x2b33}, {0x0, 0x17ae, 0x0}},
    {0x115, {0x175c, 0x23d7, -0x68f}, {-0x7a, 0x2deb, -0x2666}},
    {0x115, {-0x75c, 0x26b8, 0xe66}, {0x170, 0x2ab8, -0x2947}},
    {-1, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}},
};

static void SetCameraVector(Vector3i* vector, int x, int y, int z);
static int PlaceMembers(SafeAllocator* allocator, BattleScene* scene, BattleData* data, BattleInfo* info);
static void LoadVictoryStage(SafeAllocator* allocator, BattleScene* scene, BattleData* data, BattleInfo* info,
    const char* animation);
static void RestoreMembers(int member, BattleScene* scene, BattleData* data, BattleInfo* info, BattleMenu* menu,
    unsigned short* unk_ec8, char (*unk_5c3c)[0x70], Vector3i* unk_5728, char* skills, char* spells,
    BattleMemberPosition* positions, BattleCamera* camera);

static inline int IsPartyMember(int member)
{
    return member >= 0 && member <= 3;
}

// *Likely* whether the wireless link is idle (main and overlay 31 call it too)
int IsLinkIdle()
{
    void* link = func_0202ae24();
    if (func_0205e488(link))
        return 1;
    if (!func_0205e4f8(link, 0x63))
        return 1;
    return 0;
}

// Writes a text of the battle in the messages' buffer
static char* GetBattleText(int id)
{
    char* text = (char*)func_020421a0()->unk_5c;
    memset(text, 0, 0x960);
    func_020dd0b0(id, text);
    return text;
}

// Sets the camera of the victory for the last action
void BattleScene::SetVictoryCamera(int turn, int multiplayer)
{
    if (data_ == 0)
        return;
    cameraAction_ = -1;
    VictoryCamera* camera = sCameras;
    while (camera->action_ != -1)
    {
        if (camera->action_ == 0)
        {
            if (multiplayer == 2)
            {
                cameraAction_ = camera->action_;
                SetCameraVector(&cameraTarget_, camera->target_.x, camera->target_.y, camera->target_.z);
                _ZN8Vector3iaSERKS_(&cameraPosition_, &camera->position_);
                return;
            }
        }
        else if (func_ov000_0215fc8c(data_, camera->action_))
        {
            cameraAction_ = camera->action_;
            if (camera->action_ == 0x115)
                camera += turn % 3;
            SetCameraVector(&cameraTarget_, camera->target_.x, camera->target_.y, camera->target_.z);
            _ZN8Vector3iaSERKS_(&cameraPosition_, &camera->position_);
            return;
        }
        camera++;
    }
}

static void SetCameraVector(Vector3i* vector, int x, int y, int z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

// Victory_Update() is here (0x021d8ba0)

BattleMenuMember* BattleMenu::FindMember(int member)
{
    if (IsPartyMember(member))
    {
        for (int i = 0; i < 4; i++)
        {
            if (member == members_[i].member_)
                return &members_[i];
        }
    }
    return 0;
}

// Turns the monsters to the camera, and starts their animations at different times if animate
static void TurnMonsters(BattleData* data, BattleCamera* camera, int animate)
{
    GameState* gameState = GameState::GetInstance();
    func_0200fb8c(gameState);
    short objects[8];
    int count = func_ov000_0215eb1c(data, objects, 8, 0);
    int turned = 0;
    Vector3i center = camera->center_;
    int z = center.z;
    int turnedObjects[8];
    for (int i = 0; i < count; i++)
    {
        GameObject* monster = func_0200fea4(gameState, objects[i]);
        if (monster != 0)
        {
            Vector3i target;
            __clear(&target, sizeof(target));
            target.z = z;
            Vector3i from = func_02049b54(monster);
            from.y = 0;
            Vector3i direction;
            Vector3fix_Subtract(&target, &from, &direction);
            direction.y = 0;
            Vector3fix_Normalize(&direction, &direction);
            int angle = fix32_Atan2(direction.x, direction.z);
            func_02033874(monster, angle);
            Vector3i rotation;
            __clear(&rotation, sizeof(rotation));
            rotation.y = angle;
            func_02049bac(monster, &rotation);
            turnedObjects[turned++] = objects[i];
        }
    }
    if (animate && data->unk_8e20 > 0)
    {
        func_0203232c(turnedObjects, turned);
        for (int j = 0; j < turned; j++)
        {
            GameObject* monster = func_0200fea4(gameState, turnedObjects[j]);
            if (monster != 0 && !monster->obj3D_.IsTransitioningAnimations() && !func_02010088(monster))
            {
                monster->obj3D_.SetNormalizedAnimationTime(0x1000 / turned * j);
                monster->obj3D_.AdvanceAnimations();
            }
        }
    }
}

// The message of the end of a battle that the party didn't win, then the end
void BattleScene::ShowEndMessage()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    if (endState_ == 0)
    {
        char text[0x100];
        sprintf(text, "\n");
        MessageName name;
        char unused[0x40] = {0};
        short objects[4];
        int count = func_ov000_0215e9fc(data_, objects, 4, 0);
        short members[4] = {-1};
        int found = 0;
        for (int i = 0; i < count; i++)
        {
            GameObject* member = gameState->GetCombatantByIndex(objects[i]);
            if (member != 0 && !func_02010088(member))
            {
                BattleMemberState state;
                func_ov000_02162c14(this, objects[i], &state);
                if (state.unk_1 == 6 && !(member->currentStats_->status_ & 0x80019))
                {
                    members[found] = objects[i];
                    found++;
                }
            }
        }
        func_020e4c74(&name,gameState->GetPartyMemberByIndex(members[0]));
        if (victoryResult_ == 2)
        {
            strcat(text, GetBattleText(1));
            int j;
            Party* party;
            GameState* gameState2 = GameState::GetInstance();
            party = func_02010828(gameState2);
            for (j = 0; j < party->count_; j++)
            {
                GameObject* member = func_0200ff1c(gameState2, party->members_[j]);
                if (member != 0)
                    func_02053ec8(member, 2);
            }
            GameResources* resources = func_ov017_0218b5b0();
            func_02012fe4();
            unsigned short link = info_->unk_8;
            func_ov017_021c9ad4(link);
            func_ov017_021a23b0(resources, link);
        }
        else if (victoryResult_ == 4)
        {
            strcat(text, GetBattleText(2));
        }
        else
        {
            strcat(text, GetBattleText(3));
        }
        messages->arguments_ = &name;
        func_0204500c(messages, text, 0, 0xe3);
        messages->unk_19b1 = 0;
        messages->unk_19b2 = 0;
        messages->unk_19be = 1;
        messages->unk_195b |= 2;
        messages->busy_ = 1;
        func_0205eaa0(data_02108760, 9);
        endState_++;
    }
    else if (messages->unk_9a0 == 0 && ++endState_ >= 0x1e)
    {
        func_02043204(messages);
        func_02043124(messages);
        if (victoryResult_ == 2)
        {
            func_ov000_02160d80(this, 4);
            return;
        }
        for (int k = 0; k < 4; k++)
        {
            BattleMenuMember* member = menu_.FindMember(k);
            if (member != 0 && member->unk_1c == 6)
                member->SetPanelUnk10(0x66);
        }
        func_ov000_02160da0(this);
    }
}

// The effect of the battles with data_->unk_8e49 2, after its messages
void BattleScene::UpdateSpecialEffect()
{
    if (data_->unk_8e49 != 2)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* models = func_02057924();
    if (unk_772e == 0)
    {
        if (func_020421a0()->unk_9a0 == 4)
            unk_772e = 1;
    }
    else if (unk_772e == 1)
    {
        if (func_020421a0()->unk_9a0 == 5)
            unk_772e = 2;
    }
    if (unk_7728 == 0)
    {
        unk_774c.Reset();
        func_0207df50(&unk_7760);
        unk_772a = loader->QueueLoadFile("data/effect/ev999991210.chr", &unk_774c);
        unk_7728 = 1;
    }
    else if (unk_7728 == 1)
    {
        if (loader->GetTaskStatus(unk_772a))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(unk_772a, &file, &size);
            func_02057e6c(models, 0x13, &unk_774c, file, size, &unk_7760);
            loader->RemoveTask(unk_772a);
            unk_7728 = 2;
        }
    }
    else if (unk_7728 == 2 && unk_772e == 2)
    {
        GameObjectParams params;
        func_02078484(&params);
        params.unk_11_1 = 1;
        params.unk_10 = 0;
        params.position_.z = -0x3000;
        params.scale_.x = 0x10a;
        params.scale_.y = 0x10a;
        params.scale_.z = 0x10a;
        unk_772c = func_02057fb4(models, 0x13, &params);
        unk_772e = -1;
        unk_7728 = -1;
    }
}

// A special scene of the victory, with eb0091.chr, ex3000.chr and s264.chr, before the party walks to the stage
void BattleScene::UpdateSpecialScene()
{
    GameResources* resources = func_ov017_0218b5b0();
    signed char step = unk_7712;
    if (step == 0)
    {
        if (!func_ov000_021759f4(&menu_))
            return;
        unk_774c.Reset();
        func_0207df50(&unk_7760);
        unk_7714 = unk_771e = unk_7720 = -1;
        SetBrightness(resources, -0x10, 0xf);
        unk_7714 = BackgroundLoader::GetInstance()->QueueLoadFile("data/effect/eb0091.chr", &unk_774c);
        unk_771e = BackgroundLoader::GetInstance()->QueueLoadFile("data/effect/ex3000.chr", &unk_774c);
        unk_7720 = BackgroundLoader::GetInstance()->QueueLoadFile("data/chara_sub/s264_<LG>.chr", &unk_774c);
        unk_7712 = 1;
        unk_7749 = 1;
    }
    else if (step == 1)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        if (loader->GetTaskStatus(unk_771e) && loader->GetTaskStatus(unk_7720) && loader->GetTaskStatus(unk_7714)
            && !IsBrightnessTransitionActive(resources))
        {
            short tasks[3] = {unk_7714, unk_771e, unk_7720};
            unsigned char slots[3] = {0x12, 0x1d, 0x1e};
            unsigned char* slot = slots;
            short* task = tasks;
            for (int i = 0; i < 3; i++)
            {
                void* file;
                unsigned int size;
                loader->GetLoadedFileByID(*task, &file, &size);
                func_02057e6c(func_02057924(), *slot++, &unk_774c, file, size, &unk_7760);
                loader->RemoveTask(*task++);
            }
            unk_7714 = unk_771e = unk_7720 = -1;
            func_ov000_021626a0(this, 0x26, 1);
            func_ov000_021626a0(this, 0x27, 0);
            func_ov000_02167e6c(this);
            unk_7712 = 2;
        }
    }
    else if (step == 2)
    {
        func_0205eb54(data_02108760, 0x1b3, 0x1b3);
        func_0205eb90(data_02108760, 1, 0);
        unk_7711 = 1;
        func_ov000_021626a0(this, 0x26, 0);
        func_ov000_021626a0(this, 0x27, 0);
        func_0203b4d8(resources, 0x100000);
        GameObjectParams params;
        func_02078484(&params);
        params.unk_11_0 = 1;
        params.unk_10 = 1;
        params.scale_.x = 0x800;
        params.scale_.y = 0x800;
        params.scale_.z = 0x800;
        params.position_.x = 0;
        params.position_.z = 0;
        params.position_.y = -0xa000;
        unk_7722 = func_02057fb4(func_02057924(), 0x1d, &params);
        unk_7724 = func_02057fb4(func_02057924(), 0x1e, &params);
        unk_7726 = 0;
        SetMainBrightness(resources, 0, 0xf);
        unk_7712 = 3;
    }
    else if (step == 3)
    {
        int ending = 0;
        GameObject* object = GameState::GetInstance()->GetGameObjectByIndex(unk_7722);
        if (object != 0)
        {
            Object3D* model = &object->obj3D_;
            int progress = model->normalizedAnimationTime_ - model->prevFrameNormalizedAnimationTime_;
            if (progress > 0)
            {
                int length = fix32_Divide(model->animationTime_ - model->prevFrameAnimationTime_, progress);
                if (FIX32_MULTIPLY(length, 0x1000 - model->normalizedAnimationTime_) <= 0x1e000)
                    ending = 1;
            }
        }
        if (object == 0 || ending)
        {
            unk_7726 = 0;
            SetMainBrightness(resources, -0x10, 0xf);
            unk_7712 = 4;
        }
    }
    else if (step == 4)
    {
        if (!IsBrightnessTransitionActive(resources))
        {
            SetMainBrightness(resources, -0x10, 0);
            func_02057f00(func_02057924(), 0x1d);
            func_02057f00(func_02057924(), 0x1e);
            unk_7722 = unk_7724 = -1;
            func_ov000_021626a0(this, 0x26, 1);
            func_0203b4e8(resources, 0x100000);
            unk_7712 = 5;
        }
    }
    else if (step == 5)
    {
        func_0205eb80(data_02108760);
        unk_7711 = 0;
        SetMainBrightness(resources, -0x10, 0);
        GameState* gameState = GameState::GetInstance();
        GameObjectParams params;
        func_02078484(&params);
        for (int j = 0; j < 4; j++)
        {
            GameObject* member = gameState->GetCombatantByIndex(j);
            if (member != 0)
                func_02049f50(member, 0x1f, 0);
            params.unk_14[0] = j;
            params.unk_10 = 0;
            unk_7716[j] = func_02057fb4(func_02057924(), 0x12, &params);
        }
        func_ov000_02175808(&menu_);
        menu_.flags_ |= 0x200;
        func_ov000_021637c8(this);
        LoadVictoryStage(&unk_774c, this, data_, info_, "1");
        func_ov000_02163894(this);
        func_ov000_021636ac(this);
        unk_7712 = 6;
        func_0205eb54(data_02108760, 0x1b3, 0x1b3);
        func_0205eb90(data_02108760, 2, 0);
        unk_7711 = 1;
    }
    else if (step == 6)
    {
        func_ov000_02163928(this);
        if (PlaceMembers(&allocator_, this, data_, info_))
        {
            func_ov000_02163710(this, 0);
            unk_7712 = -1;
        }
    }
    else if (step == -1)
    {
        func_ov000_02163928(this);
    }
}

// The end of the special scene: the field's camera again
void BattleScene::EndSpecialScene()
{
    GameState* gameState = GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_02057f00(func_02057924(), 0x12);
    func_02057f00(func_02057924(), 0x1d);
    func_02057f00(func_02057924(), 0x1e);
    for (int i = 0; i < 4; i++)
    {
        if (func_020a35e0(info_, i))
        {
            GameObject* member = func_0200ff1c(gameState, i);
            if (member != 0)
            {
                member->obj3D_.RemoveAnimationPackageByID(3);
                func_02033b88(member, 0);
            }
        }
    }
    BattleCamera* fieldCamera = func_020100bc(gameState);
    BattleCamera* camera = func_ov000_02160f14(this);
    Vector3i target = fieldCamera->unk_70;
    func_ov000_0216d370(camera, 1, 1, 1);
    _ZN8Vector3iaSERKS_(&camera->target_, &fieldCamera->target_);
    func_0202e694(camera, &target);
    _ZN8Vector3iaSERKS_(&camera->position_, &fieldCamera->position_);
    func_020100c4(gameState, func_ov000_02160f14(this));
    func_0200fd48(gameState, 0xcf);
    loader->RemoveTask(unk_7714);
    loader->RemoveTask(unk_771e);
    loader->RemoveTask(unk_7720);
    unk_7714 = unk_771e = unk_7720 = -1;
    unk_774c.Reset();
}

// A member who left a multiplayer battle (overlay 0 calls it too)
void BattleScene::RemoveMember(int member, unsigned char update)
{
    GameState* gameState = GameState::GetInstance();
    BattleInfo* info = info_;
    BattleMenu* menu = &menu_;
    BattleData* data = data_;
    void* unk = func_0207d78c();
    void* link = func_0202ae18();
    GameResources* resources = func_ov017_0218b5b0();
    int removed = 0;
    if (func_020a35e0(info, member))
    {
        removed = 1;
        unk_7748 = 1;
    }
    func_ov000_02174a50(menu, member);
    func_020a367c(info, member);
    func_0207da94(unk, member);
    func_ov017_02191b40(resources, member);
    if (member == info->leader_)
    {
        if (func_0202c508(link))
            func_ov000_0216377c(this, func_0207db58(unk, info->unk_8, func_020100a8(gameState)));
        else
            func_ov017_021c9b90(info->unk_8, member);
    }
    func_ov000_0215fb04(data, member);
    if (update && endState_ != 0x11 && removed && func_020a36a8(info))
    {
        ResetMembersState();
        func_ov017_021cc050(info->unk_8);
    }
}

// Shows the members again in a multiplayer battle (overlay 0 calls it)
void BattleScene::ShowMembers()
{
    void* unk = func_ov017_0218b5b0()->unknown_ptr_3704;
    if (IsLinkIdle() && func_02046b08(unk))
    {
        BattleInfo* info = info_;
        if (func_020a35e0(info, info->leader_))
            RestoreMembers(-1, this, data_, info_, &menu_, &unk_ec8, unk_5c3c, unk_5728, skillTable_, spellTable_,
                positions_, &camera_);
    }
}

// Overlay 0 calls it too
void BattleScene::ResetMembersState()
{
    int state = endState_;
    if (state == 0)
        endState_ = 0;
    else if (state != 0 && state != 1 && state != 2)
        endState_ = 3;
    func_ov000_0217fcc4(&menu_, -1);
    unk_772f = 0;
    memset(unk_54f4, 0, sizeof(unk_54f4));
    Party* party = func_02010828(GameState::GetInstance());
    for (int i = 0; i < party->count_; i++)
    {
        signed char member = party->members_[i];
        if (menu_.FindMember(member) != 0)
        {
            func_ov000_0217f518();
            BattleMemberState state;
            func_ov000_02162c14(this, member, &state);
            func_ov017_021c6814(info_->unk_8, member, &state, 0, -1, 0);
        }
    }
    int flag = func_ov000_02160fd4(this, 0x2000000);
    unk_55f4 = unk_7734;
    if (flag)
        func_ov000_02160fa8(this, 0x2000000);
    func_020466e4(func_020d6c00(), unk_7738);
    func_ov000_02176038(&menu_);
}
