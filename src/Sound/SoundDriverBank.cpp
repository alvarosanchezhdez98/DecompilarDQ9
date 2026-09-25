#include "Sound/Sound.h"
#include "System/Cache.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_bank.c: links the banks to their wave archives, and reads their instruments

// The instrument types (SNDInstType)
#define INSTRUMENT_NULL 5
#define INSTRUMENT_DRUM_SET 16
#define INSTRUMENT_KEY_SPLIT 17

// SND_INST_MAX_KEYSPLIT
#define KEY_SPLIT_COUNT 8

// HW_MAIN_MEM: a wave's address below it is an offset in its wave archive
#define MAIN_MEMORY 0x02000000

// The NitroSDK copies the instruments as blocks, which C++ does through a structure with an array
struct InstrumentParametersCopy
{
    unsigned short data[sizeof(InstrumentParameters) / sizeof(unsigned short)];
};

struct InstrumentDataCopy
{
    unsigned short data[sizeof(InstrumentData) / sizeof(unsigned short)];
};

// SNDDrumSet: the instruments of a range of keys
struct DrumSet
{
    unsigned char min;
    unsigned char max;
    InstrumentData instruments[];
};

// SNDKeySplit: the instruments of up to 8 ranges of keys, each up to a key
struct KeySplit
{
    unsigned char key[KEY_SPLIT_COUNT];
    InstrumentData instruments[KEY_SPLIT_COUNT];
};

extern "C"
{
    // SNDi_LockMutex and SNDi_UnlockMutex
    void func_020d21f8();
    void func_020d220c();

    void func_020d2b34(SoundBank* bank, int index, SoundWaveArchive* waveArc)
    {
        func_020d21f8();
        if (bank->waveArcLink[index].waveArc != NULL)
        {
            if (waveArc == bank->waveArcLink[index].waveArc)
            {
                func_020d220c();
                return;
            }
            if (&bank->waveArcLink[index] == bank->waveArcLink[index].waveArc->topLink)
            {
                bank->waveArcLink[index].waveArc->topLink = bank->waveArcLink[index].next;
                CleanCacheRange(bank->waveArcLink[index].waveArc, sizeof(SoundWaveArchive));
            }
            else
            {
                SoundWaveArchiveLink* link;
                for (link = bank->waveArcLink[index].waveArc->topLink; link != NULL; link = link->next)
                {
                    if (&bank->waveArcLink[index] == link->next)
                        break;
                }
                link->next = bank->waveArcLink[index].next;
                CleanCacheRange(link, sizeof(SoundWaveArchiveLink));
            }
        }
        {
            SoundWaveArchiveLink* const next = waveArc->topLink;
            waveArc->topLink = &bank->waveArcLink[index];
            bank->waveArcLink[index].next = next;
            bank->waveArcLink[index].waveArc = waveArc;
        }
        func_020d220c();
        CleanCacheRange(bank, sizeof(SoundBank));
        CleanCacheRange(waveArc, sizeof(SoundWaveArchive));
    }

    void func_020d2c00(SoundBank* bank)
    {
        func_020d21f8();
        for (int i = 0; i < BANK_WAVE_ARCHIVE_COUNT; i++)
        {
            SoundWaveArchiveLink* const bankLink = &bank->waveArcLink[i];
            SoundWaveArchive* const waveArc = bank->waveArcLink[i].waveArc;
            if (waveArc == NULL)
                continue;
            if (bankLink == waveArc->topLink)
            {
                waveArc->topLink = bank->waveArcLink[i].next;
                CleanCacheRange(waveArc, sizeof(SoundWaveArchive));
            }
            else
            {
                SoundWaveArchiveLink* link;
                for (link = waveArc->topLink; link != NULL; link = link->next)
                {
                    if (bankLink == link->next)
                        break;
                }
                link->next = bank->waveArcLink[i].next;
                CleanCacheRange(link, sizeof(SoundWaveArchiveLink));
            }
        }
        func_020d220c();
    }

    void func_020d2c98(SoundWaveArchive* waveArc)
    {
        SoundWaveArchiveLink* link;
        SoundWaveArchiveLink* next;
        func_020d21f8();
        link = waveArc->topLink;
        while (link != NULL)
        {
            next = link->next;
            link->waveArc = NULL;
            link->next = NULL;
            CleanCacheRange(link, sizeof(SoundWaveArchiveLink));
            link = next;
        }
        func_020d220c();
    }

    InstrumentPosition func_020d2ce0(const SoundBank* bank)
    {
        InstrumentPosition pos;
        pos.prgNo = 0;
        pos.index = 0;
        return pos;
    }

    int func_020d2d00(const SoundBank* bank, InstrumentData* inst, InstrumentPosition* pos)
    {
        while (pos->prgNo < bank->instCount)
        {
            unsigned long offset = bank->instOffset[pos->prgNo];
            inst->type = offset;
            offset >>= 8;
            switch (inst->type)
            {
            case INSTRUMENT_PCM:
            case 2:
            case 3:
            case 4:
            case INSTRUMENT_NULL:
                *(InstrumentParametersCopy*)&inst->param =
                    *(const InstrumentParametersCopy*)((const unsigned char*)bank + offset);
                pos->prgNo++;
                return true;
            case INSTRUMENT_DRUM_SET:
            {
                const DrumSet* const drumSet = (const DrumSet*)((const unsigned char*)bank + offset);
                while (pos->index < drumSet->max - drumSet->min + 1)
                {
                    *(InstrumentDataCopy*)inst = *(const InstrumentDataCopy*)&drumSet->instruments[pos->index];
                    pos->index++;
                    return true;
                }
                break;
            }
            case INSTRUMENT_KEY_SPLIT:
            {
                const KeySplit* const keySplit = (const KeySplit*)((const unsigned char*)bank + offset);
                while (pos->index < KEY_SPLIT_COUNT)
                {
                    if (keySplit->key[pos->index] == 0)
                        break;
                    *(InstrumentDataCopy*)inst = *(const InstrumentDataCopy*)&keySplit->instruments[pos->index];
                    pos->index++;
                    return true;
                }
                break;
            }
            }
            pos->prgNo++;
            pos->index = 0;
        }
        return false;
    }

    unsigned long func_020d2eb0(const SoundWaveArchive* waveArc)
    {
        return waveArc->waveCount;
    }

    void func_020d2eb8(SoundWaveArchive* waveArc, int index, const void* address)
    {
        func_020d21f8();
        waveArc->waveOffset[index] = (unsigned long)address;
        CleanCacheRange(&waveArc->waveOffset[index], sizeof(unsigned long));
        func_020d220c();
    }

    const void* func_020d2eec(const SoundWaveArchive* waveArc, int index)
    {
        const void* data;
        func_020d21f8();
        data = (const void*)waveArc->waveOffset[index];
        if (data != NULL)
        {
            if ((unsigned long)data < MAIN_MEMORY)
                data = (const void*)((unsigned long)waveArc + (unsigned long)data);
        }
        else
        {
            data = NULL;
        }
        func_020d220c();
        return data;
    }
}
