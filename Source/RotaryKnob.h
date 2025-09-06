/*
  ==============================================================================

    RotaryKnob.h
    Created: 16 Jun 2025 11:34:45pm
    Author:  Alex

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotaryKnob  : public juce::Component
{
public:
    RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts,
        const juce::ParameterID& parameterID, bool drawFromMiddle=false);
    ~RotaryKnob() override;
    
    juce::Slider slider;
    juce::Label label;
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
