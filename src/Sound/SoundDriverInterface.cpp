#include "Sound/Sound.h"
#include "Sound/SoundDriver.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's snd_interface.c: the functions that send commands to the sound driver, which runs on the ARM7. Each
// one fills a command (SNDCommand) and adds it to the list that SND_FlushCommand sends.

// The members of the driver's players (SNDPlayer) and tracks (SNDTrack) that the functions set
#define PLAYER_PRIORITY 4
#define PLAYER_VOLUME 6
#define TRACK_PITCH 0xc

extern "C"
{
    // SND_LockChannel
    void func_020d1fb0(unsigned long channelMask, unsigned long flags);
    // SND_UnlockChannel
    void func_020d1fd0(unsigned long channelMask, unsigned long flags);
    // SND_InvalidateSeqData
    void func_020d2084(const void* start, const void* end);
    // SND_InvalidateBankData
    void func_020d20a4(const void* start, const void* end);
    // SND_InvalidateWaveData
    void func_020d20c4(const void* start, const void* end);
    // SND_SetMasterVolume
    void func_020d20e4(int volume);
    // SND_SetOutputSelector
    void func_020d2104(int left, int right, int channel1, int channel3);
    // SNDi_SetPlayerParam
    void func_020d212c(int playerNo, unsigned long offset, unsigned long data, int size);
    // SNDi_SetTrackParam
    void func_020d2154(int playerNo, unsigned long trackBitMask, unsigned long offset, unsigned long data, int size);
    // PushCommand_impl
    static void func_020d217c(int command, unsigned long arg0, unsigned long arg1, unsigned long arg2,
                              unsigned long arg3);

    void func_020d1de8(int playerNo)
    {
        func_020d217c(COMMAND_STOP_SEQ, playerNo, 0, 0, 0);
    }

    void func_020d1e08(int playerNo, const void* seqBase, unsigned long seqOffset, const SoundBank* bank)
    {
        func_020d217c(COMMAND_PREPARE_SEQ, playerNo, (unsigned long)seqBase, seqOffset, (unsigned long)bank);
    }

    void func_020d1e30(int playerNo)
    {
        func_020d217c(COMMAND_START_PREPARED_SEQ, playerNo, 0, 0, 0);
    }

    void func_020d1e50(int playerNo, int flag)
    {
        func_020d217c(COMMAND_PAUSE_SEQ, playerNo, flag, 0, 0);
    }

    void func_020d1e70(int playerNo, int volume)
    {
        func_020d212c(playerNo, PLAYER_VOLUME, volume, sizeof(short));
    }

    void func_020d1e88(int playerNo, int prio)
    {
        func_020d212c(playerNo, PLAYER_PRIORITY, prio, sizeof(unsigned char));
    }

    void func_020d1ea0(int playerNo, unsigned long trackBitMask, int pitch)
    {
        func_020d2154(playerNo, trackBitMask, TRACK_PITCH, pitch, sizeof(short));
    }

    void func_020d1ebc(int playerNo, unsigned long trackBitMask, unsigned long channelMask)
    {
        func_020d217c(COMMAND_ALLOCATABLE_CHANNEL, playerNo, trackBitMask, channelMask, 0);
    }

    void func_020d1ee4(unsigned long channelMask, unsigned long captureMask, unsigned long alarmMask,
                       unsigned long flags)
    {
        func_020d217c(COMMAND_START_TIMER, channelMask, captureMask, alarmMask, flags);
    }

    void func_020d1f0c(unsigned long channelMask, unsigned long captureMask, unsigned long alarmMask,
                       unsigned long flags)
    {
        int i;
        unsigned long mask = alarmMask;
        for (i = 0; i < 8 && mask != 0; i++, mask >>= 1)
        {
            if (mask & 1)
                func_020d2960(i);
        }
        func_020d217c(COMMAND_STOP_TIMER, channelMask, captureMask, alarmMask, flags);
    }

    void func_020d1f70(int alarmNo, unsigned long tick, unsigned long period, void (*handler)(void* arg), void* arg)
    {
        func_020d217c(COMMAND_SETUP_ALARM, alarmNo, tick, period, func_020d2980(alarmNo, handler, arg));
    }

    void func_020d1fb0(unsigned long channelMask, unsigned long flags)
    {
        func_020d217c(COMMAND_LOCK_CHANNEL, channelMask, flags, 0, 0);
    }

    void func_020d1fd0(unsigned long channelMask, unsigned long flags)
    {
        func_020d217c(COMMAND_UNLOCK_CHANNEL, channelMask, flags, 0, 0);
    }

    void func_020d1ff0(unsigned long channelMask, int volume, int shift)
    {
        func_020d217c(COMMAND_CHANNEL_VOLUME, channelMask, volume, shift, 0);
    }

    void func_020d2018(unsigned long channelMask, int pan)
    {
        func_020d217c(COMMAND_CHANNEL_PAN, channelMask, pan, 0, 0);
    }

    void func_020d2038(int channelNo, int format, const void* data, int loop, int loopStart, int loopLength,
                       int volume, int shift, int timer, int pan)
    {
        func_020d217c(COMMAND_SETUP_CHANNEL_PCM, channelNo | timer << 16, (unsigned long)data,
                      volume << 24 | shift << 22 | loopLength, loop << 26 | format << 24 | pan << 16 | loopStart);
    }

    void func_020d2084(const void* start, const void* end)
    {
        func_020d217c(COMMAND_INVALIDATE_SEQ, (unsigned long)start, (unsigned long)end, 0, 0);
    }

    void func_020d20a4(const void* start, const void* end)
    {
        func_020d217c(COMMAND_INVALIDATE_BANK, (unsigned long)start, (unsigned long)end, 0, 0);
    }

    void func_020d20c4(const void* start, const void* end)
    {
        func_020d217c(COMMAND_INVALIDATE_WAVE, (unsigned long)start, (unsigned long)end, 0, 0);
    }

    void func_020d20e4(int volume)
    {
        func_020d217c(COMMAND_MASTER_VOLUME, volume, 0, 0, 0);
    }

    void func_020d2104(int left, int right, int channel1, int channel3)
    {
        func_020d217c(COMMAND_OUTPUT_SELECTOR, left, right, channel1, channel3);
    }

    void func_020d212c(int playerNo, unsigned long offset, unsigned long data, int size)
    {
        func_020d217c(COMMAND_PLAYER_PARAM, playerNo, offset, data, size);
    }

    void func_020d2154(int playerNo, unsigned long trackBitMask, unsigned long offset, unsigned long data, int size)
    {
        func_020d217c(COMMAND_TRACK_PARAM, playerNo | size << 24, trackBitMask, offset, data);
    }

    static void func_020d217c(int command, unsigned long arg0, unsigned long arg1, unsigned long arg2,
                              unsigned long arg3)
    {
        SoundCommand* const cmd = func_020d2404(COMMAND_BLOCK);
        if (cmd == NULL)
            return;
        cmd->id = command;
        cmd->arg[0] = arg0;
        cmd->arg[1] = arg1;
        cmd->arg[2] = arg2;
        cmd->arg[3] = arg3;
        func_020d248c(cmd);
    }
}
