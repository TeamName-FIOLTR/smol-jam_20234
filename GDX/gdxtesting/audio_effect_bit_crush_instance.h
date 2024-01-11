#ifndef AUDIOEFFECTBITCRUSHINSTANCE_H
#define AUDIOEFFECTBITCRUSHINSTNACE_H

#include <godot_cpp/classes/audio_effect_instance.hpp>
#include "audio_effect_bit_crush.h"

namespace godot{
    class AudioEffectBitCrushInstance : public AudioEffectInstance{
        GDCLASS(AudioEffectBitCrushInstance, AudioEffectInstance)
    friend class AudioEffectBitCrush;
    Ref<AudioEffectBitCrush> base;
    
private:

protected:
    static void _bind_methods();

public:
    AudioEffectBitCrushInstance();
    ~AudioEffectBitCrushInstance();
    void _process(const void *src_buffer, AudioFrame *dst_buffer, int32_t frame_count);
    // bool _process_silence() const;

    };

}

#endif