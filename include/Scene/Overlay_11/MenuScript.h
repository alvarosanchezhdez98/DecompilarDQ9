#pragma once

#include "Graphics/Sprite.h"
#include "Memory/SafeAllocator.h"
#include "System/Matrix.h"
#include "Text/TextTable.h"

// A value of a script: a command's parameter, or a variable that a command writes its result to
struct ScriptValue
{
    enum Type
    {
        Type_Int,
        Type_Float,
        Type_String,
        // A variable: value_.variable_ is the ScriptValue that a command writes to
        Type_Variable,
    };

    int type_;
    union
    {
        int int_;
        float float_;
        const char* string_;
        ScriptValue* variable_;
    } value_;

    int ToInt() const;
    float ToFloat() const;
    // Writes the result of a command to the variable
    void Set(int value);

    const char* ToString() const
    {
        return type_ == Type_String ? value_.string_ : 0;
    }
};

// A command of the scripts: it takes the command's parameters and their count, and returns 0 when it fails
typedef int (*ScriptCommand)(ScriptValue* params, int count);

// Overlay 17's interpreter of the menus' scripts (data/menu/*.stb, which start with "SB2"): func_ov017_021d4c04
// initializes it, func_ov017_021d4cc0 sets its commands, func_ov017_021d4df8 returns whether a script has an entry,
// func_ov017_021d4ce4 starts an entry and func_ov017_021d4ccc runs the script
struct ScriptEngine
{
    char unk_0[0x3c];
    // The script stopped
    int stopped_;
    char unk_40[0x14];
};

// The part of the objects that overlay 23 shows on the menus: func_ov023_021f672c initializes it, func_ov023_021f67ac
// adds an object, func_ov023_021f6880 returns an object by its ID and func_ov023_021f6844 removes a heap's objects
struct MenuObjectList
{
    char unk_0[0x74];
};

// A vtable of overlay 23's objects
struct MenuObjectVTable;

// The virtual functions of overlay 23's objects, in the order of their vtables. The commands call them through this
// class, which the game doesn't construct: see MenuObject
class MenuObjectFunctions
{
public:
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void SetPosition(Vector3fix* position);
    virtual void Unk20();
    virtual void Unk24(int);
    virtual void Unk28();
    virtual void Unk2c();
    virtual void Unk30();
    virtual void Unk34(int);
    virtual void Unk38();
    virtual void Unk3c(int);
    virtual void Unk40();
    virtual void Unk44(int);
    virtual void Unk48();
    virtual void Unk4c(int);
    virtual void Unk50();
    virtual void Unk54(int);
    virtual void Unk58();
    virtual void Unk5c(int);
    virtual void Unk60();
    virtual void Unk64(int);
    virtual void Unk68();
    virtual void Unk6c(int);
    virtual void Unk70();
    virtual void Unk74(int);
    virtual void Unk78();
    virtual void Unk7c(int);
    virtual void Unk80();
    virtual void Unk84(int);
    virtual void Unk88();
    virtual void Unk8c(int);
    virtual void Unk90();
    virtual void Unk94(int);
    virtual void Unk98();
    virtual void Unk9c(int);
    virtual void Unka0();
    virtual void UnkA4(int);
    virtual void Unka8();
    virtual void UnkAc(int, int, int);
    virtual void UnkB0(int);
    virtual void Unkb4();
    virtual void Unkb8();
    virtual void Unkbc();
    virtual void Unkc0();
    virtual void UnkC4(int, int, int);
    virtual void SetPosition2(Vector3fix* position);
    virtual void Unkcc();
    virtual void UnkD0();
    virtual void UnkD4();
    virtual void Unkd8();
    virtual void Unkdc();
    virtual void Unke0();
    virtual void Unke4();
    virtual int UnkE8();
};

