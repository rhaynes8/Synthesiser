/*
  ==============================================================================

    SynthSound.h
    Created: 11 Feb 2021 11:24:32pm
    Author:  Richie Haynes

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};
