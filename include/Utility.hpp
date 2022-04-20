#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <exception>
#include <string>

#define BLOCK_SIZE 4
#define NUM_SETS   64  // NUM_SETS = CACHE_SIZE/BLOCK_SIZE = 256/4 = 64
#define NUM_REGS   16
#define REG_SIZE   8

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
	HLT,
	INVALID
};

const Instruction ins_sym_mapping[UINT8_MAX] = {
	Instruction::ADD,
	Instruction::SUB,
	Instruction::MUL,
	Instruction::INC,
	Instruction::AND,
	Instruction::OR,
	Instruction::NOT,
	Instruction::XOR,
	Instruction::LOAD,
	Instruction::STORE,
	Instruction::JMP,
	Instruction::BEQZ,
	Instruction::INVALID,
	Instruction::INVALID,
	Instruction::INVALID,
	Instruction::HLT};

class invalid_param : public std::exception
{
private:
	const char *what_str;

public:
	invalid_param(const char *arg);
	virtual const char *what() const throw();
};

#endif	// UTILITY_HPP
