/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainLawsAudioProcessor::GainLawsAudioProcessor()
    : anotherBuffer (1,1)
	,pluginON(0)
{
    // Set up some default values..
    lastUIWidth = 400;
    lastUIHeight = 200;
}

GainLawsAudioProcessor::~GainLawsAudioProcessor()
{
}

//==============================================================================
void GainLawsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	if (!init)
	{
		C = 0.5;
		panMode = 0;

		anotherBuffer.setSize(1,samplesPerBlock);
		anotherBuffer.clear();
		init = !init;
	}
}


void GainLawsAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
	const int numTracks = getNumInputChannels();

	if (pluginON)
	{
		if (panMode == 0)
		{
			L = C;
			R = 1-C;
		}
		else if (panMode == 1)
		{ 
			L = sqrt(C);
			R = sqrt(1-C);
		}
		else if (panMode == 2)
		{
			L = sin(C*(M_PI/2));
			R = cos(C*(M_PI/2));
		}
		// Apply gain
		buffer.applyGain(0,0,numSamples,(float)R);
		buffer.applyGain(1,0,numSamples,(float)L);
	}
}

void GainLawsAudioProcessor::pluginONOFF(bool state)
{
	pluginON = state;
}

void GainLawsAudioProcessor::changeMode()
{
	panMode++;
	if (panMode > 2)
		panMode = 0;
}

int GainLawsAudioProcessor::getMode()
{
	if (panMode > 2 || panMode < 0)
		panMode = 0;
	return panMode;
}

void GainLawsAudioProcessor::changePan(float newC)
{
	if (newC > 1)
		newC = 1;
	if (newC < 0)
		newC = 0;

	C = newC;
}

float GainLawsAudioProcessor::ExpMovAv(float prevEMA, float input, float alpha)//, bool first)
{
	float newEMA = alpha*input + (1-alpha)*prevEMA;

	if (fabs(newEMA) < 0.000001)
		newEMA = 0.0f;
	return newEMA;
}

void GainLawsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void GainLawsAudioProcessor::reset()
{
    // Use this method as the place to clear any var2 lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    anotherBuffer.clear();
}

//==============================================================================
AudioProcessorEditor* GainLawsAudioProcessor::createEditor()
{
    return new GainLawsAudioProcessorEditor (this);
}

//==============================================================================
void GainLawsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void GainLawsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

const String GainLawsAudioProcessor::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String GainLawsAudioProcessor::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool GainLawsAudioProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool GainLawsAudioProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool GainLawsAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool GainLawsAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

int GainLawsAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float GainLawsAudioProcessor::getParameter (int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case Param1:    return var1;
        case Param2:    return var2;
        default:            return 0.0f;
    }
}

void GainLawsAudioProcessor::setParameter (int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case Param1:    var1 = newValue;  break;
        case Param2:    var2 = newValue;  break;
        default:            break;
    }
}

const String GainLawsAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case Param1:     return "var1";
        case Param2:    return "var2";
        default:            break;
    }

    return String::empty;
}

const String GainLawsAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

bool GainLawsAudioProcessor::silenceInProducesSilenceOut() const
{
	return false;
}

double GainLawsAudioProcessor::getTailLengthSeconds() const
{
	return false;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainLawsAudioProcessor();
}
