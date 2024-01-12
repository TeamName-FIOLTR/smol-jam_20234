#include "audio_effect_lufs_meter_instance.h"
#include <godot_cpp/classes/audio_frame.hpp>
#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AudioEffectLufsMeterInstance::_bind_methods(){
    // ClassDB::bind_method(D_METHOD("_process"), &AudioEffectLufsMeterInstance::_process);

}

AudioEffectLufsMeterInstance::AudioEffectLufsMeterInstance(){
    int numberOfChannels_ = 1; // testing for now
    previousSamplesPreFilterInput_ = AudioBuffer(
        numberOfChannels_, KMETER_MAXIMUM_FILTER_STAGES - 1),
    previousSamplesPreFilterOutput_ = AudioBuffer(
        numberOfChannels_, KMETER_MAXIMUM_FILTER_STAGES - 1),
    previousSamplesWeightingFilterInput_ = AudioBuffer(
        numberOfChannels_, KMETER_MAXIMUM_FILTER_STAGES - 1),
    previousSamplesWeightingFilterOutput_ = AudioBuffer(
        numberOfChannels_, KMETER_MAXIMUM_FILTER_STAGES - 1),
    previousSamplesOutputTemp_ = AudioBuffer(1, fftBufferSize_)


}

AudioEffectLufsMeterInstance::~AudioEffectLufsMeterInstance(){

}

void AudioEffectLufsMeterInstance::_process(const void *src_buffer, AudioFrame *dst_buffer, int32_t frame_count){
    // WARN_PRINT("lol audio");
    float sample_rate = AudioServer::get_singleton()->get_mix_rate();
    // AudioServer::get_singleton()->get_bus_channels(0);

    AudioFrame * src_as_audio_frame = (AudioFrame *)src_buffer;

    for(int i = 0; i < frame_count; i++){

        dst_buffer[i].left = Math::snapped(src_as_audio_frame[i].left,Math::pow(2.0f,-base->get_bit_depth()));
        dst_buffer[i].right = dst_buffer[i].left;
        // dst_buffer[i].left = 0.3;
        // dst_buffer[i].right = 0.0;
    };

}

void AudioEffectLufsMeterInstance::copyFrom(const AudioFrame* source, const int samples){
    ((PackedFloat32Array)(fftSampleBuffer_[0])).resize(samples);
    for(int i = 0; i < samples; i++){
        ((PackedFloat32Array)(fftSampleBuffer_[0]))[i] = source[i].left;
        // fftSampleBuffer_[i].y = source[i].right;
    }

    calculateLoudness();

}

void AudioEffectLufsMeterInstance::calculateLoudness(){
    float meterMinimumDecibel = fMeterMinimumDecibel;

    filterSamples_ItuBs1770();
}


void AudioEffectLufsMeterInstance::filterSamples_ItuBs1770(){
    //this is supposed to loop for every audio channel, but i'm going with the first one for now
    //pre-filter
    previousSamplesOutputTemp_[0].clear();
    PackedFloat32Array samplesInput = fftSampleBuffer_[0];
    PackedFloat32Array samplesOutput = previousSamplesOutputTemp_[0];

    PackedFloat32Array samplesInputOld_1 = previousSamplesPreFilterInput_[0];
    PackedFloat32Array samplesOutputOld_1 = previousSamplesPreFilterOutput_[0];

    for(int sample = 0; sample < fftSampleBuffer_.size(); sample++){
        double outputSum;

            if (sample < 2)
            {
                if (sample == 0)
                {
                    outputSum =
                        preFilterInputCoefficients_[0] * samplesInput[sample] +
                        preFilterInputCoefficients_[1] * samplesInputOld_1[1] +
                        preFilterInputCoefficients_[2] * samplesInputOld_1[0] +
                        preFilterOutputCoefficients_[1] * samplesOutputOld_1[1] +
                        preFilterOutputCoefficients_[2] * samplesOutputOld_1[0];
                }
                else
                {
                    outputSum =
                        preFilterInputCoefficients_[0] * samplesInput[sample] +
                        preFilterInputCoefficients_[1] * samplesInput[sample - 1] +
                        preFilterInputCoefficients_[2] * samplesInputOld_1[1] +
                        preFilterOutputCoefficients_[1] * samplesOutput[sample - 1] +
                        preFilterOutputCoefficients_[2] * samplesOutputOld_1[1];
                }
            }
            else
            {
                outputSum =
                    preFilterInputCoefficients_[0] * samplesInput[sample] +
                    preFilterInputCoefficients_[1] * samplesInput[sample - 1] +
                    preFilterInputCoefficients_[2] * samplesInput[sample - 2] +
                    preFilterOutputCoefficients_[1] * samplesOutput[sample - 1] +
                    preFilterOutputCoefficients_[2] * samplesOutput[sample - 2];
            }

            // dither output to float // shhh we won't worry about whatever this was
            // samplesOutput[sample] = dither_.ditherSample(channel, outputSum);

            // avoid underflows (1e-20f corresponds to -400 dBFS)
            if (Math::abs(samplesOutput[sample]) < 1e-20)
            {
                samplesOutput[sample] = 0.0f;
            }
        
    }

}
// bool AudioEffectLufsMeterInstance::_process_silence() const {
//     return true;
// };