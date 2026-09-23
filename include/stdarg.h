#pragma once

// Variable arguments like MWCC's for ARM: the arguments are on the stack, aligned to 4 bytes

typedef char* va_list;

#define __va_align(size) ((((unsigned long)(size)) + 3U) & ~3U)
#define va_start(ap, parm) ((ap) = (va_list)((char*)((unsigned long)&(parm) & ~3U) + __va_align(sizeof(parm))))
#define va_arg(ap, type) (*(type*)(((ap) += __va_align(sizeof(type))) - __va_align(sizeof(type))))
#define va_end(ap) ((void)0)
