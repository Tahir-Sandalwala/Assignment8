#ifndef CACHE_HPP
#define CACHE_HPP

#include "Utility.hpp"

class Cache
{
protected:
	Block m_set[NUM_SETS];

public:
	uint8_t read(uint8_t address);
	void write(uint8_t address, uint8_t data);
};

#endif	// CACHE_HPP
