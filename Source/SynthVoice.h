/*
  ==============================================================================

    SynthVoice.h
    Created: 11 Feb 2021 11:24:15pm
    Author:  Richie Haynes

  ==============================================================================
*/

#pragma once
#include "SynthSound.h"
#include "Audio Data/SynthADSR.h"
#include "Audio Data/SynthFilter.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound * sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void update(const float attack, const float decay, const float sustain, const float release);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
private:
    
    // lambda = capture, input, function code
    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Oscillator<float> osc {[] (float x) { return std::sin(x); }};
    juce::dsp::Gain<float> gain;
    SynthADSR adsr;
    SynthFilter filter;
};

