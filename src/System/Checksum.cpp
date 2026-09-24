#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's checksum.c: the 16-bit one's complement checksum of the internet protocols (RFC 1071)

extern "C"
{
    // usa: func_020d1d1c
    // MATHi_Checksum16Update: adds data to a checksum
    void func_020d1d1c(unsigned short* context, const void* input, unsigned long length)
    {
        int swapped = false;
        unsigned long sum = 0;
        const unsigned char* data = (const unsigned char*)input;
        unsigned long n;
        unsigned long blocks;

        // The halfwords must be aligned: start with the first byte as the high one, and swap the result's bytes
        if ((unsigned long)data & 1)
        {
            sum += *data++ << 8;
            length--;
            swapped = true;
        }

        // Folds the carries every 0x10000 halfwords, before the sum can overflow
        blocks = length >> 17;
        while (blocks != 0)
        {
            blocks--;
            length -= 0x20000;
            for (n = 0x10000; n != 0; n--)
            {
                sum += *(const unsigned short*)data;
                data += 2;
            }
            sum = (sum >> 16) + (sum & 0xffff);
            sum = (unsigned short)(sum + (sum >> 16));
        }

        for (n = length >> 1; n != 0; n--)
        {
            sum += *(const unsigned short*)data;
            data += 2;
        }
        if (length & 1)
        {
            sum += *data;
        }

        sum = (sum >> 16) + (sum & 0xffff);
        sum = (sum >> 16) + (sum & 0xffff);
        if (swapped)
        {
            sum = ((sum << 24) | (sum << 8)) >> 16;
        }

        sum += *context;
        sum += sum >> 16;
        *context = (unsigned short)sum;
    }
}