extern "C"
{
    void func_0204719c(void*);
    void func_02047230(void*);
    void func_02048080(void*);

    // The vtables of the objects' classes
    extern const MenuObjectVTable data_ov023_021fe3e4;
    extern const MenuObjectVTable data_ov023_021fe4f0;
    extern const MenuObjectVTable data_ov023_021fe604;
    extern const MenuObjectVTable data_ov023_021fe708;
    extern const MenuObjectVTable data_ov023_021fe80c;
    extern const MenuObjectVTable data_ov023_021fe910;
    extern const MenuObjectVTable data_ov023_021fea34;
    extern const MenuObjectVTable data_ov023_021feb40;
    extern const MenuObjectVTable data_ov023_021fec60;
    extern const MenuObjectVTable data_ov023_021fed64;
    extern const MenuObjectVTable data_ov023_021fee68;
    extern const MenuObjectVTable data_ov023_021fef74;
    extern const MenuObjectVTable data_ov023_021ff078;
    extern const MenuObjectVTable data_ov023_021ff17c;
    extern const MenuObjectVTable data_ov023_021ff280;
    extern const MenuObjectVTable data_ov023_021ff384;
    extern const MenuObjectVTable data_ov023_021ff4b0;
    extern const MenuObjectVTable data_ov023_021ff5b4;
    extern const MenuObjectVTable data_ov023_021ff6b8;
    extern const MenuObjectVTable data_ov023_021ff7c4;
    extern const MenuObjectVTable data_ov023_021ff8c8;
    // Overlay 4's
    extern const MenuObjectVTable data_ov004_021705f8;

    void func_020de824(void*);
    void func_020df80c(void*);
    void func_020dfc2c(TextTable* table);
    void func_ov023_021e4e8c(void*);

    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a494(SpriteRenderer* renderer);
}

// An object that overlay 23 shows on a menu. Overlay 23's classes are polymorphic: until it's decompiled, the objects
// have their vtable as a member, which this constructor sets first like a compiler would. The commands construct the
// objects on the stack and copy them to a heap
struct MenuObject
{
    const MenuObjectVTable* vtable_;
    char unk_4[8];
    // Flags that the scripts set and clear, such as 1 and 4
    unsigned char flags_;
    char unk_d[3];

    MenuObject(const MenuObjectVTable* vtable) : vtable_(vtable) {}

    // Calls the virtual functions: the object's vtable_ is MenuObjectFunctions' vptr
    MenuObjectFunctions* Functions()
    {
        return (MenuObjectFunctions*)this;
    }
};

// The objects of type 8
struct MenuObjectType8 : MenuObject
{
    char unk_10[0x32];
    short unk_42;
    unsigned char unk_44;
    unsigned char unk_45_0 : 1;
    unsigned char unk_45_1 : 6;
    unsigned char unk_45_7 : 1;
};

// A part of some objects, which func_02048080 clears when it's constructed and destroyed
struct MenuObjectBuffer
{
    void* unk_0;
    int unk_4;

    MenuObjectBuffer()
    {
        func_02048080(this);
    }

    ~MenuObjectBuffer()
    {
        func_02048080(this);
    }
};

// A sprite renderer that func_0205a444 initializes and func_0205a494 destroys
struct MenuSpriteRenderer : SpriteRenderer
{
    MenuSpriteRenderer()
    {
        func_0205a444(this);
    }

    ~MenuSpriteRenderer()
    {
        func_0205a494(this);
    }
};

// A table of texts that func_020dfc2c initializes
struct MenuTextTable : TextTable
{
    MenuTextTable()
    {
        func_020dfc2c(this);
    }
};

// What func_020df80c initializes
struct MenuObjectPart_020df80c
{
    char unk_0[0x10];

    MenuObjectPart_020df80c()
    {
        func_020df80c(this);
    }
};

// What func_020de824 initializes
struct MenuObjectPart_020de824
{
    char unk_0[0x1c];

    MenuObjectPart_020de824()
    {
        func_020de824(this);
    }
};

// What func_ov023_021f6f20 initializes (sizeof == 0xac)
struct MenuObject_021f6f20 : MenuObject
{
    char unk_10[0x10];
    // func_0204719c initializes it and func_02047230 destroys it
    char unk_20[0x14];
    MenuObjectBuffer unk_34;
    char unk_3c[0x70];

    // The game's compiler didn't inline these (two commands use them): they're after the first command that uses
    // them (MenuScriptCommands.cpp)
    MenuObject_021f6f20();
    ~MenuObject_021f6f20();
};

// What func_ov023_021f745c initializes (sizeof == 0x54)
struct MenuObject_021f745c : MenuObject
{
    char unk_10[0x44];

    MenuObject_021f745c() : MenuObject(&data_ov023_021fe4f0) {}
};

