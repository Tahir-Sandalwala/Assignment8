#ifndef CACHE_HPP
#define CACHE_HPP

#include "Utility.hpp"

class Cache
{
public:
	uint8_t read(uint8_t address) const;
	void write(uint8_t address, uint8_t data);

	Cache();

protected:
	Block m_set[NUM_SETS];
};

typedef Cache ICache;
typedef Cache DCache;

#endif	// CACHE_HPP
