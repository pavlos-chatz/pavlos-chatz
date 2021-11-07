/*
  ==============================================================================

    Oscillator.h
    Created: 15 Oct 2021 4:13:37pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

class Oscillator
{
public:
	Oscillator(float sampleRate);
	~Oscillator();

	double getSample();
	/* /brief To sample in a sub sample rate from the Oscillator.  
	 * @param samplesSinceLastCall Samples since the previous time getSample() was called. Note that one over this is the resampling ratio.
	 *
	 */
	double getSample(int samplesSinceLastCall);
	void setFrequency(float newFreq);
	void setAmplitude(double newAmp);

private:
	float freqency; /*> Frequency in hertz */
	float sampleRate;

	double amplitude;
	double phase;

	const double M_2PI = 2.0 * 3.14159265359;
};