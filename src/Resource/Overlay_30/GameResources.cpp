#include "Resource/GameResources.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "System/Interrupts.h"
#include "System/Memory.h"
#include <globaldefs.h>
#include <std_library_functions.h>

#define INTERRUPT_MASTER_ENABLE (*(volatile unsigned short*)0x04000208)

extern "C"
{
    // Allocates from an allocator (AllocatorUnion::Allocate)
    void* func_02012db0(AllocatorUnion* allocator, unsigned int size);
    // Frees memory of an allocator (AllocatorUnion::Free) unless size is 0
    void func_02012dbc(AllocatorUnion* allocator, void* data, unsigned int size);
    // Does nothing
    void func_02012de4(AllocatorUnion* allocator);

    void func_0204719c(Unknown_0201c0e8* object);
    void func_02020554(void*);
    void func_0204af64(void*);
    void func_02046958(void*);
    void func_02054280(GameResources::Substruct_12C8* substruct);
    void func_020d8080(void*);
    void func_020d9850(void*);
    void func_020d9dec(void*, int);
    void func_020dac68(void*);
    void func_020dbc9c(Unknown_14* object);
    void func_020e3c34(Unknown_28* object);

    void func_ov017_0218b664(GameResources* resources);
    void func_ov017_02191b70(GameResources* resources);
    void func_ov017_021941ec(void*);
    void func_ov017_021996fc(GameResources* resources);
    void func_ov017_0219a674(void*);
    void func_ov017_0219e310(void*, int);
    void func_ov017_021a124c(void*);
    void func_ov017_021a5568(void*);
    void func_ov017_021a5b48(GameResources* resources);
    void func_ov017_021a967c(void*, int);
    void func_ov017_021a9bc4(void*, int);
    void func_ov017_021aa16c(void*);
    void func_ov017_021aa3f4(void*);
    void func_ov017_021aa50c(void*);
    void func_ov017_021ab250(void*);
    void func_ov017_021abb68(void*, int);
    void func_ov017_021ac2ec(void*);
    void func_ov017_021acd7c(void*);
    void func_ov017_021adc58(void*);
    void func_ov017_021ae800(void*);
    void func_ov017_021aeedc(void*);
    void func_ov017_021af59c(void*);
    void func_ov017_021b11b0(void*);
    void func_ov017_021b14a0(void*);
    void func_ov017_021b1d44(void*, int, int);
    void func_ov017_021b2174(void*);
    void func_ov017_021b2c4c(void*);
    void func_ov017_021b2f64(Unknown_48* object);
    void func_ov017_021b46d8(Unknown_18* object);
    void func_ov017_021b57fc(void*);
    void func_ov017_021b61e4(void*);
    void func_ov017_021b6f18(void*);
    void func_ov017_021b8c70(void*);
    void func_ov017_021b8d1c(void*);
    void func_ov017_021ba90c(void*);
    void func_ov017_021bac58(void*);
    void func_ov017_021baedc(void*);
    void func_ov017_021bdbf0(void*);
    void func_ov017_021be0a0(void*);
    void func_ov017_021be40c(void*);
    void func_ov017_021beba4(void*);
    void func_ov017_021befe4(void*);
    void func_ov017_021bf410(void*);
    void func_ov017_021c0124(void*, int);
    void func_ov017_021c0334(void*);
    void func_ov017_021c0760(void*, int);
    void func_ov017_021c1350(void*, int, int);
    void func_ov017_021c16a8(void*);
    void func_ov017_021c17cc(void*);
    void func_ov017_021c1e40(void*);
    void func_ov017_021c2688(void*);
    void func_ov017_021c2744(void*);
    void func_ov017_021c2b28(void*, int, int);
    void func_ov017_021c316c(void*, int);
}

inline void* operator new(unsigned long size, void* pointer)
{
    return pointer;
}

// OS_EnableIrq
static inline unsigned short EnableIrq()
{
    unsigned short previous = INTERRUPT_MASTER_ENABLE;
    INTERRUPT_MASTER_ENABLE = 1;
    return previous;
}

// NONMATCHING: the build uses the original's instructions after #else (see Decompiling.md). The original inlines
// GameResources' constructor, which only #pragma always_inline does (the compiler never inlines a constructor with
// more than 2 stores in a new expression otherwise), but it also computes every pointer into the GameResourcesData
// before constructing the members, and keeps them on the stack. The compiler does that with the arguments of an inlined
// function when they are calls to inline functions: a constructor with a parameter per pointer, called with getters
// of GameResourcesData, gives the original's code except for the order of the computations (objdiff: 27 %, and 0 %
// for this C, whose instructions differ from the start).
#ifdef NONMATCHING
#pragma always_inline on
GameResources* CreateGameResources(AllocatorUnion* allocator, GameResourcesData** data)
{
    *data = (GameResourcesData*)func_02012db0(allocator, sizeof(GameResourcesData));
    if (*data == NULL)
    {
        return NULL;
    }
    GameResources* resources = new (func_02012db0(allocator, sizeof(GameResources))) GameResources(*data);
    resources->Initialize();
    func_02012de4(allocator);
    return resources;
}
#pragma always_inline reset
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10Unknown_14C1Ev(); // Unknown_14::Unknown_14
    void _ZN10Unknown_14D1Ev(); // Unknown_14::~Unknown_14
    void _ZN10Unknown_18C1Ev(); // Unknown_18::Unknown_18
    void _ZN10Unknown_18D1Ev(); // Unknown_18::~Unknown_18
    void _ZN10Unknown_28C1Ev(); // Unknown_28::Unknown_28
    void _ZN10Unknown_28D1Ev(); // Unknown_28::~Unknown_28
    void _ZN10Unknown_48C1Ev(); // Unknown_48::Unknown_48
    void _ZN10Unknown_48D1Ev(); // Unknown_48::~Unknown_48
    void _ZN13GameResources10InitializeEv(); // GameResources::Initialize
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN16Unknown_0201c0e8C1Ev(); // Unknown_0201c0e8::Unknown_0201c0e8
    void _ZN16Unknown_0201c0e8D1Ev(); // Unknown_0201c0e8::~Unknown_0201c0e8
    void _ZN7Model3D5ClearEv(); // Model3D::Clear
    void _ZN8Object3D10InitializeEv(); // Object3D::Initialize
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    // The compiler's function that constructs the objects of an array
    void __construct_array();
}

