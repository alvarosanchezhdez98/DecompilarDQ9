// The compiler emits the functions whose addresses the commands take before them (in reverse order), which it only
// does with this
#pragma ipa file

#include "Scene/Overlay_11/MenuScript.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/Memory.h"
#include "System/VRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    void* func_0203cf4c();
    void func_0203cfb4(void*);
    void func_0203e0a0(void*, unsigned short);
    unsigned short* func_02012fe4();
    void func_0203b4d8(GameResources* resources, int);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);

    // The menu that runs a script
    MenuScript* func_ov017_021b2164();
    void func_ov017_0219b938(GameResources* resources);
    void func_ov017_0219bf74();
    void func_ov017_021a27e8(GameResources* resources);
    void func_ov017_021a316c(GameResources* resources);
    // Sets the commands of a script engine
    void func_ov017_021d4cc0(ScriptEngine* engine, ScriptCommand* commands, int count);

    // Adds an object to the list, returns an object by its ID and returns its type
    void func_ov023_021f67ac(MenuObjectList* objects, void* object);
    MenuObject* func_ov023_021f6880(MenuObjectList* objects, int id);
    int func_ov023_021f6bc0(MenuObjectList* objects);
    int func_ov023_021f6f10(MenuObject* object);
    int func_ov023_021f6f20(MenuObject_021f6f20* object, MenuScript* script, int id, int heap, int, const char* file);
    int func_ov023_021f745c(MenuObject_021f745c* object, MenuScript* script, int id, int heap, const char* archive,
                            const char* file, int, int, int);
    int func_ov023_021f7da0(MenuObject_021f7da0* object, MenuScript* script, int id, int heap, int, int, int, int,
                            int);
    void func_ov023_021f7eb8(MenuObject* object, MenuScript* script, int, short, short, short, short, unsigned char,
                             unsigned char, bool);
    void func_ov023_021f8120(MenuObject* object);
    int func_ov023_021f89f4(MenuObject_021f89f4* object, MenuScript* script, int id, int heap, int, int, int, int,
                            int, int, int);
    int func_ov023_021f8cf4(MenuObject_021f8cf4* object, MenuScript* script, int id, int heap, int, int);
    int func_ov023_021f9b30(MenuObject* object, unsigned short, unsigned short, unsigned short);
    int func_ov023_021f9ec8(MenuObject_021f9ec8* object, MenuScript* script, int id, int heap, int);
    void func_ov023_021fa078(MenuObject* object, MenuScript* script, unsigned short, Vector3fix*, int, int);
    int func_ov023_021fa298(MenuObject_021fa298* object, MenuScript* script, int id, int heap, const char* archive,
                            const char* file, int);
    int func_ov023_021fa760(MenuObject_021fa760* object, MenuScript* script, int id, int heap, const char* archive,
                            const char* file, int);
    int func_ov023_021fad84(MenuObject_021fad84* object, MenuScript* script, int id, int heap, int, int);
    int func_ov023_021fb2b0(MenuObject_021fb2b0* object, MenuScript* script, int id, int heap, int, int);
    int func_ov023_021fb534(MenuObject_021fb534* object, MenuScript* script, int id, int heap, const char* file, int);
    void func_ov023_021f6844(MenuObjectList* objects, int heap);
    void func_ov023_021f6e90(MenuObjectList* objects, int id, void* values);
    void func_ov023_021f6eb8(MenuObjectList* objects, int id);
    void* func_ov023_021f7318(MenuObject* object);
    void func_ov023_021f7320(MenuObject* object);
    void func_ov023_021f79ec(MenuObject* object, const char* text);
    void func_ov023_021f8944(MenuObject* object, MenuScript* script, unsigned char, int);
    void func_ov023_021f9c0c(MenuObject* object);
    void func_ov023_021f9c58(MenuObject* object, unsigned short);
    void func_ov023_021f9c60(MenuObject* object, unsigned short);
    void func_ov023_021f9da0(MenuObject* object, bool);
    // Returns the names that the object shows
    void* func_ov023_021fa598(MenuObject* object);
    void func_ov023_021fb25c(MenuObject* object, int, int, int, int);
    void func_ov023_021fb274(MenuObject* object, signed char);
    void func_ov023_021fb284(MenuObject* object, signed char);
    int func_ov023_021fba80(MenuObject_021fba80* object, MenuScript* script, int id, int heap);
    int func_ov023_021fbb64(MenuObject_021fbb64* object, MenuScript* script, int id, int heap, int, int, int, int,
                            int, int, int);
    int func_ov023_021fbd00(MenuObject_021fbd00* object, MenuScript* script, int id, int heap, int, int,
                            unsigned char);
    int func_ov023_021fbe08(MenuObject_021fbe08* object, MenuScript* script, int id, int heap, int);
    int func_ov023_021fc1f4(MenuObject_021fc1f4* object, MenuScript* script, int id, int heap);
    int func_ov023_021fc408(MenuObject_021fc408* object, MenuScript* script, int id, int heap, int, int, int, int,
                            int, int);
    int func_ov023_021fc518(MenuObject_021fc518* object, MenuScript* script, int id, int heap, int, int);
    int func_ov023_021fcdd4(MenuObject_021fcdd4* object, MenuScript* script, int id, int heap, int, const char*);
    int func_ov023_021fd1e0(MenuObject_021fd1e0* object, MenuScript* script, int id, int heap, void*, void*);
    int func_ov023_021fd320(MenuObject_021fd320* object, MenuScript* script, int id, int heap, int, int, int, int,
                            int);
    int func_ov004_02167820(MenuObject_02167820* object, MenuScript* script, int id, int heap);

    // Writes a command's result
    void func_ov017_021d6134(ScriptValue* params, int value);

    // The sound player, the pad and the touch screen
    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern unsigned char data_02114e54[];
    int func_02011b50(GameState* gameState, int);
    int func_02012444(void* pad, int buttons);
    void* func_0202ae18();
    int func_0202b7d8();
    int func_0202ba00(void*);
    MessageSystem* func_020421a0();
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    int func_020457e0(MessageSystem* messages);
    void func_02048004(void*, void*);
    void func_0205eaa0(void* sound, int effect, int);
    const char* func_02072a68(void* names, int index);
    int func_0209ca2c(void*);
}

// The object with this ID *likely* is the menu's cursor
#define CURSOR_ID 0xffff

int ScriptValue::ToInt() const
{
    if (type_ != Type_Float)
        return value_.int_;
    return value_.float_;
}

float ScriptValue::ToFloat() const
{
    if (type_ != Type_Int)
        return value_.float_;
    return value_.int_;
}

void ScriptValue::Set(int value)
{
    if (type_ == Type_Variable)
        value_.variable_->value_.int_ = value;
}

// Sets the brightness of both screens: the brightness and the duration (in milliseconds)
static int Command_SetBrightness(ScriptValue* params, int count)
{
    GameResources* resources = func_ov017_0218b5b0();
    int brightness = params[0].ToInt();
    SetBrightness(resources, brightness, params[1].ToInt() / 34);
    return 1;
}

