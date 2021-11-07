/*
  ==============================================================================

    IIR.cpp
    Created: 11 Oct 2021 10:51:56pm
    Author:  Admin

  ==============================================================================
*/

#include "IIR.h"

namespace adsp
{
	IIRFilter::IIRFilter(int order)
		: order(order)
	{
		xh_state = (double*)std::calloc(order, sizeof(double));
	}

	IIRFilter::~IIRFilter()
	{
		//if (xh_state != nullptr) std::free(xh_state);
	}

	void IIRFilter::setCoefficients(std::vector<double>&& b_vec, std::vector<double>&& a_vec)
	{
		b = b_vec;
		a = a_vec;
	}

	double IIRFilter::process(double x)
	{
		xh_state[2] = a[0] * x - a[1] * xh_state[1] - a[2] * xh_state[0];
		x = b[0] * xh_state[2] + b[1] * xh_state[1] + b[2] * xh_state[0];

		// shift contents of "cicular" buffer for state
		xh_state[0] = xh_state[1];
		xh_state[1] = xh_state[2];

		return x;
	}

	void IIRFilter::processBlock(float* block, int numSamples)
	{
		for (int i = 0; i < numSamples; i++)
		{
			xh_state[2] = a[0] * (double)block[i] - a[1] * xh_state[1] - a[2] * xh_state[0];
			allpass_output = (b[0] * xh_state[2] + b[1] * xh_state[1] + b[2] * xh_state[0]);

			block[i] = (float) 0.5 * (block[i] - allpass_output); 
			// shift contents of "cicular" buffer for state
			xh_state[0] = xh_state[1];
			xh_state[1] = xh_state[2];
		}
	}

	void IIRFilter::processBlockNonInplace(float* blockSource, float* blockDest, int numSamples)
	{
		for (int i = 0; i < numSamples; i++)
		{
			xh_state[2] = a[0] * (double)blockSource[i] - a[1] * xh_state[1] - a[2] * xh_state[0];
			allpass_output = (b[0] * xh_state[2] + b[1] * xh_state[1] + b[2] * xh_state[0]);

			blockDest[i] = (float)0.5 * (blockSource[i] - allpass_output);
			// shift contents of "cicular" buffer for state
			xh_state[0] = xh_state[1];
			xh_state[1] = xh_state[2];
		}
	}

}
// TODO : make a circular buffer for the state to support arbitrary order IIRs. Now biquads. 