/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "UI Data/SynthAdsrComponent.h"
#include "UI Data/SynthFilterComponent.h"

//==============================================================================
SynthesiserAudioProcessorEditor::SynthesiserAudioProcessorEditor (SynthesiserAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.adsrTree), filter (audioProcessor.filterTree)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // Attack
    setResizable(true, true);
    setSize (800, 600);

    addAndMakeVisible(adsr);
    
}

SynthesiserAudioProcessorEditor::~SynthesiserAudioProcessorEditor()
{
}

//==============================================================================
void SynthesiserAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    //auto rectangleWidth = 9*(getWidth() / 40);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::yellow);
    g.setFont (15.0f);
    
    //g.drawRoundedRectangle(5, 25, rectangleWidth, getHeight() / 2 - 20, 2, 2);
    
    
    
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthesiserAudioProcessorEditor::resized()
{

    adsr.setBounds(10, 10, getWidth()/5, getHeight()/3);
    
}


