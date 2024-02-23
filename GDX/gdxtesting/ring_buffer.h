#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <godot_cpp/variant/typed_array.hpp>
// #include <godot_cpp/variant/packed_int32_array.hpp>
#include "audio_buffer.h"

class RingBufferProcessor;

namespace godot{
    class RingBuffer{ // adaptation of the RingBuffer class from the FrutJUCE module in K-Meter -> https://github.com/mzuther/K-Meter/blob/master/Source/frut/audio/ring_buffer.h
        public:
    RingBuffer(const int numberOfChannels,
               const int numberOfSamples,
               const int preDelay,
               const int chunkSize);

    void clear();
    void setCallbackClass(RingBufferProcessor *callbackClass);

    int getNumberOfChannels() const;
    int getNumberOfSamples() const;
    int getPreDelay() const;


    /// Add audio samples from an AudioBuffer.  **This function will
    /// call the callback function every time the total number of
    /// samples added to this buffer (now or before) exceeds the
    /// "chunk" size.  The write position will be moved.**
    ///
    /// @param source source buffer
    ///
    /// @param sourceStartSample the index in the source buffer to
    ///        start reading from
    ///
    /// @param numberOfSamples number of samples to copy
    ///
    inline void addFrom(
        const AudioBuffer &source,
        const int sourceStartSample,
        const int numberOfSamples)
    {
        bool updatePosition = true;

        importFrom(source, sourceStartSample,
                   numberOfSamples,
                   updatePosition);
    }


    /// Overwrite audio samples from an AudioBuffer.  **This function
    /// will not call the callback function and leave the write
    /// position alone.**
    ///
    /// @param source source buffer
    ///
    /// @param sourceStartSample the index in the source buffer to
    ///        start reading from
    ///
    /// @param numberOfSamples number of samples to copy
    ///
    inline void overwriteFrom(
        const AudioBuffer &source,
        const int sourceStartSample,
        const int numberOfSamples)
    {
        bool updatePosition = false;

        importFrom(source, sourceStartSample,
                   numberOfSamples,
                   updatePosition);
    }


    /// Remove audio samples from this ring buffer to an AudioBuffer.
    /// **The read position will be moved.**
    ///
    /// @param destination destination buffer
    ///
    /// @param destStartSample the index in the destination buffer to
    ///        start writing to
    ///
    /// @param numberOfSamples number of samples to copy
    ///
    inline void removeTo(
        AudioBuffer &destination,
        const int destStartSample,
        const int numberOfSamples)
    {
        bool updatePosition = true;

        exportTo(destination, destStartSample,
                 numberOfSamples,
                 updatePosition);
    }


    /// Copy audio samples to an AudioBuffer.  **This function will
    /// leave the read position alone.**
    ///
    /// @param destination destination buffer
    ///
    /// @param destStartSample the index in the destination buffer to
    ///        start writing to
    ///
    /// @param numberOfSamples number of samples to copy
    ///
    inline void copyTo(
        AudioBuffer &destination,
        const int destStartSample,
        const int numberOfSamples)
    {
        bool updatePosition = false;

        exportTo(destination, destStartSample,
                 numberOfSamples,
                 updatePosition);
    }


    void removeToNull(const int numberOfSamples);

protected:
    void importFrom(const AudioBuffer &source,
                    const int sourceStartSample,
                    const int numberOfSamples,
                    const bool updatePosition);

    void exportTo(AudioBuffer &destination,
                  const int destStartSample,
                  const int numberOfSamples,
                  const bool updatePosition);

    RingBufferProcessor *callbackClass_;
    // BufferPosition bufferPosition_; // i think i can do without this idk tho

    PackedInt32Array channelOffsets_;
    // HeapBlock audioData_; // idk what this is if it breaks ill look into it later

    int numberOfChannels_;
    int chunkSize_;
    int samplesToFilledChunk_;

// private:
    // JUCE_LEAK_DETECTOR(RingBuffer);

    // const Type ringBufferMemTestByte_;
};
}


#endif