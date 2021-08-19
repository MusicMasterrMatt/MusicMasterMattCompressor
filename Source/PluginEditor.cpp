/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MusicMasterMattCompressorAudioProcessorEditor::MusicMasterMattCompressorAudioProcessorEditor (MusicMasterMattCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    ThresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    ThresholdSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 100, 100);
    ThresholdSlider.setRange(-60, 0, 0.25);
    ThresholdSlider.setValue(0);//set the defualt setting
    addAndMakeVisible(ThresholdSlider);
    
    ThresholdSliderAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "THRESHOLD", ThresholdSlider);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MusicMasterMattCompressorAudioProcessorEditor::~MusicMasterMattCompressorAudioProcessorEditor()
{
}

//==============================================================================
void MusicMasterMattCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    
}

void MusicMasterMattCompressorAudioProcessorEditor::resized()
{
    ThresholdSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 50, 200, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
