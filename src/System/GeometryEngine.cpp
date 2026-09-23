#include "System/Graphics.h"
#include "System/Matrix.h"
#include "System/DMA.h"
#include <globaldefs.h>

#pragma optimize_for_size off
// Compiled with -O4 like the other NitroSDK files: at -O2, G3X_InitTable's loop is compiled differently
#pragma optimization_level 4

// The NitroSDK's g3x.c: initializes and resets the geometry engine, and reads its state

#define REG_BG0OFS (*(volatile unsigned int*)0x04000010)
#define REG_EDGE_COLOR_TABLE 0x04000330
#define REG_ALPHA_TEST_REF (*(volatile unsigned short*)0x04000340)
#define REG_CLEAR_COLOR (*(volatile unsigned int*)0x04000350)
#define REG_CLEAR_DEPTH (*(volatile unsigned short*)0x04000354)
#define REG_CLEAR_IMAGE_OFFSET (*(volatile unsigned short*)0x04000356)
#define REG_FOG_OFFSET (*(volatile unsigned short*)0x0400035c)
#define REG_FOG_TABLE 0x04000360
#define REG_SHININESS (*(volatile unsigned int*)0x040004d0)
#define REG_CLIP_MATRIX_RESULT 0x04000640
#define REG_VECTOR_MATRIX_RESULT 0x04000680

#define DISP3DCNT_TOON_HIGHLIGHT 0x2
#define DISP3DCNT_ALPHA_TEST 0x4
#define DISP3DCNT_ANTI_ALIASING 0x10
#define DISP3DCNT_FOG_ONLY_ALPHA 0x40
#define DISP3DCNT_FOG 0x80
#define DISP3DCNT_FOG_SHIFT 0xf00
#define DISP3DCNT_LINE_BUFFER_UNDERFLOW 0x1000 // cleared by writing 1
#define DISP3DCNT_LIST_RAM_OVERFLOW 0x2000 // cleared by writing 1

#define GXSTAT_TEST_BUSY 0x1
#define GXSTAT_BOX_TEST_RESULT 0x2
#define GXSTAT_POSITION_VECTOR_LEVEL 0x1f00
#define GXSTAT_PROJECTION_LEVEL 0x2000
#define GXSTAT_MATRIX_STACK_BUSY 0x4000
#define GXSTAT_MATRIX_STACK_ERROR 0x8000 // cleared by writing 1
#define GXSTAT_BUSY 0x8000000
#define GXSTAT_FIFO_INTERRUPT 0xc0000000
#define GXSTAT_FIFO_INTERRUPT_EMPTY 0x80000000

extern "C"
{
    // The NitroSDK's MI_Copy64B, MI_Copy36B and MI_Copy32B
    void func_020ca568(volatile const void* src, void* dst);
    void func_020ca528(volatile const void* src, void* dst);
    void func_020ca50c(const void* src, volatile void* dst);
    // The NitroSDK's MIi_CpuCopy16 and MIi_CpuClear32
    void func_020ca3b8(const void* src, volatile void* dst, unsigned int len);
    void func_020ca3ec(int value, volatile void* dst, unsigned int len);

    void func_020c5354();
    void func_020c537c();
    void func_020c5414();
    void func_020c55b0();
    int func_020c5650(int* level);
    int func_020c5680(int* level);
    void func_020c56dc(volatile void* fifo);
}

// The NitroSDK's inline functions for the geometry engine's registers

static inline int IsGeometryBusy()
{
    return GXSTATUS & GXSTAT_BUSY;
}

static inline void ResetMatrixStackError()
{
    GXSTATUS |= GXSTAT_MATRIX_STACK_ERROR;
}

static inline void ResetLineBufferUnderflow()
{
    DISP3DCNT |= DISP3DCNT_LINE_BUFFER_UNDERFLOW;
}

static inline void ResetListRamOverflow()
{
    DISP3DCNT |= DISP3DCNT_LIST_RAM_OVERFLOW;
}

// Writing the flags that are cleared by writing 1 would clear them, so the functions below write 0 to them

static inline void SetToonShading()
{
    DISP3DCNT = (unsigned short)(DISP3DCNT
        & ~(DISP3DCNT_TOON_HIGHLIGHT | DISP3DCNT_LINE_BUFFER_UNDERFLOW | DISP3DCNT_LIST_RAM_OVERFLOW));
}

static inline void EnableAntiAliasing()
{
    DISP3DCNT = (unsigned short)(DISP3DCNT & ~(DISP3DCNT_LINE_BUFFER_UNDERFLOW | DISP3DCNT_LIST_RAM_OVERFLOW)
        | DISP3DCNT_ANTI_ALIASING);
}

