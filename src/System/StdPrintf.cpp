#include <globaldefs.h>
#include <stdarg.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's std_sprintf.c: the STD library's vsnprintf, which OS_Printf and the game use. It knows Shift JIS: the
// second byte of a character is never read as a '%'.

// Whether a byte starts a character of 2 bytes in Shift JIS (0x81-0x9f and 0xe0-0xfc)
#define IS_SJIS_LEAD_BYTE(c) ((unsigned int)((((unsigned char)(c)) ^ 0x20) - 0xa1) < 0x3c)

// Where the characters go: len is the room that's left in the buffer
struct PrintfOutput
{
    unsigned long len;
    char* cur;
    char* base;
};

// The flags of a conversion
enum
{
    FLAG_BLANK = 0x1,
    FLAG_PLUS = 0x2,
    FLAG_SHARP = 0x4,
    FLAG_MINUS = 0x8,
    FLAG_ZERO = 0x10,
    FLAG_L1 = 0x20,
    FLAG_H1 = 0x40,
    FLAG_L2 = 0x80,
    FLAG_H2 = 0x100,
    FLAG_UNSIGNED = 0x1000,
};

extern "C"
{
    // The runtime's division of 64-bit numbers, which the assembly of STD_TVSNPrintf calls
    unsigned long long _ll_udiv(unsigned long long dividend, unsigned long long divisor);

    // string_put_char
    static void func_020d3084(PrintfOutput* output, char c)
    {
        if (output->len != 0)
        {
            *output->cur = c;
            output->len--;
        }
        output->cur++;
    }

    // string_fill_char
    static void func_020d30b4(PrintfOutput* output, char c, int count)
    {
        if (count > 0)
        {
            unsigned long i;
            unsigned long n = output->len;
            if (n > (unsigned long)count)
                n = count;
            for (i = 0; i < n; i++)
                output->cur[i] = c;
            output->len -= n;
            output->cur += count;
        }
    }

    // string_put_string
    static void func_020d3108(PrintfOutput* output, const char* string, int count)
    {
        if (count > 0)
        {
            unsigned long i;
            unsigned long n = output->len;
            if (n > (unsigned long)count)
                n = count;
            for (i = 0; i < n; i++)
                output->cur[i] = string[i];
            output->len -= n;
            output->cur += count;
        }
    }

    // STD_TVSNPrintf
    // NONMATCHING: the C matches 64.5 %: the code is the same, but the compiler keeps the width in r11 and the arguments
    // on the stack, where the original keeps them in r10 and r11, so most registers differ.
#ifdef NONMATCHING
    int func_020d3160(char* dst, unsigned long len, const char* fmt, va_list args)
    {
        char buf[24];
        int bufCount;
        char prefix[2];
        const char* s = fmt;
        PrintfOutput output;
        output.len = len;
        output.cur = output.base = dst;
        while (*s != '\0')
        {
            if (IS_SJIS_LEAD_BYTE(*s))
            {
                func_020d3084(&output, *s++);
                if (*s != '\0')
                    func_020d3084(&output, *s++);
            }
            else if (*s != '%')
            {
                func_020d3084(&output, *s++);
            }
            else
            {
                int flag = 0;
                int width = 0;
                int precision = -1;
                int radix = 10;
                char hexChar = 'a' - 10;
                const char* const start = s;
                for (;;)
                {
                    switch (*++s)
                    {
                    case '+':
                        if (s[-1] != ' ')
                            break;
                        flag |= FLAG_PLUS;
                        continue;
                    case ' ':
                        flag |= FLAG_BLANK;
                        continue;
                    case '-':
                        flag |= FLAG_MINUS;
                        continue;
                    case '0':
                        flag |= FLAG_ZERO;
                        continue;
                    }
                    break;
                }
                if (*s == '*')
                {
                    ++s, width = va_arg(args, int);
                    if (width < 0)
                        width = -width, flag |= FLAG_MINUS;
                }
                else
                {
                    while (*s >= '0' && *s <= '9')
                        width = width * 10 + *s++ - '0';
                }
                if (*s == '.')
                {
                    ++s, precision = 0;
                    if (*s == '*')
                    {
                        ++s, precision = va_arg(args, int);
                        if (precision < 0)
                            precision = -1;
                    }
                    else
                    {
                        while (*s >= '0' && *s <= '9')
                            precision = precision * 10 + *s++ - '0';
                    }
                }
                switch (*s)
                {
                case 'h':
                    if (*++s != 'h')
                        flag |= FLAG_H1;
                    else
                        ++s, flag |= FLAG_H2;
                    break;
                case 'l':
                    if (*++s != 'l')
                        flag |= FLAG_L1;
                    else
                        ++s, flag |= FLAG_L2;
                    break;
                }
                switch (*s)
                {
                case 'd':
                case 'i':
                    goto putInteger;
                case 'o':
                    flag |= FLAG_UNSIGNED;
                    radix = 8;
                    goto putInteger;
                case 'u':
                    flag |= FLAG_UNSIGNED;
                    goto putInteger;
                case 'X':
                    hexChar = 'A' - 10;
                    goto putHexadecimal;
                case 'x':
                    goto putHexadecimal;
                case 'p':
                    // Like "%#010x"
                    flag |= FLAG_SHARP;
                    precision = 8;
                    goto putHexadecimal;
                case 'c':
                    if (precision >= 0)
                        goto putInvalid;
                    {
                        const int c = va_arg(args, int);
                        width -= 1;
                        if (flag & FLAG_MINUS)
                        {
                            func_020d3084(&output, c);
                            func_020d30b4(&output, ' ', width);
                        }
                        else
                        {
                            const char pad = flag & FLAG_ZERO ? '0' : ' ';
                            func_020d30b4(&output, pad, width);
                            func_020d3084(&output, c);
                        }
                        ++s;
                    }
                    break;
                case 's':
                {
                    int count = 0;
                    const char* const string = va_arg(args, const char*);
                    if (precision < 0)
                    {
                        while (string[count] != '\0')
                            ++count;
                    }
                    else
                    {
                        while (count < precision && string[count] != '\0')
                            ++count;
                    }
                    width -= count;
                    if (flag & FLAG_MINUS)
                    {
                        func_020d3108(&output, string, count);
                        func_020d30b4(&output, ' ', width);
                    }
                    else
                    {
                        const char pad = flag & FLAG_ZERO ? '0' : ' ';
                        func_020d30b4(&output, pad, width);
                        func_020d3108(&output, string, count);
                    }
                    ++s;
                    break;
                }
                case 'n':
                {
                    const int count = output.cur - output.base;
                    if (flag & FLAG_H2)
                        ;
                    else if (flag & FLAG_H1)
                        *va_arg(args, short*) = count;
                    else if (flag & FLAG_L2)
                        *va_arg(args, unsigned long long*) = count;
                    else
                        *va_arg(args, int*) = count;
                    ++s;
                    break;
                }
                case '%':
                    if (start + 1 != s)
                        goto putInvalid;
                    func_020d3084(&output, *s++);
                    break;
                default:
                    goto putInvalid;
                putInvalid:
                    func_020d3108(&output, start, s - start);
                    break;
                putHexadecimal:
                    flag |= FLAG_UNSIGNED;
                    radix = 16;
                putInteger:
                {
                    unsigned long long value = 0;
                    int prefixCount = 0;
                    if (flag & FLAG_MINUS)
                        flag &= ~FLAG_ZERO;
                    if (precision < 0)
                        precision = 1;
                    else
                        flag &= ~FLAG_ZERO;
                    if (flag & FLAG_UNSIGNED)
                    {
                        if (flag & FLAG_H2)
                            value = va_arg(args, unsigned char);
                        else if (flag & FLAG_H1)
                            value = va_arg(args, unsigned short);
                        else if (!(flag & FLAG_L2))
                            value = va_arg(args, unsigned long);
                        else
                            value = va_arg(args, unsigned long long);
                        flag &= ~(FLAG_PLUS | FLAG_BLANK);
                        if (flag & FLAG_SHARP)
                        {
                            if (radix == 16)
                            {
                                if (value != 0)
                                {
                                    prefix[0] = hexChar + (10 + 'x' - 'a');
                                    prefix[1] = '0';
                                    prefixCount = 2;
                                }
                            }
                            else if (radix == 8)
                            {
                                prefix[0] = '0';
                                prefixCount = 1;
                            }
                        }
                    }
                    else
                    {
                        if (flag & FLAG_H2)
                            value = va_arg(args, signed char);
                        else if (flag & FLAG_H1)
                            value = va_arg(args, short);
                        else if (!(flag & FLAG_L2))
                            value = va_arg(args, long);
                        else
                            value = va_arg(args, unsigned long long);
                        if ((value >> 32) & 0x80000000)
                        {
                            value = ~value + 1;
                            prefix[0] = '-';
                            prefixCount = 1;
                        }
                        else if (value != 0 || precision != 0)
                        {
                            if (flag & FLAG_PLUS)
                            {
                                prefix[0] = '+';
                                prefixCount = 1;
                            }
                            else if (flag & FLAG_BLANK)
                            {
                                prefix[0] = ' ';
                                prefixCount = 1;
                            }
                        }
                    }
                    bufCount = 0;
                    switch (radix)
                    {
                    case 8:
                        while (value != 0)
                        {
                            const int digit = value & 7;
                            value >>= 3;
                            buf[bufCount++] = digit + '0';
                        }
                        break;
                    case 10:
                        if ((value >> 32) == 0)
                        {
                            unsigned long v = value;
                            while (v != 0)
                            {
                                const unsigned long quotient = v / 10;
                                const int digit = v - quotient * 10;
                                v = quotient;
                                buf[bufCount++] = digit + '0';
                            }
                        }
                        else
                        {
                            while (value != 0)
                            {
                                const unsigned long long quotient = value / 10;
                                const int digit = value - quotient * 10;
                                value = quotient;
                                buf[bufCount++] = digit + '0';
                            }
                        }
                        break;
                    case 16:
                        while (value != 0)
                        {
                            const int digit = value & 0xf;
                            value >>= 4;
                            buf[bufCount++] = digit < 10 ? digit + '0' : digit + hexChar;
                        }
                        break;
                    }
                    if (prefixCount > 0 && prefix[0] == '0')
                    {
                        prefixCount = 0;
                        buf[bufCount++] = '0';
                    }
                    {
                        int padCount = precision - bufCount;
                        if (flag & FLAG_ZERO)
                        {
                            if (padCount < width - bufCount - prefixCount)
                                padCount = width - bufCount - prefixCount;
                        }
                        if (padCount > 0)
                            width -= padCount;
                        width -= prefixCount + bufCount;
                        if (!(flag & FLAG_MINUS))
                            func_020d30b4(&output, ' ', width);
                        while (prefixCount > 0)
                            func_020d3084(&output, prefix[--prefixCount]);
                        func_020d30b4(&output, '0', padCount);
                        while (bufCount > 0)
                            func_020d3084(&output, buf[--bufCount]);
                        if (flag & FLAG_MINUS)
                            func_020d30b4(&output, ' ', width);
                        ++s;
                    }
                }
                    break;
                }
            }
        }
        if (output.len != 0)
            *output.cur = '\0';
        else if (len != 0)
            output.base[len - 1] = '\0';
        return output.cur - output.base;
    }
#else
    asm int func_020d3160(char* dst, unsigned long len, const char* fmt, va_list args)
    {
        stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
        sub sp, sp, #0x30
        mov r9, r2
        str r1, [sp, #0xc]
        str r0, [sp, #0x14]
        str r0, [sp, #0x10]
        ldrsb r0, [r9, #0x0]
        str r1, [sp, #0x0]
        mov r11, r3
        cmp r0, #0x0
        beq @L020d399c
    @L020d319c:
        ldrsb r1, [r9, #0x0]
        and r0, r1, #0xff
        eor r0, r0, #0x20
        sub r0, r0, #0xa1
        cmp r0, #0x3c
        bhs @L020d31d8
        add r0, sp, #0xc
        bl func_020d3084
        ldrsb r1, [r9, #0x1]!
        cmp r1, #0x0
        beq @L020d3990
        add r0, sp, #0xc
        add r9, r9, #0x1
        bl func_020d3084
        b @L020d3990
    @L020d31d8:
        cmp r1, #0x25
        beq @L020d31f0
        add r0, sp, #0xc
        add r9, r9, #0x1
        bl func_020d3084
        b @L020d3990
    @L020d31f0:
        mov r5, #0x0
        mov r10, r5
        mov r2, r9
        sub r6, r5, #0x1
        mov r0, #0xa
        mov r3, #0x57
    @L020d3208:
        ldrsb r4, [r9, #0x1]!
        cmp r4, #0x20
        bgt @L020d321c
        beq @L020d3258
        b @L020d3270
    @L020d321c:
        cmp r4, #0x30
        bgt @L020d3270
        cmp r4, #0x2b
        blt @L020d3270
        beq @L020d3244
        cmp r4, #0x2d
        beq @L020d3260
        cmp r4, #0x30
        beq @L020d3268
        b @L020d3270
    @L020d3244:
        ldrsb r1, [r9, #-0x1]
        cmp r1, #0x20
        bne @L020d3270
        orr r5, r5, #0x2
        b @L020d3208
    @L020d3258:
        orr r5, r5, #0x1
        b @L020d3208
    @L020d3260:
        orr r5, r5, #0x8
        b @L020d3208
    @L020d3268:
        orr r5, r5, #0x10
        b @L020d3208
    @L020d3270:
        cmp r4, #0x2a
        bne @L020d3294
        add r11, r11, #0x4
        ldr r10, [r11, #-0x4]
        add r9, r9, #0x1
        cmp r10, #0x0
        rsblt r10, r10, #0x0
        orrlt r5, r5, #0x8
        b @L020d32bc
    @L020d3294:
        mov r1, #0xa
        b @L020d32a8
    @L020d329c:
        ldrsb r4, [r9], #0x1
        mla r4, r10, r1, r4
        sub r10, r4, #0x30
    @L020d32a8:
        ldrsb r4, [r9, #0x0]
        cmp r4, #0x30
        blt @L020d32bc
        cmp r4, #0x39
        ble @L020d329c
    @L020d32bc:
        ldrsb r1, [r9, #0x0]
        cmp r1, #0x2e
        bne @L020d3318
        ldrsb r1, [r9, #0x1]!
        mov r6, #0x0
        cmp r1, #0x2a
        bne @L020d32f0
        add r11, r11, #0x4
        ldr r6, [r11, #-0x4]
        add r9, r9, #0x1
        cmp r6, #0x0
        mvnlt r6, #0x0
        b @L020d3318
    @L020d32f0:
        mov r1, #0xa
        b @L020d3304
    @L020d32f8:
        ldrsb r4, [r9], #0x1
        mla r4, r6, r1, r4
        sub r6, r4, #0x30
    @L020d3304:
        ldrsb r4, [r9, #0x0]
        cmp r4, #0x30
        blt @L020d3318
        cmp r4, #0x39
        ble @L020d32f8
    @L020d3318:
        ldrsb r1, [r9, #0x0]
        cmp r1, #0x68
        beq @L020d3330
        cmp r1, #0x6c
        beq @L020d3348
        b @L020d335c
    @L020d3330:
        ldrsb r1, [r9, #0x1]!
        cmp r1, #0x68
        orrne r5, r5, #0x40
        addeq r9, r9, #0x1
        orreq r5, r5, #0x100
        b @L020d335c
    @L020d3348:
        ldrsb r1, [r9, #0x1]!
        cmp r1, #0x6c
        orrne r5, r5, #0x20
        addeq r9, r9, #0x1
        orreq r5, r5, #0x80
    @L020d335c:
        ldrsb r1, [r9, #0x0]
        cmp r1, #0x69
        bgt @L020d33a0
        cmp r1, #0x63
        blt @L020d3384
        beq @L020d3410
        cmp r1, #0x64
        cmpne r1, #0x69
        beq @L020d35c8
        b @L020d35ac
    @L020d3384:
        cmp r1, #0x25
        bgt @L020d3394
        beq @L020d3590
        b @L020d35ac
    @L020d3394:
        cmp r1, #0x58
        beq @L020d33fc
        b @L020d35ac
    @L020d33a0:
        cmp r1, #0x6e
        bgt @L020d33b0
        beq @L020d3538
        b @L020d35ac
    @L020d33b0:
        sub r1, r1, #0x6f
        cmp r1, #0x9
        addls pc, pc, r1, lsl #0x2
        b @L020d35ac
    @L020d33c0:
        b @L020d33e8
        b @L020d3404
        b @L020d35ac
        b @L020d35ac
        b @L020d3484
        b @L020d35ac
        b @L020d33f4
        b @L020d35ac
        b @L020d35ac
        b @L020d35c0
    @L020d33e8:
        orr r5, r5, #0x1000
        mov r0, #0x8
        b @L020d35c8
    @L020d33f4:
        orr r5, r5, #0x1000
        b @L020d35c8
    @L020d33fc:
        mov r3, #0x37
        b @L020d35c0
    @L020d3404:
        orr r5, r5, #0x4
        mov r6, #0x8
        b @L020d35c0
    @L020d3410:
        cmp r6, #0x0
        bge @L020d35ac
        add r11, r11, #0x4
        tst r5, #0x8
        ldr r4, [r11, #-0x4]
        beq @L020d344c
        mov r1, r4, lsl #0x18
        add r0, sp, #0xc
        mov r1, r1, asr #0x18
        bl func_020d3084
        add r0, sp, #0xc
        sub r2, r10, #0x1
        mov r1, #0x20
        bl func_020d30b4
        b @L020d347c
    @L020d344c:
        tst r5, #0x10
        movne r0, #0x30
        moveq r0, #0x20
        mov r1, r0, lsl #0x18
        add r0, sp, #0xc
        mov r1, r1, asr #0x18
        sub r2, r10, #0x1
        bl func_020d30b4
        mov r1, r4, lsl #0x18
        add r0, sp, #0xc
        mov r1, r1, asr #0x18
        bl func_020d3084
    @L020d347c:
        add r9, r9, #0x1
        b @L020d3990
    @L020d3484:
        add r11, r11, #0x4
        cmp r6, #0x0
        ldr r7, [r11, #-0x4]
        mov r4, #0x0
        bge @L020d34bc
        ldrsb r0, [r7, #0x0]
        cmp r0, #0x0
        beq @L020d34d0
    @L020d34a4:
        add r4, r4, #0x1
        ldrsb r0, [r7, r4]
        cmp r0, #0x0
        bne @L020d34a4
        b @L020d34d0
    @L020d34b8:
        add r4, r4, #0x1
    @L020d34bc:
        cmp r4, r6
        bge @L020d34d0
        ldrsb r0, [r7, r4]
        cmp r0, #0x0
        bne @L020d34b8
    @L020d34d0:
        tst r5, #0x8
        sub r10, r10, r4
        beq @L020d3500
        add r0, sp, #0xc
        mov r1, r7
        mov r2, r4
        bl func_020d3108
        add r0, sp, #0xc
        mov r2, r10
        mov r1, #0x20
        bl func_020d30b4
        b @L020d3530
    @L020d3500:
        tst r5, #0x10
        movne r0, #0x30
        moveq r0, #0x20
        mov r1, r0, lsl #0x18
        add r0, sp, #0xc
        mov r2, r10
        mov r1, r1, asr #0x18
        bl func_020d30b4
        add r0, sp, #0xc
        mov r1, r7
        mov r2, r4
        bl func_020d3108
    @L020d3530:
        add r9, r9, #0x1
        b @L020d3990
    @L020d3538:
        ldr r1, [sp, #0x10]
        ldr r0, [sp, #0x14]
        tst r5, #0x100
        sub r2, r1, r0
        bne @L020d3588
        tst r5, #0x40
        beq @L020d3564
        add r11, r11, #0x4
        ldr r0, [r11, #-0x4]
        strh r2, [r0, #0x0]
        b @L020d3588
    @L020d3564:
        add r11, r11, #0x4
        tst r5, #0x80
        ldreq r0, [r11, #-0x4]
        streq r2, [r0, #0x0]
        beq @L020d3588
        ldr r0, [r11, #-0x4]
        mov r1, r2, asr #0x1f
        str r2, [r0, #0x0]
        str r1, [r0, #0x4]
    @L020d3588:
        add r9, r9, #0x1
        b @L020d3990
    @L020d3590:
        add r0, r2, #0x1
        cmp r0, r9
        bne @L020d35ac
        add r0, sp, #0xc
        add r9, r9, #0x1
        bl func_020d3084
        b @L020d3990
    @L020d35ac:
        mov r1, r2
        add r0, sp, #0xc
        sub r2, r9, r2
        bl func_020d3108
        b @L020d3990
    @L020d35c0:
        orr r5, r5, #0x1000
        mov r0, #0x10
    @L020d35c8:
        tst r5, #0x8
        bicne r5, r5, #0x10
        cmp r6, #0x0
        bicge r5, r5, #0x10
        movlt r6, #0x1
        mov r4, #0x0
        tst r5, #0x1000
        beq @L020d3688
        tst r5, #0x100
        beq @L020d3600
        add r11, r11, #0x4
        ldrb r7, [r11, #-0x4]
        mov r1, #0x0
        b @L020d3638
    @L020d3600:
        tst r5, #0x40
        beq @L020d3618
        add r11, r11, #0x4
        ldrh r7, [r11, #-0x4]
        mov r1, #0x0
        b @L020d3638
    @L020d3618:
        tst r5, #0x80
        addeq r11, r11, #0x4
        ldreq r7, [r11, #-0x4]
        moveq r1, #0x0
        beq @L020d3638
        add r11, r11, #0x8
        ldr r7, [r11, #-0x8]
        ldr r1, [r11, #-0x4]
    @L020d3638:
        bic r5, r5, #0x3
        tst r5, #0x4
        beq @L020d3748
        cmp r0, #0x10
        bne @L020d3670
        cmp r1, #0x0
        cmpeq r7, #0x0
        beq @L020d3748
        add r4, r3, #0x21
        mov r2, #0x30
        strb r4, [sp, #0x8]
        strb r2, [sp, #0x9]
        mov r4, #0x2
        b @L020d3748
    @L020d3670:
        cmp r0, #0x8
        bne @L020d3748
        mov r2, #0x30
        strb r2, [sp, #0x8]
        mov r4, #0x1
        b @L020d3748
    @L020d3688:
        tst r5, #0x100
        beq @L020d36a0
        add r11, r11, #0x4
        ldrsb r7, [r11, #-0x4]
        mov r1, r7, asr #0x1f
        b @L020d36d8
    @L020d36a0:
        tst r5, #0x40
        beq @L020d36b8
        add r11, r11, #0x4
        ldrsh r7, [r11, #-0x4]
        mov r1, r7, asr #0x1f
        b @L020d36d8
    @L020d36b8:
        tst r5, #0x80
        addeq r11, r11, #0x4
        ldreq r7, [r11, #-0x4]
        moveq r1, r7, asr #0x1f
        beq @L020d36d8
        add r11, r11, #0x8
        ldr r7, [r11, #-0x8]
        ldr r1, [r11, #-0x4]
    @L020d36d8:
        mov r12, #0x0
        and r2, r12, #0x0
        and r8, r1, #0x80000000
        cmp r2, #0x0
        cmpeq r8, #0x0
        beq @L020d3710
        mvn r4, r7
        mov r2, #0x2d
        mvn r1, r1
        strb r2, [sp, #0x8]
        adds r7, r4, #0x1
        adc r1, r1, r12
        mov r4, #0x1
        b @L020d3748
    @L020d3710:
        cmp r1, r12
        cmpeq r7, r12
        cmpeq r6, #0x0
        beq @L020d3748
        tst r5, #0x2
        beq @L020d3738
        mov r2, #0x2b
        strb r2, [sp, #0x8]
        mov r4, #0x1
        b @L020d3748
    @L020d3738:
        tst r5, #0x1
        movne r2, #0x20
        strneb r2, [sp, #0x8]
        movne r4, #0x1
    @L020d3748:
        cmp r0, #0x8
        mov r8, #0x0
        beq @L020d3768
        cmp r0, #0xa
        beq @L020d37b4
        cmp r0, #0x10
        beq @L020d384c
        b @L020d3898
    @L020d3768:
        cmp r1, r8
        cmpeq r7, r8
        beq @L020d3898
        add r2, sp, #0x18
        mov r0, r8
        mov lr, #0x7
        mov r12, r8
    @L020d3784:
        and r3, r7, lr
        add r3, r3, #0x30
        strb r3, [r2, r8]
        mov r3, r1, lsr #0x3
        cmp r3, r0
        mov r7, r7, lsr #0x3
        orr r7, r7, r1, lsl #0x1d
        mov r1, r3
        cmpeq r7, r12
        add r8, r8, #0x1
        bne @L020d3784
        b @L020d3898
    @L020d37b4:
        mov r0, r8
        cmp r0, r8
        cmpeq r1, r8
        bne @L020d3800
        cmp r7, #0x0
        beq @L020d3898
        ldr r12, =0xcccccccd
        add r3, sp, #0x18
        mov r2, #0xa
    @L020d37d8:
        umull r1, r0, r7, r12
        movs r0, r0, lsr #0x3
        mul r1, r0, r2
        sub r1, r7, r1
        mov r7, r0
        add r0, r1, #0x30
        strb r0, [r3, r8]
        add r8, r8, #0x1
        bne @L020d37d8
        b @L020d3898
    @L020d3800:
        cmp r1, r8
        cmpeq r7, r8
        beq @L020d3898
    @L020d380c:
        mov r0, r7
        mov r2, #0xa
        mov r3, #0x0
        bl _ll_udiv
        mov r2, #0xa
        umull r3, r2, r0, r2
        subs r2, r7, r3
        add r3, r2, #0x30
        add r2, sp, #0x18
        strb r3, [r2, r8]
        cmp r1, #0x0
        cmpeq r0, #0x0
        mov r7, r0
        add r8, r8, #0x1
        bne @L020d380c
        b @L020d3898
    @L020d384c:
        cmp r1, r8
        cmpeq r7, r8
        beq @L020d3898
        add r12, sp, #0x18
        mov lr, #0xf
    @L020d3860:
        and r2, r7, lr
        mov r7, r7, lsr #0x4
        mov r0, r1, lsr #0x4
        orr r7, r7, r1, lsl #0x1c
        cmp r2, #0xa
        mov r1, r0
        addlt r0, r2, #0x30
        addge r0, r2, r3
        strb r0, [r12, r8]
        mov r0, #0x0
        cmp r1, r0
        cmpeq r7, r0
        add r8, r8, #0x1
        bne @L020d3860
    @L020d3898:
        cmp r4, #0x0
        ble @L020d38c0
        ldrsb r0, [sp, #0x8]
        cmp r0, #0x30
        bne @L020d38c0
        add r0, sp, #0x18
        mov r1, #0x30
        strb r1, [r0, r8]
        add r8, r8, #0x1
        mov r4, #0x0
    @L020d38c0:
        tst r5, #0x10
        sub r6, r6, r8
        beq @L020d38dc
        sub r0, r10, r8
        sub r0, r0, r4
        cmp r6, r0
        movlt r6, r0
    @L020d38dc:
        cmp r6, #0x0
        subgt r10, r10, r6
        add r0, r4, r8
        sub r10, r10, r0
        ands r0, r5, #0x8
        str r0, [sp, #0x4]
        bne @L020d3908
        add r0, sp, #0xc
        mov r2, r10
        mov r1, #0x20
        bl func_020d30b4
    @L020d3908:
        cmp r4, #0x0
        ble @L020d3934
        add r0, sp, #0x8
        add r5, r0, r4
        add r7, sp, #0xc
    @L020d391c:
        ldrsb r1, [r5, #-0x1]!
        mov r0, r7
        sub r4, r4, #0x1
        bl func_020d3084
        cmp r4, #0x0
        bgt @L020d391c
    @L020d3934:
        add r0, sp, #0xc
        mov r2, r6
        mov r1, #0x30
        bl func_020d30b4
        cmp r8, #0x0
        ble @L020d3970
        add r0, sp, #0x18
        add r5, r0, r8
        add r4, sp, #0xc
    @L020d3958:
        ldrsb r1, [r5, #-0x1]!
        mov r0, r4
        sub r8, r8, #0x1
        bl func_020d3084
        cmp r8, #0x0
        bgt @L020d3958
    @L020d3970:
        ldr r0, [sp, #0x4]
        cmp r0, #0x0
        beq @L020d398c
        add r0, sp, #0xc
        mov r2, r10
        mov r1, #0x20
        bl func_020d30b4
    @L020d398c:
        add r9, r9, #0x1
    @L020d3990:
        ldrsb r0, [r9, #0x0]
        cmp r0, #0x0
        bne @L020d319c
    @L020d399c:
        ldr r0, [sp, #0xc]
        cmp r0, #0x0
        beq @L020d39b8
        ldr r0, [sp, #0x10]
        mov r1, #0x0
        strb r1, [r0, #0x0]
        b @L020d39d4
    @L020d39b8:
        ldr r0, [sp, #0x0]
        cmp r0, #0x0
        beq @L020d39d4
        ldr r1, [sp, #0x14]
        mov r2, #0x0
        add r0, r1, r0
        strb r2, [r0, #-0x1]
    @L020d39d4:
        ldr r1, [sp, #0x10]
        ldr r0, [sp, #0x14]
        sub r0, r1, r0
        add sp, sp, #0x30
        ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
    }
#endif
}
