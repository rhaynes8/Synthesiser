/*
  ==============================================================================

    SynthFilter.h
    Created: 21 Feb 2021 12:30:24pm
    Author:  Richie Haynes

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class SynthFilter : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void processNextBlock(juce::AudioBuffer<float>& buffer);
    float processNextSample(int channel, float inputValue);
    void updateFilter(double frequency, double resonance);
    float getResonance();
    void setResonance(float resonance);
    float getFrequency();
    void setFrequency(float frequency);
    float getSampleRate();
    void setSampleRate(float sampleRate);
    
    
private:
    float mCutoffFrequency;
    float mSampleRate;
    float mResonance;
    juce::dsp::StateVariableFilter::Parameters<float> parameters;
};