static int Command_01(ScriptValue* params, int count)
{
    GameResources* resources = func_ov017_0218b5b0();
    MenuScript* script = func_ov017_021b2164();
    void* unk = func_0203cf4c();
    unsigned short* unk2 = func_02012fe4();
    switch (params[0].ToInt())
    {
        case 0:
            if (script->GetFlags(MenuScript::Flag_1))
                return 1;
            func_0203e0a0(unk, *unk2);
            func_ov017_0219bf74();
            script->SetFlags(MenuScript::Flag_1);
            break;

        case 1:
            if (script->GetFlags(MenuScript::Flag_2))
                return 1;
            func_0203e0a0(unk, *unk2);
            func_ov017_021a27e8(resources);
            func_0203cfb4(unk);
            func_ov017_021a316c(resources);
            func_0203b4d8(resources, 8);
            func_0203b4d8(resources, 0x10);
            script->SetFlags(MenuScript::Flag_2);
            break;

        case 2:
            if (script->GetFlags(MenuScript::Flag_4))
                return 1;
            func_ov017_0219b938(resources);
            resources->allocators_[5].Reset();
            script->SetFlags(MenuScript::Flag_4);
            break;
    }
    return 1;
}

// Creates a heap in one of GameResources' allocators: the allocator (0, 1 or 2) and the heap's ID
static int Command_CreateHeap(ScriptValue* params, int count)
{
    GameResources* resources = func_ov017_0218b5b0();
    MenuHeap* heaps = func_ov017_021b2164()->GetHeap();
    SafeAllocator* parent;
    int allocator = params[0].ToInt();
    int id = params[1].ToInt();
    if (heaps->Find(id) != 0)
        return 0;

    parent = 0;
    switch (allocator)
    {
        case 0:
            parent = &resources->allocators_[0];
            break;
        case 1:
            parent = &resources->allocators_[7];
            break;
        case 2:
            parent = &resources->allocators_[5];
            break;
    }
    if (parent == 0)
        return 0;

    MenuHeap* heap = (MenuHeap*)parent->Allocate(sizeof(MenuHeap));
    if (heap == 0)
        return 0;

    heap->Initialize();
    heap->id_ = id;
    unsigned int size = parent->GetMaxPossibleAllocation();
    void* buffer = parent->Allocate(size);
    if (buffer == 0)
        return 0;

    heap->allocator_.CreateTypeB(buffer, size, 4);
    heaps->AddNext(heap);
    return 1;
}

// Creates a heap in another one: the other heap's ID, the heap's ID and its size (all the other heap by default)
// NONMATCHING: The compiler puts the new heap and its size in other registers, and the parameters
// in lower ones (55.4 %, with the variables declared in every order)
#ifdef NONMATCHING
static int Command_CreateChildHeap(ScriptValue* params, int count)
{
    int parentId = params[0].ToInt();
    int id = params[1].ToInt();
    MenuHeap* heaps = func_ov017_021b2164()->GetHeap();
    MenuHeap* parent = heaps->Find(parentId);
    if (parent == 0)
        return 0;
    if (heaps->Find(id) != 0)
        return 0;

    MenuHeap* heap = (MenuHeap*)parent->allocator_.Allocate(sizeof(MenuHeap));
    if (heap == 0)
        return 0;

    heap->Initialize();
    heap->id_ = id;
    unsigned int size;
    if (count >= 3)
        size = params[2].ToInt();
    else
        size = parent->allocator_.GetMaxPossibleAllocation();
    if (size == 0)
        return 0;

    void* buffer = parent->allocator_.Allocate(size);
    if (buffer == 0)
        return 0;

    heap->allocator_.CreateTypeB(buffer, size, 4);
    parent->AddChild(heap);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript7GetHeapEv(); // MenuScript::GetHeap
    void _ZN10MenuScript8FindHeapEi(); // MenuScript::FindHeap
    void _ZN13SafeAllocator11CreateTypeBEPvji(); // SafeAllocator::CreateTypeB
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN8MenuHeap10InitializeEv(); // MenuHeap::Initialize
    void _ZN8MenuHeap4FindEi(); // MenuHeap::Find
    void _ZN8MenuHeap8AddChildEPS_(); // MenuHeap::AddChild
    void _ZNK11ScriptValue5ToIntEv(); // ScriptValue::ToInt
    void _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(); // SafeAllocator::GetMaxPossibleAllocation
    void _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv(); // SafeAllocator::GetSizeWithLargestBlockRemoved
}

static asm int Command_CreateChildHeap(ScriptValue* params, int count)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    mov r9, r0
    mov r8, r1
    bl _ZNK11ScriptValue5ToIntEv
    mov r4, r0
    add r0, r9, #0x8
    bl _ZNK11ScriptValue5ToIntEv
    mov r5, r0
    bl func_ov017_021b2164
    bl _ZN10MenuScript7GetHeapEv
    mov r1, r4
    mov r4, r0
    bl _ZN8MenuHeap4FindEi
    movs r6, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r0, r4
    mov r1, r5
    bl _ZN8MenuHeap4FindEi
    cmp r0, #0x0
    movne r0, #0x0
    ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    add r0, r6, #0x4
    mov r1, #0x20
    bl _ZN13SafeAllocator8AllocateEj
    movs r7, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    bl _ZN8MenuHeap10InitializeEv
    str r5, [r7, #0x0]
    cmp r8, #0x3
    blt @L02184f5c
    add r0, r9, #0x10
    bl _ZNK11ScriptValue5ToIntEv
    b @L02184f64
@L02184f5c:
    add r0, r6, #0x4
    bl _ZNK13SafeAllocator24GetMaxPossibleAllocationEv
@L02184f64:
    mov r4, r0
    cmp r4, #0x0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r1, r4
    add r0, r6, #0x4
    bl _ZN13SafeAllocator8AllocateEj
    movs r1, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r2, r4
    add r0, r7, #0x4
    mov r3, #0x4
    bl _ZN13SafeAllocator11CreateTypeBEPvji
    mov r0, r6
    mov r1, r7
    bl _ZN8MenuHeap8AddChildEPS_
    mov r0, #0x1
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// Saves the state of the VRAM's managers in a heap: the heap and two IDs, which it doesn't use
static int Command_SaveVRAMState(ScriptValue* params, int count)
{
    int heapId = params[0].ToInt();
    params[1].ToInt();
    params[2].ToInt();
    MenuHeap* heap = func_ov017_021b2164()->FindHeap(heapId);
    if (heap == 0)
        return 0;

    MenuVRAMState* state = (MenuVRAMState*)heap->allocator_.Allocate(sizeof(MenuVRAMState));
    if (state == 0)
        return 0;

    func_0207df90(&state->state_);
    func_0207dfac(&state->state_);
    return 1;
}

static int Command_Nothing(ScriptValue* params, int count)
{
    return 1;
}

// The game's compiler didn't inline MenuObject_021f6f20's destructor, which IPA would: this does the same (and
// ToString() is written out, as the pragma would stop inlining it too)
#pragma dont_inline on
static int Command_06(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk = params[2].ToInt();
    const char* file = params[3].type_ == ScriptValue::Type_String ? params[3].value_.string_ : 0;
    if (file == 0)
        return 0;

    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f6f20* object = (MenuObject_021f6f20*)heap->allocator_.Allocate(sizeof(MenuObject_021f6f20));
    if (object == 0)
        return 0;

    MenuObject_021f6f20 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f6f20));
    if (!func_ov023_021f6f20(object, script, id, heapId, unk, file))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

#pragma dont_inline reset

MenuObject_021f6f20::MenuObject_021f6f20() : MenuObject(&data_ov023_021fe3e4)
{
    func_0204719c(unk_20);
}

MenuObject_021f6f20::~MenuObject_021f6f20()
{
    func_02047230(unk_20);
}

// Sets the position of an object: its ID, x and y
static int Command_SetPosition(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    Vector3fix position;
    position.x = params[1].ToFloat() * 4096.0f;
    position.y = params[2].ToFloat() * 4096.0f;
    position.z = 0;
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->SetPosition(&position);
    return 1;
}

static int Command_08(ScriptValue* params, int count)
{
    params[0].Set(func_ov023_021f6bc0(func_ov017_021b2164()->GetObjects()));
    return 1;
}

static int Command_09(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* file = params[2].ToString();
    if (file == 0)
        return 0;

    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f745c* object = (MenuObject_021f745c*)heap->allocator_.Allocate(sizeof(MenuObject_021f745c));
    if (object == 0)
        return 0;

    MenuObject_021f745c prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f745c));
    if (!func_ov023_021f745c(object, script, id, heapId, 0, file, unk3, unk4, unk5))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_0a(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToInt();
    int unk6 = params[6].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f7da0* object = (MenuObject_021f7da0*)heap->allocator_.Allocate(sizeof(MenuObject_021f7da0));
    if (object == 0)
        return 0;

    MenuObject_021f7da0 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f7da0));
    if (!func_ov023_021f7da0(object, script, id, heapId, unk2, unk3, unk4, unk5, unk6))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_0b(ScriptValue* params, int count)
{
    int unk1;
    int id = params[0].ToInt();
    unk1 = params[1].ToInt();
    short unk2 = params[2].ToInt();
    short unk3 = params[3].ToInt();
    short unk4 = params[4].ToInt();
    short unk5 = params[5].ToInt();
    unsigned char unk6 = params[6].ToInt();
    unsigned char unk7 = params[7].ToInt();
    bool unk8 = params[8].ToInt() != 0;
    MenuScript* script = func_ov017_021b2164();
    MenuObject* object = func_ov023_021f6880(script->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 6)
        return 0;

    func_ov023_021f7eb8(object, script, unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8);
    script->SetUnk1c8();
    return 1;
}

static int Command_0c(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 6)
        return 0;

    func_ov023_021f8120(object);
    return 1;
}

// Starts loading a file (data/<name>), if no other one is loading
static int Command_LoadFile(ScriptValue* params, int count)
{
    const char* name = params[0].ToString();
    if (name == 0)
        return 0;

    MenuScript* script = func_ov017_021b2164();
    if (script->GetLoadTask() >= 0)
        return 0;

    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    char path[0x50];
    sprintf(path, "data/%s", name);
    script->SetLoadTask(loader->QueueLoadFile(path, 0));
    return 1;
}

// Stops loading the file
static int Command_RemoveLoadedFile(ScriptValue* params, int count)
{
    MenuScript* script = func_ov017_021b2164();
    int task = script->GetLoadTask();
    BackgroundLoader::GetInstance()->RemoveTask(task);
    script->SetLoadTask(-1);
    return 1;
}

// Writes whether the file is loaded
static int Command_IsFileLoaded(ScriptValue* params, int count)
{
    int task = func_ov017_021b2164()->GetLoadTask();
    params[0].Set(BackgroundLoader::GetInstance()->GetTaskStatus(task) == 0 ? 1 : 0);
    return 1;
}

static int Command_10(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* file = params[2].ToString();
    if (file == 0)
        return 0;

    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    int unk = params[3].ToInt();
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fa298* object = (MenuObject_021fa298*)heap->allocator_.Allocate(sizeof(MenuObject_021fa298));
    if (object == 0)
        return 0;

    MenuObject_021fa298 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fa298));
    if (!func_ov023_021fa298(object, script, id, heapId, 0, file, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// Sets the enabled backgrounds and objects of a screen (0 is the main screen, 1 the sub screen)
static int Command_SetVisiblePlanes(ScriptValue* params, int count)
{
    int screen = params[0].ToInt();
    int planes = params[1].ToInt();
    if (screen == 0)
        DISPCNT = (DISPCNT & ~0x1f00) | (planes << 8);
    else if (screen == 1)
        DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | (planes << 8);
    return 1;
}

static int Command_12(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f8cf4* object = (MenuObject_021f8cf4*)heap->allocator_.Allocate(sizeof(MenuObject_021f8cf4));
    if (object == 0)
        return 0;

    MenuObject_021f8cf4 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f8cf4));
    if (!func_ov023_021f8cf4(object, script, id, heapId, unk3, unk2))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_13(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int id2 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuObjectList* objects = func_ov017_021b2164()->GetObjects();
    MenuObject* object = func_ov023_021f6880(objects, id);
    MenuObject* object2 = func_ov023_021f6880(objects, id2);
    if (object == 0 || object2 == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    return func_ov023_021f9b30(object, id2, unk3, unk2) ? 1 : 0;
}

static int Command_14(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuObject* object = func_ov023_021f6880(script->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    script->SetUnk1b0(id);
    return 1;
}

static int Command_15(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuScript* script = func_ov017_021b2164();
    if (func_ov023_021f6880(script->GetObjects(), id) == 0)
        return 0;

    script->SetUnk1b2(id);
    return 1;
}

static int Command_16(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToFloat();
    int unk6 = params[6].ToFloat();
    int unk7 = params[7].ToFloat();
    int unk8 = params[8].ToFloat();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f89f4* object = (MenuObject_021f89f4*)heap->allocator_.Allocate(sizeof(MenuObject_021f89f4));
    if (object == 0)
        return 0;

    MenuObject_021f89f4 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f89f4));
    if (!func_ov023_021f89f4(object, script, id, heapId, unk2, unk3, unk4, unk5, unk6, unk7, unk8))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_17(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk3c(value);
    return 1;
}

static int Command_CreateCursor(ScriptValue* params, int count)
{
    MenuScript* script = func_ov017_021b2164();
    MenuObjectList* objects = script->GetObjects();
    if (func_ov023_021f6880(objects, CURSOR_ID) != 0)
        return 0;

    int heapId = params[0].ToInt();
    int unk = params[1].ToInt();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f9ec8* object = (MenuObject_021f9ec8*)heap->allocator_.Allocate(sizeof(MenuObject_021f9ec8));
    if (object == 0)
        return 0;

    MenuObject_021f9ec8 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f9ec8));
    if (!func_ov023_021f9ec8(object, script, CURSOR_ID, heapId, unk))
        return 0;

    func_ov023_021f67ac(objects, object);
    return 1;
}

static int Command_CreateSprites(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* file = params[2].ToString();
    if (file == 0)
        return 0;

    int unk = params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fa760* object = (MenuObject_021fa760*)heap->allocator_.Allocate(sizeof(MenuObject_021fa760));
    if (object == 0)
        return 0;

    MenuObject_021fa760 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fa760));
    if (!func_ov023_021fa760(object, script, id, heapId, 0, file, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

MenuObject_021fa760::MenuObject_021fa760() : MenuObject(&data_ov023_021feb40) {}

static int Command_1a(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fad84* object = (MenuObject_021fad84*)heap->allocator_.Allocate(sizeof(MenuObject_021fad84));
    if (object == 0)
        return 0;

    MenuObject_021fad84 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fad84));
    if (!func_ov023_021fad84(object, script, id, heapId, unk2, unk3))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_1b(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fb2b0* object = (MenuObject_021fb2b0*)heap->allocator_.Allocate(sizeof(MenuObject_021fb2b0));
    if (object == 0)
        return 0;

    MenuObject_021fb2b0 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fb2b0));
    if (!func_ov023_021fb2b0(object, script, id, heapId, unk2, unk3))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_1c(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* file = params[2].ToString();
    if (file == 0)
        return 0;

    int unk = params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fb534* object = (MenuObject_021fb534*)heap->allocator_.Allocate(sizeof(MenuObject_021fb534));
    if (object == 0)
        return 0;

    MenuObject_021fb534 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fb534));
    if (!func_ov023_021fb534(object, script, id, heapId, file, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_1d(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->UnkC4(unk1, unk2, unk3);
    return 1;
}

static int Command_1e(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    Vector3fix position;
    position.x = params[1].ToFloat() * 4096.0f;
    position.y = params[2].ToFloat() * 4096.0f;
    position.z = params[3].ToFloat() * 4096.0f;
    int unk4 = params[4].ToFloat() * 4096.0f;
    int unk5 = params[5].ToFloat() * 4096.0f;
    MenuScript* script = func_ov017_021b2164();
    MenuObjectList* objects = script->GetObjects();
    if (func_ov023_021f6880(objects, id) == 0)
        return 0;

    MenuObject* cursor = func_ov023_021f6880(objects, CURSOR_ID);
    if (cursor == 0)
        return 0;

    func_ov023_021fa078(cursor, script, id, &position, unk4, unk5);
    return 1;
}

// The NitroSDK's functions that set the backgrounds' control registers, which the compiler didn't inline because
// Command_SetBGControl takes their addresses
static inline void G2_SetBG0Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG0CNT = (BG0CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) |
             (bgExtPltt << 13);
}

static inline void G2_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG1CNT = (BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) |
             (bgExtPltt << 13);
}

static inline void G2_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    BG2CNT = (BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

static inline void G2_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    BG3CNT = (BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

static inline void G2S_SetBG0Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG0CNTSUB = (BG0CNTSUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) |
                (bgExtPltt << 13);
}

static inline void G2S_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG1CNTSUB = (BG1CNTSUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) |
                (bgExtPltt << 13);
}

static inline void G2S_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    BG2CNTSUB = (BG2CNTSUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

static inline void G2S_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    BG3CNTSUB = (BG3CNTSUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

typedef void (*BGControlFunction)(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt);
typedef void (*BGControlTextFunction)(int screenSize, int colorMode, int screenBase, int charBase);

// Sets a background's control register: the screen, the background and the register's fields
static int Command_SetBGControl(ScriptValue* params, int count)
{
    int screen = params[0].ToInt();
    int bg = params[1].ToInt();
    int screenSize = params[2].ToInt();
    int colorMode = params[3].ToInt();
    int screenBase = params[4].ToInt();
    int charBase = params[5].ToInt();
    int bgExtPltt = params[6].ToInt();
    BGControlFunction functions[2][4] = {
        {G2_SetBG0Control, G2_SetBG1Control, (BGControlFunction)G2_SetBG2ControlText,
         (BGControlFunction)G2_SetBG3ControlText},
        {G2S_SetBG0Control, G2S_SetBG1Control, (BGControlFunction)G2S_SetBG2ControlText,
         (BGControlFunction)G2S_SetBG3ControlText},
    };
    BGControlFunction function = functions[screen][bg];
    if (bg < 2)
        function(screenSize, colorMode, screenBase, charBase, bgExtPltt);
    else
        ((BGControlTextFunction)function)(screenSize, colorMode, screenBase, charBase);
    return 1;
}

// The NitroSDK's functions that set the backgrounds' priorities
static inline void G2_SetBG0Priority(int priority)
{
    BG0CNT = (BG0CNT & ~3) | priority;
}

static inline void G2_SetBG1Priority(int priority)
{
    BG1CNT = (BG1CNT & ~3) | priority;
}

static inline void G2_SetBG2Priority(int priority)
{
    BG2CNT = (BG2CNT & ~3) | priority;
}

static inline void G2_SetBG3Priority(int priority)
{
    BG3CNT = (BG3CNT & ~3) | priority;
}

static inline void G2S_SetBG0Priority(int priority)
{
    BG0CNTSUB = (BG0CNTSUB & ~3) | priority;
}

static inline void G2S_SetBG1Priority(int priority)
{
    BG1CNTSUB = (BG1CNTSUB & ~3) | priority;
}

static inline void G2S_SetBG2Priority(int priority)
{
    BG2CNTSUB = (BG2CNTSUB & ~3) | priority;
}

static inline void G2S_SetBG3Priority(int priority)
{
    BG3CNTSUB = (BG3CNTSUB & ~3) | priority;
}

// Sets the priorities of a screen's backgrounds: the screen and the priority of each background from BG0
static int Command_SetBGPriorities(ScriptValue* params, int count)
{
    int screen = params++->ToInt();
    void (*functions[2][4])(int priority) = {
        {G2_SetBG0Priority, G2_SetBG1Priority, G2_SetBG2Priority, G2_SetBG3Priority},
        {G2S_SetBG0Priority, G2S_SetBG1Priority, G2S_SetBG2Priority, G2S_SetBG3Priority},
    };
    void (**function)(int priority) = functions[screen];
    for (count--; count != 0; count--)
        (*function++)(params++->ToInt());
    return 1;
}

// Sets up the alpha blending of a screen: the screen (0 is the main one) and ColorEffect_ConfigureAlphaBlend's
// parameters
static int Command_SetAlphaBlend(ScriptValue* params, int count)
{
    int screen = params[0].ToInt();
    int pixel1Source = params[1].ToInt();
    int pixel2Source = params[2].ToInt();
    int pixel1Alpha = params[3].ToInt();
    int pixel2Alpha = params[4].ToInt();
    if (screen == 0)
        ColorEffect_ConfigureAlphaBlend(0x4000050, pixel1Source, pixel2Source, pixel1Alpha, pixel2Alpha);
    else if (screen == 1)
        ColorEffect_ConfigureAlphaBlend(0x4001050, pixel1Source, pixel2Source, pixel1Alpha, pixel2Alpha);
    return 1;
}

struct MenuObjectParams_021fd1e0
{
    int unk_0;
    int unk_4;
};

struct MenuObjectFlags_021fd1e0
{
    bool unk_0;
    bool unk_1;
};

static int Command_22(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    MenuObjectParams_021fd1e0 values;
    values.unk_0 = params[2].ToInt();
    values.unk_4 = params[3].ToInt();
    MenuObjectFlags_021fd1e0 flags;
    flags.unk_0 = params[4].ToInt() != 0;
    flags.unk_1 = params[5].ToInt() != 0;
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fd1e0* object = (MenuObject_021fd1e0*)heap->allocator_.Allocate(sizeof(MenuObject_021fd1e0));
    if (object == 0)
        return 0;

    MenuObject_021fd1e0 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fd1e0));
    if (!func_ov023_021fd1e0(object, script, id, heapId, &values, &flags))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_23(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    Vector3fix position;
    position.x = params[1].ToFloat() * 4096.0f;
    position.y = params[2].ToFloat() * 4096.0f;
    position.z = 0;
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->SetPosition2(&position);
    return 1;
}

static int Command_24(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fba80* object = (MenuObject_021fba80*)heap->allocator_.Allocate(sizeof(MenuObject_021fba80));
    if (object == 0)
        return 0;

    MenuObject_021fba80 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fba80));
    if (!func_ov023_021fba80(object, script, id, heapId))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_25(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->UnkD0();
    return 1;
}

static int Command_26(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->UnkD4();
    return 1;
}

// Runs a native function of the menu
static int Command_RunCallback(ScriptValue* params, int count)
{
    int callback = params[0].ToInt();
    if (callback <= 0)
        return 0;

    func_ov017_021b2164()->RunCallback(callback);
    return 1;
}

static int Command_28(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk44(value);
    return 1;
}

