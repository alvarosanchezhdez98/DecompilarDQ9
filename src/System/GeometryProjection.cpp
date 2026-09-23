#include "System/Graphics.h"
#include "System/Matrix.h"
#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's g3_util.c: computes projection and view matrices, and optionally loads them into the geometry engine

extern "C"
{
    void func_020c516c(const Matrix4x4* m);
    void func_020c5188(const Matrix4x3* m);

    // usa: func_020c5770
    // G3i_OrthoW_: computes an orthographic projection matrix with Mat4x4_WriteProjectionUnknown (MTX_OrthoW), and
    // loads it into the projection matrix if load is set. out can be NULL.
    void func_020c5770(fix32_t top, fix32_t bottom, fix32_t left, fix32_t right, fix32_t near, fix32_t far,
        fix32_t scaleW, int load, Matrix4x4* out)
    {
        Matrix4x4 temp;
        if (out == NULL)
            out = &temp;

        Mat4x4_WriteProjectionUnknown(top, bottom, left, right, near, far, scaleW, out);
        if (load)
        {
            GXFIFO_MATRIX_MODE = 0; // projection
            func_020c516c(out);
        }
    }

    // usa: func_020c57d4
    // G3i_LookAt_: computes a view matrix with Mat4x3_WriteViewMatrix (MTX_LookAt), and loads it into the
    // position+vector matrix if load is set. out can be NULL.
    void func_020c57d4(const Vector3fix* eye, const Vector3fix* up, const Vector3fix* target, int load, Matrix4x3* out)
    {
        Matrix4x3 temp;
        if (out == NULL)
            out = &temp;

        Mat4x3_WriteViewMatrix(eye, up, target, out);
        if (load)
        {
            GXFIFO_MATRIX_MODE = 2; // position+vector
            func_020c5188(out);
        }
    }
}
