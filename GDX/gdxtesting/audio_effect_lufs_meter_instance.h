#ifndef AUDIO_EFFECT_LUFS_METER_INSTANCE_H
#define AUDIO_EFFECT_LUFS_METER_INSTANCE_H

#include <godot_cpp/classes/audio_effect_instance.hpp>
#include <godot_cpp/classes/audio_frame.hpp>
#include "audio_effect_lufs_meter.h"
#include "audio_buffer.h"

namespace godot{
    class AudioEffectLufsMeterInstance : public AudioEffectInstance{
        GDCLASS(AudioEffectLufsMeterInstance, AudioEffectInstance)
    friend class AudioEffectLufsMeter;
    Ref<AudioEffectLufsMeter> base;
    
private:
    // alot of this was taken from K-Meter's source code by Martin Zuther (mzuther) under the GPL v3
    void calculateFilterKernel();
    void calculateFilterKernel_Rms();
    void calculateFilterKernel_ItuBs1770();

    void calculateLoudness();
    void filterSamples_Rms(const int channel);
    void filterSamples_ItuBs1770();

    double sampleRate_;

    PackedFloat64Array loudnessValues_;

    PackedFloat64Array preFilterInputCoefficients_;
    PackedFloat64Array preFilterOutputCoefficients_;

    PackedFloat64Array weightingFilterInputCoefficients_;
    PackedFloat64Array weightingFilterOutputCoefficients_;

    // these were originally AudioBuffer<float> for the JUCE library, so for ref -> https://docs.juce.com/master/classAudioBuffer.html
    AudioBuffer previousSamplesPreFilterInput_;
    AudioBuffer previousSamplesPreFilterOutput_;

    AudioBuffer previousSamplesWeightingFilterInput_;
    AudioBuffer previousSamplesWeightingFilterOutput_;

    AudioBuffer previousSamplesOutputTemp_;

    //fft things
    AudioBuffer fftSampleBuffer_;

    int averageAlgorithm_;
    float peakToAverageCorrection_;

    // from meter ballistics

    // maximum RMS peak-to-average gain correction; for more information,
    // see the method AverageLevelFiltered::calculateFilterKernel()
    float fPeakToAverageCorrection = +3.0103f;

    // logarithmic levels have no minimum level, so let's define one:
    // (90 dB meter range + 0.01 to make sure that the minimum level is
    // below the meter's threshold + 20 dB maximum crest factor +
    // peak-to-average gain correction)
    float fMeterMinimumDecibel = -(90.01f + 20.0f + fPeakToAverageCorrection);


protected:
    static void _bind_methods();

public:
    AudioEffectLufsMeterInstance();
    ~AudioEffectLufsMeterInstance();
    void _process(const void *src_buffer, AudioFrame *dst_buffer, int32_t frame_count);

    // from K-Meter
    static const int KMETER_MAXIMUM_FILTER_STAGES = 3;

    // AverageLevelFiltered(const int numberOfChannels,
    //                      const double sampleRate,
    //                      const int fftBufferSize,
    //                      const int averageAlgorithm);

    // virtual ~AverageLevelFiltered();
    virtual void reset();

    int getAlgorithm() const;
    void setAlgorithm(const int averageAlgorithm);

    float getLevel(const int channel);

    // void copyTo(AudioBuffer<float> &destination,
    //             const int numberOfSamples);

    void copyFrom(const AudioFrame* source,
                  const int numberOfSamples);
    // bool _process_silence() const;

    };

}

#endif