static inline void DisableAlphaTest()
{
    DISP3DCNT &= (unsigned short)~(DISP3DCNT_ALPHA_TEST | DISP3DCNT_LINE_BUFFER_UNDERFLOW | DISP3DCNT_LIST_RAM_OVERFLOW);
}

static inline void SetFifoInterruptWhenEmpty()
{
    GXSTATUS = (GXSTATUS & ~GXSTAT_FIFO_INTERRUPT) | GXSTAT_FIFO_INTERRUPT_EMPTY;
}

static inline void ResetPolygonState()
{
    GXFIFO_POLYGON_ATTRIBUTES = 0x1f0080; // modulation, back faces culled, polygon ID 0, opaque
    GXFIFO_TEXIMAGE_PARAMS = 0; // no texture
    GXFIFO_PALETTE_BASE = 0;
}

extern "C"
{
    // usa: func_020c51dc
    // G3X_Init: initializes the geometry engine and its tables
    void func_020c51dc()
    {
        func_020c5354();
        GXFIFO_POLYGON_END = 0;

        while (IsGeometryBusy()) {}

        DISP3DCNT = 0;
        GXSTATUS = 0;
        REG_BG0OFS = 0;

        ResetListRamOverflow();
        ResetLineBufferUnderflow();
        SetToonShading();
        EnableAntiAliasing();
        DisableAlphaTest();

        ResetMatrixStackError();
        SetFifoInterruptWhenEmpty();

        func_020c537c();

        REG_CLEAR_COLOR = 0;
        REG_CLEAR_DEPTH = 0x7fff;
        REG_CLEAR_IMAGE_OFFSET = 0;
        GX_FOG_COLOR = 0;
        REG_FOG_OFFSET = 0;

        BG0CNT = (unsigned short)(BG0CNT & ~BGCNT_MASK_PRIORITY); // the 3D layer has the highest priority

        func_020c55b0();

        ResetPolygonState();
    }

    // usa: func_020c52e8
    // G3X_Reset: resets the geometry engine's state and its matrix stacks
    void func_020c52e8()
    {
        while (IsGeometryBusy()) {}

        ResetMatrixStackError();
        ResetListRamOverflow();
        ResetLineBufferUnderflow();

        func_020c5414();

        ResetPolygonState();
    }

    // usa: func_020c5354
    // G3X_ClearFifo: clears the geometry FIFO and waits for the geometry engine
    void func_020c5354()
    {
        func_020c56dc(&GXFIFO);

        while (IsGeometryBusy()) {}
    }

    // usa: func_020c537c
    // G3X_InitMtxStack: empties the matrix stacks and sets every matrix to the identity
    void func_020c537c()
    {
        int positionVectorLevel;
        int projectionLevel;

        ResetMatrixStackError();

        while (func_020c5650(&positionVectorLevel)) {}
        while (func_020c5680(&projectionLevel)) {}

        GXFIFO_MATRIX_MODE = 3; // texture
        GXFIFO_MATRIX_IDENTITY = 0;

        GXFIFO_MATRIX_MODE = 0; // projection
        if (projectionLevel != 0)
            GXFIFO_MATRIX_POP = projectionLevel;
        GXFIFO_MATRIX_IDENTITY = 0;

        GXFIFO_MATRIX_MODE = 2; // position+vector
        GXFIFO_MATRIX_POP = positionVectorLevel;
        GXFIFO_MATRIX_IDENTITY = 0;
    }

    // usa: func_020c5414
    // G3X_ResetMtxStack: empties the matrix stacks, and sets the texture and position+vector matrices to the identity
    void func_020c5414()
    {
        int positionVectorLevel;
        int projectionLevel;

        ResetMatrixStackError();

        while (func_020c5650(&positionVectorLevel)) {}
        while (func_020c5680(&projectionLevel)) {}

        GXFIFO_MATRIX_MODE = 3; // texture
        GXFIFO_MATRIX_IDENTITY = 0;

        GXFIFO_MATRIX_MODE = 0; // projection
        if (projectionLevel != 0)
            GXFIFO_MATRIX_POP = projectionLevel;

        GXFIFO_MATRIX_MODE = 2; // position+vector
        GXFIFO_MATRIX_POP = positionVectorLevel;
        GXFIFO_MATRIX_IDENTITY = 0;
    }

    // usa: func_020c54a4
    // G3X_SetFog
    void func_020c54a4(int enable, int onlyAlpha, int shift, int offset)
    {
        if (enable)
        {
            REG_FOG_OFFSET = (unsigned short)offset;
            DISP3DCNT = (unsigned short)((DISP3DCNT & ~(DISP3DCNT_FOG_SHIFT | DISP3DCNT_FOG_ONLY_ALPHA
                | DISP3DCNT_LINE_BUFFER_UNDERFLOW | DISP3DCNT_LIST_RAM_OVERFLOW))
                | ((shift << 8) | (onlyAlpha << 6) | DISP3DCNT_FOG));
        }
        else
        {
            DISP3DCNT &= (unsigned short)~(DISP3DCNT_FOG | DISP3DCNT_LINE_BUFFER_UNDERFLOW | DISP3DCNT_LIST_RAM_OVERFLOW);
        }
    }

    // usa: func_020c54fc
    // G3X_GetClipMtx: reads the clip matrix, the product of the position and projection matrices.
    // Returns -1 if the geometry engine is busy, 0 if done.
    int func_020c54fc(Matrix4x4* m)
    {
        if (IsGeometryBusy())
            return -1;
        func_020ca568((volatile const void*)REG_CLIP_MATRIX_RESULT, m);
        return 0;
    }

    // usa: func_020c552c
    // G3X_GetVectorMtx: reads the directional vector matrix.
    // Returns -1 if the geometry engine is busy, 0 if done.
    int func_020c552c(Matrix3x3* m)
    {
        if (IsGeometryBusy())
            return -1;
        func_020ca528((volatile const void*)REG_VECTOR_MATRIX_RESULT, m);
        return 0;
    }

    // usa: func_020c555c
    // G3X_SetEdgeColorTable: sets the 8 edge colors
    void func_020c555c(const unsigned short* colors)
    {
        func_020ca3b8(colors, (volatile void*)REG_EDGE_COLOR_TABLE, 16);
    }

    // usa: func_020c5574
    // G3X_SetFogTable: sets the 32 fog densities
    void func_020c5574(const unsigned int* table)
    {
        func_020ca50c(table, (volatile void*)REG_FOG_TABLE);
    }

    // usa: func_020c5588
    // G3X_SetClearColor: sets the color, depth and polygon ID of the rear plane
    void func_020c5588(unsigned short color, int alpha, int depth, int polygonID, int fog)
    {
        unsigned int value = color | (alpha << 16) | (polygonID << 24);
        if (fog)
            value |= 0x8000;

        REG_CLEAR_COLOR = value;
        REG_CLEAR_DEPTH = (unsigned short)depth;
    }

    // usa: func_020c55b0
    // G3X_InitTable: clears the edge colors, the fog table and the shininess table
    void func_020c55b0()
    {
        int i;

        if (data_020f2270 != -1) // DMA channel set
        {
            DMAMemsetAsync(data_020f2270, REG_EDGE_COLOR_TABLE, 0, 16, NULL, 0);
            DMAMemsetSynchronous(data_020f2270, REG_FOG_TABLE, 0, 96);
        }
        else
        {
            func_020ca3ec(0, (volatile void*)REG_EDGE_COLOR_TABLE, 16);
            func_020ca3ec(0, (volatile void*)REG_FOG_TABLE, 96);
        }

        for (i = 0; i < 32; ++i)
            REG_SHININESS = 0;
    }

    // usa: func_020c5650
    // G3X_GetMtxStackLevelPV: reads the level of the position+vector matrix stack.
    // Returns -1 if the matrix stack is busy, 0 if done.
    int func_020c5650(int* level)
    {
        if (GXSTATUS & GXSTAT_MATRIX_STACK_BUSY)
            return -1;
        *level = (GXSTATUS & GXSTAT_POSITION_VECTOR_LEVEL) >> 8;
        return 0;
    }

    // usa: func_020c5680
    // G3X_GetMtxStackLevelPJ: reads the level of the projection matrix stack.
    // Returns -1 if the matrix stack is busy, 0 if done.
    int func_020c5680(int* level)
    {
        if (GXSTATUS & GXSTAT_MATRIX_STACK_BUSY)
            return -1;
        *level = (GXSTATUS & GXSTAT_PROJECTION_LEVEL) >> 13;
        return 0;
    }

    // usa: func_020c56b0
    // G3X_GetBoxTestResult: reads the result of the box test.
    // Returns -1 if the test is busy, 0 if done.
    int func_020c56b0(int* in)
    {
        if (GXSTATUS & GXSTAT_TEST_BUSY)
            return -1;
        *in = GXSTATUS & GXSTAT_BOX_TEST_RESULT;
        return 0;
    }

    // usa: func_020c56dc
    // GXi_NopClearFifo128_: writes 128 zeros (NOP commands) to the geometry FIFO
#ifdef __MWERKS__
    asm void func_020c56dc(register volatile void* fifo)
    {
        mov r1, #0
        mov r2, #0
        mov r3, #0
        mov r12, #0
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        stmia r0, {r1, r2, r3, r12}
        bx lr
    }
#else
    void func_020c56dc(volatile void* fifo)
    {
        for (int i = 0; i < 128; i++)
            *(volatile unsigned int*)fifo = 0;
    }
#endif
}
