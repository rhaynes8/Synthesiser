/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"


//==============================================================================
SynthesiserAudioProcessor::SynthesiserAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),

adsrTree(*this, &undoManager, "PARAMETERS",
         {   std::make_unique<juce::AudioParameterFloat> ("attack", "Attack", 0, 5, 0.5),
             std::make_unique<juce::AudioParameterFloat> ("decay", "Decay", 0, 5, 0.5),
             std::make_unique<juce::AudioParameterFloat> ("sustain", "Sustain", 0, 5, 0.5),
             std::make_unique<juce::AudioParameterFloat> ("release", "Release", 0, 5, 0.5) } ),

filterTree(*this, &undoManager, "FILTERPARAMETERS",
           { std::make_unique<juce::AudioParameterFloat> ("cutoff", "Cutoff", 0, 20000, 1000),
             std::make_unique<juce::AudioParameterFloat> ("resonance", "Resonance", 0, 5, 1) })

#endif
{
    // Add voices and sounds to newly made synthesiser
    // API: The object passed will be managed by the synthesiser and will be deleted when no longer needed
    // Avoids the need to delete the memory from the heap after 'new' keywordd
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
    
    
    
}

SynthesiserAudioProcessor::~SynthesiserAudioProcessor()
{
}

//==============================================================================
const juce::String SynthesiserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthesiserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthesiserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthesiserAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthesiserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthesiserAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthesiserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthesiserAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthesiserAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthesiserAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


//==============================================================================
void SynthesiserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);

    // Prepare each voice through iteration
    for (int i = 0; i < synth.getNumVoices(); i++) {

        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
}

void SynthesiserAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthesiserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthesiserAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    buffer.clear();
    
    for (int i = 0; i < synth.getNumVoices(); i++) {
        
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i))) {
            
            voice->update(*adsrTree.getRawParameterValue("attack"), *adsrTree.getRawParameterValue("decay"), *adsrTree.getRawParameterValue("sustain"), *adsrTree.getRawParameterValue("release"));
            

        }
    }
    // Once all voice are updated, render next block (which in turn renders each next block for each voice)
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool SynthesiserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthesiserAudioProcessor::createEditor()
{
    return new SynthesiserAudioProcessorEditor (*this);
}

//==============================================================================
void SynthesiserAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthesiserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthesiserAudioProcessor();
}