static int Command_29(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToFloat();
    int unk4 = params[4].ToFloat();
    int unk5 = params[5].ToFloat();
    int unk6 = params[6].ToFloat();
    int unk7 = params[7].ToInt();
    int unk8 = params[8].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fbb64* object = (MenuObject_021fbb64*)heap->allocator_.Allocate(sizeof(MenuObject_021fbb64));
    if (object == 0)
        return 0;

    MenuObject_021fbb64 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fbb64));
    if (!func_ov023_021fbb64(object, script, id, heapId, unk2, unk3, unk4, unk5, unk6, unk7, unk8))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// NONMATCHING: The compiler assigns the registers of the parameters and of some variables in another order (80.8 %
// at best, with the variables declared at the top in every order)
#ifdef NONMATCHING
static int Command_2a(ScriptValue* params, int count)
{
    unsigned char unk4;
    MenuObjectList* objects;
    MenuScript* script;
    MenuHeap* heap;
    MenuObject_021fbd00* object;
    int unk;
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int otherId = params[3].ToInt();
    unk4 = 0;
    if (count - 4 != 0)
        unk4 = params[4].ToInt();

    script = func_ov017_021b2164();
    heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    object = (MenuObject_021fbd00*)heap->allocator_.Allocate(sizeof(MenuObject_021fbd00));
    if (object == 0)
        return 0;

    unk = 0;
    objects = script->GetObjects();
    MenuObject* other = func_ov023_021f6880(objects, otherId);
    if (other != 0)
        unk = other->Functions()->UnkE8();

    MenuObject_021fbd00 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fbd00));
    if (!func_ov023_021fbd00(object, script, id, heapId, unk2, unk, unk4))
        return 0;

    func_ov023_021f67ac(objects, object);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript7GetHeapEv(); // MenuScript::GetHeap
    void _ZN10MenuScript8FindHeapEi(); // MenuScript::FindHeap
    void _ZN13SafeAllocator11CreateTypeBEPvji(); // SafeAllocator::CreateTypeB
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN8MenuHeap10InitializeEv(); // MenuHeap::Initialize
    void _ZN8MenuHeap4FindEi(); // MenuHeap::Find
    void _ZN8MenuHeap8AddChildEPS_(); // MenuHeap::AddChild
    void _ZNK11ScriptValue5ToIntEv(); // ScriptValue::ToInt
    void _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(); // SafeAllocator::GetMaxPossibleAllocation
    void _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv(); // SafeAllocator::GetSizeWithLargestBlockRemoved
}

static asm int Command_2a(ScriptValue* params, int count)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x3cc
    sub sp, sp, #0x400
    mov r5, r0
    mov r4, r1
    bl _ZNK11ScriptValue5ToIntEv
    str r0, [sp, #0xc]
    add r0, r5, #0x8
    bl _ZNK11ScriptValue5ToIntEv
    mov r9, r0
    add r0, r5, #0x10
    bl _ZNK11ScriptValue5ToIntEv
    mov r10, r0
    add r0, r5, #0x18
    bl _ZNK11ScriptValue5ToIntEv
    mov r8, r0
    subs r0, r4, #0x4
    mov r4, #0x0
    beq @L02186a10
    add r0, r5, #0x20
    bl _ZNK11ScriptValue5ToIntEv
    and r4, r0, #0xff
@L02186a10:
    bl func_ov017_021b2164
    mov r1, r9
    mov r5, r0
    bl _ZN10MenuScript8FindHeapEi
    movs r6, r0
    moveq r0, #0x0
    beq @L02186b30
    add r0, r6, #0x4
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    ldr r1, =0x7bc
    add r0, r6, #0x4
    bl _ZN13SafeAllocator8AllocateEj
    movs r6, r0
    moveq r0, #0x0
    beq @L02186b30
    mov r0, r5
    mov r7, #0x0
    bl _ZN10MenuScript10GetObjectsEv
    mov r1, r8
    mov r11, r0
    bl func_ov023_021f6880
    cmp r0, #0x0
    beq @L02186a7c
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0xe8]
    blx r1
    mov r7, r0
