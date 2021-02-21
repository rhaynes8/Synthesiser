/*
  ==============================================================================

    SynthFilterComponent.h
    Created: 21 Feb 2021 12:29:51pm
    Author:  Richie Haynes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SynthFilterComponent  : public juce::Component
{
public:
    SynthFilterComponent(juce::AudioProcessorValueTreeState& filterTree);
    ~SynthFilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void sliderParameters(juce::Slider& slider);
    void labelParameters(juce::Label& label, juce::Slider& slider, juce::String string);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Slider    frequencySlider;
    juce::Label     frequencyLabel;
    std::unique_ptr <SliderAttachment> frequencySliderValue;
    juce::Slider    resonanceSlider;
    juce::Label     resonanceLabel;
    std::unique_ptr <SliderAttachment> resonanceSliderValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFilterComponent)
};
