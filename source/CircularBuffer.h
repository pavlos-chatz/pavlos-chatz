/*
  ==============================================================================

    circularBuffer.h
    Created: 11 Oct 2021 10:56:24pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

template <typename T> 
class CircularBuffer {
	CircularBuffer();
	~CircularBuffer();

public:
	void write(const T*buffer);
	void read(T*buffer);

private:
	int size;
	T* data;

	int readIndex;  
	int writeIndex; 
};