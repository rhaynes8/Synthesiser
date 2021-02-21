/*
  ==============================================================================

    SynthFilter.cpp
    Created: 21 Feb 2021 12:30:24pm
    Author:  Richie Haynes

  ==============================================================================
*/

#include "SynthFilter.h"

void SynthFilter::updateFilter(double frequency, double resonance)
{
    setResonance(resonance);
    setFrequency(frequency);
}

void SynthFilter::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    spec.sampleRate = sampleRate;
    
    prepare(spec);
}

void SynthFilter::processNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block (buffer);
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

float SynthFilter::getResonance()
{
    return mResonance;
}
void SynthFilter::setResonance(float resonance)
{
    mResonance = resonance;
}

float SynthFilter::getFrequency() {
    return mCutoffFrequency;
}

void SynthFilter::setFrequency(float frequency) {
    mCutoffFrequency = frequency;
}

float SynthFilter::getSampleRate() {
    return mSampleRate;
}

void SynthFilter::setSampleRate(float sampleRate)
{
    mSampleRate = sampleRate;
}
