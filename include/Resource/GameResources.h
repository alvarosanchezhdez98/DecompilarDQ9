#pragma once

#include "Memory/SafeAllocator.h"
#include "World/Object3D.h"

struct TreasureMapLanguageDataOffsets;

// Starts the initialization of the objects that GameResources points to, and constructs and destructs the ones of its
// arrays (see DECLARE_UNKNOWN_OBJECT)
extern "C" void func_0204693c(void* object);

// sizeof == 0x88, the objects of GameResources::unknown_array_2b90. Their constructor and destructor are in main, and
// func_0204719c initializes them
struct Unknown_0201c0e8
{
    char unknown_0[0x88];

    Unknown_0201c0e8();
    ~Unknown_0201c0e8();
};

// The objects of GameResources' other arrays: overlay 30 has their constructors and destructors, which call
// func_0204693c
#define DECLARE_UNKNOWN_OBJECT(name, size)          \
    struct name                                     \
    {                                               \
        char unknown_0[size];                       \
                                                    \
        name();                                     \
        ~name();                                    \
    };

DECLARE_UNKNOWN_OBJECT(Unknown_48, 0x48)
DECLARE_UNKNOWN_OBJECT(Unknown_18, 0x18)
DECLARE_UNKNOWN_OBJECT(Unknown_14, 0x14)
DECLARE_UNKNOWN_OBJECT(Unknown_28, 0x28)

// The parts of GameResourcesData that GameResources::Initialize() initializes itself, after func_0204693c. The first
// byte *likely* tells their type
struct Unknown_1720
{
    unsigned char type_;
    char unknown_1[7];
    int unknown_8;
    SafeAllocator allocator_c;
    int unknown_20;
    unsigned char unknown_24;
    char unknown_25[3];
};

struct Unknown_19a0
{
    unsigned char type_;
    char unknown_1[7];
    SafeAllocator allocator_8;
    unsigned char unknown_1c;
    unsigned char unknown_1d;
    unsigned char unknown_1e;
    unsigned char unknown_1f;
    signed char unknown_20;
    char unknown_21[3];
    int unknown_24;
};

struct Unknown_19c8
{
    unsigned char type_;
    char unknown_1[7];
    SafeAllocator allocator_8;
    int unknown_1c;
    int unknown_20;
    char unknown_24[0x7c];
    unsigned short unknown_a0;
    char unknown_a2[2];
    int unknown_a4;
    int unknown_a8;
    int unknown_ac;
    int unknown_b0;
    unsigned char unknown_b4;
    char unknown_b5[3];
};

struct Unknown_222c
{
    unsigned char type_;
    char unknown_1[0xb];
    int unknown_c;
    int unknown_10;
    char unknown_14[0x14];
    unsigned char unknown_28;
    char unknown_29[0x11];
    unsigned char unknown_3a;
    unsigned char unknown_3b;
};

struct Unknown_22b4
{
    char unknown_0[0x33];
    unsigned char unknown_33;
    char unknown_34[0x28];
};

struct Unknown_27e8
{
    unsigned char type_;
    char unknown_1[7];
    unsigned short unknown_8;
    unsigned char unknown_a;
    char unknown_b;
    short unknown_c;
    unsigned char unknown_e;
    unsigned char unknown_f;
};