@L02186a7c:
    add r8, sp, #0x30
    ldr r1, =data_ov023_021ff17c
    mov r0, r8
    str r1, [sp, #0x10]
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r8, #0x14
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r8, #0x28
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r8, #0x54
    bl func_020dfc2c
    add r0, r8, #0x6c
    bl func_020df80c
    add r0, r8, #0x7c
    bl func_020df80c
    add r0, r8, #0x8c
    bl func_020dfc2c
    add r0, r8, #0xa4
    bl func_020dfc2c
    add r0, r8, #0x12c
    bl func_0205a444
    ldr r2, =0x7bc
    mov r0, r6
    add r1, sp, #0x10
    bl memcpy
    str r10, [sp, #0x0]
    str r7, [sp, #0x4]
    ldr r2, [sp, #0xc]
    mov r1, r5
    mov r3, r9
    mov r0, r6
    str r4, [sp, #0x8]
    bl func_ov023_021fbd00
    cmp r0, #0x0
    bne @L02186b18
    add r0, sp, #0x15c
    bl func_0205a494
    mov r0, #0x0
    b @L02186b30
@L02186b18:
    mov r0, r11
    mov r1, r6
    bl func_ov023_021f67ac
    add r0, sp, #0x15c
    bl func_0205a494
    mov r0, #0x1
@L02186b30:
    add sp, sp, #0x3cc
    add sp, sp, #0x400
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static int Command_2b(ScriptValue* params, int count)
{
    int unk;
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    unk = 0;
    if (count - 2 != 0)
        unk = params[2].ToInt();

    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fbe08* object = (MenuObject_021fbe08*)heap->allocator_.Allocate(sizeof(MenuObject_021fbe08));
    if (object == 0)
        return 0;

    MenuObject_021fbe08 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fbe08));
    if (!func_ov023_021fbe08(object, script, id, heapId, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// Removes the objects of a heap and frees it
static int Command_ClearHeap(ScriptValue* params, int count)
{
    int heapId = params[0].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    func_ov023_021f6844(script->GetObjects(), heapId);
    heap->allocator_.Reset();
    return 1;
}

static int Command_2d(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    func_ov023_021f9c0c(object);
    return 1;
}

static int Command_2e(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    func_ov023_021f9c58(object, value);
    return 1;
}

static int Command_2f(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    func_ov023_021f9c60(object, value);
    return 1;
}

// Finishes the menu
static int Command_Finish(ScriptValue* params, int count)
{
    func_ov017_021b2164()->finished_ = true;
    return 1;
}

static int Command_31(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk4c(value);
    return 1;
}

static int Command_32(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk54(value);
    return 1;
}

// Writes whether the brightness is changing
static int Command_IsBrightnessChanging(ScriptValue* params, int count)
{
    params[0].Set(IsBrightnessTransitionActive(func_ov017_0218b5b0()));
    return 1;
}

// Like Command_2f, but it returns 0
static int Command_34(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    func_ov023_021f9c60(object, value);
    return 0;
}

static int Command_35(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int set = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    if (set != 0)
        object->flags_ |= 4;
    else
        object->flags_ &= ~4;
    return 1;
}

static int Command_36(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    const char* text = params[1].ToString();
    if (text == 0)
        return 0;

    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 2)
        return 0;

    func_ov023_021f79ec(object, text);
    return 1;
}

static int Command_37(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int set = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    if (set != 0)
        object->flags_ |= 1;
    else
        object->flags_ &= ~1;
    return 1;
}

// Allocates the buffer in a heap: the heap and the width and height in tiles of 32 bytes
static int Command_AllocateBuffer(ScriptValue* params, int count)
{
    int heapId = params[0].ToInt();
    MenuScript* script = func_ov017_021b2164();
    if (script->FindHeap(heapId) == 0)
        return 0;

    int width = params[1].ToInt();
    if (script->AllocateBuffer(heapId, (width * params[2].ToInt()) << 5) == 0)
        return 1;
    return 0;
}

static int Command_39(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 8)
        return 0;

    ((MenuObjectType8*)object)->unk_45_1 = unk1;
    ((MenuObjectType8*)object)->unk_42 = unk2;
    return 1;
}

static int Command_3a(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fc1f4* object = (MenuObject_021fc1f4*)heap->allocator_.Allocate(sizeof(MenuObject_021fc1f4));
    if (object == 0)
        return 0;

    MenuObject_021fc1f4 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fc1f4));
    if (!func_ov023_021fc1f4(object, script, id, heapId))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_3b(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    object->Functions()->Unk5c(value);
    return 1;
}

static int Command_3c(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToInt();
    int unk6 = params[6].ToInt();
    int unk7 = params[7].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fc408* object = (MenuObject_021fc408*)heap->allocator_.Allocate(sizeof(MenuObject_021fc408));
    if (object == 0)
        return 0;

    MenuObject_021fc408 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fc408));
    if (!func_ov023_021fc408(object, script, id, heapId, unk2, unk3, unk4, unk5, unk6, unk7))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// Sets flags of an object
static int Command_SetObjectFlags(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    unsigned char flags = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->flags_ |= flags;
    return 1;
}

// Clears flags of an object
static int Command_ClearObjectFlags(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    unsigned char flags = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->flags_ &= ~flags;
    return 1;
}

static int Command_3f(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    unsigned char value = params[1].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuObject* object = func_ov023_021f6880(script->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 6)
        return 0;

    func_ov023_021f8944(object, script, value, 1);
    return 1;
}

// Shows one of the names of an object in the message window
static int Command_ShowName(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int index = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 1;
    if (func_ov023_021f6f10(object) != 4)
        return 1;

    void* names = func_ov023_021fa598(object);
    if (names == 0)
        return 1;

    MessageSystem* messages = func_020421a0();
    func_0204500c(messages, func_02072a68(names, (short)index), 0, 0xe3);
    messages->busy_ = 1;
    messages->unk_19d2 = 1;
    return 1;
}

static int Command_41(ScriptValue* params, int count)
{
    MessageSystem* messages = func_020421a0();
    func_02043204(messages);
    func_02043124(messages);
    return 1;
}

static int Command_42(ScriptValue* params, int count)
{
    int state = func_020421a0()->unk_9a0;
    int result = 1;
    if (state == 0 || state == 3)
        result = 0;
    params[0].Set(result);
    return 1;
}

// Writes whether a message is shown
static int Command_IsMessageShown(ScriptValue* params, int count)
{
    params[0].Set(func_020421a0()->busy_);
    return 1;
}

static int Command_44(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
    {
        object->Functions()->Unk64(unk1);
        object->Functions()->Unk6c(unk2);
    }
    return 1;
}

// Sets the callbacks of the answers of the question (yes and no)
static int Command_SetAnswerCallbacks(ScriptValue* params, int count)
{
    int yes = params[0].ToInt();
    int no = params[1].ToInt();
    func_ov017_021b2164()->SetAnswerCallbacks(yes, no);
    return 1;
}

static int Command_46(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 1;
    if (func_ov023_021f6f10(object) != 1)
        return 1;

    func_ov023_021fb25c(object, unk1, unk2, unk3, unk4);
    return 1;
}

static int Command_47(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
        object->Functions()->UnkA4(value);
    return 1;
}

static int Command_48(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    object->Functions()->Unk74(value);
    return 1;
}

static int Command_49(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
    {
        object->Functions()->Unk84(unk1);
        object->Functions()->Unk8c(unk2);
    }
    return 1;
}

// NONMATCHING: The compiler assigns the registers of some variables and of the loops that construct the object
// in another order (62.3 %)
#ifdef NONMATCHING
static int Command_4a(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    params[3].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    int unk = ((int*)func_ov017_0218b5b0()->unknown_ptr_3b4c)[0x13];
    MenuObject_021fc518* object = (MenuObject_021fc518*)heap->allocator_.Allocate(sizeof(MenuObject_021fc518));
    if (object == 0)
        return 0;

    MenuObject_021fc518 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fc518));
    if (!func_ov023_021fc518(object, script, id, heapId, unk2, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript7GetHeapEv(); // MenuScript::GetHeap
    void _ZN10MenuScript8FindHeapEi(); // MenuScript::FindHeap
    void _ZN13SafeAllocator11CreateTypeBEPvji(); // SafeAllocator::CreateTypeB
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN8MenuHeap10InitializeEv(); // MenuHeap::Initialize
    void _ZN8MenuHeap4FindEi(); // MenuHeap::Find
    void _ZN8MenuHeap8AddChildEPS_(); // MenuHeap::AddChild
    void _ZNK11ScriptValue5ToIntEv(); // ScriptValue::ToInt
    void _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(); // SafeAllocator::GetMaxPossibleAllocation
    void _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv(); // SafeAllocator::GetSizeWithLargestBlockRemoved
}

static asm int Command_4a(ScriptValue* params, int count)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x7c
    sub sp, sp, #0x1800
    mov r4, r0
    bl _ZNK11ScriptValue5ToIntEv
    str r0, [sp, #0x8]
    add r0, r4, #0x8
    bl _ZNK11ScriptValue5ToIntEv
    mov r9, r0
    add r0, r4, #0x10
    bl _ZNK11ScriptValue5ToIntEv
    mov r10, r0
    add r0, r4, #0x18
    bl _ZNK11ScriptValue5ToIntEv
    bl func_ov017_021b2164
    mov r1, r9
    mov r11, r0
    bl _ZN10MenuScript8FindHeapEi
    movs r4, r0
    moveq r0, #0x0
    beq @L02187840
    add r0, r4, #0x4
    bl _ZNK13SafeAllocator30GetSizeWithLargestBlockRemovedEv
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r2, [r0, #0xb4c]
    ldr r1, =0x1870
    add r0, r4, #0x4
    ldr r8, [r2, #0x4c]
    bl _ZN13SafeAllocator8AllocateEj
    movs r5, r0
    moveq r0, #0x0
    beq @L02187840
    ldr r0, =data_ov023_021ff5b4
    add r7, sp, #0x2c
    str r0, [sp, #0xc]
@L021877b0:
    add r0, r7, #0x2b8
    add r6, r0, #0x400
    add r4, r7, #0x780
@L021877bc:
    mov r0, r6
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r6, r6, #0x14
    cmp r6, r4
    blo @L021877bc
    mov r0, r4
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    mov r0, r7
    bl func_ov023_021e4e8c
    add r0, sp, #0x1800
    add r7, r7, #0xc20
    add r0, r0, #0x6c
    cmp r7, r0
    blo @L021877b0
    ldr r2, =0x1870
    add r1, sp, #0xc
    mov r0, r5
    bl memcpy
    str r10, [sp, #0x0]
    ldr r2, [sp, #0x8]
    mov r0, r5
    mov r1, r11
    mov r3, r9
    str r8, [sp, #0x4]
    bl func_ov023_021fc518
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L02187840
    mov r0, r11
    bl _ZN10MenuScript10GetObjectsEv
    mov r1, r5
    bl func_ov023_021f67ac
    mov r0, #0x1
@L02187840:
    add sp, sp, #0x7c
    add sp, sp, #0x1800
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Sets the brightness of the main screen: the brightness and the duration (in milliseconds)
static int Command_SetMainBrightness(ScriptValue* params, int count)
{
    GameResources* resources = func_ov017_0218b5b0();
    int brightness = params[0].ToInt();
    SetMainBrightness(resources, brightness, params[1].ToInt() / 34);
    return 1;
}

// Sets the brightness of the sub screen: the brightness and the duration (in milliseconds)
static int Command_SetSubBrightness(ScriptValue* params, int count)
{
    GameResources* resources = func_ov017_0218b5b0();
    int brightness = params[0].ToInt();
    SetSubBrightness(resources, brightness, params[1].ToInt() / 34);
    return 1;
}

// Allocates the data in a heap: the heap and the size
static int Command_AllocateData(ScriptValue* params, int count)
{
    int heapId = params[0].ToInt();
    int size = params[1].ToInt();
    MenuScript* script = func_ov017_021b2164();
    if (script->FindHeap(heapId) == 0)
        return 0;

    script->AllocateData(heapId, size);
    return 1;
}

static int Command_4e(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f745c* object = (MenuObject_021f745c*)heap->allocator_.Allocate(sizeof(MenuObject_021f745c));
    if (object == 0)
        return 0;

    MenuObject_021f745c prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f745c));
    if (!func_ov023_021f745c(object, script, id, heapId, 0, 0, unk2, unk3, unk4))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// Creates a copy of an object of Command_06's class: the ID, the heap and the other object's ID (dont_inline: see
// Command_06)
#pragma dont_inline on
static int Command_4f(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int otherId = params[2].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuObjectList* objects = script->GetObjects();
    MenuObject* other = func_ov023_021f6880(objects, otherId);
    func_ov023_021f6f10(other);
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f6f20* object = (MenuObject_021f6f20*)heap->allocator_.Allocate(sizeof(MenuObject_021f6f20));
    if (object == 0)
        return 0;

    MenuObject_021f6f20 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f6f20));
    if (!func_ov023_021f6f20(object, script, id, heapId, 0, 0))
        return 0;

    void* source = func_ov023_021f7318(other);
    func_02048004(source, func_ov023_021f7318(object));
    func_ov023_021f7320(object);
    func_ov023_021f67ac(objects, object);
    return 1;
}

#pragma dont_inline reset
static int Command_50(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    const char* text = params[3].ToString();
    if (text == 0)
        return 0;

    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fcdd4* object = (MenuObject_021fcdd4*)heap->allocator_.Allocate(sizeof(MenuObject_021fcdd4));
    if (object == 0)
        return 0;

    MenuObject_021fcdd4 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fcdd4));
    if (!func_ov023_021fcdd4(object, script, id, heapId, unk2, text))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_51(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    signed char value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 1)
        return 0;

    func_ov023_021fb274(object, value);
    return 1;
}

static int Command_52(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
    {
        object->Functions()->Unk94(unk1);
        object->Functions()->Unk9c(unk2);
    }
    return 1;
}

static int Command_53(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int unk1 = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
        object->Functions()->UnkAc(unk1, unk2, unk3);
    return 1;
}

static int Command_54(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 7)
        return 0;

    func_ov023_021f9da0(object, value != 0);
    return 1;
}

static int Command_55(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 1)
        return 0;

    func_ov023_021fb284(object, value);
    return 1;
}

static int Command_56(ScriptValue* params, int count)
{
    func_ov017_021b2164()->SetUnk1b0(0);
    return 1;
}

// Creates an object of overlay 4's class
static int Command_57(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_02167820* object = (MenuObject_02167820*)heap->allocator_.Allocate(sizeof(MenuObject_02167820));
    if (object == 0)
        return 0;

    MenuObject_02167820 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_02167820));
    if (!func_ov004_02167820(object, script, id, heapId))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

// Sets the entries that start with the answers of the question (yes and no)
static int Command_SetAnswerEntries(ScriptValue* params, int count)
{
    int yes = params[0].ToInt();
    int no = params[1].ToInt();
    func_ov017_021b2164()->SetAnswerEntries(yes, no);
    return 1;
}

// The screen that the main engine draws on
enum GXDispSelect
{
    GX_DISP_SELECT_SUB_MAIN,
    GX_DISP_SELECT_MAIN_SUB,
};

// The NitroSDK's GX_SetDispSelect, which the compiler doesn't inline in this form
static inline void GX_SetDispSelect(GXDispSelect select)
{
    POWCNT = (unsigned short)((POWCNT & ~0x8000) | (select << 15));
}

// Makes the main engine draw on the top screen
static int Command_SwapScreens(ScriptValue* params, int count)
{
    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    return 1;
}

// Makes the main engine draw on the bottom screen
static int Command_UnswapScreens(ScriptValue* params, int count)
{
    GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
    return 1;
}

static int Command_5b(ScriptValue* params, int count)
{
    int result = 0;
    GameState* gameState = GameState::GetInstance();
    if (func_02011b50(gameState, 1))
    {
        if (func_02011b50(gameState, 2))
            result = 1;
        if (func_02011b50(gameState, 4))
            result = 2;
        if (func_02011b50(gameState, 8))
            result = 3;
        void* unk = func_0202ae18();
        if (func_0202b7d8() && func_0202ba00(unk) == 6)
            result = 4;
    }
    func_ov017_021d6134(params, result);
    return 1;
}

static int Command_5c(ScriptValue* params, int count)
{
    int value = params[0].ToInt();
    func_020421a0()->unk_99c = value;
    return 1;
}

// Maps VRAM banks to the main screen's backgrounds (the index of a combination), after saving the current ones
static int Command_MapMainBGBanks(ScriptValue* params, int count)
{
    func_ov017_021b2164()->SaveMainBanks();
    int index = params[0].ToInt();
    int banks[] = {0, 0x20, 0x40, 0x60, 0x10, 0x30, 0x70, 1, 2, 4, 8, 3, 6, 0xc, 7, 0xe, 0xf};
    MapVRAMBanksToMainBG(banks[index]);
    return 1;
}

// Maps VRAM banks to the sub screen's backgrounds (the index of a combination), after saving the current ones
static int Command_MapSubBGBanks(ScriptValue* params, int count)
{
    func_ov017_021b2164()->SaveSubBanks();
    int index = params[0].ToInt();
    int banks[] = {0, 4, 0x80, 0x180};
    MapVRAMBanksToSubBG(banks[index]);
    return 1;
}

// Maps the saved VRAM banks back to the main screen's backgrounds
static int Command_RestoreMainBGBanks(ScriptValue* params, int count)
{
    MapVRAMBanksToMainBG(func_ov017_021b2164()->mainBanks_);
    return 1;
}

// Maps the saved VRAM banks back to the sub screen's backgrounds
static int Command_RestoreSubBGBanks(ScriptValue* params, int count)
{
    MapVRAMBanksToSubBG(func_ov017_021b2164()->subBanks_);
    return 1;
}

static int Command_61(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk7c(value);
    return 1;
}

static int Command_62(ScriptValue* params, int count)
{
    int value = params[0].ToInt();
    func_020421a0()->unk_19ca = value != 0;
    return 1;
}

static int Command_63(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    int unk2 = params[2].ToInt();
    int unk3 = params[3].ToInt();
    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToInt();
    int unk6 = params[6].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fd320* object = (MenuObject_021fd320*)heap->allocator_.Allocate(sizeof(MenuObject_021fd320));
    if (object == 0)
        return 0;

    MenuObject_021fd320 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fd320));
    if (!func_ov023_021fd320(object, script, id, heapId, unk2, unk3, unk4, unk5, unk6))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_64(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->UnkA4(value);
    return 1;
}

