#ifndef ALU_HPP
#define ALU_HPP

#include "Utility.hpp"

class ALU
{
public:
	int8_t ADD(int8_t a, int8_t b);
	int8_t SUB(int8_t a, int8_t b);
	int8_t MUL(int8_t a, int8_t b);
	int8_t INC(int8_t &a);
	int8_t AND(int8_t a, int8_t b);
	int8_t OR(int8_t a, int8_t b);
	int8_t NOT(int8_t a);
	int8_t XOR(int8_t a, int8_t b);
};

#endif	// ALU_HPP