// What func_ov023_021f7da0 initializes (sizeof == 0x110)
struct MenuObject_021f7da0 : MenuObject
{
    char unk_10[0x100];

    MenuObject_021f7da0() : MenuObject(&data_ov023_021fe604) {}
};

// What func_ov023_021f89f4 initializes (sizeof == 0x50)
struct MenuObject_021f89f4 : MenuObject
{
    char unk_10[0x40];

    MenuObject_021f89f4() : MenuObject(&data_ov023_021fe708) {}
};

// What func_ov023_021f8cf4 initializes (sizeof == 0x64)
struct MenuObject_021f8cf4 : MenuObject
{
    char unk_10[0x54];

    MenuObject_021f8cf4() : MenuObject(&data_ov023_021fe80c) {}
};

// What func_ov023_021f9ec8 initializes (sizeof == 0x28), *likely* the cursor
struct MenuObject_021f9ec8 : MenuObject
{
    char unk_10[0x18];

    MenuObject_021f9ec8() : MenuObject(&data_ov023_021fe910) {}
};

// What func_ov023_021fa298 initializes (sizeof == 0x30)
struct MenuObject_021fa298 : MenuObject
{
    char unk_10[0x20];

    MenuObject_021fa298() : MenuObject(&data_ov023_021fea34) {}
};

// What func_ov023_021fa760 initializes (sizeof == 0x88), *likely* sprites
struct MenuObject_021fa760 : MenuObject
{
    char unk_10[0x14];
    MenuSpriteRenderer renderer_;
    char unk_78[0x10];

    // The game's compiler didn't inline it (two commands use it): it's after the first command that uses it
    // (MenuScriptCommands.cpp)
    MenuObject_021fa760();
};

// What func_ov023_021fad84 initializes (sizeof == 0x4c)
struct MenuObject_021fad84 : MenuObject
{
    char unk_10[0x3c];

    MenuObject_021fad84() : MenuObject(&data_ov023_021fec60) {}
};

// What func_ov023_021fb2b0 initializes (sizeof == 0x2c)
struct MenuObject_021fb2b0 : MenuObject
{
    char unk_10[0x1c];

    MenuObject_021fb2b0() : MenuObject(&data_ov023_021fed64) {}
};

// A part of MenuObject_021fb534
struct MenuObjectPart_021fb534
{
    char unk_0[0x54];
    MenuObjectBuffer unk_54;
};

// What func_ov023_021fb534 initializes (sizeof == 0xb4)
struct MenuObject_021fb534 : MenuObject
{
    char unk_10[0x10];
    MenuObjectPart_021fb534 unk_20;
    char unk_7c[0x38];

    MenuObject_021fb534() : MenuObject(&data_ov023_021fee68) {}
};

// What func_ov023_021fba80 initializes (sizeof == 0x24)
struct MenuObject_021fba80 : MenuObject
{
    char unk_10[0x14];

    MenuObject_021fba80() : MenuObject(&data_ov023_021fef74) {}
};

// What func_ov023_021fbb64 initializes (sizeof == 0x40)
struct MenuObject_021fbb64 : MenuObject
{
    char unk_10[0x30];

    MenuObject_021fbb64() : MenuObject(&data_ov023_021ff078) {}
};

// A part of MenuObject_021fbd00
struct MenuObjectPart_021fbd00
{
    SafeAllocator unk_0;
    SafeAllocator unk_14;
    SafeAllocator unk_28;
    char unk_3c[0x18];
    MenuTextTable unk_54;
    MenuObjectPart_020df80c unk_6c;
    MenuObjectPart_020df80c unk_7c;
    MenuTextTable unk_8c;
    MenuTextTable unk_a4;
    char unk_bc[0x70];
    MenuSpriteRenderer renderer_;
    char unk_180[0x61c];
};

// What func_ov023_021fbd00 initializes (sizeof == 0x7bc)
struct MenuObject_021fbd00 : MenuObject
{
    char unk_10[0x10];
    MenuObjectPart_021fbd00 unk_20;

    MenuObject_021fbd00() : MenuObject(&data_ov023_021ff17c) {}
};

// What func_ov023_021fbe08 initializes (sizeof == 0x50)
struct MenuObject_021fbe08 : MenuObject
{
    char unk_10[0x10];
    SafeAllocator allocator_;
    MenuObjectPart_020de824 unk_34;

