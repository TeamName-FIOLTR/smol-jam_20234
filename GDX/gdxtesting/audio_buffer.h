#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <godot_cpp/variant/typed_array.hpp>

namespace godot{
    class AudioBuffer{ //adaptation of the AudioBuffer class from the JUCE library -> https://docs.juce.com/master/classAudioBuffer.html
        public:
        TypedArray<PackedFloat32Array> channels;

        AudioBuffer();
        AudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate);
        ~AudioBuffer();

        int getNumChannels();
        int getNumSamples();

        void setSize(int newNumChannels, int newNumSamples);
        void clear();
        void clear(int startSample, int numSamples);
        void clear(int channel, int startSample, int numSamples);

        float getSample(int channel, int sampleIndex);
        void setSample(int destChannel, int destSample, float newValue);
        void addSample(int destChannel, int destSample, float valueToAdd);

        void copyFrom (int destChannel, int destStartSample, AudioBuffer &source, int sourceChannel, int sourceStartSample, int numSamples);
        void makeCopyOf(AudioBuffer &source);
    };
}

#endif