// The block of 0x36c0 bytes that overlay 30 allocates with GameResources, which points to its parts
struct GameResourcesData
{
    char unknown_0[0x14];
    Model3D unknown_14;
    Object3D unknown_c0;
    char unknown_16c[0xc30];
    char unknown_d9c[0x20];
    char unknown_dbc[8];
    char unknown_dc4[8];
    char unknown_dcc[8];
    char unknown_dd4[0x24];
    char unknown_df8[0x2c];
    char unknown_e24[0x13c];
    char unknown_f60[0xc];
    char unknown_f6c[0x6cc];
    char unknown_1638[0x30];
    char unknown_1668[0x60];
    char unknown_16c8[0xc];
    char unknown_16d4[0x28];
    char unknown_16fc[0x24];
    Unknown_1720 unknown_1720;
    char unknown_1748[0x1c8];
    char unknown_1910[0x24];
    char unknown_1934[0x6c];
    Unknown_19a0 unknown_19a0;
    Unknown_19c8 unknown_19c8;
    char unknown_1a80[0x10];
    char unknown_1a90[0x68];
    char unknown_1af8[0x20];
    char unknown_1b18[0x28];
    char unknown_1b40[0x2c];
    char unknown_1b6c[0x24];
    char unknown_1b90[0x284];
    char unknown_1e14[0x40];
    char unknown_1e54[0x40];
    char unknown_1e94[0x14];
    char unknown_1ea8[0x28c];
    char unknown_2134[0x10];
    char unknown_2144[0x28];
    char unknown_216c[0xc0];
    Unknown_222c unknown_222c;
    char unknown_2268[0x4c];
    Unknown_22b4 unknown_22b4;
    char unknown_2310[0x50];
    char unknown_2360[0x20];
    char unknown_2380[0x24];
    char unknown_23a4[0xc];
    char unknown_23b0[0x104];
    char unknown_24b4[0x14];
    char unknown_24c8[0x10];
    char unknown_24d8[0x274];
    char unknown_274c[0x70];
    char unknown_27bc[0x2c];
    Unknown_27e8 unknown_27e8;
    char unknown_27f8[0x10];
    char unknown_2808[0x290];
    char unknown_2a98[0x14];
    char unknown_2aac[0x58];
    char unknown_2b04[0x14];
    char unknown_2b18[0x54];
    char unknown_2b6c[0x48];
    char unknown_2bb4[0x288];
    char unknown_2e3c[0x24];
    char unknown_2e60[0x50];
    char unknown_2eb0[0xc];
    char unknown_2ebc[0x2c];
    char unknown_2ee8[0x10];
    char unknown_2ef8[0x1c];
    char unknown_2f14[0xa0];
    char unknown_2fb4[0xc];
    char unknown_2fc0[0xc];
    char unknown_2fcc[0x14];
    char unknown_2fe0[0x6c];
    char unknown_304c[0x2c];
    char unknown_3078[2];
    char unknown_307a[2];
    char unknown_307c[0xbc];
    char unknown_3138[2];
    char unknown_313a[2];
    char unknown_313c[0x19c];
    char unknown_32d8[0x54];
    char unknown_332c[0x234];
    char unknown_3560[0x11];
    char unknown_3571[0x103];
    char unknown_3674[0x4c];
};

// sizeof == 0x44c8 (usa/eur). Referenced in a huge number of places, seems to be responsible for all kinds of resource
// management in game (memory allocation and pointers to persistent data).
//
// Overlay 30 creates it (CreateGameResources), with the parts of a GameResourcesData, and initializes it
// (GameResources::Initialize), which is where most of the type information comes from.
struct GameResources
{
    unsigned int brightnessFlags_0;
    unsigned int brightnessFlags_4;
    unsigned int brightnessFlags_8;

    float mainBrightness;
    int mainBrightnessTarget;
    int mainBrightnessTimeRemaining;

    float subBrightness;
    int subBrightnessTarget;
    int subBrightnessTimeRemaining;

    bool mainBrightnessLocked;
    bool subBrightnessLocked;
    bool mainBrightnessDirty;
    bool subBrightnessDirty;
    bool allowBrightnessApply;