    MenuObject_021fbe08() : MenuObject(&data_ov023_021ff280) {}
};

// What func_ov023_021fc1f4 initializes (sizeof == 0x2c)
struct MenuObject_021fc1f4 : MenuObject
{
    char unk_10[0x1c];

    MenuObject_021fc1f4() : MenuObject(&data_ov023_021ff384) {}
};

// What func_ov023_021fc408 initializes (sizeof == 0x30)
struct MenuObject_021fc408 : MenuObject
{
    char unk_10[0x20];

    MenuObject_021fc408() : MenuObject(&data_ov023_021ff4b0) {}
};

// A part of MenuObject_021fc518, which func_ov023_021e4e8c initializes
struct MenuObjectPart_021fc518
{
    char unk_0[0x6b8];
    SafeAllocator allocators_[10];
    SafeAllocator allocator_;
    char unk_794[0x48c];

    MenuObjectPart_021fc518()
    {
        func_ov023_021e4e8c(this);
    }
};

// What func_ov023_021fc518 initializes (sizeof == 0x1870)
struct MenuObject_021fc518 : MenuObject
{
    char unk_10[0x10];
    MenuObjectPart_021fc518 unk_20[2];
    char unk_1860[0x10];

    MenuObject_021fc518() : MenuObject(&data_ov023_021ff5b4) {}
};

// What func_ov023_021fcdd4 initializes (sizeof == 0xcc)
struct MenuObject_021fcdd4 : MenuObject
{
    char unk_10[0xbc];

    MenuObject_021fcdd4() : MenuObject(&data_ov023_021ff6b8) {}
};

// What func_ov023_021fd1e0 initializes (sizeof == 0x2c)
struct MenuObject_021fd1e0 : MenuObject
{
    char unk_10[0x1c];

    MenuObject_021fd1e0() : MenuObject(&data_ov023_021ff7c4) {}
};

// What func_ov023_021fd320 initializes (sizeof == 0x30)
struct MenuObject_021fd320 : MenuObject
{
    char unk_10[0x20];

    MenuObject_021fd320() : MenuObject(&data_ov023_021ff8c8) {}
};

// A part of MenuObject_02167820
struct MenuObjectPart_02167820
{
    char unk_0[4];
    MenuTextTable unk_4;
    char unk_1c[0x44];
    MenuSpriteRenderer renderer_;
};

// What overlay 4's func_ov004_02167820 initializes (sizeof == 0x118)
struct MenuObject_02167820 : MenuObject
{
    char unk_10[0x10];
    SafeAllocator allocator_;
    MenuObjectPart_02167820 unk_34;
    char unk_e8[0x30];

    MenuObject_02167820() : MenuObject(&data_ov004_021705f8) {}
};

// A heap of a menu: a script creates it with an ID in one of GameResources' allocators or in another heap (its parent)
struct MenuHeap
{
    int id_;
    SafeAllocator allocator_;
    // The next heap of the same parent
    MenuHeap* next_;
    // The first heap created in this one
    MenuHeap* child_;

    void Initialize();
    // Returns the heap with this ID: this one, one after it or one in them
    MenuHeap* Find(int id);
    void AddNext(MenuHeap* heap);
    void AddChild(MenuHeap* heap);
};

// A saved state of the VRAM's managers, which func_0207df50 saves and func_0207dfc8 copies (*likely* NitroSystem's
// texture and palette VRAM managers, which it calls)
struct VRAMManagerState
{
    char unk_0[0x70];
};

// A state of the VRAM's managers that a script saves with an ID
struct MenuVRAMState
{
    unsigned short id_;
    unsigned short unk_2;
    VRAMManagerState state_;
    int unk_74;
    MenuVRAMState* next_;

    void Initialize();
};

// The system of the menus that run a script (data/menu/*.stb): the title, the treasure maps, the accolades...
// Overlay 17 loads the script, allocates this (sizeof == 0x1e0) and calls Initialize(), Load(), CreateHeap(),
// SaveVRAMState() and Update() every frame until it returns false. Overlay 4 has the native functions of the menus,
// which the scripts run with Callback commands
class MenuScript
{
public:
    // A native function of a menu, which returns whether it's still running
    typedef int (*Callback)(MenuScript* script);

