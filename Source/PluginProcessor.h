/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//struct

//{
    //float Threshold {0};
    //float Ratio {0};
    //float Attack {0};
    //float Release {0};
//};



//==============================================================================
/**
*/
class MusicMasterMattCompressorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MusicMasterMattCompressorAudioProcessor();
    ~MusicMasterMattCompressorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
   
    static juce::AudioProcessorValueTreeState apvts; // THIS IS A CONSTRUCTER
    apvts.addParameterListener ("THRESHOLD");
    apvts.addParameterListener ("RATIO");


private:

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    std::atomic<float>* thresholdRaw = nullptr;
    std::atomic<float>* ratioRaw = nullptr;
    
    
    juce::dsp::Compressor<float> compressor;
    

    //juce::Slider Threshold;
    //juce::Slider Ratio;
    
    //template <juce::dsp::Compressor<juce::Process>
    //using Compressor =
      
  
      
 
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicMasterMattCompressorAudioProcessor)
};
