/*
  ==============================================================================

    ADSR.h
    Created: 20 Feb 2021 12:51:09am
    Author:  Richie Haynes

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthADSR : public juce::ADSR
{
public:
    
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    float getAttack();
    void setAttack(float attack);
    float getDecay();
    void setDecay(float decay);
    float getSustain();
    void setSustain(float sustain);
    float getRelease();
    void setRelease(float release);
    
    
private:
    juce::ADSR::Parameters adsrParams;
    
};