    char unknown_29[3];
    int unknown_2c;
    int unknown_30;
    int unknown_34;
    // allocators_[17] is the lootable containers' (see LootableContainer.cpp)
    SafeAllocator allocators_[0x21];
    char unknown_2cc[0xe70];
    SafeAllocator allocator_113c;
    char unknown_1150[0x70];
    SafeAllocator allocator_11c0;
    char unknown_11d4[0x70];
    SafeAllocator allocator_1244;
    char unknown_1258[0x70];
    struct Substruct_12C8
    {
        char unknown_0[4];
        SafeAllocator allocator_array_4[10];
        char unknown_cc[0x460];
        SafeAllocator allocator_52c;
        SafeAllocator allocator_540;
        SafeAllocator allocator_554;
        char unknown_568[0x70];
        SafeAllocator allocator_5d8;
    } substruct_array_12c8[4];
    char unknown_2a78[0x90];
    int unknown_2b08;
    SafeAllocator allocator_2b0c;
    char unknown_2b20[0x70];
    Unknown_0201c0e8 unknown_array_2b90[0x12];
    Unknown_0201c0e8 unknown_3520;
    Unknown_0201c0e8 unknown_35a8;
    int unknown_3630;
    unsigned char unknown_3634[0x12];
    unsigned char unknown_3646[0x12];
    unsigned char unknown_3658[0x12];
    char unknown_366a[0x2];
    int unknown_366c[0x12];
    char unknown_36b4[0x14];
    Model3D* unknown_ptr_36c8;
    Object3D* unknown_ptr_36cc;
    void* unknown_ptr_36d0;
    int unknown_36d4;
    void* unknown_ptr_36d8;
    unsigned char unknown_36dc[5];
    unsigned char unknown_36e1[9];
    char unknown_36ea[0x2];
    int unknown_36ec;
    int unknown_36f0;
    int unknown_36f4;
    int unknown_36f8;
    void* unknown_ptr_36fc;
    void* unknown_ptr_3700;
    void* unknown_ptr_3704;
    void* unknown_ptr_3708;
    void* unknown_ptr_370c;
    void* unknown_ptr_3710;
    void* unknown_ptr_3714;
    void* unknown_ptr_3718;
    void* unknown_ptr_371c;
    void* unknown_ptr_3720;
    void* unknown_ptr_3724;
    void* unknown_ptr_3728;
    void* unknown_ptr_372c;
    Unknown_1720* unknown_ptr_3730;
    void* unknown_ptr_3734;
    void* unknown_ptr_3738;
    Unknown_48 unknown_array_373c[0xc];
    Unknown_18 unknown_array_3a9c[4];
    void* unknown_ptr_3afc;
    Unknown_19a0* unknown_ptr_3b00;
    Unknown_19c8* unknown_ptr_3b04;
    void* unknown_ptr_3b08;
    void* unknown_ptr_3b0c;
    void* unknown_ptr_3b10;
    void* unknown_ptr_3b14;
    void* unknown_ptr_3b18;
    void* unknown_ptr_3b1c;
    void* unknown_ptr_3b20;
    void* unknown_ptr_3b24;
    void* unknown_ptr_3b28;
    void* unknown_ptr_3b2c;
    void* unknown_ptr_3b30;
    void* unknown_ptr_3b34;
    void* unknown_ptr_3b38;
    void* unknown_ptr_3b3c;
    Unknown_222c* unknown_ptr_3b40;
    void* unknown_ptr_3b44;
    Unknown_22b4* unknown_ptr_3b48;
    void* unknown_ptr_3b4c;
    void* unknown_ptr_3b50;
    void* unknown_ptr_3b54;
    void* unknown_ptr_3b58;
    void* unknown_ptr_3b5c;
    void* unknown_ptr_3b60;
    void* unknown_ptr_3b64;
    void* unknown_ptr_3b68;
    void* unknown_ptr_3b6c;
    void* unknown_ptr_3b70;
    Unknown_27e8* unknown_ptr_3b74;
    void* unknown_ptr_3b78;
    void* unknown_ptr_3b7c;
    void* unknown_ptr_3b80;
    void* unknown_ptr_3b84;
    void* unknown_ptr_3b88;
    void* unknown_ptr_3b8c;
    void* unknown_ptr_3b90;
    void* unknown_ptr_3b94;
    void* unknown_ptr_3b98;
    void* unknown_ptr_3b9c;
    void* unknown_ptr_3ba0;
    void* unknown_ptr_3ba4;
    void* unknown_ptr_3ba8;
    void* unknown_ptr_3bac;
    void* unknown_ptr_3bb0;
    void* unknown_ptr_3bb4;
    void* unknown_ptr_3bb8;
    void* unknown_ptr_3bbc;
    void* unknown_ptr_3bc0;
    void* unknown_ptr_3bc4;
    Unknown_14 unknown_array_3bc8[3];
    Unknown_28 unknown_array_3c04[4];
    void* unknown_ptr_3ca4;
    void* unknown_ptr_3ca8;
    void* unknown_ptr_3cac;
    void* unknown_ptr_3cb0;
    char unknown_3cb4[0x3d4];
    void* unknown_ptr_4088;
    void* unknown_ptr_408c;
    void* unknown_ptr_4090;
    char unknown_4094[0x130];
    void* unknown_ptr_41c4;
    char unknown_41c8[0x118];
    unsigned char unknown_42e0;
    unsigned char unknown_42e1;
    unsigned char unknown_42e2;
    unsigned char unknown_42e3;
    unsigned char unknown_42e4;
    unsigned char unknown_42e5;
    char unknown_42e6[0x1];
    unsigned char unknown_42e7;
    unsigned char unknown_42e8;
    unsigned char unknown_42e9;
    unsigned char unknown_42ea;
    char unknown_42eb[0x1];
    unsigned short unknown_42ec;
    unsigned short unknown_42ee;
    unsigned char unknown_42f0;
    unsigned char unknown_42f1[0x2d];
    unsigned char unknown_431e;
    char unknown_431f[0x1];
    int unknown_4320;
    int unknown_4324;
    void* unknown_ptr_4328;
    signed char unknown_432c;
    signed char unknown_432d[3];
    unsigned char unknown_4330;
    unsigned char unknown_4331;
    char unknown_4332[0x2];
    int unknown_4334;
    int unknown_4338;
    int unknown_433c;
    int unknown_4340;
    int unknown_4344;
    int unknown_4348;
    int unknown_434c;
    int unknown_4350;
    unsigned char unknown_4354;
    unsigned char unknown_4355;
    char unknown_4356[0x6];
    struct
    {
        unsigned char unknown_0;
        char unknown_1[0x2f];
    } unknown_435c[4];
    void* unknown_ptr_441c;
    unsigned char unknown_4420;
    unsigned char unknown_4421;
    unsigned short unknown_4422;
    unsigned short unknown_4424;
    char unknown_4426[0x2];
    int unknown_4428;
    unsigned char unknown_442c;
    unsigned char unknown_442d;
    unsigned char unknown_442e;
    unsigned char unknown_442f;
    short unknown_4430;
    unsigned char unknown_4432;
    char unknown_4433[0x1];
    int unknown_4434;
    int unknown_4438;
    int unknown_443c;
    int unknown_4440;
    char unknown_4444[0x2];
    signed char unknown_4446;
    char unknown_4447[0x3];
    unsigned short unknown_444a[4];
    char unknown_4452[0x2];
    int unknown_4454;
    int unknown_4458;
    signed char unknown_445c[4][11];
    unsigned char unknown_4488;
    unsigned char unknown_4489;
    unsigned char unknown_448a;
    char unknown_448b[0x1];
    TreasureMapLanguageDataOffsets* pTMapLanguageOffsets;
    unsigned char unknown_4490;
    unsigned char unknown_4491;
    char unknown_4492[0x2];
    int unknown_4494;
    int unknown_4498;
    char unknown_449c[0x10];
    unsigned short unknown_44ac;
    char unknown_44ae[0x16];
    void* unknown_ptr_44c4;

