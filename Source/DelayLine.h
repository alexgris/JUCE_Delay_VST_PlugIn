/*
  ==============================================================================

    DelayLine.h
    Created: 9 Nov 2025 4:01:05pm
    Author:  Alex

  ==============================================================================
*/

#pragma once
#include <memory>

class DelayLine {

public:

    void setMaximumDelayInSamples(int maxLengthInSamples);
    void reset() noexcept;

    void write(float input) noexcept;
    float read(float delayInSamples) const noexcept;

    int getBufferLength() const noexcept {
        return bufferLength;
    }


private:

    std::unique_ptr<float[]> buffer;
    int bufferLength = 0;
    int writeIndex = 0;
};
