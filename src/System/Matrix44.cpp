#include "System/MathCoprocessor.h"
#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_mtx44.c: 4x4 matrices, e.g. projections. Its other functions aren't in the ROM.

extern "C"
{
#ifdef __MWERKS__
    // usa: func_020c21dc
    // MTX_Identity44_
    asm void Mat4x4_WriteIdentity(Matrix4x4* out)
    {
        mov r2, #0x1000
        mov r3, #0
        stmia r0!, {r2, r3}
        mov r1, #0
        stmia r0!, {r1, r3}
        stmia r0!, {r1, r2, r3}
        stmia r0!, {r1, r3}
        stmia r0!, {r1, r2, r3}
        stmia r0!, {r1, r3}
        stmia r0!, {r1, r2}
        bx lr
    }

    // usa: func_020c2208
    // MTX_Copy44To43_
    asm void Mat4x4_ConvertTo4x3(const Matrix4x4* in, Matrix4x3* out)
    {
        ldmia r0!, {r2, r3, r12}
        add r0, r0, #4
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        add r0, r0, #4
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        add r0, r0, #4
        stmia r1!, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        add r0, r0, #4
        stmia r1!, {r2, r3, r12}
        bx lr
    }
#endif

    // usa: func_020c223c
    // MTX_Concat44
    void Mat4x4_Multiply(const Matrix4x4* inA, const Matrix4x4* inB, Matrix4x4* out)
    {
        Matrix4x4 tmp;
        Matrix4x4* p;
        register long x, y, z, w;
        register long xx, yy, zz, ww;

        if (out == inB)
        {
            p = &tmp;
        }
        else
        {
            p = out;
        }

        // Row 0
        x = inA->entries[0];
        y = inA->entries[1];
        z = inA->entries[2];
        w = inA->entries[3];

        p->entries[0] = (long)(((int64_t)x * inB->entries[0] + (int64_t)y * inB->entries[4] + (int64_t)z * inB->entries[8]
                                + (int64_t)w * inB->entries[12]) >> 12);
        p->entries[1] = (long)(((int64_t)x * inB->entries[1] + (int64_t)y * inB->entries[5] + (int64_t)z * inB->entries[9]
                                + (int64_t)w * inB->entries[13]) >> 12);
        p->entries[3] = (long)(((int64_t)x * inB->entries[3] + (int64_t)y * inB->entries[7] + (int64_t)z * inB->entries[11]
                                + (int64_t)w * inB->entries[15]) >> 12);

        xx = inB->entries[2];
        yy = inB->entries[6];
        zz = inB->entries[10];
        ww = inB->entries[14];

        p->entries[2] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);

        // Row 1
        x = inA->entries[4];
        y = inA->entries[5];
        z = inA->entries[6];
        w = inA->entries[7];

        p->entries[6] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);
        p->entries[5] = (long)(((int64_t)x * inB->entries[1] + (int64_t)y * inB->entries[5] + (int64_t)z * inB->entries[9]
                                + (int64_t)w * inB->entries[13]) >> 12);
        p->entries[7] = (long)(((int64_t)x * inB->entries[3] + (int64_t)y * inB->entries[7] + (int64_t)z * inB->entries[11]
                                + (int64_t)w * inB->entries[15]) >> 12);

        xx = inB->entries[0];
        yy = inB->entries[4];
        zz = inB->entries[8];
        ww = inB->entries[12];

        p->entries[4] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);

        // Row 2
        x = inA->entries[8];
        y = inA->entries[9];
        z = inA->entries[10];
        w = inA->entries[11];

        p->entries[8] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);
        p->entries[9] = (long)(((int64_t)x * inB->entries[1] + (int64_t)y * inB->entries[5] + (int64_t)z * inB->entries[9]
                                + (int64_t)w * inB->entries[13]) >> 12);
        p->entries[11] = (long)(((int64_t)x * inB->entries[3] + (int64_t)y * inB->entries[7] + (int64_t)z * inB->entries[11]
                                 + (int64_t)w * inB->entries[15]) >> 12);

        xx = inB->entries[2];
        yy = inB->entries[6];
        zz = inB->entries[10];
        ww = inB->entries[14];

        p->entries[10] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);

        // Row 3
        x = inA->entries[12];
        y = inA->entries[13];
        z = inA->entries[14];
        w = inA->entries[15];

        p->entries[14] = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz + (int64_t)w * ww) >> 12);
        p->entries[13] = (long)(((int64_t)x * inB->entries[1] + (int64_t)y * inB->entries[5] + (int64_t)z * inB->entries[9]
                                 + (int64_t)w * inB->entries[13]) >> 12);
        p->entries[12] = (long)(((int64_t)x * inB->entries[0] + (int64_t)y * inB->entries[4] + (int64_t)z * inB->entries[8]
                                 + (int64_t)w * inB->entries[12]) >> 12);
        p->entries[15] = (long)(((int64_t)x * inB->entries[3] + (int64_t)y * inB->entries[7] + (int64_t)z * inB->entries[11]
                                 + (int64_t)w * inB->entries[15]) >> 12);

        if (p == &tmp)
        {
            *out = tmp;
        }
    }

    // usa: func_020c28a0
    // MTX_PerspectiveW: a perspective projection from the sine and cosine of the vertical field of view, the aspect
    // ratio, the near and far planes and a scale for W
    void Mat4x4_MaybeWriteFrustum(fix32_t fovySin, fix32_t fovyCos, fix32_t aspect, fix32_t near, fix32_t far,
                                  fix32_t scaleW, Matrix4x4* out)
    {
        long cotangent;
        int64_t inverse;

        cotangent = fix32_Divide(fovyCos, fovySin);
        StartDivision64_32SameMode((uint64_t)0x1000 << 32, near - far);
        if (scaleW != 0x1000)
        {
            cotangent = (cotangent * scaleW) / 0x1000;
        }

        out->entries[1] = 0;
        out->entries[2] = 0;
        out->entries[3] = 0;
        out->entries[4] = 0;
        out->entries[5] = cotangent;
        out->entries[6] = 0;
        out->entries[7] = 0;
        out->entries[8] = 0;
        out->entries[9] = 0;
        out->entries[11] = -scaleW;
        out->entries[12] = 0;
        out->entries[13] = 0;
        out->entries[15] = 0;

        inverse = GetHardwareDividerResult();
        StartDivision64_32SameMode((uint64_t)cotangent << 32, aspect);
        if (scaleW != 0x1000)
        {
            inverse = (inverse * scaleW) / 0x1000;
        }
        out->entries[10] = (long)(((far + near) * inverse + 0x80000000LL) >> 32);
        out->entries[14] = (long)(((long)(((int64_t)(near << 1) * far + 0x800) >> 12) * inverse + 0x80000000LL) >> 32);
        out->entries[0] = fix32_GetDivisionResult();
    }

    // usa: func_020c29ec
    // MTX_OrthoW
    void Mat4x4_WriteProjectionUnknown(fix32_t top, fix32_t bottom, fix32_t left, fix32_t right, fix32_t near,
                                       fix32_t far, fix32_t scaleW, Matrix4x4* out)
    {
        int64_t inverseWidth;
        int64_t inverseHeight;
        int64_t inverseDepth;

        fix32_QueueComputeReciprocal(right - left);

        out->entries[1] = 0;
        out->entries[2] = 0;
        out->entries[3] = 0;
        out->entries[4] = 0;
        out->entries[6] = 0;
        out->entries[7] = 0;
        out->entries[8] = 0;
        out->entries[9] = 0;
        out->entries[11] = 0;
        out->entries[15] = scaleW;

        inverseWidth = GetHardwareDividerResult();
        StartDivision64_32SameMode((uint64_t)0x1000 << 32, top - bottom);
        if (scaleW != 0x1000)
        {
            inverseWidth = (inverseWidth * scaleW) / 0x1000;
        }
        out->entries[0] = (long)((0x2000 * inverseWidth + 0x80000000LL) >> 32);

        inverseHeight = GetHardwareDividerResult();
        StartDivision64_32SameMode((uint64_t)0x1000 << 32, near - far);
        if (scaleW != 0x1000)
        {
            inverseHeight = (inverseHeight * scaleW) / 0x1000;
        }
        out->entries[5] = (long)((0x2000 * inverseHeight + 0x80000000LL) >> 32);

        inverseDepth = GetHardwareDividerResult();
        if (scaleW != 0x1000)
        {
            inverseDepth = (inverseDepth * scaleW) / 0x1000;
        }
        out->entries[10] = (long)((0x2000 * inverseDepth + 0x80000000LL) >> 32);

        out->entries[12] = (long)((-(right + left) * inverseWidth + 0x80000000LL) >> 32);
        out->entries[13] = (long)((-(top + bottom) * inverseHeight + 0x80000000LL) >> 32);
        out->entries[14] = (long)(((far + near) * inverseDepth + 0x80000000LL) >> 32);
    }
}
