#include "Sound/Sound.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// NitroSystem's fader.c: moves a volume to a target over a number of frames

extern "C"
{
    // usa: func_020c01ec
    // NNSi_SndFaderInit
    void func_020c01ec(SoundFader* fader)
    {
        fader->origin = fader->target = 0;
        fader->counter = fader->frame = 0;
    }

    // usa: func_020c0204
    // NNSi_SndFaderSet
    void func_020c0204(SoundFader* fader, int target, int frame)
    {
        fader->origin = func_020c022c(fader);
        fader->target = target;
        fader->frame = frame;
        fader->counter = 0;
    }

    // usa: func_020c022c
    // NNSi_SndFaderGet
    int func_020c022c(const SoundFader* fader)
    {
        long long value;
        if (fader->counter >= fader->frame)
            return fader->target;

        value = (fader->target - fader->origin) * fader->counter / fader->frame + fader->origin;
        return (int)value;
    }

    // usa: func_020c0260
    // NNSi_SndFaderUpdate
    void func_020c0260(SoundFader* fader)
    {
        if (fader->counter < fader->frame)
            fader->counter++;
    }

    // usa: func_020c0278
    // NNSi_SndFaderIsFinished
    int func_020c0278(const SoundFader* fader)
    {
        return fader->counter >= fader->frame ? 1 : 0;
    }
}
