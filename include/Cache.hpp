#ifndef CACHE_HPP
#define CACHE_HPP

#include "Utility.hpp"

class Cache
{
protected:
	Block set[NUM_SETS];

public:
	int read(int address);
	void write(int address, int data);
};

#endif	// CACHE_HPP
