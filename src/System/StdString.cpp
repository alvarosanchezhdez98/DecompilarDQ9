#include <globaldefs.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's std_string.c: the string functions of the STD library

extern "C"
{
    int func_020d2ff0(const char* string);

    // STD_CopyLString: copies up to length - 1 characters and ends the copy, like strlcpy
    int func_020d2f28(char* dst, const char* src, int length)
    {
        int i;
        const char* s = src;
        for (i = 0; i < length - 1; i++)
        {
            dst[i] = *s;
            if (*s == '\0')
                break;
            s++;
        }
        if (i >= length - 1 && length != 0)
            dst[i] = '\0';
        return func_020d2ff0(src);
    }

    // STD_SearchString: like strstr
    // NONMATCHING: the C matches 46.2 %: only the registers differ (the original keeps the offset in the string in r5
    // and the pattern's character in r4), and no order of the declarations changes them.
#ifdef NONMATCHING
    char* func_020d2f88(const char* string, const char* pattern)
    {
        for (int i = 0; string[i] != '\0'; i++)
        {
            int j = 0;
            const char* s = &string[i];
            while (pattern[j] != '\0' && *s == pattern[j])
            {
                s++;
                j++;
            }
            if (pattern[j] == '\0')
                return (char*)&string[i];
        }
        return NULL;
    }
#else
    asm char* func_020d2f88(const char* string, const char* pattern)
    {
        stmdb sp!, {r3, r4, r5, lr}
        ldrsb r2, [r0, #0x0]
        mov r5, #0x0
        cmp r2, #0x0
        beq @L020d2ff8
        mov r3, r5
    @L020d2fb0:
        mov r12, r3
        add lr, r0, r5
        b @L020d2fc4
    @L020d2fbc:
        add lr, lr, #0x1
        add r12, r12, #0x1
    @L020d2fc4:
        ldrsb r4, [r1, r12]
        cmp r4, #0x0
        beq @L020d2fdc
        ldrsb r2, [lr, #0x0]
        cmp r2, r4
        beq @L020d2fbc
    @L020d2fdc:
        cmp r4, #0x0
        addeq r0, r0, r5
        ldmeqia sp!, {r3, r4, r5, pc}
        add r5, r5, #0x1
        ldrsb r2, [r0, r5]
        cmp r2, #0x0
        bne @L020d2fb0
    @L020d2ff8:
        mov r0, #0x0
        ldmia sp!, {r3, r4, r5, pc}
    }
#endif

    // STD_GetStringLength
    int func_020d2ff0(const char* string)
    {
        int length = 0;
        while (string[length] != '\0')
            length++;
        return length;
    }

    // STD_CompareString
    int func_020d3018(const char* string1, const char* string2)
    {
        while (*string1 == *string2 && *string1 != '\0')
        {
            string1++;
            string2++;
        }
        return *string1 - *string2;
    }

    // STD_CompareNString
    int func_020d3044(const char* string1, const char* string2, int length)
    {
        if (length != 0)
        {
            for (int i = 0; i < length; i++)
            {
                const int c1 = (unsigned char)string1[i];
                const int c2 = (unsigned char)string2[i];
                if (c1 != c2)
                    return c1 - c2;
            }
        }
        return 0;
    }
}
