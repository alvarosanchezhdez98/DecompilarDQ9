#include "Scene/Overlay_13/SkillUpScreen.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "System/Cache.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include <std_library_functions.h>

// The touch screen
struct TouchPanel
{
    char unk_0[0x5c];
    // The screen is touched
    unsigned char touched_;
};

// What func_0205a3d0 returns
struct SpriteAnimationEntry
{
    char unk_0[4];
    short x_;
    short y_;
    char unk_8[0xd];
    unsigned char flags_;
};

// A sprite's OAM attributes
struct OamAttributes
{
    unsigned short attr0_;
    unsigned short attr1_;
    unsigned short attr2_;
};

extern "C"
{
    // The sound player
    extern char data_02108760[];
    // The pad
    extern char data_02114e30[];
    // The touch screen
    extern TouchPanel data_02114e54;

    // Returns whether the buttons are pressed, and repeated
    bool func_02012444(void* pad, int buttons);
    bool func_0201248c(void* pad, int buttons);
    void func_0201250c(void* pad);
    // Whether the rectangle is touched
    bool func_02012734(TouchPanel* touch, int x, int y, int width, int height);
    // Whether the touch screen was tapped
    bool func_02012aac(TouchPanel* touch);
    // The functions that write the control codes of a text
    void func_02041a28(char* text, int x);
    void func_02041a5c(char* text, int);
    void func_02041acc(char* text, int);
    void func_02041b70(char* text, int item, const char* itemText);
    void func_02041c08(char* text, int, int, int, int, int);
    void func_02041cc0(char* text, int);
    void func_02041d48(char* text, int, int, int, int);
    void func_02041d9c(char* text, int);
    void func_02041e70(char* text, int color);
    void func_02041ea4(char* text, int);
    void func_02041fac(char* text, const char* line, int);
    void func_02042058(char* text, const char* append);
    // Returns the width of a text
    int func_020420e8(const char* text, bool large);
    // The text system
    MessageSystem* func_020421a0();
    void* func_020421b0(unsigned char);
    void func_02043204(MessageSystem* messages);
    void func_0204359c(MessageSystem* messages, int);
    void func_020439b0(MessageSystem* messages, int);
    // Shows a message
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    void func_02046380();
    void func_020465c0(MessageSystem* messages, int, int);
    void func_020465d8(MessageSystem* messages, int, int);
    void func_020465f0(MessageSystem* messages, int, int);
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    int func_02046900(void* pac);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b0e8(BackgroundGraphics* graphics, void* characters);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204bc74(BackgroundGraphics* graphics, int, int, int, int, int, int);
    // The rectangle of a canvas' item
    void func_0204c610(Canvas* canvas, short item, short* x, short* y, short* width, short* height);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, unsigned int size);
    bool func_0204c7cc();
    bool func_0204c7e0();
    // A party member's data
    PartyMemberData* func_02053c6c(PartyMember* member);
    void func_0205a330(SpriteAnimationList* animations, int elapsed);
    void func_0205a370(SpriteAnimationList* animations, unsigned short animation);
    SpriteAnimationEntry* func_0205a3d0(SpriteAnimationList* animations, unsigned short animation);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205bc10(void*);
    void func_0205bc24(void*, int);
    void func_0205c77c(void*, int);
    void func_0205c790(TextMenu* menu);
    void func_0205c904(TextMenu* menu, int);
    void func_0205c96c(TextMenu* menu, int);
    void func_0205cb60(TextMenu* menu);
    int func_0205cb64(TextMenu* menu);
    void func_0205cb74(TextMenu* menu, const char* item);
    void func_0205cc50(TextMenu* menu, int, int);
    void func_0205cd28(TextMenu* menu);
    void func_0205cd94(TextMenu* menu);
    void func_0205ce94(TextMenu* menu);
    int func_0205cecc(TextMenu* menu);
    void func_0205cef8(TextWindow* window);
    void func_0205cf04(TextWindow* window);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int numCanvases);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    int func_0205d0e0(TextWindow* window, int);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, const unsigned char* colors, int);
    void func_0205d5d0(TextWindow* window, int, char* text, int, int);
    void func_0205d6a0(TextWindow* window, int);
    int func_0205d794(TextWindow* window);
    void func_0205d7a0(TextWindow* window);
    // A window's canvases
    Canvas* func_0205d81c(TextWindow* window, int canvas);
    Canvas* func_0205d888(TextWindow* window);
    Canvas* func_0205d8c4(TextWindow* window);
    int func_0205d97c(TextWindow* window);
    bool func_0205da38(TextWindow* window, int);
    void func_0205da88(TextWindow* window, int, int, int);
    void func_0205de24(TextWindow* window, int, int);
    void func_0205deb4(TextWindow* window, unsigned char, unsigned char);
    void func_0205dee8(TextWindow* window, int);
    // Plays a sound effect
    void func_0205eaa0(void* sound, int effect, int);
    void func_02074af4(void*);
    void func_02074b64(void*);
    void func_02074bd0(void*);
    void func_02074bf4(void*);
    // The music player
    void* func_02094a00();
    void func_02094b30(void* music, int, int);
    void func_02094b3c(void* music, int);
    bool func_02094b4c(void* music);
    // The skill of a vocation
    signed char func_020dd11c(unsigned char vocation, unsigned char index);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, short id);
    const char* func_020e51cc(int id);
}

// The palettes of the backgrounds' characters, and the backgrounds' priorities?
static const unsigned char sBackgroundPriorities[2] = {1, 0};
static const unsigned char sBackgroundPalettes[2] = {1, 2};

const int SkillPointMenu::sConfirmButtons = 0x601;
const unsigned int SkillPointMenu::sIconSize = 0x80;

// Whether an item of the window's first canvas is touched
static bool IsItemTouched(TextWindow* window, int item)
{
    if (data_02114e54.touched_)
    {
        Canvas* canvas = func_0205d81c(window, 0);
        if (canvas != NULL)
        {
            short canvasX = canvas->x_;
            short canvasY = canvas->y_;
            short x;
            short y;
            short width;
            short height;
            func_0204c610(canvas, item, &x, &y, &width, &height);
            return func_02012734(&data_02114e54, x + (short)(canvasX * 8), y + (short)(canvasY * 8), width, height);
        }
    }
    return false;
}

static Sprite* GetSprite(SpriteRenderer* renderer, unsigned short index)
{
    Sprite* sprite = NULL;
    if (renderer->sprites_ != NULL && index < renderer->capacity_)
        sprite = &renderer->sprites_[index];
    return sprite;
}