asm GameResources* CreateGameResources(AllocatorUnion* allocator, GameResourcesData** data)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x144
    mov r5, r1
    mov r1, #0x36c0
    str r0, [sp, #0x4]
    bl func_02012db0
    str r0, [r5, #0x0]
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L021d921c
    ldr r1, =0x44c8
    ldr r0, [sp, #0x4]
    bl func_02012db0
    movs r4, r0
    beq @L021d9208
    ldr r12, [r5, #0x0]
    add r0, r12, #0x2d8
    add r0, r0, #0x3000
    add r1, r12, #0x13c
    str r0, [sp, #0x8]
    add r0, r1, #0x3000
    add r2, r12, #0x3a
    str r0, [sp, #0xc]
    add r0, r2, #0x3100
    add r3, r12, #0x138
    str r0, [sp, #0x10]
    add r0, r3, #0x3000
    add r9, r12, #0x7c
    str r0, [sp, #0x14]
    add r0, r9, #0x3000
    add r10, r12, #0x7a
    str r0, [sp, #0x18]
    add r0, r10, #0x3000
    str r0, [sp, #0x1c]
    add r0, r12, #0x78
    add r0, r0, #0x3000
    str r0, [sp, #0x20]
    add r0, r12, #0x4c
    add r0, r0, #0x3000
    str r0, [sp, #0x24]
    add r0, r12, #0xfe0
    add r0, r0, #0x2000
    str r0, [sp, #0x28]
    add r0, r12, #0x3cc
    add r0, r0, #0x2c00
    str r0, [sp, #0x2c]
    add r0, r12, #0x2fc0
    add r11, r12, #0x3b4
    str r0, [sp, #0x30]
    add r0, r11, #0x2c00
    str r0, [sp, #0x34]
    add r0, r11, #0x2800
    str r0, [sp, #0x54]
    add r0, r12, #0x314
    add r0, r0, #0x2c00
    str r0, [sp, #0x38]
    add r0, r12, #0x2f8
    add r1, r0, #0x2c00
    str r1, [sp, #0x3c]
    add r1, r12, #0x2e8
    add r1, r1, #0x2c00
    str r1, [sp, #0x40]
    add r1, r12, #0x2bc
    add r1, r1, #0x2c00
    str r1, [sp, #0x44]
    add r1, r12, #0xeb0
    add r1, r1, #0x2000
    str r1, [sp, #0x48]
    add r1, r12, #0xe60
    add r1, r1, #0x2000
    str r1, [sp, #0x4c]
    add r1, r12, #0x23c
    add r1, r1, #0x2c00
    str r1, [sp, #0x50]
    add r1, r12, #0x36c
    add r2, r1, #0x2800
    str r2, [sp, #0x58]
    add r2, r12, #0x318
    add r3, r2, #0x2800
    str r3, [sp, #0x5c]
    add r3, r12, #0x304
    add r3, r3, #0x2800
    str r3, [sp, #0x60]
    add r3, r12, #0x2ac
    add r3, r3, #0x2800
    str r3, [sp, #0x64]
    add r3, r12, #0x298
    add r3, r3, #0x2800
    str r3, [sp, #0x68]
    add r3, r12, #0x8
    add r3, r3, #0x2800
    str r3, [sp, #0x6c]
    add r3, r12, #0x3f8
    add r3, r3, #0x2400
    str r3, [sp, #0x70]
    add r3, r12, #0x3e8
    add r3, r3, #0x2400
    str r3, [sp, #0x74]
    add r3, r12, #0x3bc
    add r3, r3, #0x2400
    str r3, [sp, #0x78]
    add r3, r12, #0x34c
    add r3, r3, #0x2400
    str r3, [sp, #0x7c]
    add r3, r12, #0xd8
    add r3, r3, #0x2400
    str r3, [sp, #0x80]
    add r3, r12, #0xc8
    add r3, r3, #0x2400
    str r3, [sp, #0x84]
    add r3, r12, #0xb4
    add r3, r3, #0x2400
    str r3, [sp, #0x88]
    add r3, r12, #0x3b0
    add r3, r3, #0x2000
    str r3, [sp, #0x8c]
    add r3, r12, #0x3a4
    add r3, r3, #0x2000
    str r3, [sp, #0x90]
    add r3, r12, #0x2380
    str r3, [sp, #0x94]
    add r3, r12, #0x360
    add r3, r3, #0x2000
    str r3, [sp, #0x98]
    add r3, r12, #0x310
    add r3, r3, #0x2000
    str r3, [sp, #0x9c]
    add r3, r12, #0x2b4
    add r3, r3, #0x2000
    str r3, [sp, #0xa0]
    add r3, r12, #0x268
    add r9, r3, #0x2000
    str r9, [sp, #0xa4]
    add r9, r12, #0x22c
    add r9, r9, #0x2000
    str r9, [sp, #0xa8]
    add r9, r12, #0x16c
    str r9, [sp, #0x134]
    add r9, r9, #0x2000
    str r9, [sp, #0xac]
    add r9, r12, #0x144
    add r9, r9, #0x2000
    str r9, [sp, #0xb0]
    add r9, r12, #0x134
    add r10, r9, #0x2000
    str r10, [sp, #0xb4]
    add r10, r12, #0x2a8
    add r10, r10, #0x1c00
    str r10, [sp, #0xb8]
    add r10, r12, #0x294
    add r8, r12, #0x274
    add r7, r12, #0x71
    add r6, r12, #0x560
    add r5, r12, #0x32c
    add r10, r10, #0x1c00
    add r8, r8, #0x3400
    add r7, r7, #0x3500
    add r6, r6, #0x3000
    add r5, r5, #0x3000
    str r10, [sp, #0xbc]
    add r0, r0, #0x1800
    str r0, [sp, #0xd8]
    add r0, r9, #0x1800
    str r0, [sp, #0xec]
    add r0, r3, #0x1400
    str r0, [sp, #0x108]
    add r0, r12, #0x254
    add r0, r0, #0x1c00
    str r0, [sp, #0xc0]
    add r0, r12, #0x214
    add r0, r0, #0x1c00
    str r0, [sp, #0xc4]
    add r0, r12, #0xb90
    add r0, r0, #0x1000
    str r0, [sp, #0xc8]
    add r0, r1, #0x1800
    str r0, [sp, #0xcc]
    add r0, r1, #0xc00
    str r0, [sp, #0x110]
    add r0, r12, #0x1b40
    str r0, [sp, #0xd0]
    add r0, r12, #0xa90
    add r0, r0, #0x1000
    str r0, [sp, #0xdc]
    add r0, r12, #0x1a80
    str r0, [sp, #0xe0]
    add r0, r12, #0x1c8
    add r0, r0, #0x1800
    str r0, [sp, #0xe4]
    add r0, r12, #0x9a0
    add r0, r0, #0x1000
    str r0, [sp, #0xe8]
    add r0, r12, #0x910
    add r0, r0, #0x1000
    str r0, [sp, #0xf0]
    add r0, r12, #0x348
    add r0, r0, #0x1400
    str r0, [sp, #0xf4]
    add r0, r12, #0x720
    add r0, r0, #0x1000
    str r0, [sp, #0xf8]
    add r0, r12, #0x2fc
    add r0, r0, #0x1400
    str r0, [sp, #0xfc]
    add r0, r12, #0x2d4
    add r0, r0, #0x1400
    str r0, [sp, #0x100]
    add r0, r12, #0x2c8
    add r0, r0, #0x1400
    str r0, [sp, #0x104]
    add r0, r12, #0x238
    add r0, r0, #0x1400
    str r0, [sp, #0x10c]
    add r0, r12, #0xf60
    str r0, [sp, #0x114]
    add r0, r12, #0x224
    add r0, r0, #0xc00
    str r0, [sp, #0x118]
    add r0, r12, #0x1f8
    add r0, r0, #0xc00
    str r0, [sp, #0x11c]
    add r0, r12, #0x1d4
    add r0, r0, #0xc00
    str r0, [sp, #0x120]
    add r0, r12, #0x1cc
    add r0, r0, #0xc00
    str r0, [sp, #0x124]
    add r0, r12, #0x1c4
    add r0, r0, #0xc00
    str r0, [sp, #0x128]
    add r0, r12, #0x1bc
    add r0, r0, #0xc00
    str r0, [sp, #0x12c]
    add r0, r12, #0x19c
    add r0, r0, #0xc00
    str r0, [sp, #0x130]
    add r0, r12, #0xc0
    add r2, r2, #0x1800
    str r0, [sp, #0x138]
    add r0, r12, #0x14
    str r2, [sp, #0xd4]
    str r0, [sp, #0x13c]
    add r10, r4, #0x38
    add r9, r4, #0x2cc
@L021d8e10:
    mov r0, r10
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r10, r10, #0x14
    cmp r10, r9
    blo @L021d8e10
    add r0, r4, #0x13c
    add r0, r0, #0x1000
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x11c0
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x244
    add r0, r0, #0x1000
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x2c8
    add r10, r0, #0x1000
    add r0, r4, #0x278
    add r0, r0, #0x2800
    str r0, [sp, #0x140]
@L021d8e58:
    add r9, r10, #0x4
    add r11, r10, #0xcc
@L021d8e60:
    mov r0, r9
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r9, r9, #0x14
    cmp r9, r11
    blo @L021d8e60
    add r0, r10, #0x12c
    add r0, r0, #0x400
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r10, #0x540
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r10, #0x154
    add r0, r0, #0x400
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r10, #0x1d8
    add r0, r0, #0x400
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r10, #0x1ec
    add r10, r0, #0x400
    ldr r0, [sp, #0x140]
    cmp r10, r0
    blo @L021d8e58
    add r0, r4, #0x30c
    add r0, r0, #0x2800
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r1, =_ZN16Unknown_0201c0e8D1Ev
    add r0, r4, #0xb90
    str r1, [sp, #0x0]
    ldr r3, =_ZN16Unknown_0201c0e8C1Ev
    add r0, r0, #0x2000
    mov r1, #0x12
    mov r2, #0x88
    bl __construct_array
    add r0, r4, #0x520
    add r0, r0, #0x3000
    bl _ZN16Unknown_0201c0e8C1Ev
    add r0, r4, #0x1a8
    add r0, r0, #0x3400
    bl _ZN16Unknown_0201c0e8C1Ev
    ldr r1, [sp, #0x13c]
    add r0, r4, #0x3000
    str r1, [r0, #0x6c8]
    ldr r1, [sp, #0x138]
    ldr r3, =_ZN10Unknown_48C1Ev
    str r1, [r0, #0x6cc]
    ldr r1, [sp, #0x134]
    mov r2, #0x48
    str r1, [r0, #0x6d0]
    ldr r1, [sp, #0x130]
    str r1, [r0, #0x6d8]
    ldr r1, [sp, #0x12c]
    str r1, [r0, #0x6fc]
    ldr r1, [sp, #0x128]
    str r1, [r0, #0x700]
    ldr r1, [sp, #0x124]
    str r1, [r0, #0x704]
    ldr r1, [sp, #0x120]
    str r1, [r0, #0x708]
    ldr r1, [sp, #0x11c]
    str r1, [r0, #0x70c]
    ldr r1, [sp, #0x118]
    str r1, [r0, #0x710]
    ldr r1, [sp, #0x114]
    str r1, [r0, #0x714]
    ldr r1, [sp, #0x110]
    str r1, [r0, #0x718]
    ldr r1, [sp, #0x10c]
    str r1, [r0, #0x71c]
    ldr r1, [sp, #0x108]
    str r1, [r0, #0x720]
    ldr r1, [sp, #0x104]
    str r1, [r0, #0x724]
    ldr r1, [sp, #0x100]
    str r1, [r0, #0x728]
    ldr r1, [sp, #0xfc]
    str r1, [r0, #0x72c]
    ldr r1, [sp, #0xf8]
    str r1, [r0, #0x730]
    ldr r1, [sp, #0xf4]
    str r1, [r0, #0x734]
    ldr r1, [sp, #0xf0]
    str r1, [r0, #0x738]
    ldr r1, =_ZN10Unknown_48D1Ev
    add r0, r4, #0x33c
    str r1, [sp, #0x0]
    add r0, r0, #0x3400
    mov r1, #0xc
    bl __construct_array
    ldr r1, =_ZN10Unknown_18D1Ev
    add r0, r4, #0x29c
    str r1, [sp, #0x0]
    ldr r3, =_ZN10Unknown_18C1Ev
    add r0, r0, #0x3800
    mov r1, #0x4
    mov r2, #0x18
    bl __construct_array
    ldr r1, [sp, #0xec]
    add r0, r4, #0x3000
    str r1, [r0, #0xafc]
    ldr r1, [sp, #0xe8]
    str r1, [r0, #0xb00]
    ldr r1, [sp, #0xe4]
    str r1, [r0, #0xb04]
    ldr r1, [sp, #0xe0]
    str r1, [r0, #0xb08]
    ldr r1, [sp, #0xdc]
    str r1, [r0, #0xb0c]
    ldr r1, [sp, #0xd8]
    str r1, [r0, #0xb10]
    ldr r1, [sp, #0xd4]
    str r1, [r0, #0xb14]
    ldr r1, [sp, #0xd0]
    str r1, [r0, #0xb18]
    ldr r1, [sp, #0xcc]
    str r1, [r0, #0xb1c]
    ldr r1, [sp, #0xc8]
    str r1, [r0, #0xb20]
    ldr r1, [sp, #0xc4]
    str r1, [r0, #0xb24]
    ldr r1, [sp, #0xc0]
    str r1, [r0, #0xb28]
    ldr r1, [sp, #0xbc]
    str r1, [r0, #0xb2c]
    ldr r1, [sp, #0xb8]
    str r1, [r0, #0xb30]
    ldr r1, [sp, #0xb4]
    str r1, [r0, #0xb34]
    ldr r1, [sp, #0xb0]
    str r1, [r0, #0xb38]
    ldr r1, [sp, #0xac]
    str r1, [r0, #0xb3c]
    ldr r1, [sp, #0xa8]
    str r1, [r0, #0xb40]
    ldr r1, [sp, #0xa4]
    str r1, [r0, #0xb44]
    ldr r1, [sp, #0xa0]
    str r1, [r0, #0xb48]
    ldr r1, [sp, #0x9c]
    str r1, [r0, #0xb4c]
    ldr r1, [sp, #0x98]
    str r1, [r0, #0xb50]
    ldr r1, [sp, #0x94]
    str r1, [r0, #0xb54]
    ldr r1, [sp, #0x90]
    str r1, [r0, #0xb58]
    ldr r1, [sp, #0x8c]
    str r1, [r0, #0xb5c]
    ldr r1, [sp, #0x88]
    str r1, [r0, #0xb60]
    ldr r1, [sp, #0x84]
    str r1, [r0, #0xb64]
    ldr r1, [sp, #0x80]
    str r1, [r0, #0xb68]
    ldr r1, [sp, #0x7c]
    str r1, [r0, #0xb6c]
    ldr r1, [sp, #0x78]
    str r1, [r0, #0xb70]
    ldr r1, [sp, #0x74]
    str r1, [r0, #0xb74]
    ldr r1, [sp, #0x70]
    str r1, [r0, #0xb78]
    ldr r1, [sp, #0x6c]
    str r1, [r0, #0xb7c]
    ldr r1, [sp, #0x68]
    str r1, [r0, #0xb80]
    ldr r1, [sp, #0x64]
    str r1, [r0, #0xb84]
    ldr r1, [sp, #0x60]
    str r1, [r0, #0xb88]
    ldr r1, [sp, #0x5c]
    str r1, [r0, #0xb8c]
    ldr r1, [sp, #0x58]
    ldr r2, =_ZN10Unknown_14D1Ev
    str r1, [r0, #0xb90]
    ldr r1, [sp, #0x54]
    ldr r3, =_ZN10Unknown_14C1Ev
    str r1, [r0, #0xb94]
    ldr r1, [sp, #0x50]
    str r1, [r0, #0xb98]
    ldr r1, [sp, #0x4c]
    str r1, [r0, #0xb9c]
    ldr r1, [sp, #0x48]
    str r1, [r0, #0xba0]
    ldr r1, [sp, #0x44]
    str r1, [r0, #0xba4]
    ldr r1, [sp, #0x40]
    str r1, [r0, #0xba8]
    ldr r1, [sp, #0x3c]
    str r1, [r0, #0xbac]
    ldr r1, [sp, #0x38]
    str r1, [r0, #0xbb0]
    ldr r1, [sp, #0x34]
    str r1, [r0, #0xbb4]
    ldr r1, [sp, #0x30]
    str r1, [r0, #0xbb8]
    ldr r1, [sp, #0x2c]
    str r1, [r0, #0xbbc]
    ldr r1, [sp, #0x28]
    str r1, [r0, #0xbc0]
    ldr r1, [sp, #0x24]
    str r1, [r0, #0xbc4]
    add r0, r4, #0x3c8
    str r2, [sp, #0x0]
    add r0, r0, #0x3800
    mov r1, #0x3
    mov r2, #0x14
    bl __construct_array
    ldr r1, =_ZN10Unknown_28D1Ev
    add r0, r4, #0x4
    str r1, [sp, #0x0]
    ldr r3, =_ZN10Unknown_28C1Ev
    add r0, r0, #0x3c00
    mov r1, #0x4
    mov r2, #0x28
    bl __construct_array
    add r1, r4, #0x3000
    ldr r0, [sp, #0x20]
    str r8, [r1, #0xca4]
    str r0, [r1, #0xca8]
    ldr r0, [sp, #0x1c]
    str r0, [r1, #0xcac]
    ldr r0, [sp, #0x18]
    str r0, [r1, #0xcb0]
    ldr r0, [sp, #0x14]
    add r1, r4, #0x4000
    str r0, [r1, #0x88]
    ldr r0, [sp, #0x10]
    str r0, [r1, #0x8c]
    ldr r0, [sp, #0xc]
    str r0, [r1, #0x90]
    ldr r0, [sp, #0x8]
    str r0, [r1, #0x1c4]
    str r5, [r1, #0x328]
    str r6, [r1, #0x41c]
    str r7, [r1, #0x4c4]
@L021d9208:
    mov r0, r4
    bl _ZN13GameResources10InitializeEv
    ldr r0, [sp, #0x4]
    bl func_02012de4
    mov r0, r4
@L021d921c:
    add sp, sp, #0x144
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

Unknown_48::Unknown_48()
{
    func_0204693c(this);
}

Unknown_48::~Unknown_48()
{
    func_0204693c(this);
}

Unknown_18::Unknown_18()
{
    func_0204693c(this);
}

Unknown_18::~Unknown_18()
{
    func_0204693c(this);
}

Unknown_14::Unknown_14()
{
    func_0204693c(this);
}

Unknown_14::~Unknown_14()
{
    func_0204693c(this);
}

Unknown_28::Unknown_28()
{
    func_0204693c(this);
}

Unknown_28::~Unknown_28()
{
    func_0204693c(this);
}

void DestroyGameResources(GameResources* resources, AllocatorUnion* allocator, GameResourcesData** data)
{
    if (resources != NULL)
    {
        func_02012dbc(allocator, resources, 1);
    }
    if (*data != NULL)
    {
        func_02012dbc(allocator, *data, sizeof(GameResourcesData));
        *data = NULL;
    }
    func_02012de4(allocator);
}

// NONMATCHING: the C matches 98.8 %, so the build uses the original's instructions after #else. After
// unknown_ptr_3730's allocator is reset, the compiler gives other registers to the pointer and to the constants of the
// next two stores.
#ifdef NONMATCHING
void GameResources::Initialize()
{
    func_ov017_0218b5a0(this);
    InitializeBrightnessState(this);
    EnableIrq();
    EnableSpecificInterrupts(IRQ_MASK_TIMER_0_OVERFLOW);
    GameState::GetInstance();
    unknown_2c = 0;
    unknown_30 = 0;
    unknown_34 = 0;
    for (int i = 0; i < 0x21; i++)
    {
        allocators_[i].ResetAllocatorPointer();
    }
    allocator_113c.ResetAllocatorPointer();
    allocator_11c0.ResetAllocatorPointer();
    allocator_1244.ResetAllocatorPointer();
    for (int i = 0; i < 4; i++)
    {
        func_02054280(&substruct_array_12c8[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            unknown_445c[i][j] = -1;
        }
    }
    unknown_4438 = 0;
    unknown_443c = 0;
    unknown_4440 = 0;
    unknown_2b08 = -1;
    allocator_2b0c.ResetAllocatorPointer();
    for (int i = 0; i < 0x12; i++)
    {
        func_0204719c(&unknown_array_2b90[i]);
    }
    func_0204719c(&unknown_3520);
    func_0204719c(&unknown_35a8);
    unknown_3630 = 0;
    for (int i = 0; i < 0x12; i++)
    {
        unknown_3634[i] = 0;
        unknown_3646[i] = 0;
        unknown_3658[i] = 0;
        unknown_366c[i] = 0;
    }
    func_ov017_0219a674(unknown_36b4);
    unknown_ptr_36c8->Clear();
    unknown_ptr_36cc->Initialize();
    unknown_4331 = 0;
    func_02020554(unknown_ptr_36d0);
    unknown_36d4 = 0;
    for (int i = 0; i < 4; i++)
    {
        unknown_435c[i].unknown_0 = 0;
    }
    VectorizedMemset(unknown_36dc, 0, sizeof(unknown_36dc));
    VectorizedMemset(unknown_36e1, 0, sizeof(unknown_36e1));
    func_0204af64(unknown_ptr_36d8);
    unknown_36ec = -1;
    unknown_36f0 = 0;
    unknown_36f4 = 0;
    unknown_36f8 = 0;
    pTMapLanguageOffsets = NULL;
    unknown_4490 = 0;
    func_ov017_0218b664(this);
    unknown_4446 = -1;
    for (int i = 0; i < 4; i++)
    {
        unknown_444a[i] = 0;
    }
    unknown_4454 = 0x24;
    unknown_4458 = 1;
    unknown_4488 = 0;
    unknown_4489 = 1;
    unknown_448a = 0;

    func_02046958(unknown_ptr_36fc);
    func_02046958(unknown_ptr_3700);
    func_02046958(unknown_ptr_3704);
    func_ov017_021a124c(unknown_ptr_3708);
    func_ov017_0219e310(unknown_ptr_370c, 1);
    func_ov017_021b8d1c(unknown_ptr_3710);
    func_ov017_021b6f18(unknown_ptr_3718);
    func_ov017_021a5568(unknown_ptr_371c);
    func_ov017_021bf410(unknown_ptr_3720);
    func_ov017_021b8c70(unknown_ptr_3724);
    func_ov017_021bac58(unknown_ptr_3728);
    func_ov017_021ba90c(unknown_ptr_372c);
    func_0204693c(unknown_ptr_3730);
    unknown_ptr_3730->type_ = 0x11;
    unknown_ptr_3730->unknown_8 = 0;
    unknown_ptr_3730->allocator_c.ResetAllocatorPointer();
    unknown_ptr_3730->unknown_20 = 0;
    unknown_ptr_3730->unknown_24 = 0xff;
    func_ov017_021baedc(unknown_ptr_3734);
    func_ov017_021b2c4c(unknown_ptr_3738);
    for (int i = 0; i < 12; i++)
    {
        func_ov017_021b2f64(&unknown_array_373c[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        func_ov017_021b46d8(&unknown_array_3a9c[i]);
    }
    func_ov017_021b57fc(unknown_ptr_3afc);
    func_0204693c(unknown_ptr_3b00);
    unknown_ptr_3b00->type_ = 0x17;
    unknown_ptr_3b00->unknown_24 = 0;
    unknown_ptr_3b00->unknown_1f = 0;
    unknown_ptr_3b00->unknown_1c = 0;
    unknown_ptr_3b00->allocator_8.ResetAllocatorPointer();
    unknown_ptr_3b00->unknown_1d = 0;
    unknown_ptr_3b00->unknown_1e = 0xff;
    unknown_ptr_3b00->unknown_20 = -1;
    func_0204693c(unknown_ptr_3b04);
    unknown_ptr_3b04->type_ = 0x18;
    unknown_ptr_3b04->unknown_20 = 0;
    unknown_ptr_3b04->unknown_1c = 0;
    unknown_ptr_3b04->unknown_b4 = 0;
    unknown_ptr_3b04->allocator_8.ResetAllocatorPointer();
    unknown_ptr_3b04->unknown_a0 = 0;
    unknown_ptr_3b04->unknown_a4 = 0;
    unknown_ptr_3b04->unknown_a8 = 0;
    unknown_ptr_3b04->unknown_ac = 0;
    unknown_ptr_3b04->unknown_b0 = 0;
    func_ov017_021aa3f4(unknown_ptr_3b08);
    func_ov017_021aa50c(unknown_ptr_3b0c);
    func_ov017_021ab250(unknown_ptr_3b10);
    func_ov017_021abb68(unknown_ptr_3b14, 0);
    func_ov017_021ac2ec(unknown_ptr_3b18);
    func_ov017_021c0124(unknown_ptr_3b1c, 0);
    func_ov017_021acd7c(unknown_ptr_3b20);
    func_ov017_021adc58(unknown_ptr_3b24);
    func_ov017_021ae800(unknown_ptr_3b28);
    func_ov017_021aeedc(unknown_ptr_3b2c);
    func_ov017_021af59c(unknown_ptr_3b30);
    func_ov017_021b11b0(unknown_ptr_3b34);
    func_ov017_021c0334(unknown_ptr_3b38);
    func_ov017_021c0760(unknown_ptr_3b3c, 1);
    func_0204693c(unknown_ptr_3b40);
    unknown_ptr_3b40->type_ = 0x2a;
    unknown_ptr_3b40->unknown_c = 0;
    unknown_ptr_3b40->unknown_10 = 0;
    Unknown_222c* object = unknown_ptr_3b40;
    object->unknown_3a = 0;
    object->unknown_3b = 0;
    unknown_ptr_3b40->unknown_28 = 0xff;
    func_ov017_021b14a0(unknown_ptr_3b44);
    func_ov017_021b1d44(unknown_ptr_3b48, 0x40, 1);
    unknown_ptr_3b48->unknown_33 = 8;
    func_ov017_021b2174(unknown_ptr_3b4c);
    func_ov017_021c1350(unknown_ptr_3b50, 0, 0);
    func_ov017_021c17cc(unknown_ptr_3b54);
    func_ov017_021c16a8(unknown_ptr_3b58);
    func_ov017_021b61e4(unknown_ptr_3b5c);
    func_ov017_021bdbf0(unknown_ptr_3b60);
    func_ov017_021be0a0(unknown_ptr_3b64);
    func_ov017_021a9bc4(unknown_ptr_3b68, 0);
    func_ov017_021beba4(unknown_ptr_3b6c);
    func_ov017_021befe4(unknown_ptr_3b70);
    func_0204693c(unknown_ptr_3b74);
    unknown_ptr_3b74->type_ = 0x36;
    unknown_ptr_3b74->unknown_8 = 0;
    unknown_ptr_3b74->unknown_a = 0;
    unknown_ptr_3b74->unknown_c = -1;
    unknown_ptr_3b74->unknown_e = 0;
    unknown_ptr_3b74->unknown_f = 0;
    func_ov017_021aa16c(unknown_ptr_3b88);
    func_ov017_021c1e40(unknown_ptr_3ba0);
    func_ov017_021c2688(unknown_ptr_3ba8);
    func_ov017_021c2744(unknown_ptr_3bac);
    func_ov017_021c2b28(unknown_ptr_3bb0, 0, 0);
    func_ov017_021c316c(unknown_ptr_3bb4, 0);
    func_ov017_021a967c(unknown_ptr_3b84, 0);
    func_020d9dec(unknown_ptr_3bbc, 1);
    func_020dac68(unknown_ptr_3bc4);
    func_020d9850(unknown_ptr_3bb8);
    func_020d8080(unknown_ptr_3ba4);
    for (int i = 0; i < 3; i++)
    {
        func_020dbc9c(&unknown_array_3bc8[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        func_020e3c34(&unknown_array_3c04[i]);
    }
    func_ov017_021be40c(unknown_ptr_3ca4);
    func_ov017_021996fc(this);
    func_ov017_021a5b48(this);

    unknown_42e0 = 2;
    unknown_42e1 = 0;
    unknown_42e4 = 0;
    unknown_42ea = 0;
    unknown_42ec = 0;
    unknown_42ee = 0;
    unknown_42f0 = 0;
    memset(unknown_42f1, 0, sizeof(unknown_42f1));
    unknown_431e = 0;
    unknown_4320 = 1;
    unknown_4324 = 0;
    unknown_432c = -1;
    for (int i = 0; i < 3; i++)
    {
        unknown_432d[i] = -1;
    }
    unknown_4330 = 0;
    unknown_4334 = 0;
    unknown_4338 = 0;
    unknown_433c = 0;
    unknown_4340 = 0;
    unknown_4491 = 0;
    unknown_42e7 = 0;
    unknown_42e8 = 0;
    unknown_4494 = 0;
    unknown_4348 = 0;
    unknown_434c = 0;
    unknown_4350 = 0;
    unknown_42e9 = 0;
    unknown_4354 = 0;
    unknown_42e2 = 0;
    unknown_42e3 = 0;
    unknown_4344 = 0;
    unknown_4498 = 0;
    func_ov017_021941ec(unknown_ptr_441c);
    unknown_4420 = 1;
    unknown_4421 = 0;
    unknown_4422 = 0;
    unknown_4424 = 0;
    unknown_4428 = -1;
    unknown_442c = 0;
    unknown_442d = 0;
    unknown_442e = 0;
    unknown_4430 = -1;
    unknown_442f = 0;
    unknown_4434 = 0;
    unknown_4432 = 2;
    unknown_42e5 = 0;
    unknown_4355 = 0;
    func_ov017_02191b70(this);
    unknown_44ac = 0;
}
#else
asm void GameResources::Initialize()
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r4, r0
    bl func_ov017_0218b5a0
    mov r0, r4
    bl InitializeBrightnessState
    ldr r2, =0x4000208
    mov r1, #0x1
    ldrh r0, [r2, #0x0]
    mov r0, #0x8
    strh r1, [r2, #0x0]
    bl EnableSpecificInterrupts
    bl _ZN9GameState11GetInstanceEv
    mov r7, #0x0
    str r7, [r4, #0x2c]
    str r7, [r4, #0x30]
    str r7, [r4, #0x34]
    add r6, r4, #0x38
    mov r5, #0x14
    b @L021d9398
@L021d938c:
    mla r0, r7, r5, r6
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r7, r7, #0x1
@L021d9398:
    cmp r7, #0x21
    blt @L021d938c
    add r0, r4, #0x13c
    add r0, r0, #0x1000
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x11c0
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x244
    add r0, r0, #0x1000
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x2c8
    mov r7, #0x0
    add r6, r0, #0x1000
    ldr r5, =0x5ec
    b @L021d93e0
@L021d93d4:
    mla r0, r7, r5, r6
    bl func_02054280
    add r7, r7, #0x1
@L021d93e0:
    cmp r7, #0x4
    blt @L021d93d4
    mov r6, #0x0
    mvn r3, #0x0
    mov r5, r6
    mov r1, #0xb
    b @L021d9424
@L021d93fc:
    mla r2, r6, r1, r4
    mov r7, r5
    b @L021d9418
@L021d9408:
    add r0, r2, r7
    add r0, r0, #0x4000
    strb r3, [r0, #0x45c]
    add r7, r7, #0x1
@L021d9418:
    cmp r7, #0xb
    blt @L021d9408
    add r6, r6, #0x1
@L021d9424:
    cmp r6, #0x4
    blt @L021d93fc
    mov r1, #0x0
    add r0, r4, #0x4000
    str r1, [r0, #0x438]
    str r1, [r0, #0x43c]
    add r2, r4, #0x30c
    str r1, [r0, #0x440]
    sub r3, r1, #0x1
    add r1, r4, #0x2000
    add r0, r2, #0x2800
    str r3, [r1, #0xb08]
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0xb90
    mov r7, #0x0
    add r6, r0, #0x2000
    mov r5, #0x88
    b @L021d9478
@L021d946c:
    mla r0, r7, r5, r6
    bl func_0204719c
    add r7, r7, #0x1
@L021d9478:
    cmp r7, #0x12
    blt @L021d946c
    add r0, r4, #0x520
    add r0, r0, #0x3000
    bl func_0204719c
    add r0, r4, #0x1a8
    add r0, r0, #0x3400
    bl func_0204719c
    mov r3, #0x0
    add r0, r4, #0x3000
    str r3, [r0, #0x630]
    mov r2, r3
    b @L021d94d0
@L021d94ac:
    add r0, r4, r3
    add r0, r0, #0x3000
    strb r2, [r0, #0x634]
    add r1, r4, r3, lsl #0x2
    strb r2, [r0, #0x646]
    strb r2, [r0, #0x658]
    add r0, r1, #0x3000
    str r2, [r0, #0x66c]
    add r3, r3, #0x1
@L021d94d0:
    cmp r3, #0x12
    blt @L021d94ac
    add r0, r4, #0x2b4
    add r0, r0, #0x3400
    bl func_ov017_0219a674
    add r0, r4, #0x3000
    ldr r0, [r0, #0x6c8]
    bl _ZN7Model3D5ClearEv
    add r0, r4, #0x3000
    ldr r0, [r0, #0x6cc]
    bl _ZN8Object3D10InitializeEv
    add r0, r4, #0x4000
    mov r1, #0x0
    strb r1, [r0, #0x331]
    add r0, r4, #0x3000
    ldr r0, [r0, #0x6d0]
    bl func_02020554
    mov r3, #0x0
    add r0, r4, #0x3000
    str r3, [r0, #0x6d4]
    mov r2, r3
    mov r0, #0x30
    b @L021d953c
@L021d952c:
    mla r1, r3, r0, r4
    add r1, r1, #0x4000
    strb r2, [r1, #0x35c]
    add r3, r3, #0x1
@L021d953c:
    cmp r3, #0x4
    blt @L021d952c
    add r0, r4, #0x2dc
    add r0, r0, #0x3400
    mov r1, #0x0
    mov r2, #0x5
    bl VectorizedMemset
    add r0, r4, #0xe1
    add r0, r0, #0x3600
    mov r1, #0x0
    mov r2, #0x9
    bl VectorizedMemset
    add r0, r4, #0x3000
    ldr r0, [r0, #0x6d8]
    bl func_0204af64
    add r0, r4, #0x3000
    mvn r1, #0x0
    str r1, [r0, #0x6ec]
    mov r2, #0x0
    str r2, [r0, #0x6f0]
    str r2, [r0, #0x6f4]
    str r2, [r0, #0x6f8]
    add r1, r4, #0x4000
    str r2, [r1, #0x48c]
    mov r0, r4
    strb r2, [r1, #0x490]
    bl func_ov017_0218b664
    add r0, r4, #0x4000
    mvn r1, #0x0
    mov r2, #0x0
    strb r1, [r0, #0x446]
    mov r1, r2
    b @L021d95d0
@L021d95c0:
    add r0, r4, r2, lsl #0x1
    add r0, r0, #0x4400
    strh r1, [r0, #0x4a]
    add r2, r2, #0x1
@L021d95d0:
    cmp r2, #0x4
    blt @L021d95c0
    add r0, r4, #0x4000
    mov r1, #0x24
    str r1, [r0, #0x454]
    mov r2, #0x1
    str r2, [r0, #0x458]
    mov r1, #0x0
    strb r1, [r0, #0x488]
    strb r2, [r0, #0x489]
    strb r1, [r0, #0x48a]
    add r0, r4, #0x3000
    ldr r0, [r0, #0x6fc]
    bl func_02046958
    add r0, r4, #0x3000
    ldr r0, [r0, #0x700]
    bl func_02046958
    add r0, r4, #0x3000
    ldr r0, [r0, #0x704]
    bl func_02046958
    add r0, r4, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a124c
    add r0, r4, #0x3000
    ldr r0, [r0, #0x70c]
    mov r1, #0x1
    bl func_ov017_0219e310
    add r0, r4, #0x3000
    ldr r0, [r0, #0x710]
    bl func_ov017_021b8d1c
    add r0, r4, #0x3000
    ldr r0, [r0, #0x718]
    bl func_ov017_021b6f18
    add r0, r4, #0x3000
    ldr r0, [r0, #0x71c]
    bl func_ov017_021a5568
    add r0, r4, #0x3000
    ldr r0, [r0, #0x720]
    bl func_ov017_021bf410
    add r0, r4, #0x3000
    ldr r0, [r0, #0x724]
    bl func_ov017_021b8c70
    add r0, r4, #0x3000
    ldr r0, [r0, #0x728]
    bl func_ov017_021bac58
    add r0, r4, #0x3000
    ldr r0, [r0, #0x72c]
    bl func_ov017_021ba90c
    add r0, r4, #0x3000
    ldr r0, [r0, #0x730]
    bl func_0204693c
    add r0, r4, #0x3000
    ldr r1, [r0, #0x730]
    mov r3, #0x11
    strb r3, [r1, #0x0]
    ldr r1, [r0, #0x730]
    mov r2, #0x0
    str r2, [r1, #0x8]
    ldr r0, [r0, #0x730]
    add r0, r0, #0xc
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x3000
    ldr r2, [r0, #0x730]
    mov r1, #0x0
    str r1, [r2, #0x20]
    ldr r2, [r0, #0x730]
    mov r3, #0xff
    strb r3, [r2, #0x24]
    ldr r0, [r0, #0x734]
    bl func_ov017_021baedc
    add r0, r4, #0x3000
    ldr r0, [r0, #0x738]
    bl func_ov017_021b2c4c
    add r0, r4, #0x33c
    mov r7, #0x0
    add r6, r0, #0x3400
    mov r5, #0x48
    b @L021d9714
@L021d9708:
    mla r0, r7, r5, r6
    bl func_ov017_021b2f64
    add r7, r7, #0x1
@L021d9714:
    cmp r7, #0xc
    blt @L021d9708
    add r0, r4, #0x29c
    mov r7, #0x0
    add r6, r0, #0x3800
    mov r5, #0x18
    b @L021d973c
@L021d9730:
    mla r0, r7, r5, r6
    bl func_ov017_021b46d8
    add r7, r7, #0x1
@L021d973c:
    cmp r7, #0x4
    blt @L021d9730
    add r0, r4, #0x3000
    ldr r0, [r0, #0xafc]
    bl func_ov017_021b57fc
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb00]
    bl func_0204693c
    add r0, r4, #0x3000
    ldr r1, [r0, #0xb00]
    mov r2, #0x17
    strb r2, [r1, #0x0]
    ldr r1, [r0, #0xb00]
    mov r2, #0x0
    str r2, [r1, #0x24]
    ldr r1, [r0, #0xb00]
    strb r2, [r1, #0x1f]
    ldr r1, [r0, #0xb00]
    strb r2, [r1, #0x1c]
    ldr r0, [r0, #0xb00]
    add r0, r0, #0x8
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x3000
    mov r3, #0xff
    ldr r1, [r0, #0xb00]
    mov r2, #0x0
    strb r2, [r1, #0x1d]
    ldr r1, [r0, #0xb00]
    sub r2, r3, #0x100
    strb r3, [r1, #0x1e]
    ldr r1, [r0, #0xb00]
    strb r2, [r1, #0x20]
    ldr r0, [r0, #0xb04]
    bl func_0204693c
    add r0, r4, #0x3000
    ldr r1, [r0, #0xb04]
    mov r2, #0x18
    strb r2, [r1, #0x0]
    ldr r1, [r0, #0xb04]
    mov r2, #0x0
    str r2, [r1, #0x20]
    ldr r1, [r0, #0xb04]
    str r2, [r1, #0x1c]
    ldr r1, [r0, #0xb04]
    strb r2, [r1, #0xb4]
    ldr r0, [r0, #0xb04]
    add r0, r0, #0x8
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    add r0, r4, #0x3000
    ldr r1, [r0, #0xb04]
    mov r2, #0x0
    strh r2, [r1, #0xa0]
    ldr r1, [r0, #0xb04]
    str r2, [r1, #0xa4]
    ldr r1, [r0, #0xb04]
    str r2, [r1, #0xa8]
    ldr r1, [r0, #0xb04]
    str r2, [r1, #0xac]
    ldr r1, [r0, #0xb04]
    str r2, [r1, #0xb0]
    ldr r0, [r0, #0xb08]
    bl func_ov017_021aa3f4
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb0c]
    bl func_ov017_021aa50c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb10]
    bl func_ov017_021ab250
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb14]
    mov r1, #0x0
    bl func_ov017_021abb68
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb18]
    bl func_ov017_021ac2ec
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb1c]
    mov r1, #0x0
    bl func_ov017_021c0124
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb20]
    bl func_ov017_021acd7c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb24]
    bl func_ov017_021adc58
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb28]
    bl func_ov017_021ae800
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb2c]
    bl func_ov017_021aeedc
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb30]
    bl func_ov017_021af59c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb34]
    bl func_ov017_021b11b0
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb38]
    bl func_ov017_021c0334
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb3c]
    mov r1, #0x1
    bl func_ov017_021c0760
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb40]
    bl func_0204693c
    add r0, r4, #0x3000
    mov r2, #0x2a
    ldr r1, [r0, #0xb40]
    mov r3, #0x0
    strb r2, [r1, #0x0]
    ldr r1, [r0, #0xb40]
    mov r2, #0xff
    str r3, [r1, #0xc]
    ldr r1, [r0, #0xb40]
    str r3, [r1, #0x10]
    ldr r1, [r0, #0xb40]
    strb r3, [r1, #0x3a]
    strb r3, [r1, #0x3b]
    ldr r1, [r0, #0xb40]
    strb r2, [r1, #0x28]
    ldr r0, [r0, #0xb44]
    bl func_ov017_021b14a0
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb48]
    mov r1, #0x40
    mov r2, #0x1
    bl func_ov017_021b1d44
    mov r2, #0x8
    add r0, r4, #0x3000
    ldr r1, [r0, #0xb48]
    strb r2, [r1, #0x33]
    ldr r0, [r0, #0xb4c]
    bl func_ov017_021b2174
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb50]
    mov r1, #0x0
    mov r2, r1
    bl func_ov017_021c1350
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb54]
    bl func_ov017_021c17cc
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb58]
    bl func_ov017_021c16a8
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb5c]
    bl func_ov017_021b61e4
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb60]
    bl func_ov017_021bdbf0
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb64]
    bl func_ov017_021be0a0
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb68]
    mov r1, #0x0
    bl func_ov017_021a9bc4
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb6c]
    bl func_ov017_021beba4
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb70]
    bl func_ov017_021befe4
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb74]
    bl func_0204693c
    mov r2, #0x36
    add r0, r4, #0x3000
    ldr r1, [r0, #0xb74]
    mov r3, #0x0
    strb r2, [r1, #0x0]
    ldr r1, [r0, #0xb74]
    sub r2, r3, #0x1
    strh r3, [r1, #0x8]
    ldr r1, [r0, #0xb74]
    strb r3, [r1, #0xa]
    ldr r1, [r0, #0xb74]
    strh r2, [r1, #0xc]
    ldr r1, [r0, #0xb74]
    strb r3, [r1, #0xe]
    ldr r1, [r0, #0xb74]
    strb r3, [r1, #0xf]
    ldr r0, [r0, #0xb88]
    bl func_ov017_021aa16c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xba0]
    bl func_ov017_021c1e40
    add r0, r4, #0x3000
    ldr r0, [r0, #0xba8]
    bl func_ov017_021c2688
    add r0, r4, #0x3000
    ldr r0, [r0, #0xbac]
    bl func_ov017_021c2744
    add r0, r4, #0x3000
    mov r1, #0x0
    ldr r0, [r0, #0xbb0]
    mov r2, r1
    bl func_ov017_021c2b28
    add r0, r4, #0x3000
    ldr r0, [r0, #0xbb4]
    mov r1, #0x0
    bl func_ov017_021c316c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xb84]
    mov r1, #0x0
    bl func_ov017_021a967c
    add r0, r4, #0x3000
    ldr r0, [r0, #0xbbc]
    mov r1, #0x1
    bl func_020d9dec
    add r0, r4, #0x3000
    ldr r0, [r0, #0xbc4]
    bl func_020dac68
    add r0, r4, #0x3000
    ldr r0, [r0, #0xbb8]
    bl func_020d9850
    add r0, r4, #0x3000
    ldr r0, [r0, #0xba4]
    bl func_020d8080
    add r0, r4, #0x3c8
    mov r7, #0x0
    add r6, r0, #0x3800
    mov r5, #0x14
    b @L021d9ad0
@L021d9ac4:
    mla r0, r7, r5, r6
    bl func_020dbc9c
    add r7, r7, #0x1
@L021d9ad0:
    cmp r7, #0x3
    blt @L021d9ac4
    add r0, r4, #0x4
    mov r7, #0x0
    add r6, r0, #0x3c00
    mov r5, #0x28
    b @L021d9af8
@L021d9aec:
    mla r0, r7, r5, r6
    bl func_020e3c34
    add r7, r7, #0x1
@L021d9af8:
    cmp r7, #0x4
    blt @L021d9aec
    add r0, r4, #0x3000
    ldr r0, [r0, #0xca4]
    bl func_ov017_021be40c
    mov r0, r4
    bl func_ov017_021996fc
    mov r0, r4
    bl func_ov017_021a5b48
    add r0, r4, #0xf1
    add r3, r4, #0x4000
    mov r1, #0x2
    strb r1, [r3, #0x2e0]
    mov r1, #0x0
    strb r1, [r3, #0x2e1]
    strb r1, [r3, #0x2e4]
    strb r1, [r3, #0x2ea]
    add r2, r4, #0x4200
    strh r1, [r2, #0xec]
    strh r1, [r2, #0xee]
    add r0, r0, #0x4200
    mov r2, #0x2d
    strb r1, [r3, #0x2f0]
    bl memset
    add r0, r4, #0x4000
    mov r2, #0x0
    mov r1, #0x1
    strb r2, [r0, #0x31e]
    str r1, [r0, #0x320]
    str r2, [r0, #0x324]
    sub r1, r1, #0x2
    strb r1, [r0, #0x32c]
    b @L021d9b8c
@L021d9b7c:
    add r0, r4, r2
    add r0, r0, #0x4000
    strb r1, [r0, #0x32d]
    add r2, r2, #0x1
@L021d9b8c:
    cmp r2, #0x3
    blt @L021d9b7c
    add r0, r4, #0x4000
    mov r1, #0x0
    strb r1, [r0, #0x330]
    str r1, [r0, #0x334]
    str r1, [r0, #0x338]
    str r1, [r0, #0x33c]
    str r1, [r0, #0x340]
    strb r1, [r0, #0x491]
    strb r1, [r0, #0x2e7]
    strb r1, [r0, #0x2e8]
    str r1, [r0, #0x494]
    str r1, [r0, #0x348]
    str r1, [r0, #0x34c]
    str r1, [r0, #0x350]
    strb r1, [r0, #0x2e9]
    strb r1, [r0, #0x354]
    strb r1, [r0, #0x2e2]
    strb r1, [r0, #0x2e3]
    str r1, [r0, #0x344]
    str r1, [r0, #0x498]
    ldr r0, [r0, #0x41c]
    bl func_ov017_021941ec
    mov r3, #0x0
    add r1, r4, #0x4000
    mov r0, #0x1
    strb r0, [r1, #0x420]
    strb r3, [r1, #0x421]
    add r0, r4, #0x4400
    strh r3, [r0, #0x22]
    strh r3, [r0, #0x24]
    sub r2, r3, #0x1
    str r2, [r1, #0x428]
    strb r3, [r1, #0x42c]
    strb r3, [r1, #0x42d]
    strb r3, [r1, #0x42e]
    strh r2, [r0, #0x30]
    strb r3, [r1, #0x42f]
    str r3, [r1, #0x434]
    mov r0, #0x2
    strb r0, [r1, #0x432]
    strb r3, [r1, #0x2e5]
    mov r0, r4
    strb r3, [r1, #0x355]
    bl func_ov017_02191b70
    add r0, r4, #0x4400
    mov r1, #0x0
    strh r1, [r0, #0xac]
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif
