/*
  ==============================================================================

    SynthVoice.cpp
    Created: 11 Feb 2021 11:24:15pm
    Author:  Richie Haynes

  ==============================================================================
*/

// Feels as though attack and release don't contribute
// Add sliders and values for decay and sustain
// Watch TAP video if no progress

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound * sound)
{
    
    // Check that the our incoming sound is in fact a synthesiser sound
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;

}


void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
    
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepare(spec);
    gain.prepare(spec);
    gain.setGainLinear(0.1);
    adsr.setSampleRate(sampleRate);
    
    
    
}
// Method for updating ADSR in real time
void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{

    adsr.updateADSR(attack, decay, sustain, release);

}



void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    // If we're not playing, don't execute rest of render code
    if (!isVoiceActive())
        return;
    
    // Create separate buffer to main buffer in order to store audio information,
    // which can then be allocated to main buffer upon change
    // This avoids clicks and pops due to discontinuities. E.g. is osc is at +0.7 at 217 samples, when note is changed, it will begin at 0 with the same phase.
    // false and trues are for memory reallocation upon numSamples changing - check API
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock(synthBuffer);
    
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    // Add synth buffer to main output buffer
    for (int channel = 0; channel < synthBuffer.getNumChannels(); channel++) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
    }
    // Check if the adsr is active
    if (!adsr.isActive()) {
        // Clear the incoming midi note if not
        clearCurrentNote();
    }
    
}