    inline GameResources(GameResourcesData* data)
        : unknown_ptr_36c8(&data->unknown_14)
        , unknown_ptr_36cc(&data->unknown_c0)
        , unknown_ptr_36d0(data->unknown_16c)
        , unknown_ptr_36d8(data->unknown_d9c)
        , unknown_ptr_36fc(data->unknown_dbc)
        , unknown_ptr_3700(data->unknown_dc4)
        , unknown_ptr_3704(data->unknown_dcc)
        , unknown_ptr_3708(data->unknown_dd4)
        , unknown_ptr_370c(data->unknown_df8)
        , unknown_ptr_3710(data->unknown_e24)
        , unknown_ptr_3714(data->unknown_f60)
        , unknown_ptr_3718(data->unknown_f6c)
        , unknown_ptr_371c(data->unknown_1638)
        , unknown_ptr_3720(data->unknown_1668)
        , unknown_ptr_3724(data->unknown_16c8)
        , unknown_ptr_3728(data->unknown_16d4)
        , unknown_ptr_372c(data->unknown_16fc)
        , unknown_ptr_3730(&data->unknown_1720)
        , unknown_ptr_3734(data->unknown_1748)
        , unknown_ptr_3738(data->unknown_1910)
        , unknown_ptr_3afc(data->unknown_1934)
        , unknown_ptr_3b00(&data->unknown_19a0)
        , unknown_ptr_3b04(&data->unknown_19c8)
        , unknown_ptr_3b08(data->unknown_1a80)
        , unknown_ptr_3b0c(data->unknown_1a90)
        , unknown_ptr_3b10(data->unknown_1af8)
        , unknown_ptr_3b14(data->unknown_1b18)
        , unknown_ptr_3b18(data->unknown_1b40)
        , unknown_ptr_3b1c(data->unknown_1b6c)
        , unknown_ptr_3b20(data->unknown_1b90)
        , unknown_ptr_3b24(data->unknown_1e14)
        , unknown_ptr_3b28(data->unknown_1e54)
        , unknown_ptr_3b2c(data->unknown_1e94)
        , unknown_ptr_3b30(data->unknown_1ea8)
        , unknown_ptr_3b34(data->unknown_2134)
        , unknown_ptr_3b38(data->unknown_2144)
        , unknown_ptr_3b3c(data->unknown_216c)
        , unknown_ptr_3b40(&data->unknown_222c)
        , unknown_ptr_3b44(data->unknown_2268)
        , unknown_ptr_3b48(&data->unknown_22b4)
        , unknown_ptr_3b4c(data->unknown_2310)
        , unknown_ptr_3b50(data->unknown_2360)
        , unknown_ptr_3b54(data->unknown_2380)
        , unknown_ptr_3b58(data->unknown_23a4)
        , unknown_ptr_3b5c(data->unknown_23b0)
        , unknown_ptr_3b60(data->unknown_24b4)
        , unknown_ptr_3b64(data->unknown_24c8)
        , unknown_ptr_3b68(data->unknown_24d8)
        , unknown_ptr_3b6c(data->unknown_274c)
        , unknown_ptr_3b70(data->unknown_27bc)
        , unknown_ptr_3b74(&data->unknown_27e8)
        , unknown_ptr_3b78(data->unknown_27f8)
        , unknown_ptr_3b7c(data->unknown_2808)
        , unknown_ptr_3b80(data->unknown_2a98)
        , unknown_ptr_3b84(data->unknown_2aac)
        , unknown_ptr_3b88(data->unknown_2b04)
        , unknown_ptr_3b8c(data->unknown_2b18)
        , unknown_ptr_3b90(data->unknown_2b6c)
        , unknown_ptr_3b94(data->unknown_2bb4)
        , unknown_ptr_3b98(data->unknown_2e3c)
        , unknown_ptr_3b9c(data->unknown_2e60)
        , unknown_ptr_3ba0(data->unknown_2eb0)
        , unknown_ptr_3ba4(data->unknown_2ebc)
        , unknown_ptr_3ba8(data->unknown_2ee8)
        , unknown_ptr_3bac(data->unknown_2ef8)
        , unknown_ptr_3bb0(data->unknown_2f14)
        , unknown_ptr_3bb4(data->unknown_2fb4)
        , unknown_ptr_3bb8(data->unknown_2fc0)
        , unknown_ptr_3bbc(data->unknown_2fcc)
        , unknown_ptr_3bc0(data->unknown_2fe0)
        , unknown_ptr_3bc4(data->unknown_304c)
        , unknown_ptr_3ca4(data->unknown_3674)
        , unknown_ptr_3ca8(data->unknown_3078)
        , unknown_ptr_3cac(data->unknown_307a)
        , unknown_ptr_3cb0(data->unknown_307c)
        , unknown_ptr_4088(data->unknown_3138)
        , unknown_ptr_408c(data->unknown_313a)
        , unknown_ptr_4090(data->unknown_313c)
        , unknown_ptr_41c4(data->unknown_32d8)
        , unknown_ptr_4328(data->unknown_332c)
        , unknown_ptr_441c(data->unknown_3560)
        , unknown_ptr_44c4(data->unknown_3571)
    {
    }

