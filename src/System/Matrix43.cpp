#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_mtx43.c: 4x3 matrices, affine transformations. Its other functions aren't in the ROM.

extern "C"
{
    // usa: func_020ca528
    // The NitroSDK's MI_Copy36B: copies 36 bytes
    void func_020ca528(const void* src, void* dst);
    // usa: func_020ca544
    // The NitroSDK's MI_Copy48B: copies 48 bytes
    void func_020ca544(const void* src, void* dst);

#ifdef __MWERKS__
    // usa: func_020c1840
    // MTX_Identity43_
    asm void Mat4x3_WriteIdentity(Matrix4x3* out)
    {
        mov r2, #0x1000
        mov r3, #0
        stmia r0!, {r2, r3}
        mov r1, #0
        stmia r0!, {r1, r3}
        stmia r0!, {r2, r3}
        stmia r0!, {r1, r3}
        stmia r0!, {r2, r3}
        stmia r0!, {r1, r3}
        bx lr
    }

    // usa: func_020c1868
    // MTX_Copy43To44_
    asm void Mat4x3_ConvertTo4x4(const Matrix4x3* in, Matrix4x4* out)
    {
        stmfd sp!, {r4}
        mov r12, #0
        ldmia r0!, {r2-r4}
        stmia r1!, {r2-r4, r12}
        ldmia r0!, {r2-r4}
        stmia r1!, {r2-r4, r12}
        ldmia r0!, {r2-r4}
        stmia r1!, {r2-r4, r12}
        mov r12, #0x1000
        ldmia r0!, {r2-r4}
        stmia r1!, {r2-r4, r12}
        ldmfd sp!, {r4}
        bx lr
    }
#endif

    // usa: func_020c189c
    // MTX_TransApply43
    void Mat4x3_ApplyTranslation(const Matrix4x3* in, Matrix4x3* out, fix32_t x, fix32_t y, fix32_t z)
    {
        if (in != out)
        {
            func_020ca528(in, out);
        }

        int64_t xx = x;
        int64_t yy = y;
        int64_t zz = z;

        out->rows[3].x = in->rows[3].x + (long)((xx * in->rows[0].x + yy * in->rows[1].x + zz * in->rows[2].x) >> 12);
        out->rows[3].y = in->rows[3].y + (long)((xx * in->rows[0].y + yy * in->rows[1].y + zz * in->rows[2].y) >> 12);
        out->rows[3].z = in->rows[3].z + (long)((xx * in->rows[0].z + yy * in->rows[1].z + zz * in->rows[2].z) >> 12);
    }

    // usa: func_020c1948
    // MTX_ScaleApply43
    void Mat4x3_ApplyScale(const Matrix4x3* in, Matrix4x3* out, fix32_t x, fix32_t y, fix32_t z)
    {
        Mat3x3_ApplyScale(&in->rotation, &out->rotation, x, y, z);

        out->rows[3].x = in->rows[3].x;
        out->rows[3].y = in->rows[3].y;
        out->rows[3].z = in->rows[3].z;
    }

#ifdef __MWERKS__
#pragma thumb on
    // usa: func_020c197c
    // MTX_RotX43_
    asm void Mat4x3_WriteRotationX(Matrix4x3* out, fix32_t sine, fix32_t cosine)
    {
        str r1, [r0, #20]
        neg r1, r1
        str r1, [r0, #28]
        mov r1, #1
        lsl r1, r1, #12
        stmia r0!, {r1}
        mov r3, #0
        mov r1, #0
        stmia r0!, {r1, r3}
        stmia r0!, {r1, r2}
        str r1, [r0, #4]
        add r0, #12
        stmia r0!, {r2, r3}
        stmia r0!, {r1, r3}
        bx lr
        lsl r0, r0, #0 // 0x0000: padding to align the next function, in the original's symbol
    }

    // usa: func_020c199c
    // MTX_RotY43_
    asm void Mat4x3_WriteRotationY(Matrix4x3* out, fix32_t sine, fix32_t cosine)
    {
        str r1, [r0, #24]
        mov r3, #0
        stmia r0!, {r2, r3}
        neg r1, r1
        stmia r0!, {r1, r3}
        mov r1, #1
        lsl r1, r1, #12
        stmia r0!, {r1, r3}
        add r0, #4
        mov r1, #0
        stmia r0!, {r1, r2, r3}
        stmia r0!, {r1, r3}
        bx lr
        lsl r0, r0, #0 // padding
    }

    // usa: func_020c19b8
    // MTX_RotZ43_
    asm void Mat4x3_WriteRotationZ(Matrix4x3* out, fix32_t sine, fix32_t cosine)
    {
        stmia r0!, {r2}
        mov r3, #0
        stmia r0!, {r1, r3}
        neg r1, r1
        stmia r0!, {r1, r2, r3}
        mov r1, #0
        mov r2, #0
        mov r3, #1
        lsl r3, r3, #12
        stmia r0!, {r1, r2, r3}
        mov r3, #0
        stmia r0!, {r1, r2, r3}
        bx lr
        lsl r0, r0, #0 // padding
    }
#pragma thumb off
#endif

    // usa: func_020c19d4
    // MTX_Inverse43
    int Mat4x3_Invert(const Matrix4x3* in, Matrix4x3* out)
    {
        Matrix4x3 tmp;
        Matrix4x3* p;
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

        p->rows[3].x = -(long)(((int64_t)p->rows[0].x * in->rows[3].x + (int64_t)p->rows[1].x * in->rows[3].y
                                + (int64_t)p->rows[2].x * in->rows[3].z) >> 12);

        p->rows[3].y = -(long)(((int64_t)p->rows[0].y * in->rows[3].x + (int64_t)p->rows[1].y * in->rows[3].y
                                + (int64_t)p->rows[2].y * in->rows[3].z) >> 12);

        p->rows[3].z = -(long)(((int64_t)p->rows[0].z * in->rows[3].x + (int64_t)p->rows[1].z * in->rows[3].y
                                + (int64_t)p->rows[2].z * in->rows[3].z) >> 12);

        if (p == &tmp)
        {
            func_020ca544(&tmp, out);
        }

        return 0;
    }

    // usa: func_020c1d60
    // MTX_Concat43
    void Mat4x3_Multiply(const Matrix4x3* inA, const Matrix4x3* inB, Matrix4x3* out)
    {
        Matrix4x3 tmp;
        Matrix4x3* p;
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
        xx = inB->rows[0].z;
        yy = inB->rows[1].z;
        zz = inB->rows[2].z;

        p->rows[2].z = (long)(((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12);

        // Row 3
        x = inA->rows[3].x;
        y = inA->rows[3].y;
        z = inA->rows[3].z;

        p->rows[3].z = (long)((((int64_t)x * xx + (int64_t)y * yy + (int64_t)z * zz) >> 12) + inB->rows[3].z);
        p->rows[3].y = (long)((((int64_t)x * inB->rows[0].y + (int64_t)y * inB->rows[1].y + (int64_t)z * inB->rows[2].y) >> 12)
                              + inB->rows[3].y);
        p->rows[3].x = (long)((((int64_t)x * inB->rows[0].x + (int64_t)y * inB->rows[1].x + (int64_t)z * inB->rows[2].x) >> 12)
                              + inB->rows[3].x);

        if (p == &tmp)
        {
            *out = tmp;
        }
    }

    // usa: func_020c2034
    // MTX_MultVec43
    void Mat4x3_ApplyToVector(const Vector3fix* inVec, const Matrix4x3* inMat, Vector3fix* out)
    {
        register long x, y, z;

        x = inVec->x;
        y = inVec->y;
        z = inVec->z;

        out->x = (long)(((int64_t)x * inMat->rows[0].x + (int64_t)y * inMat->rows[1].x + (int64_t)z * inMat->rows[2].x) >> 12);
        out->x += inMat->rows[3].x;

        out->y = (long)(((int64_t)x * inMat->rows[0].y + (int64_t)y * inMat->rows[1].y + (int64_t)z * inMat->rows[2].y) >> 12);
        out->y += inMat->rows[3].y;

        out->z = (long)(((int64_t)x * inMat->rows[0].z + (int64_t)y * inMat->rows[1].z + (int64_t)z * inMat->rows[2].z) >> 12);
        out->z += inMat->rows[3].z;
    }

    // usa: func_020c20d4
    // MTX_LookAt
    void Mat4x3_WriteViewMatrix(const Vector3fix* eye, const Vector3fix* up, const Vector3fix* target, Matrix4x3* out)
    {
        Vector3fix look;
        Vector3fix right;
        Vector3fix newUp;

        look.x = eye->x - target->x;
        look.y = eye->y - target->y;
        look.z = eye->z - target->z;
        Vector3fix_Normalize(&look, &look);
        Vector3fix_CrossProduct(up, &look, &right);
        Vector3fix_Normalize(&right, &right);
        Vector3fix_CrossProduct(&look, &right, &newUp);

        out->rows[0].x = right.x;
        out->rows[0].y = newUp.x;
        out->rows[0].z = look.x;
        out->rows[1].x = right.y;
        out->rows[1].y = newUp.y;
        out->rows[1].z = look.y;
        out->rows[2].x = right.z;
        out->rows[2].y = newUp.z;
        out->rows[2].z = look.z;

        out->rows[3].x = -Vector3fix_InnerProduct(eye, &right);
        out->rows[3].y = -Vector3fix_InnerProduct(eye, &newUp);
        out->rows[3].z = -Vector3fix_InnerProduct(eye, &look);
    }
}
