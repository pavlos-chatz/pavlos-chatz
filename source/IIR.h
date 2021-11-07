/*
  ==============================================================================

    IIR.h
    Created: 11 Oct 2021 10:51:56pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include <vector>

namespace adsp
{
	class IIRFilter {

	public:
		IIRFilter(int order);
		~IIRFilter();

		void setCoefficients(std::vector<double>&& b_vec, std::vector<double>&& a_vec);
		double process(double x);
		void processBlock(float* block, int numSamples);
		void processBlockNonInplace(float* blockSource, float* blockDest, int numSamples);

	private:
		int order;

		// Filter Coefficients
		std::vector<double> b;
		std::vector<double> a;

		// State for a canonical form IIR
		double* xh_state;
		double allpass_output;

	};
}