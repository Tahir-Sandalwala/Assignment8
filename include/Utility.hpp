#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>

#define BLOCK_SIZE 4
#define NUM_SETS   64  // NUM_SETS = CACHE_SIZE/BLOCK_SIZE = 256/4 = 64
#define NUM_REGS   16
#define REG_SIZE   8

typedef uint8_t Block[BLOCK_SIZE];

#endif	// UTILITY_HPP
