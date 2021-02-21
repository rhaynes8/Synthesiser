/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 20 Feb 2021 12:50:35am
    Author:  Richie Haynes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthAdsrComponent.h"

//==============================================================================
SynthAdsrComponent::SynthAdsrComponent(juce::AudioProcessorValueTreeState& adsrTree)
{
    
       // Attack
       sliderParameters(attackSlider);
       labelParameters(attackLabel, attackSlider, "A");
       attackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (adsrTree, "attack", attackSlider);
    
       
       // Decay
       
       sliderParameters(decaySlider);
       labelParameters(decayLabel, decaySlider, "D");
       decaySliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (adsrTree, "decay", decaySlider);
       
       // Sustain
       sliderParameters(sustainSlider);
       labelParameters(sustainLabel, sustainSlider, "S");
       sustainSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (adsrTree, "sustain", sustainSlider);

       
       // Release
       sliderParameters(releaseSlider);
       labelParameters(releaseLabel, releaseSlider, "R");
       releaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (adsrTree, "release", releaseSlider);

}

SynthAdsrComponent::~SynthAdsrComponent()
{
}

void SynthAdsrComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SynthAdsrComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto distance = 10;
    auto sliderWidth = 20;
    auto sliderHeight = bounds.getHeight() - 2*distance;
    auto startY = 30;
    
    
    //auto sliderWidth = getWidth() / 20;
    
    attackSlider.setBounds(10, startY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + distance, startY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + distance, startY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + distance, startY, sliderWidth, sliderHeight);

}

void SynthAdsrComponent::sliderParameters(juce::Slider& slider)
{
    slider.setRange(0.0f, 5.0f);
    slider.setValue(0.5f);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(&slider);
    slider.setPopupDisplayEnabled(true, true, this);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
}

void SynthAdsrComponent::labelParameters(juce::Label& label, juce::Slider& slider, juce::String string)
{
    label.setText(string, juce::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(&label);
}
