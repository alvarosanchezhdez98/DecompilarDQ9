#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_mtx33.c: 3x3 matrices. Its other functions aren't in the ROM.

// The NitroSDK's mul64: a 64-bit value times a fixed-point number
static inline long MultiplyFx64(int64_t x, long y)
{
    return (long)((x * y) >> 12);
}

extern "C"
{
    // usa: func_020ca528
    // The NitroSDK's MI_Copy36B: copies 36 bytes
    void func_020ca528(const void* src, void* dst);

#ifdef __MWERKS__
    // usa: func_020c1180
    // MTX_Identity33_
    asm void Mat3x3_WriteIdentity(Matrix3x3* out)
    {
        mov r2, #0x1000
        str r2, [r0, #32]
        mov r3, #0
        stmia r0!, {r2, r3}
        mov r1, #0
        stmia r0!, {r1, r3}
        stmia r0!, {r2, r3}
        stmia r0!, {r1, r3}
        bx lr
    }
#endif

    // usa: func_020c11a4
    // MTX_ScaleApply33
    void Mat3x3_ApplyScale(const Matrix3x3* in, Matrix3x3* out, fix32_t x, fix32_t y, fix32_t z)
    {
        int64_t v;

        v = x;
        out->rows[0].x = MultiplyFx64(v, in->rows[0].x);
        out->rows[0].y = MultiplyFx64(v, in->rows[0].y);
        out->rows[0].z = MultiplyFx64(v, in->rows[0].z);

        v = y;
        out->rows[1].x = MultiplyFx64(v, in->rows[1].x);
        out->rows[1].y = MultiplyFx64(v, in->rows[1].y);
        out->rows[1].z = MultiplyFx64(v, in->rows[1].z);

        v = z;
        out->rows[2].x = MultiplyFx64(v, in->rows[2].x);
        out->rows[2].y = MultiplyFx64(v, in->rows[2].y);
        out->rows[2].z = MultiplyFx64(v, in->rows[2].z);
    }

#ifdef __MWERKS__
#pragma thumb on
    // usa: func_020c1264
    // MTX_RotX33_
    asm void Mat3x3_WriteRotationX(Matrix3x3* out, fix32_t sine, fix32_t cosine)
    {
        mov r3, #1
        lsl r3, r3, #12
        str r3, [r0, #0]
        mov r3, #0
        str r3, [r0, #4]
        str r3, [r0, #8]
        str r3, [r0, #12]
        str r2, [r0, #16]
        str r1, [r0, #20]
        str r3, [r0, #24]
        neg r1, r1
        str r1, [r0, #28]
        str r2, [r0, #32]
        bx lr
    }

    // usa: func_020c1280
    // MTX_RotY33_
    asm void Mat3x3_WriteRotationY(Matrix3x3* out, fix32_t sine, fix32_t cosine)
    {
        str r2, [r0, #0]
        str r2, [r0, #32]
        mov r3, #0
        str r3, [r0, #4]
        str r3, [r0, #12]
        str r3, [r0, #20]
        str r3, [r0, #28]
        neg r2, r1
        mov r3, #1
        lsl r3, r3, #12
        str r1, [r0, #24]
        str r2, [r0, #8]
        str r3, [r0, #16]
        bx lr
    }

    // usa: func_020c129c
    // MTX_RotZ33_
    asm void Mat3x3_WriteRotationZ(Matrix3x3* out, fix32_t sine, fix32_t cosine)
    {
        stmia r0!, {r2}
        mov r3, #0
        stmia r0!, {r1, r3}
        neg r1, r1
        stmia r0!, {r1, r2}
        mov r1, #1
        lsl r1, r1, #12
        str r3, [r0, #0]
        str r3, [r0, #4]
        str r3, [r0, #8]
        str r1, [r0, #12]
        bx lr
    }
#pragma thumb off
#endif

    // usa: func_020c12b4
    // MTX_Inverse33
    int Mat3x3_Invert(const Matrix3x3* in, Matrix3x3* out)
    {
        Matrix3x3 tmp;
        Matrix3x3* p;
        long det, det00, det10, det20, tmp01, tmp02, tmp11, tmp12, tmp21, tmp22;

        if (in == out)
        {
            p = &tmp;
        }
        else
        {
            p = out;
        }

        det00 = (long)(((int64_t)in->rows[1].y * in->rows[2].z - (int64_t)in->rows[1].z * in->rows[2].y + (int64_t)0x800) >> 12);
        det10 = (long)(((int64_t)in->rows[1].x * in->rows[2].z - (int64_t)in->rows[1].z * in->rows[2].x + (int64_t)0x800) >> 12);
        det20 = (long)(((int64_t)in->rows[1].x * in->rows[2].y - (int64_t)in->rows[1].y * in->rows[2].x + (int64_t)0x800) >> 12);

        det = (long)(((int64_t)in->rows[0].x * det00 - (int64_t)in->rows[0].y * det10 + (int64_t)in->rows[0].z * det20
                      + (int64_t)0x800) >> 12);

        if (0 == det)
        {
            return -1;
        }

        fix32_QueueComputeReciprocal(det);

        tmp01 = (long)(((int64_t)in->rows[0].y * in->rows[2].z - (int64_t)in->rows[2].y * in->rows[0].z) >> 12);
        tmp02 = (long)(((int64_t)in->rows[0].y * in->rows[1].z - (int64_t)in->rows[1].y * in->rows[0].z) >> 12);
        tmp11 = (long)(((int64_t)in->rows[0].x * in->rows[2].z - (int64_t)in->rows[2].x * in->rows[0].z) >> 12);
        tmp12 = (long)(((int64_t)in->rows[0].x * in->rows[1].z - (int64_t)in->rows[1].x * in->rows[0].z) >> 12);

        det = fix32_GetDivisionResult();
        p->rows[0].x = (long)(((int64_t)det * det00) >> 12);
        p->rows[0].y = -(long)(((int64_t)det * tmp01) >> 12);
        p->rows[0].z = (long)(((int64_t)det * tmp02) >> 12);

        p->rows[1].x = -(long)(((int64_t)det * det10) >> 12);
        p->rows[1].y = (long)(((int64_t)det * tmp11) >> 12);
        p->rows[1].z = -(long)(((int64_t)det * tmp12) >> 12);

        p->rows[2].x = (long)(((int64_t)det * det20) >> 12);

        tmp21 = (long)(((int64_t)in->rows[0].x * in->rows[2].y - (int64_t)in->rows[2].x * in->rows[0].y) >> 12);
        p->rows[2].y = -(long)(((int64_t)det * tmp21) >> 12);

        tmp22 = (long)(((int64_t)in->rows[0].x * in->rows[1].y - (int64_t)in->rows[1].x * in->rows[0].y) >> 12);
        p->rows[2].z = (long)(((int64_t)det * tmp22) >> 12);

        if (p == &tmp)
        {
            func_020ca528(&tmp, out);
        }

        return 0;
    }

    // usa: func_020c15a4
    // MTX_Concat33
    void Mat3x3_Multiply(const Matrix3x3* inA, const Matrix3x3* inB, Matrix3x3* out)
    {
        Matrix3x3 tmp;
        Matrix3x3* p;
        register long x, y, z, xx, yy, zz;

        if (out == inB)
        {
            p = &tmp;
        }
        else
        {
            p = out;
        }

        // Row 0
        x = inA->rows[0].x;
        y = inA->rows[0].y;
        z = inA->rows[0].z;

        p->rows[0].x = (long)(((int64_t)x * inB->rows[0].x + (int64_t)y * inB->rows[1].x + (int64_t)z * inB->rows[2].x) >> 12);
        p->rows[0].y = (long)(((int64_t)x * inB->rows[0].y + (int64_t)y * inB->rows[1].y + (int64_t)z * inB->rows[2].y) >> 12);

        xx = inB->rows[0].z;
        yy = inB->rows[1].z;
        zz = inB->rows[2].z;

        p->rows[0].z = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12);

        // Row 1
        x = inA->rows[1].x;
        y = inA->rows[1].y;
        z = inA->rows[1].z;

        p->rows[1].z = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12);
        p->rows[1].y = (long)(((int64_t)x * inB->rows[0].y + (int64_t)y * inB->rows[1].y + (int64_t)z * inB->rows[2].y) >> 12);

        xx = inB->rows[0].x;
        yy = inB->rows[1].x;
        zz = inB->rows[2].x;

        p->rows[1].x = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12);

        // Row 2
        x = inA->rows[2].x;
        y = inA->rows[2].y;
        z = inA->rows[2].z;

        p->rows[2].x = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12);
        p->rows[2].y = (long)(((int64_t)x * inB->rows[0].y + (int64_t)y * inB->rows[1].y + (int64_t)z * inB->rows[2].y) >> 12);
        p->rows[2].z = (long)(((int64_t)x * inB->rows[0].z + (int64_t)y * inB->rows[1].z + (int64_t)z * inB->rows[2].z) >> 12);

        if (p == &tmp)
        {
            *out = tmp;
        }
    }

    // usa: func_020c17c4
    // MTX_MultVec33
    void Mat3x3_ApplyToVector(const Vector3fix* inVec, const Matrix3x3* inMat, Vector3fix* out)
    {
        register long x, y, z;

        x = inVec->x;
        y = inVec->y;
        z = inVec->z;

        out->x = (long)(((int64_t)x * inMat->rows[0].x + (int64_t)y * inMat->rows[1].x + (int64_t)z * inMat->rows[2].x) >> 12);
        out->y = (long)(((int64_t)x * inMat->rows[0].y + (int64_t)y * inMat->rows[1].y + (int64_t)z * inMat->rows[2].y) >> 12);
        out->z = (long)(((int64_t)x * inMat->rows[0].z + (int64_t)y * inMat->rows[1].z + (int64_t)z * inMat->rows[2].z) >> 12);
    }
}
