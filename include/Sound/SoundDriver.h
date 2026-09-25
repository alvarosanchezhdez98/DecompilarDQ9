#pragma once

// The NitroSDK's sound driver (SND), the ARM9's side: it sends commands to the driver that runs on the ARM7, which
// shares some of its state through SoundSharedWork. Sound.h declares the functions that NitroSystem calls.

// The commands (SNDCommandID)
enum SoundCommandID
{
    COMMAND_START_SEQ,
    COMMAND_STOP_SEQ,
    COMMAND_PREPARE_SEQ,
    COMMAND_START_PREPARED_SEQ,
    COMMAND_PAUSE_SEQ,
    COMMAND_SKIP_SEQ,
    COMMAND_PLAYER_PARAM,
    COMMAND_TRACK_PARAM,
    COMMAND_MUTE_TRACK,
    COMMAND_ALLOCATABLE_CHANNEL,
    COMMAND_PLAYER_LOCAL_VAR,
    COMMAND_PLAYER_GLOBAL_VAR,
    COMMAND_START_TIMER,
    COMMAND_STOP_TIMER,
    COMMAND_SETUP_CHANNEL_PCM,
    COMMAND_SETUP_CHANNEL_PSG,
    COMMAND_SETUP_CHANNEL_NOISE,
    COMMAND_SETUP_CAPTURE,
    COMMAND_SETUP_ALARM,
    COMMAND_CHANNEL_TIMER,
    COMMAND_CHANNEL_VOLUME,
    COMMAND_CHANNEL_PAN,
    COMMAND_SURROUND_DECAY,
    COMMAND_MASTER_VOLUME,
    COMMAND_MASTER_PAN,
    COMMAND_OUTPUT_SELECTOR,
    COMMAND_LOCK_CHANNEL,
    COMMAND_UNLOCK_CHANNEL,
    COMMAND_STOP_UNLOCKED_CHANNEL,
    COMMAND_SHARED_WORK,
    COMMAND_INVALIDATE_SEQ,
    COMMAND_INVALIDATE_BANK,
    COMMAND_INVALIDATE_WAVE,
};

// SND_COMMAND_NUM: the commands that can be allocated
#define SOUND_COMMAND_COUNT 256
// SND_ALARM_NUM
#define SOUND_ALARM_COUNT 8

// A command (SNDCommand)
struct SoundCommand
{
    SoundCommand* next;
    unsigned long id;
    unsigned long arg[4];
};

// The state that the ARM7's driver shares (SNDSharedWork)
struct SoundSharedWork
{
    // The tag of the last command that the driver finished
    volatile unsigned long finishCommandTag;
    volatile unsigned long playerStatus;
    volatile unsigned short channelStatus;
    volatile unsigned short captureStatus;
    volatile unsigned long padding[5];
    struct
    {
        volatile short localVariable[16];
        volatile unsigned long tickCounter;
    } player[16];
    volatile short globalVariable[16];
};

extern "C"
{
    // SNDi_SharedWork
    extern SoundSharedWork* data_021142c0;

    // SND_AllocCommand
    SoundCommand* func_020d2404(unsigned long flags);
    // SND_PushCommand
    void func_020d248c(SoundCommand* command);
    // SND_CountWaitingCommand
    int func_020d27e0();
    // SND_CommandInit
    void func_020d2220();
    // SND_AlarmInit
    void func_020d2930();
    // SNDi_IncAlarmId
    void func_020d2960(int alarmNo);
    // SNDi_SetAlarmHandler
    unsigned char func_020d2980(int alarmNo, void (*handler)(void* arg), void* arg);
    // SNDi_CallAlarmHandler
    void func_020d29b0(int alarmNo);
    // SNDi_GetFinishedCommandTag
    unsigned long func_020d2a20();
    // SNDi_InitSharedWork
    void func_020d2a48(SoundSharedWork* work);
}
