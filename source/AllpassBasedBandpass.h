/*
  ==============================================================================

    StateVariableFilter.h
    Created: 11 Oct 2021 10:17:39pm
    Author:  pavlos

  ==============================================================================
*/

#pragma once
#include "IIR.h"

class AllpassBasedBandpass : public adsp::IIRFilter 
{

public: 
	AllpassBasedBandpass();
	~AllpassBasedBandpass();

	void setSampleRate(float newFS);
	void setCutoffNormalized(float newFC);
	void setBandwidthNormalized(float newBW);
	void updateFilterCoefficients();

private:
	void calculateTuningParameters();
	void calculateFilterCoefficients();

	double fs;
	
	// Response Parameters  
	double fb_norm; // normalized -> [0,1] = [0, fs/2]
	double fc_norm; 

	// Tuning (Intermediate) Parameters
	double c;
	double d; 

	// Filter Coefficients
	std::vector<double> b;
	std::vector<double> a; 
	double b0, b1, b2; /*> Temporary values kept here */

	// constants
	double pi = 3.14159265359; 
};