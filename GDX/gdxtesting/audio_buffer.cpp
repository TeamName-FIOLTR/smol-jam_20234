#include "audio_buffer.h"

using namespace godot;


AudioBuffer::AudioBuffer(){

};

AudioBuffer::AudioBuffer(int numChannelsToAllocate, int numSamplesToAllocate){
    setSize(numChannelsToAllocate, numSamplesToAllocate);
};

AudioBuffer::~AudioBuffer(){

};

int AudioBuffer::getNumChannels(){
    return channels.size();

};

int AudioBuffer::getNumSamples(){
    return channels[0].size(); //ignore these errors, gdx can't parse that the typed array is of type PackedFloat32Array
};

void AudioBuffer::setSize(int newNumChannels, int newNumSamples){
    channels.resize(newNumChannels);
    for(int i = 0; i < newNumChannels; i++){
        channels[i].resize(newNumSamples);
    }
};

void AudioBuffer::clear(){
    for(int i = 0; i < getNumChannels(); i++){
        channels[i].fill(0.0);
    }

};

void AudioBuffer::clear(int startSample, int numSamples){
    for(int i = 0; i < getNumChannels(); i++){
        clear(i, startSample, numSamples);
    }

};

void AudioBuffer::clear(int channel, int startSample, int numSamples){
    for(int sample = 0; sample < numSamples; sample++){
            channels[channel][sample+startSample] = 0.0;
        };
};

float AudioBuffer::getSample(int channel, int sampleIndex){
    return channels[channel][sampleIndex];
};

void AudioBuffer::setSample(int destChannel, int destSample, float newValue){
    channels[destChannel][destSample] = newValue;
};

void AudioBuffer::addSample(int destChannel, int destSample, float valueToAdd){
    channels[destChannel][destSample] += valueToAdd;
};

void AudioBuffer::copyFrom (int destChannel, int destStartSample, AudioBuffer &source, int sourceChannel, int sourceStartSample, int numSamples){
    for(int i = 0; i < numSamples; i++){
        setSample(destChannel, destStartSample+i, source.getSample(sourceChannel, sourceStartSample+i));
    }

};

void AudioBuffer::makeCopyOf(AudioBuffer &source){
    setSize(source.getNumChannels(),source.getNumSamples());
    for(int channel = 0; channel < source.getNumChannels(); channel++){
        copyFrom(channel, 0, source, channel, 0, source.getNumSamples());
    }
};