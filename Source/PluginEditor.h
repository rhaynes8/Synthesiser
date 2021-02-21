/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI Data/SynthAdsrComponent.h"
#include "UI Data/SynthFilterComponent.h"

//==============================================================================
/**
*/
class SynthesiserAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthesiserAudioProcessorEditor (SynthesiserAudioProcessor&);
    ~SynthesiserAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    SynthesiserAudioProcessor& audioProcessor;
    SynthAdsrComponent adsr;
    SynthFilterComponent filter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthesiserAudioProcessorEditor)
};
