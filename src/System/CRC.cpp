#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's crc.c: CRC-8, CRC-16 and CRC-32 with a table. Only the variants that the game uses are in the ROM:
// CRC-8 and the reflected ("Rev") CRC-16 and CRC-32.

// MATHCRC8Table, MATHCRC16Table and MATHCRC32Table
struct CRC8Table
{
    unsigned char table[256];
};

struct CRC16Table
{
    unsigned short table[256];
};

struct CRC32Table
{
    unsigned long table[256];
};

extern "C"
{
    void func_020d1b68(const CRC8Table* table, unsigned char* context, const void* input, unsigned long length);
    void func_020d1be4(const CRC16Table* table, unsigned short* context, const void* input, unsigned long length);
    void func_020d1c64(const CRC32Table* table, unsigned long* context, const void* input, unsigned long length);

    // usa: func_020d1b28
    // MATHi_CRC8InitTable
    void func_020d1b28(CRC8Table* table, unsigned char poly)
    {
        unsigned long r;
        unsigned long i, j;
        unsigned char* t = table->table;

        for (i = 0; i < 256; i++)
        {
            r = i;
            for (j = 0; j < 8; j++)
            {
                if (r & 0x80)
                {
                    r = (r << 1) ^ poly;
                }
                else
                {
                    r <<= 1;
                }
            }
            t[i] = (unsigned char)r;
        }
    }

    // usa: func_020d1b68
    // MATHi_CRC8Update
    void func_020d1b68(const CRC8Table* table, unsigned char* context, const void* input, unsigned long length)
    {
        unsigned long r;
        unsigned long i;
        const unsigned char* t = table->table;
        unsigned char* data = (unsigned char*)input;

        r = (unsigned long)*context;
        for (i = 0; i < length; i++)
        {
            r = t[(r ^ *data) & 0xff];
            data++;
        }
        *context = (unsigned char)r;
    }

    // usa: func_020d1ba0
    // MATHi_CRC16InitTableRev
    void func_020d1ba0(CRC16Table* table, unsigned short poly)
    {
        unsigned long r;
        unsigned long i, j;
        unsigned short* t = table->table;

        for (i = 0; i < 256; i++)
        {
            r = i;
            for (j = 0; j < 8; j++)
            {
                if (r & 1)
                {
                    r = (r >> 1) ^ poly;
                }
                else
                {
                    r >>= 1;
                }
            }
            t[i] = (unsigned short)r;
        }
    }

    // usa: func_020d1be4
    // MATHi_CRC16UpdateRev
    void func_020d1be4(const CRC16Table* table, unsigned short* context, const void* input, unsigned long length)
    {
        unsigned long r;
        unsigned long i;
        const unsigned short* t = table->table;
        unsigned char* data = (unsigned char*)input;

        r = (unsigned long)*context;
        for (i = 0; i < length; i++)
        {
            r = (r >> 8) ^ t[(r ^ *data) & 0xff];
            data++;
        }
        *context = (unsigned short)r;
    }

    // usa: func_020d1c24
    // MATHi_CRC32InitTableRev
    void func_020d1c24(CRC32Table* table, unsigned long poly)
    {
        unsigned long r;
        unsigned long i, j;
        unsigned long* t = table->table;

        for (i = 0; i < 256; i++)
        {
            r = i;
            for (j = 0; j < 8; j++)
            {
                if (r & 1)
                {
                    r = (r >> 1) ^ poly;
                }
                else
                {
                    r >>= 1;
                }
            }
            t[i] = r;
        }
    }

    // usa: func_020d1c64
    // MATHi_CRC32UpdateRev
    void func_020d1c64(const CRC32Table* table, unsigned long* context, const void* input, unsigned long length)
    {
        unsigned long r;
        unsigned long i;
        const unsigned long* t = table->table;
        unsigned char* data = (unsigned char*)input;

        r = (unsigned long)*context;
        for (i = 0; i < length; i++)
        {
            r = (r >> 8) ^ t[(r ^ *data) & 0xff];
            data++;
        }
        *context = r;
    }

    // usa: func_020d1ca0
    // MATH_CalcCRC8
    unsigned char func_020d1ca0(const CRC8Table* table, const void* data, unsigned long length)
    {
        unsigned char context = 0;

        func_020d1b68(table, &context, data, length);
        return context;
    }

    // usa: func_020d1cc8
    // MATH_CalcCRC16
    unsigned short func_020d1cc8(const CRC16Table* table, const void* data, unsigned long length)
    {
        unsigned short context = 0;

        func_020d1be4(table, &context, data, length);
        return context;
    }

    // usa: func_020d1cf0
    // MATH_CalcCRC32
    unsigned long func_020d1cf0(const CRC32Table* table, const void* data, unsigned long length)
    {
        unsigned long context = 0xffffffff;

        func_020d1c64(table, &context, data, length);
        return ~context;
    }
}
