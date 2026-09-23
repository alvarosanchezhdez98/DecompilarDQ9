#include "System/MathCoprocessor.h"
#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_vec.c: fixed-point 3D vectors. Its other functions aren't in the ROM.

extern "C"
{
    // usa: func_020c2d90
    // VEC_Add
    void Vector3fix_Add(const Vector3fix* a, const Vector3fix* b, Vector3fix* out)
    {
        out->x = a->x + b->x;
        out->y = a->y + b->y;
        out->z = a->z + b->z;
    }

    // usa: func_020c2dc4
    // VEC_Subtract
    void Vector3fix_Subtract(const Vector3fix* a, const Vector3fix* b, Vector3fix* out)
    {
        out->x = a->x - b->x;
        out->y = a->y - b->y;
        out->z = a->z - b->z;
    }

    // usa: func_020c2df8
    // VEC_DotProduct
    fix32_t Vector3fix_InnerProduct(const Vector3fix* a, const Vector3fix* b)
    {
        return (long)(((int64_t)a->x * b->x + (int64_t)a->y * b->y + (int64_t)a->z * b->z + (1 << 11)) >> 12);
    }

    // usa: func_020c2e34
    // VEC_CrossProduct
    void Vector3fix_CrossProduct(const Vector3fix* a, const Vector3fix* b, Vector3fix* out)
    {
        long x, y, z;

        x = (long)(((int64_t)a->y * b->z - (int64_t)a->z * b->y + (1 << 11)) >> 12);
        y = (long)(((int64_t)a->z * b->x - (int64_t)a->x * b->z + (1 << 11)) >> 12);
        z = (long)(((int64_t)a->x * b->y - (int64_t)a->y * b->x + (1 << 11)) >> 12);

        out->x = x;
        out->y = y;
        out->z = z;
    }

    // usa: func_020c2eb8
    // VEC_Mag
    fix32_t Vector3fix_Length(const Vector3fix* vec)
    {
        int64_t t, result;

        t = (int64_t)vec->x * vec->x;
        t += (int64_t)vec->y * vec->y;
        t += (int64_t)vec->z * vec->z;

        t <<= 2;

        StartSquareRoot64((uint64_t)t);
        result = ((long)GetSquareRootResult32() + 1) >> 1;
        return result;
    }

    // usa: func_020c2f18
    // VEC_Normalize
    void Vector3fix_Normalize(const Vector3fix* in, Vector3fix* out)
    {
        int64_t t;
        long root;

        t = (int64_t)in->x * in->x;
        t += (int64_t)in->y * in->y;
        t += (int64_t)in->z * in->z;

        StartDivision64_64(1LL << (12 + 12 + 32), (uint64_t)t);
        StartSquareRoot64((uint64_t)(t << 2));

        root = (long)GetSquareRootResult32();
        t = GetDivisionResult64();

        t = t * root;
        out->x = (long)((t * in->x + (1LL << (32 + 12))) >> (32 + 12 + 1));
        out->y = (long)((t * in->y + (1LL << (32 + 12))) >> (32 + 12 + 1));
        out->z = (long)((t * in->z + (1LL << (32 + 12))) >> (32 + 12 + 1));
    }

    // usa: func_020c3030
    // VEC_Distance
    fix32_t Vector3fix_Distance(const Vector3fix* a, const Vector3fix* b)
    {
        int64_t tmp, diff;

        diff = a->x - b->x;
        tmp = (int64_t)diff * diff;

        diff = a->y - b->y;
        tmp += (int64_t)diff * diff;

        diff = a->z - b->z;
        tmp += (int64_t)diff * diff;

        tmp <<= 2;
        StartSquareRoot64((uint64_t)tmp);

        return ((long)GetSquareRootResult32() + 1) >> 1;
    }
}
