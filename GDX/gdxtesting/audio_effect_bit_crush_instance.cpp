#include "audio_effect_bit_crush_instance.h"
#include <godot_cpp/classes/audio_frame.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AudioEffectBitCrushInstance::_bind_methods(){
    // ClassDB::bind_method(D_METHOD("_process"), &AudioEffectBitCrushInstance::_process);

}

AudioEffectBitCrushInstance::AudioEffectBitCrushInstance(){

}

AudioEffectBitCrushInstance::~AudioEffectBitCrushInstance(){

}

void AudioEffectBitCrushInstance::_process(const void *src_buffer, AudioFrame *dst_buffer, int32_t frame_count){
    // WARN_PRINT("lol audio");
    AudioFrame * src_as_audio_frame = (AudioFrame *)src_buffer;
    for(int i = 0; i < frame_count; i++){

        dst_buffer[i].left = Math::snapped(src_as_audio_frame[i].left,Math::pow(2.0f,-base->get_bit_depth()));
        dst_buffer[i].right = dst_buffer[i].left;
        // dst_buffer[i].left = 0.3;
        // dst_buffer[i].right = 0.0;
    };

}

// bool AudioEffectBitCrushInstance::_process_silence() const {
//     return true;
// };