// What Command_65 passes to func_ov023_021f6e90
struct MenuObjectValues
{
    unsigned char count_;
    short values_[8];
    short unk_12;
    short unk_14;
};

static int Command_65(ScriptValue* params, int count)
{
    MenuObjectValues values;
    VectorizedMemset(&values, 0, sizeof(values));
    values.unk_12 = -1;
    values.unk_14 = -1;
    int id = params++->ToInt();
    values.unk_12 = params++->ToInt();
    values.unk_14 = params++->ToInt();
    values.count_ = count - 3;
    for (int i = 0; i < values.count_; i++)
    {
        int value = params++->ToInt();
        if (i < 8)
            values.values_[i] = value;
    }
    func_ov023_021f6e90(func_ov017_021b2164()->GetObjects(), id, &values);
    return 1;
}

static int Command_66(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    func_ov023_021f6eb8(func_ov017_021b2164()->GetObjects(), id);
    return 1;
}

static int Command_67(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk24(1);
    return 1;
}

static int Command_68(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;

    object->Functions()->Unk34(value);
    return 1;
}

static int Command_69(ScriptValue* params, int count)
{
    params[0].Set(func_0209ca2c(data_02109bf4));
    return 1;
}

static int Command_6a(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object != 0)
        object->Functions()->UnkB0(value);
    return 1;
}

