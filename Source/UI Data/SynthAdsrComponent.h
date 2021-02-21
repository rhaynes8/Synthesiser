/*
  ==============================================================================

    AdsrComponent.h
    Created: 20 Feb 2021 12:50:35am
    Author:  Richie Haynes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SynthAdsrComponent  : public juce::Component
{
public:
    SynthAdsrComponent(juce::AudioProcessorValueTreeState& adsrTree);
    ~SynthAdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    

private:
    
    void sliderParameters(juce::Slider& slider);
    void labelParameters(juce::Label& label, juce::Slider& slider, juce::String string);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Slider    attackSlider;
    juce::Label     attackLabel;
    std::unique_ptr <SliderAttachment> attackSliderValue;
    juce::Slider    decaySlider;
    juce::Label     decayLabel;
    std::unique_ptr <SliderAttachment> decaySliderValue;
    juce::Slider    sustainSlider;
    juce::Label     sustainLabel;
    std::unique_ptr <SliderAttachment> sustainSliderValue;
    juce::Slider    releaseSlider;
    juce::Label     releaseLabel;
    std::unique_ptr <SliderAttachment> releaseSliderValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAdsrComponent)
};
