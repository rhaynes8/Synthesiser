/*
  ==============================================================================

    SynthFilterComponent.cpp
    Created: 21 Feb 2021 12:29:51pm
    Author:  Richie Haynes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthFilterComponent.h"

//==============================================================================
SynthFilterComponent::SynthFilterComponent(juce::AudioProcessorValueTreeState& filterTree)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SynthFilterComponent::~SynthFilterComponent()
{
}

void SynthFilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SynthFilterComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SynthFilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
