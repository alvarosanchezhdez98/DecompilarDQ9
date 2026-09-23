#include "System/Graphics.h"
#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's g3imm.c: sends matrices to the geometry engine

extern "C"
{
    // The NitroSDK's GX_SendFifo64B and GX_SendFifo48B: copy 64 or 48 bytes to the geometry FIFO
    void func_020c6938(const void* src, volatile void* fifo);
    void func_020c6914(const void* src, volatile void* fifo);
    // The NitroSDK's MI_Copy36B: copies 36 bytes
    void func_020ca528(const void* src, volatile void* dst);

    // usa: func_020c516c
    // G3_LoadMtx44: loads the specified 4x4 matrix into the current matrix
    void func_020c516c(const Matrix4x4* m)
    {
        GXFIFO = 0x16;
        func_020c6938(m, &GXFIFO);
    }

    // usa: func_020c5188
    // G3_LoadMtx43: loads the specified 4x3 matrix into the current matrix
    void func_020c5188(const Matrix4x3* m)
    {
        GXFIFO = 0x17;
        func_020c6914(m, &GXFIFO);
    }

    // usa: func_020c51a4
    // G3_MultMtx43: multiplies the current matrix by the specified 4x3 matrix
    void func_020c51a4(const Matrix4x3* m)
    {
        GXFIFO = 0x19;
        func_020c6914(m, &GXFIFO);
    }

    // usa: func_020c51c0
    // G3_MultMtx33: multiplies the current matrix by the specified 3x3 matrix
    void func_020c51c0(const Matrix3x3* m)
    {
        GXFIFO = 0x1a;
        func_020ca528(m, &GXFIFO);
    }
}
