#include "ALU.hpp"

int8_t ALU::ADD(int8_t a, int8_t b)
{
	return a + b;
}

int8_t ALU::SUB(int8_t a, int8_t b)
{
	return a - b;
}

int8_t ALU::MUL(int8_t a, int8_t b)
{
	return a * b;
}

int8_t ALU::INC(int8_t a)
{
	return a + 1;
}

int8_t ALU::AND(int8_t a, int8_t b)
{
	return a & b;
}

int8_t ALU::OR(int8_t a, int8_t b)
{
	return a | b;
}

int8_t ALU::NOT(int8_t a)
{
	return ~a;
}

int8_t ALU::XOR(int8_t a, int8_t b)
{
	return a ^ b;
}
