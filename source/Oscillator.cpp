/*
  ==============================================================================

    Oscillator.cpp
    Created: 15 Oct 2021 4:13:37pm
    Author:  Admin

  ==============================================================================
*/

#include "Oscillator.h"
#include <cmath>

Oscillator::Oscillator(float sampleRate)
	: freqency(0.0f)
	, sampleRate(sampleRate)
	, amplitude(1.0)
	, phase(0.0)
{

}

Oscillator::~Oscillator()
{
}

void Oscillator::setFrequency(float newFreq)
{
	freqency = newFreq;
}

void Oscillator::setAmplitude(double newAmp)
{
	amplitude = newAmp;
}

double Oscillator::getSample()
{
	phase += M_2PI * freqency / (double) sampleRate; 
	return amplitude * std::sin(phase);
}

double Oscillator::getSample(int samplesSinceLastCall)
{
	phase += (double)samplesSinceLastCall * M_2PI * freqency / (double)sampleRate;
	return amplitude * std::sin(phase);
}