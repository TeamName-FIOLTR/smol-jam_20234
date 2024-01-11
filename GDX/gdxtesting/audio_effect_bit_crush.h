#ifndef AUDIOEFFECTBITCRUSH_H
#define AUDIOEFFECTBITCRUSH_H

#include <godot_cpp/classes/audio_effect.hpp>
// #include "audio_effect_bit_crush_instance.h"

namespace godot{
    class AudioEffectBitCrush : public AudioEffect{
        GDCLASS(AudioEffectBitCrush, AudioEffect)
    // friend class AudioStreamBitCrushInstance;

protected:
    static void _bind_methods();

private:
    String audioeffectbitcrush_audioeffectbitcrush;
    float lol;
    float bit_depth;

public:
    AudioEffectBitCrush();
    ~AudioEffectBitCrush();

    String audioeffectbitcrush();

    Ref<AudioEffectInstance> _instantiate();

    float get_bit_depth() const;
    void set_bit_depth(const float new_bit_depth);

    };
};

#endif