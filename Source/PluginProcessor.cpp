/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
MusicMasterMattCompressorAudioProcessor::MusicMasterMattCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameter", createParameters())
#endif
{
}

MusicMasterMattCompressorAudioProcessor::~MusicMasterMattCompressorAudioProcessor()
{
}

//==============================================================================
const juce::String MusicMasterMattCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MusicMasterMattCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MusicMasterMattCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MusicMasterMattCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MusicMasterMattCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MusicMasterMattCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MusicMasterMattCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MusicMasterMattCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MusicMasterMattCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MusicMasterMattCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MusicMasterMattCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
       spec.numChannels = getTotalNumInputChannels();
       spec.sampleRate = sampleRate;
       spec.maximumBlockSize = samplesPerBlock;

    compressor.prepare(spec);
    compressor.reset();
   
    
    //void juce::dsp::Compressor<<#typename SampleType#>>::process (const ProcessContext & context);
   
}

void MusicMasterMattCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MusicMasterMattCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MusicMasterMattCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    //added 20 Aug 5pm
    auto currentThreshold = thresholdRaw->load();
    auto currentRatio = ratioRaw->load();
    //added 20 Aug 5pm
    compressor.setThreshold (currentThreshold);
    compressor.setRatio (currentRatio);
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

 // I created an Audio Block here
    //juce::dsp::AudioBlock<float> block(buffer);
    //compressor.process(juce::dsp::ProcessContextReplacing<float>(block));

  
    //added 20 Aug 5pm
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    compressor.process(context);
    

 

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MusicMasterMattCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MusicMasterMattCompressorAudioProcessor::createEditor()
{
    return new MusicMasterMattCompressorAudioProcessorEditor (*this);
    
    //return new juce::GenericAudioProcessorEditor(*this); <----- no longer needed
}

//==============================================================================
void MusicMasterMattCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MusicMasterMattCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts)
//void parameterChanged (const juce::String& parameterID, float newValue) dont need this now
//{
    //if (parameterID == "Threshold")
        //compressor.setThreshold (newValue);
    
    
    
    
    
//ChainSettings settings;
    
   // settings.Threshold = apvts.getRawParameterValue("Threshold")->load();
    //settings.Ratio = apvts.getRawParameterValue("Ratio")->load();
    //settings.Attack = apvts.getRawParameterValue("Attack")->load();
    //settings.Release = apvts.getRawParameterValue("Attack")->load();
    //return settings;
//}




//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MusicMasterMattCompressorAudioProcessor();
};

juce::AudioProcessorValueTreeState::ParameterLayout
MusicMasterMattCompressorAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("THRESHOLD", "Threshold",-60.f, 0.f, 0.f)); // There is no SKEW option though :(
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio",1.f, 40.f, 1.f)); //
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack",0.f, 200.f, 13.f));
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release",5.f, 5000.f, 1.f)); ////check that final section is the SKEW and INTERVALS  are  in the Slider clas
    
    //added  20Aug
    thresholdRaw  = apvts.getRawParameterValue ("THRESHOLD");
    ratioRaw      = apvts.getRawParameterValue ("RATIO");
    
    return { params.begin(), params.end() };
}
