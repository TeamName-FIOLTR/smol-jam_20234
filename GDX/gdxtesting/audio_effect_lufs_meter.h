#ifndef AUDIO_EFFECT_LUFS_METER_H
#define AUDIO_EFFECT_LUFS_METER_H

#include <godot_cpp/classes/audio_effect.hpp>
// #include "audio_effect_bit_crush_instance.h"

namespace godot{
    class AudioEffectLufsMeter : public AudioEffect{
        GDCLASS(AudioEffectLufsMeter, AudioEffect)
    // friend class AudioStreamLufsMeterInstance;

protected:
    static void _bind_methods();

private:
    String audioeffectLufsMeter_audioeffectLufsMeter;
    float lol;
    float bit_depth;

public:
    AudioEffectLufsMeter();
    ~AudioEffectLufsMeter();

    String audioeffectLufsMeter();

    Ref<AudioEffectInstance> _instantiate();

    float get_bit_depth() const;
    void set_bit_depth(const float new_bit_depth);

    };
};

#endif