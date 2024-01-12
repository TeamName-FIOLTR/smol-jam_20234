#include "audio_effect_lufs_meter.h"
#include "audio_effect_lufs_meter_instance.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AudioEffectLufsMeter::_bind_methods(){
    ClassDB::bind_method(D_METHOD("audioeffectLufsMeter"), &AudioEffectLufsMeter::audioeffectLufsMeter);
    ClassDB::bind_method(D_METHOD("set_bit_depth", "new_bit_depth"), &AudioEffectLufsMeter::set_bit_depth);
    ClassDB::bind_method(D_METHOD("get_bit_depth"), &AudioEffectLufsMeter::get_bit_depth);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bit_depth", PROPERTY_HINT_RANGE, "1,32,0.01"), "set_bit_depth", "get_bit_depth");
    // Class
}

AudioEffectLufsMeter::AudioEffectLufsMeter(){
    audioeffectLufsMeter_audioeffectLufsMeter = String("audioeffectLufsMeter");
}

AudioEffectLufsMeter::~AudioEffectLufsMeter(){

}

String AudioEffectLufsMeter::audioeffectLufsMeter(){
    return audioeffectLufsMeter_audioeffectLufsMeter;
}

Ref<AudioEffectInstance> AudioEffectLufsMeter::_instantiate(){
    Ref<AudioEffectLufsMeterInstance> ins;
    ins.instantiate();
    ins->base = Ref<AudioEffectLufsMeter>(this);
    return ins;
}

void AudioEffectLufsMeter::set_bit_depth(const float new_bit_depth){
    bit_depth = new_bit_depth;
}

float AudioEffectLufsMeter::get_bit_depth() const {
    return bit_depth;
}