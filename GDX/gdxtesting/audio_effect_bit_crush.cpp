#include "audio_effect_bit_crush.h"
#include "audio_effect_bit_crush_instance.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AudioEffectBitCrush::_bind_methods(){
    ClassDB::bind_method(D_METHOD("audioeffectbitcrush"), &AudioEffectBitCrush::audioeffectbitcrush);
    ClassDB::bind_method(D_METHOD("set_bit_depth", "new_bit_depth"), &AudioEffectBitCrush::set_bit_depth);
    ClassDB::bind_method(D_METHOD("get_bit_depth"), &AudioEffectBitCrush::get_bit_depth);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "bit_depth", PROPERTY_HINT_RANGE, "1,32,0.01"), "set_bit_depth", "get_bit_depth");
    // Class
}

AudioEffectBitCrush::AudioEffectBitCrush(){
    audioeffectbitcrush_audioeffectbitcrush = String("audioeffectbitcrush");
}

AudioEffectBitCrush::~AudioEffectBitCrush(){

}

String AudioEffectBitCrush::audioeffectbitcrush(){
    return audioeffectbitcrush_audioeffectbitcrush;
}

Ref<AudioEffectInstance> AudioEffectBitCrush::_instantiate(){
    Ref<AudioEffectBitCrushInstance> ins;
    ins.instantiate();
    ins->base = Ref<AudioEffectBitCrush>(this);
    return ins;
}

void AudioEffectBitCrush::set_bit_depth(const float new_bit_depth){
    bit_depth = new_bit_depth;
}

float AudioEffectBitCrush::get_bit_depth() const {
    return bit_depth;
}