    void Initialize();
};

// Overlay 30's functions, which main calls through the symbols of other overlays at the same address
GameResources* CreateGameResources(AllocatorUnion* allocator, GameResourcesData** data);
void DestroyGameResources(GameResources* resources, AllocatorUnion* allocator, GameResourcesData** data);

// size 0x44.
// Needs to be moved back to grotto
struct TreasureMapLanguageDataOffsets
{
    unsigned int bossRangesByQuality;
    unsigned int bossIDsAndWeights;
    unsigned int environs;
    unsigned int prefixRangesByMonsterRank;
    unsigned int prefixNames;
    unsigned int floorRangesByQuality;
    unsigned int unknown_18; 
    unsigned int startingMonsterRanksByQuality;
    unsigned int mapLocations;
    unsigned int seeminglyChestRanksByMonsterRank;
    unsigned int localeRankRangesByFloorCount;
    unsigned int localeNames;
    unsigned int suffixRangesByBoss;
    unsigned int suffixNames;
    unsigned int grottoBossDrops; // flat, size 0x0C per boss
    unsigned int legacyBossDrops; // flat, size 0x5C per boss
    unsigned int legacyBossData;
};

// Will rename this after getting a better idea of what the struct is
#ifdef jpn
#define func_ov017_0218b5b0 func_ov017_0218c1d0
#endif

// This is the second function in overlay 17 (the first one stores this pointer).
// So it's possible the struct is some sort of overall struct for the overlay.
extern "C" GameResources* func_ov017_0218b5b0();
// Stores the pointer that func_ov017_0218b5b0 returns (GameResources::Initialize calls it)
extern "C" void func_ov017_0218b5a0(GameResources* resources);