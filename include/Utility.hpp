#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>

#define BLOCK_SIZE 4
#define NUM_SETS   64  // NUM_SETS = CACHE_SIZE/BLOCK_SIZE = 256/4 = 64
#define NUM_REGS   16
#define REG_SIZE   8

#define IN_BUF
#define OUT_BUF

typedef uint8_t Block[BLOCK_SIZE];
typedef uint8_t Offset;

enum class Instruction
{
	ADD,
	SUB,
	MUL,
	INC,
	AND,
	OR,
	NOT,
	XOR,
	LOAD,
	STORE,
	JMP,
	BEQZ,
	HLT
};

#endif	// UTILITY_HPP
