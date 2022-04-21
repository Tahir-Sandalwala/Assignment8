#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include "Cache.hpp"
#include "Register.hpp"
#include "RegisterFile.hpp"

struct IF_ID_Buffer
{
	InstructionRegister m_ir;

	bool m_valid;

	IF_ID_Buffer() = default;
	IF_ID_Buffer(bool validity);
    IF_ID_Buffer(InstructionRegister ir, bool validity = true);
};

struct ID_EX_Buffer
{
	Instruction m_ins;
	Param m_params[3];
	bool m_stalled;

	bool m_valid;

	ID_EX_Buffer() = default;
	ID_EX_Buffer(bool validity);
    ID_EX_Buffer(Instruction ins, const Param *params, bool stalled, bool validity = true);
};

struct EX_MEM_Buffer
{
	Register m_alu_output;
	Param m_params[3];
	Instruction m_ins;

	bool m_valid;

	EX_MEM_Buffer() = default;
	EX_MEM_Buffer(bool validity);
    EX_MEM_Buffer(Register alu_output, const Param *params, Instruction ins, bool validity = true);
};

struct MEM_WB_Buffer
{
	Register m_output;
	Register m_write;
	Instruction m_ins;

	bool m_valid;

	MEM_WB_Buffer() = default;
	MEM_WB_Buffer(bool validity);
	MEM_WB_Buffer(Register output, Register write, Instruction ins, bool validity = true);
};

#endif	// BUFFERS_HPP