// Writes the answer to the question (0 is yes, 1 no)
static int Command_GetAnswer(ScriptValue* params, int count)
{
    params[0].Set(func_020457e0(func_020421a0()));
    return 1;
}

// Writes whether a button or the touch screen is pressed, and plays a sound then
static int Command_IsPressed(ScriptValue* params, int count)
{
    int pressed = 0;
    if (func_02012444(data_02114e30, 0x7f3) || data_02114e54[0x55] != 0)
    {
        func_0205eaa0(data_02108760, 1, 0);
        pressed = 1;
    }
    params[0].Set(pressed);
    return 1;
}

static int Command_6d(ScriptValue* params, int count)
{
    int state = func_020421a0()->unk_9a0;
    int result = 0;
    if (state == 3)
        result = 1;
    params[0].Set(result);
    return 1;
}

static int Command_6e(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* archive = params[2].ToString();
    if (archive == 0)
        return 0;

    const char* file = params[3].ToString();
    if (file == 0)
        return 0;

    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    int unk = params[4].ToInt();
    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fa298* object = (MenuObject_021fa298*)heap->allocator_.Allocate(sizeof(MenuObject_021fa298));
    if (object == 0)
        return 0;

    MenuObject_021fa298 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fa298));
    if (!func_ov023_021fa298(object, script, id, heapId, archive, file, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_6f(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* archive = params[2].ToString();
    if (archive == 0)
        return 0;

    const char* file = params[3].ToString();
    if (file == 0)
        return 0;

    int unk4 = params[4].ToInt();
    int unk5 = params[5].ToInt();
    int unk6 = params[6].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021f745c* object = (MenuObject_021f745c*)heap->allocator_.Allocate(sizeof(MenuObject_021f745c));
    if (object == 0)
        return 0;

    MenuObject_021f745c prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021f745c));
    if (!func_ov023_021f745c(object, script, id, heapId, archive, file, unk4, unk5, unk6))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_70(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int heapId = params[1].ToInt();
    const char* archive = params[2].ToString();
    if (archive == 0)
        return 0;

    const char* file = params[3].ToString();
    if (file == 0)
        return 0;

    int unk = params[4].ToInt();
    MenuScript* script = func_ov017_021b2164();
    MenuHeap* heap = script->FindHeap(heapId);
    if (heap == 0)
        return 0;

    heap->allocator_.GetSizeWithLargestBlockRemoved();
    MenuObject_021fa760* object = (MenuObject_021fa760*)heap->allocator_.Allocate(sizeof(MenuObject_021fa760));
    if (object == 0)
        return 0;

    MenuObject_021fa760 prototype;
    memcpy(object, &prototype, sizeof(MenuObject_021fa760));
    if (!func_ov023_021fa760(object, script, id, heapId, archive, file, unk))
        return 0;

    func_ov023_021f67ac(script->GetObjects(), object);
    return 1;
}

static int Command_71(ScriptValue* params, int count)
{
    int id = params[0].ToInt();
    int value = params[1].ToInt();
    MenuObject* object = func_ov023_021f6880(func_ov017_021b2164()->GetObjects(), id);
    if (object == 0)
        return 0;
    if (func_ov023_021f6f10(object) != 8)
        return 0;

    ((MenuObjectType8*)object)->unk_45_7 = value;
    return 1;
}

static ScriptCommand sCommands[] = {
    Command_SetBrightness,
    Command_01,
    Command_CreateHeap,
    Command_CreateChildHeap,
    Command_SaveVRAMState,
    Command_Nothing,
    Command_06,
    Command_SetPosition,
    Command_08,
    Command_09,
    Command_0a,
    Command_0b,
    Command_0c,
    Command_LoadFile,
    Command_RemoveLoadedFile,
    Command_IsFileLoaded,
    Command_10,
    Command_SetVisiblePlanes,
    Command_12,
    Command_13,
    Command_14,
    Command_15,
    Command_16,
    Command_17,
    Command_CreateCursor,
    Command_CreateSprites,
    Command_1a,
    Command_1b,
    Command_1c,
    Command_1d,
    Command_1e,
    Command_SetBGControl,
    Command_SetBGPriorities,
    Command_SetAlphaBlend,
    Command_22,
    Command_23,
    Command_24,
    Command_25,
    Command_26,
    Command_RunCallback,
    Command_28,
    Command_29,
    Command_2a,
    Command_2b,
    Command_ClearHeap,
    Command_2d,
    Command_2e,
    Command_2f,
    Command_Finish,
    Command_31,
    Command_32,
    Command_IsBrightnessChanging,
    Command_34,
    Command_35,
    Command_36,
    Command_37,
    Command_AllocateBuffer,
    Command_39,
    Command_3a,
    Command_3b,
    Command_3c,
    Command_SetObjectFlags,
    Command_ClearObjectFlags,
    Command_3f,
    Command_ShowName,
    Command_41,
    Command_42,
    Command_IsMessageShown,
    Command_44,
    Command_SetAnswerCallbacks,
    Command_46,
    Command_47,
    Command_48,
    Command_49,
    Command_4a,
    Command_SetMainBrightness,
    Command_SetSubBrightness,
    Command_AllocateData,
    Command_4e,
    Command_4f,
    Command_50,
    Command_51,
    Command_52,
    Command_53,
    Command_54,
    Command_55,
    Command_56,
    Command_57,
    Command_SetAnswerEntries,
    Command_SwapScreens,
    Command_UnswapScreens,
    Command_5b,
    Command_5c,
    Command_MapMainBGBanks,
    Command_MapSubBGBanks,
    Command_RestoreMainBGBanks,
    Command_RestoreSubBGBanks,
    Command_61,
    Command_62,
    Command_63,
    Command_64,
    Command_65,
    Command_66,
    Command_67,
    Command_68,
    Command_69,
    Command_6a,
    Command_GetAnswer,
    Command_IsPressed,
    Command_6d,
    Command_6e,
    Command_6f,
    Command_70,
    Command_71,
    0,
};

void SetMenuScriptCommands(ScriptEngine* engine)
{
    func_ov017_021d4cc0(engine, sCommands, 0x73);
}
