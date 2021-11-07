/*
  ==============================================================================

    StateVariableFilter.cpp
    Created: 11 Oct 2021 10:17:26pm
    Author:  pavlos

  ==============================================================================
*/

#include "AllpassBasedBandpass.h"

AllpassBasedBandpass::AllpassBasedBandpass()
	: IIRFilter(2)
	, fb_norm(0.3)
	, fc_norm(0.02)
	, b0(0.0)
	, b1(0.0)
	, b2(0.0)
	, c(0.0)
	, d(0.0)
{
}

AllpassBasedBandpass::~AllpassBasedBandpass() 
{

}

void AllpassBasedBandpass::calculateTuningParameters()
{
	c = (tan(pi * fb_norm / 2.0) - 1.0) / (tan(pi * fb_norm / 2.0) + 1.0);
	d = -cos(pi * fc_norm);
}

void AllpassBasedBandpass::calculateFilterCoefficients()
{
	b0 = -c;
	b1 = d * (1.0 - c);
	b2 = 1.0;
	// a0 = 1.0;
	// a1 = d * (1.0 - c); 
	// a2 = -c;

	b.clear();
	a.clear();
	b.insert(b.end(), { b0, b1, b2 });
	a.insert(a.end(), { b2, b1, b0 }); 
}

void AllpassBasedBandpass::updateFilterCoefficients()
{
	calculateTuningParameters();
	calculateFilterCoefficients();
	this->setCoefficients(std::move(b), std::move(a));
}

void AllpassBasedBandpass::setSampleRate(float newFS)
{
	fs = newFS;
}

void AllpassBasedBandpass::setCutoffNormalized(float newFC)
{
	fc_norm = newFC;
}

void AllpassBasedBandpass::setBandwidthNormalized(float newBW)
{
	fb_norm = newBW;
}