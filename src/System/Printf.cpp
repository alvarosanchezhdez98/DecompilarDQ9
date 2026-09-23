#include <stdarg.h>

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's os_printf.c: formats strings with the standard library's STD_TVSNPrintf

extern "C"
{
    // usa: func_020d3160
    // STD_TVSNPrintf, the standard library's vsnprintf
    int func_020d3160(char* dst, unsigned long len, const char* fmt, va_list args);

    int func_020c7158(char* dst, const char* fmt, va_list args);
    int func_020c7198(char* dst, unsigned long len, const char* fmt, va_list args);

    // usa: func_020c7130
    // OS_SPrintf
    int func_020c7130(char* dst, const char* fmt, ...)
    {
        int length;
        va_list args;
        va_start(args, fmt);
        length = func_020c7158(dst, fmt, args);
        va_end(args);
        return length;
    }

    // usa: func_020c7158
    // OS_VSPrintf
    int func_020c7158(char* dst, const char* fmt, va_list args)
    {
        return func_020c7198(dst, 0x7fffffff, fmt, args);
    }

    // usa: func_020c7170
    // OS_SNPrintf
    int func_020c7170(char* dst, unsigned long len, const char* fmt, ...)
    {
        int length;
        va_list args;
        va_start(args, fmt);
        length = func_020c7198(dst, len, fmt, args);
        va_end(args);
        return length;
    }

    // usa: func_020c7198
    // OS_VSNPrintf
    int func_020c7198(char* dst, unsigned long len, const char* fmt, va_list args)
    {
        return func_020d3160(dst, len, fmt, args);
    }
}
