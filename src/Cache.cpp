#include "Cache.hpp"

uint8_t Cache::read(uint8_t address) const
{
	uint8_t set = address >> 2;
	uint8_t offset = address & 3;
	return m_set[set][offset];
}

void Cache::write(uint8_t address, uint8_t val)
{
	uint8_t set = address >> 2;
	uint8_t offset = address & 3;
	m_set[set][offset] = val;
}