    // What the script frees and allocates in: the heap with ID 0, which overlay 17 creates
    MenuHeap heap_;
    MenuVRAMState vramState_;
    // What AllocateBuffer() allocated
    void* buffer_;
    unsigned int bufferSize_;
    int bufferHeap_;
    // The script's file
    void* file_;
    unsigned int fileSize_;
    // What AllocateData() allocated
    void* data_;
    unsigned int dataSize_;
    ScriptEngine engine_;
    // The entry that the script starts next, or -1
    int nextEntry_;
    // The entry that the script runs, or -1
    int entry_;
    // Flags that the scripts set for overlay 17 (1, 2 and 4 choose the scene that it runs next)
    unsigned int flags_;
    MenuObjectList objects_;
    // The BackgroundLoader task of the file that a script loads (data/<name>), or -1
    int loadTask_;
    // Whether the screens were swapped (bit 15 of POWCNT) when the menu started
    int screensSwapped_;
    // func_02074af4 (main screen) and func_02074b64 (sub screen) initialize it
    char unk_194[0x10];
    unsigned char unk_1a4;
    unsigned char unk_1a5;
    char unk_1a6[2];
    // The main and the sub screen's enabled backgrounds (bits 8 to 12 of DISPCNT) when the menu started
    int mainLayers_;
    int subLayers_;
    unsigned short unk_1b0;
    unsigned short unk_1b2;
    // The native functions that the script can run
    Callback* callbacks_;
    unsigned int callbackCount_;
    // The callback that runs until it returns 0, or 0
    unsigned short callback_;
    // The callback that runs every frame when no other one does, or 0
    unsigned short frameCallback_;
    // The callbacks and entries of the answers of a question (yes and no), or 0
    unsigned short yesCallback_;
    unsigned short noCallback_;
    unsigned short yesEntry_;
    unsigned short noEntry_;
    int unk_1c8;
    // Update() finished the menu
    bool finished_;
    // The menu is fading out
    bool finishing_;
    char unk_1ce[2];
    // In ticks, for the title's demo
    unsigned int idleTime_;
    int mainBanks_;
    int subBanks_;
    // What Finish() calls first
    void (*finishCallback_)(MenuScript* script);

    enum Flag
    {
        Flag_1 = 1,
        Flag_2 = 2,
        Flag_4 = 4,
    };

    enum Entry
    {
        // The demo that the title runs when no button is pressed for a minute
        Entry_TitleDemo = 999,
    };

    void Initialize();
    // Returns 1 when it fails
    int AllocateBuffer(int heap, unsigned int size);
    void* GetBuffer();
    bool AllocateData(int heap, unsigned int size);
    void SetData(void* data, unsigned int size);
    void* GetData();
    unsigned int GetDataSize();
    void Load(SafeAllocator* allocator, void* file, unsigned int fileSize);
    void CreateHeap(void* buffer, unsigned int size);
    MenuHeap* GetHeap();
    MenuHeap* FindHeap(int id);
    void DestroyHeap(MenuHeap* heap);
    void SaveVRAMState(VRAMManagerState* state);
    MenuVRAMState* FindVRAMState(int id);
    bool Update();
    void Draw1();
    void Draw2();
    void Draw3();
    void Finish();
    void StartEntry(int entry);
    void RunScript();
    void SetFlags(unsigned int flags);
    unsigned int GetFlags(unsigned int flags);
    MenuObjectList* GetObjects();
    void SetLoadTask(int task);
    int GetLoadTask();
    void SetUnk1b0(unsigned short value);
    unsigned short GetUnk1b0();
    void SetUnk1b2(unsigned short value);
    unsigned short GetUnk1b2();
    void SetCallbacks(Callback* callbacks, unsigned int count);
    Callback* GetCallbacks(unsigned int* count);
    void RunCallback(unsigned int callback);
    void UpdateCallbacks();
    void SetUnk1c8();
    void UpdateQuestion();
    void ClearUnk1c8();
    int GetUnk1c8();
    void SetAnswerCallbacks(int yes, int no);
    void SetAnswerEntries(int yes, int no);
    void SaveMainBanks();
    void SaveSubBanks();
    void SetFinishCallback(void (*callback)(MenuScript* script));
};

// Sets the script commands of the menus (MenuScriptCommands.cpp)
void SetMenuScriptCommands(ScriptEngine* engine);
