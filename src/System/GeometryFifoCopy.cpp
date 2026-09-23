// The NitroSDK's gxasm.c: copies data to the geometry FIFO with multiple loads and stores

extern "C"
{
#ifdef __MWERKS__
    // usa: func_020c6914
    // GX_SendFifo48B: copies 48 bytes (a 4x3 matrix) to the geometry FIFO
    asm void func_020c6914(register const void* src, register volatile void* fifo)
    {
        ldmia r0!, {r2, r3, r12}
        stmia r1, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1, {r2, r3, r12}
        ldmia r0!, {r2, r3, r12}
        stmia r1, {r2, r3, r12}
        bx lr
    }

    // usa: func_020c6938
    // GX_SendFifo64B: copies 64 bytes (a 4x4 matrix) to the geometry FIFO
    asm void func_020c6938(register const void* src, register volatile void* fifo)
    {
        stmfd sp!, {r4-r8}
        ldmia r0!, {r2-r8, r12}
        stmia r1, {r2-r8, r12}
        ldmia r0!, {r2-r8, r12}
        stmia r1, {r2-r8, r12}
        ldmfd sp!, {r4-r8}
        bx lr
    }
#else
    void func_020c6914(const void* src, volatile void* fifo)
    {
        for (int i = 0; i < 12; i++)
            *(volatile unsigned int*)fifo = ((const unsigned int*)src)[i];
    }

    void func_020c6938(const void* src, volatile void* fifo)
    {
        for (int i = 0; i < 16; i++)
            *(volatile unsigned int*)fifo = ((const unsigned int*)src)[i];
    }
#endif
}
