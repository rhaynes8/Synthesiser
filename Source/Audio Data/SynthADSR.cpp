/*
  ==============================================================================

    ADSR.cpp
    Created: 20 Feb 2021 12:51:09am
    Author:  Richie Haynes

  ==============================================================================
*/

#include "SynthADSR.h"

// Method for updating ADSR in real time
void SynthADSR::updateADSR(const float attack, const float decay, const float sustain, const float release)
{

    setAttack(attack);
    setDecay(decay);
    setSustain(sustain);
    setRelease(release);
    // Must add adsr parameters to the adsr object
    setParameters(adsrParams);

}

float SynthADSR::getAttack()
{
    return adsrParams.attack;
}
void SynthADSR::setAttack(float attack)
{
    adsrParams.attack = attack;
}

float SynthADSR::getDecay()
{
    return adsrParams.decay;
}

void SynthADSR::setDecay(float decay)
{
    adsrParams.decay = decay;
}

float SynthADSR::getSustain()
{
    return adsrParams.sustain;
}

void SynthADSR::setSustain(float sustain)
{
    adsrParams.sustain = sustain;
}

float SynthADSR::getRelease()
{
    return adsrParams.release;
}

void SynthADSR::setRelease(float release)
{
    adsrParams.release = release;
}
