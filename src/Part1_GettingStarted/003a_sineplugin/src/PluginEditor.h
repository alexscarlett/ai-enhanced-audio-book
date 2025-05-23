/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */

// Slider: we add Slider::Listener to listen for slider changes
class TestPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       public Slider::Listener
{
public:
  TestPluginAudioProcessorEditor(TestPluginAudioProcessor &);
  ~TestPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  void sliderValueChanged(Slider *slider); // Slider: prototype for slider change

private:
  juce::Slider freqControl; // declares the slider

  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  TestPluginAudioProcessor &audioProcessor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestPluginAudioProcessorEditor)
};
