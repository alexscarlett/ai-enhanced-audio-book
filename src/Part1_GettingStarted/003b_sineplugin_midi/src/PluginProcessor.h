/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 */
class TestPluginAudioProcessor : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
    ,
                                 public juce::AudioProcessorARAExtension
#endif
{
public:
  //==============================================================================
  TestPluginAudioProcessor();
  ~TestPluginAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
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
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;
  void updateFrequency(double newFreq);
  void updateDecay(float newDecay);

private:
  double phase;
  double dphase;
  double frequency;
  float amp = 0.0f;       // Current amplitude
  float targetAmp = 0.0f; // Target amplitude (0 on note off)
  float ampDecayRate;     // Decay rate per sample
  double getDPhase(double freq, double sampleRate);

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestPluginAudioProcessor)
};
