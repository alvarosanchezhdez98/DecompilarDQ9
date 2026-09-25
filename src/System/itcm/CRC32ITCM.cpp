#include <globaldefs.h>

// The CRC-32 that identifies the files by their paths (see GPC.cpp and ExtendedNitroVM.cpp), in the ITCM

// The table of the reflected CRC-32 (polynomial 0xedb88320)
extern const unsigned long data_020ee278[256];

extern "C"
{
    unsigned long func_01ff85f0(unsigned char byte, unsigned long crc);

    // The CRC-32 of some data
    unsigned long func_01ff85b8(const unsigned char* data, unsigned long length)
    {
        unsigned long crc = 0xffffffff;
        if (data != NULL)
        {
            for (; length != 0; length--)
                crc = func_01ff85f0(*data++, crc);
        }
        return ~crc;
    }

    // Adds a byte to a CRC-32
    unsigned long func_01ff85f0(unsigned char byte, unsigned long crc)
    {
        return data_020ee278[(crc ^ byte) & 0xff] ^ (crc >> 8);
    }

    // The CRC-32 of a string (the other files declare it with a `const char*`)
    unsigned long func_01ff860c(const unsigned char* string)
    {
        unsigned long crc = 0xffffffff;
        if (string != NULL)
        {
            for (; *string != '\0'; string++)
                crc = func_01ff85f0(*string, crc);
        }
        return ~crc;
    }
}