// NONMATCHING: the C matches 99.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original loads subScreen_ again right after storing it, while the compiler tests the stored value. Neither the
// flag's types, the forms of the store and the test, inline functions around them nor other optimization levels and
// compiler versions change it.
#ifdef NONMATCHING
void SkillPointMenu::Initialize(SkillPointMenuParent* parent)
{
    unk_30 = 0;
    unk_31 = 0;
    subScreen_ = parent != NULL;
    if (subScreen_)
    {
        func_02074b64(unk_20);
        planes_ = (DISPCNTSUB & 0x1f00) >> 8;
    }
    else
    {
        func_02074af4(unk_20);
        planes_ = (DISPCNT & 0x1f00) >> 8;
        DISPCNT = (DISPCNT & ~0x1f00) | 0x100;
    }
    func_0205cfd4(&window_);
    func_0205c790(&menu_);
    if (subScreen_)
    {
        TextWindow* window = &parent->window_;
        window_.base_.frame_ = window->base_.frame_;
        window_.base_.cursor_ = window->base_.cursor_;
        window_.base_.unk_94 = window->base_.unk_94;
        window_.base_.unk_95 = window->base_.unk_95;
        window_.base_.unk_96 = window->base_.unk_96;
        window_.base_.unk_97 = window->base_.unk_97;
        window_.background_ = window->background_;
        window_.unk_9c = window->unk_9c;
        window_.width_ = window->width_;
        window_.height_ = window->height_;
        window_.unk_a4 = window->unk_a4;
        window_.unk_a6 = window->unk_a6;
        window_.unk_a8 = window->unk_a8;
        window_.unk_aa = window->unk_aa;
        window_.unk_ac = window->unk_ac;
        window_.unk_ae = window->unk_ae;
        window_.unk_b0 = window->unk_b0;
        window_.unk_b1 = window->unk_b1;
        window_.unk_b2 = window->unk_b2;
        window_.unk_b3 = window->unk_b3;
        window_.unk_b4 = window->unk_b4;
        window_.unk_b5 = window->unk_b5;
        window_.unk_b6 = window->unk_b6;
        window_.unk_b7 = window->unk_b7;
        window_.unk_b8 = window->unk_b8;
        window_.unk_b9 = window->unk_b9;
        window_.unk_ba = window->unk_ba;
        window_.unk_bb = window->unk_bb;
    }
    for (int i = 0; i < 2; i++)
    {
        func_0204af64(&backgrounds_[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        func_0204c684(&canvases_[i]);
    }
    textAllocator_.ResetAllocatorPointer();
    func_020dfc40(&texts_);
    allocator_.ResetAllocatorPointer();
    for (int i = 0; i < 3; i++)
    {
        unk_638[i] = 0;
    }
    elapsed_ = 0;
    spriteRenderer_ = NULL;
    cursorAnimation_ = 0xff;
    nameEnd_ = 0;
    state_ = State_Load;
    previousState_ = State_Load;
    step_ = 0;
    stateChanged_ = false;
    ticks_ = 0;
    windowInput_ = 0;
    previousWindowInput_ = 0;
    selection_ = 0;
    confirmSelection_ = 0;
    apply_ = false;
    unk_665 = 0;
    availablePoints_ = 0;
    remainingPoints_ = 0;
    maxPoints_ = 0;
    level_ = 0;
    unk_6b4 = 0;
    text_ = NULL;
    status_ = NULL;
    vocation_ = 0;
    flags_ = 0;
    unk_6b8 = 0;
    unk_6be = 0;
    unk_6c0 = 0;
    unk_6c2 = 0;
    unk_6c4 = 0;
    unk_6c6 = 0;
    unk_6c8 = 0;
    unk_6ca = 0;
    for (int i = 0; i < 5; i++)
    {
        points_[i] = 0;
    }
    for (int i = 0; i < 5; i++)
    {
        addedPoints_[i] = 0;
    }
    for (int i = 0; i < 5; i++)
    {
        locked_[i] = 1;
    }
    canvasPixels_ = subScreen_ ? parent->unk_178 : NULL;
    for (int i = 0; i < 5; i++)
    {
        skills_[i] = 0;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
}

asm void SkillPointMenu::Initialize(SkillPointMenuParent* parent)
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    mov r5, r0
    mov r0, #0x0
    strb r0, [r5, #0x30]
    movs r4, r1
    strb r0, [r5, #0x31]
    movne r0, #0x1
    strb r0, [r5, #0x640]
    ldrb r0, [r5, #0x640]
    cmp r0, #0x0
    add r0, r5, #0x20
    beq @L021843ac
    bl func_02074b64
    ldr r0, =0x4001000
    ldr r0, [r0, #0x0]
    and r0, r0, #0x1f00
    mov r0, r0, lsr #0x8
    str r0, [r5, #0x34]
    b @L021843d4
@L021843ac:
    bl func_02074af4
    mov r1, #0x4000000
    ldr r0, [r1, #0x0]
    and r0, r0, #0x1f00
    mov r0, r0, lsr #0x8
    str r0, [r5, #0x34]
    ldr r0, [r1, #0x0]
    bic r0, r0, #0x1f00
    orr r0, r0, #0x100
    str r0, [r1, #0x0]
@L021843d4:
    add r0, r5, #0x38
    bl func_0205cfd4
    add r0, r5, #0x3d4
    bl func_0205c790
    ldrb r0, [r5, #0x640]
    cmp r0, #0x0
    beq @L021844fc
    add r12, r4, #0x188
    add lr, r12, #0x4
    add r7, r5, #0x3c
    mov r6, #0x5
@L02184400:
    ldmia lr!, {r0, r1, r2, r3}
    stmia r7!, {r0, r1, r2, r3}
    subs r6, r6, #0x1
    bne @L02184400
    add lr, r12, #0x54
    add r7, r5, #0x8c
    mov r6, #0x4
@L0218441c:
    ldmia lr!, {r0, r1, r2, r3}
    stmia r7!, {r0, r1, r2, r3}
    subs r6, r6, #0x1
    bne @L0218441c
    ldrb r0, [r12, #0x94]
    strb r0, [r5, #0xcc]
    ldrb r0, [r12, #0x95]
    strb r0, [r5, #0xcd]
    ldrb r0, [r12, #0x96]
    strb r0, [r5, #0xce]
    ldrb r0, [r12, #0x97]
    strb r0, [r5, #0xcf]
    ldr r0, [r12, #0x98]
    str r0, [r5, #0xd0]
    ldr r0, [r12, #0x9c]
    str r0, [r5, #0xd4]
    ldrsh r0, [r12, #0xa0]
    strh r0, [r5, #0xd8]
    ldrsh r0, [r12, #0xa2]
    strh r0, [r5, #0xda]
    ldrsh r0, [r12, #0xa4]
    strh r0, [r5, #0xdc]
    ldrsh r0, [r12, #0xa6]
    strh r0, [r5, #0xde]
    ldrsh r0, [r12, #0xa8]
    strh r0, [r5, #0xe0]
    ldrsh r0, [r12, #0xaa]
    strh r0, [r5, #0xe2]
    ldrsh r0, [r12, #0xac]
    strh r0, [r5, #0xe4]
    ldrsh r0, [r12, #0xae]
    strh r0, [r5, #0xe6]
    ldrb r0, [r12, #0xb0]
    strb r0, [r5, #0xe8]
    ldrb r0, [r12, #0xb1]
    strb r0, [r5, #0xe9]
    ldrb r0, [r12, #0xb2]
    strb r0, [r5, #0xea]
    ldrb r0, [r12, #0xb3]
    strb r0, [r5, #0xeb]
    ldrb r0, [r12, #0xb4]
    strb r0, [r5, #0xec]
    ldrb r0, [r12, #0xb5]
    strb r0, [r5, #0xed]
    ldrb r0, [r12, #0xb6]
    strb r0, [r5, #0xee]
    ldrb r0, [r12, #0xb7]
    strb r0, [r5, #0xef]
    ldrb r0, [r12, #0xb8]
    strb r0, [r5, #0xf0]
    ldrb r0, [r12, #0xb9]
    strb r0, [r5, #0xf1]
    ldrb r0, [r12, #0xba]
    strb r0, [r5, #0xf2]
    ldrb r0, [r12, #0xbb]
    strb r0, [r5, #0xf3]
@L021844fc:
    mov r7, #0x0
    add r6, r5, #0xf4
    b @L02184514
@L02184508:
    add r0, r6, r7, lsl #0x5
    bl func_0204af64
    add r7, r7, #0x1
@L02184514:
    cmp r7, #0x2
    blt @L02184508
    mov r8, #0x0
    add r7, r5, #0x134
    mov r6, #0xe0
    b @L02184538
@L0218452c:
    mla r0, r8, r6, r7
    bl func_0204c684
    add r8, r8, #0x1
@L02184538:
    cmp r8, #0x3
    blt @L0218452c
    add r0, r5, #0x20c
    add r0, r0, #0x400
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r5, #0x620
    bl func_020dfc40
    mov r0, r5
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    mov r2, #0x0
    mov r1, r2
    b @L02184574
@L02184568:
    add r0, r5, r2
    strb r1, [r0, #0x638]
    add r2, r2, #0x1
@L02184574:
    cmp r2, #0x3
    blt @L02184568
    mov r2, #0x0
    str r2, [r5, #0x14]
    str r2, [r5, #0x18]
    mov r0, #0xff
    strh r0, [r5, #0x1c]
    strh r2, [r5, #0x1e]
    strb r2, [r5, #0x63c]
    strb r2, [r5, #0x63d]
    strb r2, [r5, #0x63e]
    strb r2, [r5, #0x63f]
    str r2, [r5, #0x644]
    str r2, [r5, #0x648]
    str r2, [r5, #0x64c]
    str r2, [r5, #0x65c]
    str r2, [r5, #0x660]
    strb r2, [r5, #0x664]
    strb r2, [r5, #0x665]
    str r2, [r5, #0x668]
    str r2, [r5, #0x66c]
    str r2, [r5, #0x670]
    str r2, [r5, #0x6b0]
    strb r2, [r5, #0x6b4]
    str r2, [r5, #0x658]
    str r2, [r5, #0x6a4]
    strb r2, [r5, #0x6a8]
    strb r2, [r5, #0x6bc]
    str r2, [r5, #0x6b8]
    add r0, r5, #0x600
    strh r2, [r0, #0xbe]
    strh r2, [r0, #0xc0]
    strh r2, [r0, #0xc2]
    strh r2, [r0, #0xc4]
    strh r2, [r0, #0xc6]
    strh r2, [r0, #0xc8]
    strh r2, [r0, #0xca]
    mov r1, r2
    b @L0218461c
@L02184610:
    add r0, r5, r2, lsl #0x2
    str r1, [r0, #0x674]
    add r2, r2, #0x1
@L0218461c:
    cmp r2, #0x5
    blt @L02184610
    mov r2, #0x0
    mov r1, r2
    b @L0218463c
@L02184630:
    add r0, r5, r2, lsl #0x2
    str r1, [r0, #0x688]
    add r2, r2, #0x1
@L0218463c:
    cmp r2, #0x5
    blt @L02184630
    mov r2, #0x0
    mov r1, #0x1
    b @L0218465c
@L02184650:
    add r0, r5, r2
    strb r1, [r0, #0x69c]
    add r2, r2, #0x1
@L0218465c:
    cmp r2, #0x5
    blt @L02184650
    ldrb r0, [r5, #0x640]
    mov r2, #0x0
    mov r1, r2
    cmp r0, #0x0
    ldrne r0, [r4, #0x178]
    moveq r0, #0x0
    str r0, [r5, #0x654]
    b @L02184690
@L02184684:
    add r0, r5, r2
    strb r1, [r0, #0x6a9]
    add r2, r2, #0x1
@L02184690:
    cmp r2, #0x5
    blt @L02184684
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
#endif

void SkillPointMenu::Finish()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    func_020421a0()->unk_19be = 0;
    if (subScreen_)
    {
        func_02074bf4(unk_20);
        func_0205d6a0(&window_, 1);
        func_0205d1e0(&window_);
        func_0205d274(&window_);
        func_0205d2bc(&window_);
    }
    else
    {
        func_02074bd0(unk_20);
        func_0205d1e0(&window_);
        func_0205d274(&window_);
        func_0205d2bc(&window_);
        func_0205d048(&window_);
        if (canvasPixels_ != NULL)
        {
            memset(canvasPixels_, 0, 0x20);
            CleanInvalidateCacheRange(canvasPixels_, 0x20);
            LoadToMainBG1CharacterData(canvasPixels_, 0, 0x20);
        }
        DISPCNT = (DISPCNT & ~0x1f00) | (planes_ << 8);
    }
    if (textAllocator_.GetSignedAllocator() != NULL)
        textAllocator_.Destroy();
    if (allocator_.GetSignedAllocator() != NULL)
        allocator_.Destroy();
    state_ = State_End;
}

unsigned char SkillPointMenu::Update(int elapsed)
{
    elapsed_ = elapsed;
    GameState* gameState = GameState::GetInstance();
    ticks_ = gameState->GetTickCount();
    Canvas* canvas = func_0205d888(&window_);
    if (canvas != NULL && func_0204c7cc() && !(canvas->flags_ & 2))
        func_0205bc24(&window_.base_.frame_, -1);
    windowInput_ = func_0205d0e0(&window_, ticks_);
    func_0205c904(&menu_, ticks_);
    SpriteAnimationList* animations = (SpriteAnimationList*)func_020421a0()->unk_2e0;
    if (animations != NULL)
        func_0205a330(animations, gameState->GetTickCount());
    if (stateChanged_)
    {
        if (subScreen_)
            func_0205bc10(&window_.base_.frame_);
        if (state_ == State_Allocate)
        {
            window_.unk_b1 = 0;
            window_.base_.frame_.unk_4 = 1;
            window_.base_.cursor_.unk_4 = 1;
            func_0205ba68(&window_.base_.frame_, 1, 6, 0);
            func_0205ba68(&window_.base_.cursor_, 1, 6, 0);
            func_0205bacc(&window_.base_.frame_, 6);
            func_0205bacc(&window_.base_.cursor_, 6);
            int selection = selection_;
            func_0205bcdc(&window_.base_.frame_, selection);
            func_0205bb04(&window_.base_.cursor_, selection);
            RefreshPoints();
        }
        if (state_ == State_Confirm && subScreen_)
        {
            window_.unk_b1 = 3;
            window_.base_.frame_.unk_4 = 1;
            window_.base_.cursor_.unk_4 = 1;
            func_0205ba68(&window_.base_.frame_, 1, 2, 0);
            func_0205ba68(&window_.base_.cursor_, 1, 2, 0);
            func_0205bacc(&window_.base_.frame_, 2);
            func_0205bacc(&window_.base_.cursor_, 2);
            func_0205bcdc(&window_.base_.frame_, 0);
            func_0205bb04(&window_.base_.cursor_, 0);
        }
        stateChanged_ = false;
        return state_;
    }
    switch (state_)
    {
    case State_Load:
        Load();
        break;
    case State_Allocate:
        UpdateAllocate();
        break;
    case State_Message:
        if (subScreen_)
            UpdateMessageSub();
        else
            UpdateMessageMain();
        break;
    case State_Confirm:
    case State_ConfirmApply:
        if (subScreen_)
            UpdateConfirmSub();
        else
            UpdateConfirmMain();
        break;
    case State_Finish:
        Finish();
        break;
    }
    for (int i = 0; i < 4; i++)
    {
        func_0205deb4(&window_, i, unk_638[i]);
    }
    stateChanged_ = state_ != previousState_;
    previousState_ = state_;
    return state_;
}

void SkillPointMenu::Draw()
{
    if (state_ == State_Load || state_ == State_Finish || state_ == State_End)
        return;
    if (state_ == State_Confirm || state_ == State_ConfirmApply)
        func_0205c96c(&menu_, 0);
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    if (subScreen_)
        func_0205da88(&window_, 0, 2, 0);
    else
        func_0205da88(&window_, 1, 2, 1);
    func_0205d274(&window_);
    DrawCursor();
    DrawIcon();
}

void SkillPointMenu::UpdateMessage()
{
    if (state_ != State_Load && state_ != State_Finish && state_ != State_End)
    {
        GameState* gameState = GameState::GetInstance();
        MessageSystem* messages = func_020421a0();
        func_0204359c(messages, gameState->GetTickCount());
        func_020439b0(messages, 0);
        func_0205d2bc(&window_);
        func_0205cb60(&menu_);
    }
}

void SkillPointMenu::SetMember(PartyMember* member)
{
    if (member == NULL)
        return;
    PartyMemberData* data = func_02053c6c(member);
    status_ = member->status_;
    availablePoints_ = remainingPoints_ = data->unspentSkillPoints_;
    vocation_ = data->vocation_;
    level_ = data->levels_[vocation_];
    unk_6b8 = data->unk_186[vocation_];
    unk_6c0 = member->status_->unk_30;
    unk_6c4 = member->status_->unk_32;
    unk_6c6 = member->status_->unk_34;
    unk_6c8 = member->status_->unk_36;
    unk_6ca = member->status_->unk_38;
    if (subScreen_)
    {
        unk_6be = member->unk_138[0];
        unk_6c2 = member->unk_138[1];
    }
    else
    {
        unk_6be = member->unk_130[2];
        unk_6c2 = member->unk_130[3];
    }
    if (unk_6b8 != 0)
        unk_6b4 = 1;
    maxPoints_ = 100;
    for (int i = 0; i < 5; i++)
    {
        skills_[i] = func_020dd11c(vocation_, i);
        locked_[i] = 0;
        points_[i] = data->skillPoints_[skills_[i]];
    }
}

void SkillPointMenu::Apply(PartyMember* member)
{
    if (member == NULL || !apply_)
        return;
    PartyMemberData* data = func_02053c6c(member);
    data->unspentSkillPoints_ = remainingPoints_;
    for (int i = 0; i < 5; i++)
    {
        data->skillPoints_[skills_[i]] = points_[i] + addedPoints_[i];
    }
}

void SkillPointMenu::Setup(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    if (subScreen_)
    {
        textAllocator_.CreateTypeA(allocator->Allocate(0xc00), 0xc00);
        return;
    }
    unsigned int size = allocator->GetMaxPossibleAllocation();
    allocator_.CreateTypeA(allocator->Allocate(size), size);
    allocator_.Reset();
    textAllocator_.CreateTypeA(allocator_.Allocate(0xc00), 0xc00);
}

void SkillPointMenu::Load()
{
    if (state_ != State_Load)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (subScreen_)
    {
        if (step_ == 0)
        {
            task_ = loader->QueueLoadFileInGP2("data/bin/menu/str_su.gp2", "str_su_<LG>.nat", NULL);
            step_++;
        }
        else if (step_ == 1)
        {
            if (loader->GetTaskStatus(task_))
            {
                void* file;
                unsigned int size;
                loader->GetLoadedFileByID(task_, &file, &size);
                textAllocator_.Reset();
                func_020dfec0(&texts_, &textAllocator_, file, size);
                loader->RemoveTask(task_);
                task_ = -1;
                step_++;
            }
        }
        else if (step_ == 2)
        {
            text_ = (char*)func_020421a0()->unk_5c;
            BG2CNTSUB = (BG2CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
            BG0CNTSUB = (BG0CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
            BG1CNTSUB = (BG1CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
            DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1700;
            func_0205cef8(&window_);
            func_0205cf04(&window_);
            OpenPointsWindow();
            OpenMemberWindow();
            step_ = 0;
            state_ = State_Allocate;
        }
    }
    else
    {
        if (step_ == 0)
        {
            void* music = func_02094a00();
            func_02094b3c(music, 0xc);
            func_02094b30(music, 0x1f7, 0);
            step_++;
        }
        else if (step_ == 1)
        {
            if (func_02094b4c(func_02094a00()))
            {
                text_ = (char*)func_020421a0()->unk_5c;
                BackgroundGraphics* background = backgrounds_;
                for (int i = 0; i < 2; background++, i++)
                {
                    func_0204b11c(background, 0);
                    background->unk_1c_0_ = 0;
                    background->unk_1c_4_ = sBackgroundPalettes[i];
                    func_0204b5b4(background, sBackgroundPriorities[i]);
                    func_0204b12c(background, &allocator_);
                    func_0204b5e8(background, 0, 0);
                }
                BG1CNT = (BG1CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1d << 8);
                BG2CNT = (BG2CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1e << 8);
                ColorEffect_ConfigureAlphaBlend(0x04000050, BLEND_TARGET_BG1, BLEND_TARGET_BG0, 0xa, 6);
                task_ = loader->QueueLoadFile("data/ani/bg_tm.pac", NULL);
                step_++;
            }
        }
        else if (step_ == 2)
        {
            if (loader->GetTaskStatus(task_))
            {
                void* name = NULL;
                void* file;
                unsigned int size;
                void* files[2];
                unsigned int sizes[2];
                loader->GetLoadedFileByID(task_, &file, &size);
                int numFiles = func_02046900(file);
                for (int i = 0; i < numFiles; i++)
                {
                    files[i] = func_020467f0(file, i, &name, &sizes[i]);
                }
                for (int i = 0; i < numFiles; i++)
                {
                    if (files[i] != NULL)
                        func_0204b174(&backgrounds_[1], files[i], &allocator_, sizes[i]);
                }
                loader->RemoveTask(task_);
                task_ = -1;
                func_0204bc74(&backgrounds_[0], 0, 0, 0, 0x20, 0x19, 0);
                func_0204b0e8(&backgrounds_[0], NULL);
                func_0204bc74(&backgrounds_[1], 0, 0, 0, 0x20, 0x19, 0);
                func_0204b0e8(&backgrounds_[1], NULL);
                canvasPixels_ = allocator_.Allocate(0x3c00);
                for (int i = 0; i < 3; i++)
                {
                    func_0204c7a8(&canvases_[i], &allocator_, canvasPixels_, 0x380);
                    canvases_[i].background_ = &backgrounds_[1];
                }
                window_.background_ = &backgrounds_[0];
                window_.unk_b2 = 2;
                func_0205cf78(&window_, canvases_, 3);
                task_ = loader->QueueLoadFileInGP2("data/bin/menu/str_su.gp2", "str_su_<LG>.nat", NULL);
                step_++;
            }
        }
        else if (step_ == 3)
        {
            if (loader->GetTaskStatus(task_))
            {
                void* file;
                unsigned int size;
                loader->GetLoadedFileByID(task_, &file, &size);
                textAllocator_.Reset();
                func_020dfec0(&texts_, &textAllocator_, file, size);
                loader->RemoveTask(task_);
                task_ = -1;
                step_++;
            }
        }
        else if (step_ == 4)
        {
            BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY) | 2;
            BG1CNT = (BG1CNT & ~BGCNT_MASK_PRIORITY) | 1;
            BG2CNT = BG2CNT & ~BGCNT_MASK_PRIORITY;
            DISPCNT = (DISPCNT & ~0x1f00) | 0x1700;
            func_0205cef8(&window_);
            func_0205cf04(&window_);
            OpenPointsWindow();
            OpenMemberWindow();
            step_ = 0;
            state_ = State_Allocate;
        }
    }
}

void SkillPointMenu::OpenPointsWindow()
{
    func_0205de24(&window_, 0, 2);
    window_.width_ = 0x1e;
    window_.height_ = 0xd;
    window_.unk_a4 = 1;
    window_.unk_a6 = 0;
    window_.unk_a8 = 0;
    window_.unk_aa = 5;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xd;
    window_.unk_b1 = 0;
    if (subScreen_)
        window_.unk_b5 = 0;
    else
        window_.unk_b5 = 1;
    memset(text_, 0, 0x960);
    WritePoints(text_);
    func_0205d304(&window_, text_, 0, 0, 0, 1, NULL, 0);
    window_.unk_b1 = 0;
    window_.base_.frame_.unk_4 = 1;
    window_.base_.cursor_.unk_4 = 1;
    func_0205ba68(&window_.base_.frame_, 1, 6, 0);
    func_0205ba68(&window_.base_.cursor_, 1, 6, 0);
    func_0205bacc(&window_.base_.frame_, 6);
    func_0205bacc(&window_.base_.cursor_, 6);
    func_0205bcdc(&window_.base_.frame_, 1);
    func_0205bb04(&window_.base_.cursor_, 1);
}

void SkillPointMenu::WritePoints(char* text)
{
    char buffer[0x100] = {};
    const char* title = func_020e0434(&texts_, 0x2718);
    func_02041a28(buffer, (0xf0 - func_020420e8(title, false)) >> 1);
    func_02042058(buffer, title);
    func_02041fac(text, buffer, 0x10);
    if (windowInput_ == 2)
        func_02041c08(text, selection_, 8, 3, 6, 2);
    func_02041ea4(text, selection_);
    for (unsigned char i = 0; i < 5; i++)
    {
        if (locked_[i] == 0)
            func_02041e70(text, 0xf);
        else
            func_02041e70(text, 3);
        const char* name = func_020e0434(&texts_, skills_[i] + 100);
        sprintf(buffer, func_020e0434(&texts_, 0x2711), i, name);
        func_02042058(text, buffer);
        if (i != 4)
            sprintf(buffer, func_020e0434(&texts_, 0));
        func_02042058(text, buffer);
    }
    func_02041a5c(text, 0x15);
    int y;
    for (int i = 0; i < 5; i++)
    {
        y = i * 0xd;
        int points = points_[i];
        int added = addedPoints_[i];
        if (locked_[i] == 1)
            sprintf(buffer, func_020e0434(&texts_, 0x2712), y + 0x16, added, points);
        else if (i == selection_)
        {
            if (added == 0)
                sprintf(buffer, func_020e0434(&texts_, 0x2714), y + 0x16, 0xa, added, 0xb, points);
            else
                sprintf(buffer, func_020e0434(&texts_, 0x2713), y + 0x16, 0xa, added, 0xb, points, points + added);
        }
        else if (added == 0)
            sprintf(buffer, func_020e0434(&texts_, 0x2716), y + 0x16, added, points);
        else
            sprintf(buffer, func_020e0434(&texts_, 0x2715), y + 0x16, added, points, points + added);
        func_02042058(text, buffer);
        if (i != 4)
            func_02042058(text, func_020e0434(&texts_, 0));
    }
    func_02041cc0(text, 0x57);
    func_02041d48(text, 0x7fff, 0x5a, 0x10, 0x57);
    sprintf(buffer, func_020e0434(&texts_, 0x2717), remainingPoints_);
    func_02042058(text, buffer);
}

void SkillPointMenu::ShowMessage()
{
    MessageSystem* messages = func_020421a0();
    if (state_ == State_ConfirmApply)
        func_0204500c(messages, func_020e0434(&texts_, 1000), 0, 0xe3);
    else if (state_ == State_Confirm)
        func_0204500c(messages, func_020e0434(&texts_, 1001), 0, 0xe3);
    else if (state_ == State_Message)
        func_0204500c(messages, func_020e0434(&texts_, 1002), 0, 0xe3);
    messages->unk_19b2 = 0;
    messages->busy_ = 1;
}

// The colors of the message window's lines, and of the confirmation window's
static const unsigned char sMessageColors[4] = {0, 2, 2, 2};
static const unsigned char sConfirmColors[4] = {0, 2, 0, 2};

void SkillPointMenu::OpenMessageWindow()
{
    flags_ &= ~1;
    func_0205de24(&window_, 0, 2);
    window_.width_ = 0x20;
    window_.height_ = 9;
    window_.unk_a4 = 0;
    window_.unk_a6 = 0xf;
    window_.unk_a8 = 0xc;
    window_.unk_aa = 0xa;
    window_.unk_ac = 0xc;
    window_.unk_ae = 0x14;
    window_.unk_b1 = 2;
    if (subScreen_)
        window_.unk_b5 = 0;
    else
        window_.unk_b5 = 1;
    unk_638[2] = 0;
    memset(text_, 0, 0x960);
    WriteMessage(text_);
    func_0205d304(&window_, text_, 0, 0, 0, 1, sMessageColors, 1);
}

void SkillPointMenu::WriteMessage(char* text)
{
    func_02041d9c(text, 0xc);
    if (state_ == State_ConfirmApply)
        func_02042058(text, func_020e0434(&texts_, 1000));
    else if (state_ == State_Confirm)
        func_02042058(text, func_020e0434(&texts_, 1001));
    else if (state_ == State_Message)
        func_02042058(text, func_020e0434(&texts_, 1002));
}

// NONMATCHING: the C matches 95.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// At the end the compiler computes the menu's new x in another register, so it schedules the call's arguments before
// the stores. Neither local variables, inline functions for the position nor other types of it change it.
#ifdef NONMATCHING
void SkillPointMenu::OpenMenu()
{
    TextMenu* menu = &menu_;
    func_0205c790(menu);
    menu->base_.unk_95 = 1;
    menu->base_.unk_94 = 1;
    func_0205ba68(&menu->base_.frame_, 1, 2, 0);
    func_0205ba68(&menu->base_.cursor_, 1, 2, 0);
    func_0205bacc(&menu->base_.frame_, 2);
    func_0205bacc(&menu->base_.cursor_, 2);
    func_0205cb74(menu, func_020e0434(&texts_, 0xa));
    func_0205cb74(menu, func_020e0434(&texts_, 0xb));
    menu->SetPosition(0xc2, 0x92);
    func_0205cc50(menu, 0, -4);
    menu->unk_234 = 1;
    func_0205c77c(menu->unk_4, 1);
    menu->unk_233 = 1;
    menu->unk_234 = 1;
    func_0205c77c(menu->unk_4, 1);
    func_0205cd28(menu);
    func_0205cd94(menu);
    func_0205eaa0(data_02108760, 5, 0);
    menu->SetPosition(0xfe - menu->width_, menu->y_);
    func_0205cc50(menu, 0, -4);
}
#else
asm void SkillPointMenu::OpenMenu()
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    add r4, r5, #0x3d4
    mov r0, r4
    bl func_0205c790
    mov r1, #0x1
    strb r1, [r4, #0xb1]
    add r0, r4, #0x20
    mov r2, #0x2
    mov r3, #0x0
    strb r1, [r4, #0xb0]
    bl func_0205ba68
    add r0, r4, #0x70
    mov r1, #0x1
    mov r2, #0x2
    mov r3, #0x0
    bl func_0205ba68
    add r0, r4, #0x20
    mov r1, #0x2
    bl func_0205bacc
    add r0, r4, #0x70
    mov r1, #0x2
    bl func_0205bacc
    add r0, r5, #0x620
    mov r1, #0xa
    bl func_020e0434
    mov r1, r0
    mov r0, r4
    bl func_0205cb74
    add r0, r5, #0x620
    mov r1, #0xb
    bl func_020e0434
    mov r1, r0
    mov r0, r4
    bl func_0205cb74
    mov r0, #0xc2
    strh r0, [r4, #0xb4]
    mov r0, #0x92
    strh r0, [r4, #0xb6]
    mov r0, r4
    mov r1, #0x0
    sub r2, r1, #0x4
    bl func_0205cc50
    mov r1, #0x1
    strb r1, [r4, #0x234]
    add r0, r4, #0x4
    bl func_0205c77c
    mov r1, #0x1
    strb r1, [r4, #0x233]
    strb r1, [r4, #0x234]
    add r0, r4, #0x4
    bl func_0205c77c
    mov r0, r4
    bl func_0205cd28
    mov r0, r4
    bl func_0205cd94
    ldr r0, =data_02108760
    mov r1, #0x5
    mov r2, #0x0
    bl func_0205eaa0
    ldrsh r3, [r4, #0xb6]
    ldrsh r0, [r4, #0xb8]
    rsb r0, r0, #0xfe
    strh r0, [r4, #0xb4]
    mov r1, #0x0
    mov r0, r4
    sub r2, r1, #0x4
    strh r3, [r4, #0xb6]
    bl func_0205cc50
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

void SkillPointMenu::OpenConfirmWindow()
{
    func_0205de24(&window_, 0, 2);
    window_.width_ = 7;
    window_.height_ = 5;
    window_.unk_a4 = 0x19;
    window_.unk_a6 = 0x13;
    window_.unk_a8 = 0xc;
    window_.unk_aa = 7;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0x10;
    window_.unk_b1 = 3;
    if (subScreen_)
        window_.unk_b5 = 0;
    else
        window_.unk_b5 = 1;
    memset(text_, 0, 0x960);
    WriteConfirm(text_);
    func_0205d304(&window_, text_, 0, 0, 0, 1, sConfirmColors, 1);
    window_.unk_b1 = 3;
    window_.base_.frame_.unk_4 = 1;
    window_.base_.cursor_.unk_4 = 1;
    func_0205ba68(&window_.base_.frame_, 1, 2, 0);
    func_0205ba68(&window_.base_.cursor_, 1, 2, 0);
    func_0205bacc(&window_.base_.frame_, 2);
    func_0205bacc(&window_.base_.cursor_, 2);
    int selection = confirmSelection_;
    func_0205bcdc(&window_.base_.frame_, selection);
    func_0205bb04(&window_.base_.cursor_, selection);
}

void SkillPointMenu::WriteConfirm(char* text)
{
    if (windowInput_ == 2)
        func_02041c08(text, confirmSelection_, 9, 3, 6, 2);
    func_02041ea4(text, confirmSelection_);
    for (int i = 0; i < 2; i++)
    {
        char item[0x20] = {};
        func_02041d9c(item, 0xc);
        func_02042058(item, func_020e0434(&texts_, i + 0xa));
        func_02041b70(text, i, item);
        if (i < 1)
            func_02042058(text, func_020e0434(&texts_, 0));
    }
}

// The icon's sprite, and the shift of its characters' offset in VRAM, on the sub screen and on the main screen
static const int sIconSub[2] = {0x20, 7};
static const int sIconMain[2] = {0x2a, 5};

void SkillPointMenu::OpenMemberWindow()
{
    bool subScreen;
    SpriteRenderer* renderer;
    void* pixels;
    unsigned char vocation;
    func_0205de24(&window_, 0, 2);
    window_.width_ = 0xf;
    window_.height_ = 0xb;
    window_.unk_a4 = 1;
    window_.unk_a6 = 0xd;
    window_.unk_a8 = 6;
    window_.unk_aa = 5;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xd;
    window_.unk_b1 = 4;
    window_.unk_b5 = subScreen_ ? 0 : 1;
    memset(text_, 0, 0x960);
    WriteMember(text_);
    func_0205d304(&window_, text_, 0, 0, 0, 1, NULL, 0);
    renderer = spriteRenderer_;
    pixels = canvasPixels_;
    vocation = vocation_;
    subScreen = subScreen_;
    if (renderer != NULL && pixels != NULL)
    {
        const int* icon = sIconMain;
        if (subScreen)
            icon = sIconSub;
        Sprite* sprite = GetSprite(renderer, icon[0]);
        OamAttributes* oam;
        if (sprite != NULL && (oam = (OamAttributes*)sprite->unk_8) != NULL)
        {
            memcpy(pixels, func_020421b0(vocation * 4 + 0x28), sIconSize);
            unsigned int offset = (unsigned short)(oam->attr2_ & 0x3ff) << icon[1];
            CleanInvalidateCacheRange(pixels, sIconSize);
            if (subScreen)
                LoadToSubObjVRAM(pixels, offset, sIconSize);
            else
                LoadToMainObjVRAM(pixels, offset, sIconSize);
            CleanCacheRange(pixels, sIconSize);
        }
    }
}

// Where the status' names end
static const short sStatusX[6] = {0x3b, 0x3b, 0x4e, 0x4e, 0x4e, 0};

void SkillPointMenu::WriteMember(char* text)
{
    if (text == NULL)
        return;
    GameState::GetInstance();
    short nameId = 400;
    short valueId = 500;
    char line[0x200] = {};
    int nameWidth = func_020420e8(status_->name_, false);
    if (unk_6b8 != 0)
    {
        const char* title = func_020e0434(&texts_, unk_6b8 + 300);
        int color = 5;
        if (unk_6b8 == 10)
            color = 0xd;
        func_02041a5c(line, 4);
        func_02042058(line, status_->name_);
        func_02041acc(line, 0x10);
        func_02041e70(line, color);
        func_02042058(line, title);
        func_02041acc(line, 4);
        func_02041e70(line, 0xf);
        func_02042058(line, func_020e51cc(0x3f3));
        char level[0x10] = {};
        sprintf(level, "%d", level_);
        func_02042058(line, level);
    }
    else
    {
        func_02041a5c(line, 4);
        func_02042058(line, status_->name_);
        func_02041acc(line, 0x12);
        func_02042058(line, func_020e51cc(0x3f3));
        char level[0x10] = {};
        sprintf(level, "%d", level_);
        func_02042058(line, level);
    }
    char levelText[0x100] = {};
    sprintf(levelText, "%s%d", func_020e51cc(0x3f3), level_);
    int width = nameWidth + 0x12 + func_020420e8(levelText, false);
    if (unk_6b8 != 0)
        width += 9;
    width = 0x78 - width;
    nameEnd_ = nameWidth + (width >> 1) + 1;
    func_02041a28(text, width >> 1);
    func_02042058(text, line);
    func_02041fac(text, "", 0x10);
    MessageSystem* messages = func_020421a0();
    func_02046380();
    int values[7];
    values[0] = unk_6be;
    values[1] = unk_6c0;
    values[2] = unk_6c2;
    values[3] = unk_6c4;
    values[4] = unk_6c6;
    values[5] = unk_6c8;
    values[6] = unk_6ca;
    for (int i = 0; i < 7; i++)
    {
        func_020465d8(messages, i, 1);
        func_020465f0(messages, i, 3);
        func_020465c0(messages, i, values[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        func_02042058(text, func_020e0434(&texts_, nameId++));
        func_02041a28(text, sStatusX[i]);
        func_02042058(text, func_020e0434(&texts_, valueId++));
        if (i != 4)
            func_02042058(text, "\n");
    }
}

void SkillPointMenu::UpdateAllocate()
{
    int refresh;
    int close;
    int nextState;
    int previousSelection;
    flags_ |= 1;
    unk_638[0] = 0;
    unk_638[1] = 0;
    func_0205dee8(&window_, 0);
    int added[6] = {};
    for (int i = 0; i < 5; i++)
    {
        added[i] = addedPoints_[i];
    }
    previousSelection = selection_;
    refresh = 0;
    close = 0;
    nextState = -1;
    selection_ = func_0205d794(&window_);
    if (func_02012444(data_02114e30, sConfirmButtons))
    {
        if (selection_ != 5)
        {
            if (remainingPoints_ == 0)
            {
                selection_ = 5;
                func_0205d7a0(&window_);
                previousWindowInput_ = 0;
                refresh = 1;
            }
        }
        else
            nextState = State_Confirm;
    }
    else if (func_0205d97c(&window_) == 2)
        nextState = State_ConfirmApply;
    else if (func_02012444(data_02114e30, 2) && added[selection_] == 0)
        nextState = State_ConfirmApply;
    int input = windowInput_;
    if (input == 0)
    {
        if (remainingPoints_ >= 0 && selection_ < 5)
        {
            if (func_0201248c(data_02114e30, 0x20) || func_0201248c(data_02114e30, 2) ||
                IsItemTouched(&window_, 0xa))
            {
                previousWindowInput_ = 0;
                if (locked_[selection_] == 0)
                {
                    refresh = 1;
                    addedPoints_[selection_]--;
                    if (addedPoints_[selection_] < 0)
                        addedPoints_[selection_] = 0;
                    else
                        func_0205eaa0(data_02108760, 0x5d, 0);
                }
            }
            else if (remainingPoints_ > 0)
            {
                int added = 0;
                previousWindowInput_ = 0;
                int points = points_[selection_];
                if (points != 100 && points + addedPoints_[selection_] < 100)
                {
                    if (func_0201248c(data_02114e30, 0x611) || IsItemTouched(&window_, 0xb))
                    {
                        if (locked_[selection_] == 0)
                        {
                            added = 1;
                            refresh = 1;
                            addedPoints_[selection_]++;
                        }
                    }
                    if (added)
                        func_0205eaa0(data_02108760, 0x5d, 0);
                }
            }
        }
    }
    else
    {
        refresh = 1;
        if (input == 2 && previousWindowInput_ == input && previousSelection == 5 && selection_ == 5)
            nextState = State_Confirm;
        previousWindowInput_ = input;
    }
    if (nextState >= 0)
    {
        previousWindowInput_ = 0;
        state_ = nextState;
        unk_665 = 0;
        close = 1;
        refresh = 1;
        flags_ &= ~1;
        if (!subScreen_)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0205dee8(&window_, 4);
            func_0205d6a0(&window_, 0);
        }
        else
            func_0205eaa0(data_02108760, 5, 0);
        if (subScreen_)
            OpenMessageWindow();
        else
            ShowMessage();
    }
    int total = 0;
    for (int i = 0; i < 5; i++)
    {
        total += addedPoints_[i];
    }
    remainingPoints_ = availablePoints_ - total;
    if (close)
        SetCanvasHidden(0, 1);
    else if (refresh)
        RefreshPoints();
}

void SkillPointMenu::UpdateMessageMain()
{
    flags_ &= ~1;
    if (stateChanged_)
        unk_638[1] = 1;
    MessageSystem* messages = func_020421a0();
    messages->unk_19be = 1;
    if (!func_02012444(data_02114e30, 0x613) && !func_02012aac(&data_02114e54))
        return;
    state_ = State_Allocate;
    func_0201250c(data_02114e30);
    func_02043204(messages);
    unk_638[1] = 0;
    SetCanvasHidden(0, 0);
    OpenMemberWindow();
}

void SkillPointMenu::UpdateConfirmMain()
{
    if (stateChanged_)
        unk_638[1] = 1;
    MessageSystem* messages = func_020421a0();
    int playSound = 1;
    messages->unk_19be = 1;
    if (step_ == 0)
    {
        if (messages->unk_9a0 != 0)
            return;
        OpenMenu();
        WindowBase* base = &menu_.base_;
        if (state_ == State_ConfirmApply)
        {
            func_0205bcdc(&base->frame_, 1);
            func_0205bb04(&base->cursor_, 1);
        }
        else
        {
            func_0205bcdc(&base->frame_, 0);
            func_0205bb04(&base->cursor_, 0);
        }
        step_++;
    }
    else if (step_ == 1)
    {
        int item = func_0205cecc(&menu_);
        if (func_02012444(data_02114e30, sConfirmButtons))
            item = func_0205cb64(&menu_);
        else if (func_02012444(data_02114e30, 2))
        {
            item = -2;
            playSound = 0;
        }
        switch (item)
        {
        case 0:
            if (state_ == State_ConfirmApply)
            {
                state_ = State_Finish;
                func_02043204(messages);
                func_0205ce94(&menu_);
                apply_ = false;
                func_0205eaa0(data_02108760, 1, 0);
            }
            else
            {
                state_ = State_Finish;
                apply_ = true;
                func_02043204(messages);
                func_0205ce94(&menu_);
                func_0205d6a0(&window_, 1);
                func_0205eaa0(data_02108760, 1, 0);
            }
            step_ = 0;
            break;
        case -2:
        case 1:
            state_ = State_Allocate;
            step_ = 0;
            func_0201250c(data_02114e30);
            if (playSound)
                func_0205eaa0(data_02108760, 1, 0);
            apply_ = false;
            func_02043204(messages);
            func_0205ce94(&menu_);
            unk_638[1] = 0;
            SetCanvasHidden(0, 0);
            OpenMemberWindow();
            break;
        }
    }
}

void SkillPointMenu::UpdateMessageSub()
{
    flags_ &= ~1;
    unk_638[2] = 0;
    if (previousState_ != state_)
        return;
    if (!func_02012444(data_02114e30, 0x613) && !func_02012aac(&data_02114e54))
        return;
    state_ = State_Allocate;
    func_0201250c(data_02114e30);
    func_0205dee8(&window_, 2);
    func_0205d6a0(&window_, 0);
    unk_638[1] = 0;
    flags_ &= ~1;
    SetCanvasHidden(0, 0);
    OpenMemberWindow();
}

void SkillPointMenu::UpdateConfirmSub()
{
    int refresh = 0;
    flags_ |= 1;
    unk_638[2] = 0;
    if (step_ == 0)
    {
        if (state_ == State_ConfirmApply)
            confirmSelection_ = 1;
        else
            confirmSelection_ = 0;
        OpenConfirmWindow();
        step_++;
    }
    else if (step_ == 1)
    {
        func_0205dee8(&window_, 3);
        unk_638[3] = 0;
        if (func_02012444(data_02114e30, 0xc0))
        {
            confirmSelection_ = confirmSelection_ == 0 ? 1 : 0;
            refresh = 1;
        }
        if (windowInput_ == 2)
        {
            confirmSelection_ = (signed char)func_0205d794(&window_);
            refresh = 1;
        }
        if (previousState_ == state_)
        {
            if (func_02012444(data_02114e30, sConfirmButtons))
            {
                func_0205eaa0(data_02108760, 1, 0);
                if (state_ == State_ConfirmApply)
                {
                    if (confirmSelection_ == 0)
                    {
                        state_ = State_Finish;
                        func_0205d6a0(&window_, 1);
                        apply_ = false;
                    }
                    else
                    {
                        state_ = State_Allocate;
                        func_0201250c(data_02114e30);
                        apply_ = false;
                        func_0205dee8(&window_, 3);
                        func_0205d6a0(&window_, 0);
                        func_0205dee8(&window_, 2);
                        func_0205d6a0(&window_, 0);
                        unk_638[1] = 0;
                        flags_ &= ~1;
                        SetCanvasHidden(0, 0);
                        OpenMemberWindow();
                    }
                }
                else if (confirmSelection_ == 0)
                {
                    apply_ = true;
                    state_ = State_Finish;
                    func_0205d6a0(&window_, 1);
                }
                else
                {
                    func_0205dee8(&window_, 3);
                    func_0205d6a0(&window_, 0);
                    func_0205dee8(&window_, 2);
                    func_0205d6a0(&window_, 0);
                    unk_638[1] = 0;
                    state_ = State_Allocate;
                    func_0201250c(data_02114e30);
                    flags_ &= ~1;
                    SetCanvasHidden(0, 0);
                    OpenMemberWindow();
                }
                step_ = 0;
            }
            else if (func_02012444(data_02114e30, 2) || (confirmSelection_ == 1 && func_0205da38(&window_, 0x14)))
            {
                if (!func_02012444(data_02114e30, 2))
                    func_0205eaa0(data_02108760, 1, 0);
                func_0205dee8(&window_, 3);
                func_0205d6a0(&window_, 0);
                func_0205dee8(&window_, 2);
                func_0205d6a0(&window_, 0);
                unk_638[1] = 0;
                state_ = State_Allocate;
                func_0201250c(data_02114e30);
                step_ = 0;
                flags_ &= ~1;
                SetCanvasHidden(0, 0);
                OpenMemberWindow();
            }
            else if (confirmSelection_ == 0 && func_0205da38(&window_, 0x14))
            {
                func_0205eaa0(data_02108760, 1, 0);
                if (state_ == State_ConfirmApply)
                {
                    state_ = State_Finish;
                    func_0205d6a0(&window_, 1);
                    apply_ = false;
                }
                else
                {
                    apply_ = true;
                    state_ = State_Finish;
                    func_0205d6a0(&window_, 1);
                    step_ = 0;
                }
            }
        }
        if (refresh)
            RefreshConfirm();
    }
}

void SkillPointMenu::RefreshPoints()
{
    memset(text_, 0, 0x960);
    WritePoints(text_);
    func_0205d5d0(&window_, 0, text_, 1, 0);
}

void SkillPointMenu::RefreshConfirm()
{
    memset(text_, 0, 0x960);
    WriteConfirm(text_);
    func_0205d5d0(&window_, 3, text_, 1, 1);
}

void SkillPointMenu::SetCanvasHidden(int index, int hidden)
{
    Canvas* canvas = func_0205d81c(&window_, index);
    if (canvas == NULL)
        return;
    if (hidden)
        canvas->flags_ |= 0x40;
    else
        canvas->flags_ &= ~0x40;
    if (index == 0)
        RefreshPoints();
}

void SkillPointMenu::DrawCursor()
{
    if (spriteRenderer_ == NULL)
        return;
    if (!(flags_ & 1))
        return;
    Canvas* canvas = func_0205d8c4(&window_);
    if (canvas == NULL)
        return;
    if (!func_0204c7e0())
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    x += canvas->unk_bc;
    y += canvas->unk_be;
    if (state_ != State_Confirm && state_ != State_ConfirmApply)
    {
        x -= 8;
        y -= 2;
    }
    else
        x -= 8;
    SpriteAnimationList* animations = spriteRenderer_->animations_;
    if (animations == NULL)
        return;
    func_0205a370(animations, cursorAnimation_);
    SpriteAnimationEntry* entry = func_0205a3d0(animations, cursorAnimation_);
    if (entry != NULL)
        entry->flags_ |= 8;
    func_0205a330(animations, elapsed_);
    entry = func_0205a3d0(animations, cursorAnimation_);
    if (entry != NULL)
    {
        entry->x_ = x;
        entry->y_ = y;
    }
    func_0205ae8c(spriteRenderer_);
}

// NONMATCHING: the C matches 95.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler truncates the icon's y to a short before adding the x's offset, while the original does it after; the
// form that matches DrawCursor (adding to the canvas' position) gets closest.
#ifdef NONMATCHING
void SkillPointMenu::DrawIcon()
{
    if (spriteRenderer_ == NULL)
        return;
    Canvas* canvas = func_0205d81c(&window_, 4);
    if (canvas == NULL)
        return;
    if (!func_0204c7cc())
        return;
    if (canvas->flags_ & 0x20)
        return;
    int index = 0x2a;
    if (subScreen_)
        index = 0x20;
    Sprite* sprite = GetSprite(spriteRenderer_, index);
    if (sprite == NULL)
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    x += nameEnd_ + 3;
    y += 3;
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_26 = 1;
    sprite->unk_22 = 0x20;
    func_0205ac40(spriteRenderer_, sprite);
}
#else
asm void SkillPointMenu::DrawIcon()
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r4, r0
    ldr r0, [r4, #0x18]
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    add r0, r4, #0x38
    mov r1, #0x4
    bl func_0205d81c
    movs r5, r0
    ldmeqia sp!, {r3, r4, r5, pc}
    bl func_0204c7cc
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    ldrb r0, [r5, #0xc5]
    tst r0, #0x20
    ldmneia sp!, {r3, r4, r5, pc}
    ldrb r0, [r4, #0x640]
    mov r1, #0x2a
    cmp r0, #0x0
    movne r1, #0x20
    mov r1, r1, lsl #0x10
    ldr r0, [r4, #0x18]
    mov r1, r1, lsr #0x10
    bl GetSprite
    movs r1, r0
    ldmeqia sp!, {r3, r4, r5, pc}
    ldrsh r0, [r5, #0xac]
    ldrsh r2, [r5, #0xae]
    ldrsh r3, [r4, #0x1e]
    mov r0, r0, lsl #0x13
    mov r2, r2, lsl #0x13
    add r3, r3, #0x3
    add r0, r3, r0, asr #0x10
    mov r2, r2, asr #0x10
    mov r0, r0, lsl #0x10
    add r2, r2, #0x3
    mov r3, r0, asr #0x4
    mov r0, r2, lsl #0x10
    str r3, [r1, #0x14]
    mov r0, r0, asr #0x4
    str r0, [r1, #0x18]
    mov r0, #0x1
    strb r0, [r1, #0x26]
    mov r0, #0x20
    strb r0, [r1, #0x22]
    ldr r0, [r4, #0x18]
    bl func_0205ac40
    ldmia sp!, {r3, r4, r5, pc}
}
#endif
