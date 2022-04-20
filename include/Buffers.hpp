#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include "Cache.hpp"
#include "Register.hpp"
#include "RegisterFile.hpp"

struct IF_ID_Buffer
{
	const InstructionRegister &m_ir;

    IF_ID_Buffer(const InstructionRegister &ir);
};

struct ID_EX_Buffer
{
	Instruction m_ins;
	Param m_params[3];

    ID_EX_Buffer(Instruction ins, const Param *params);
};

struct EX_MEM_Buffer
{
	const Register m_alu_output;
	Param m_params[3];
	Instruction m_ins;

    EX_MEM_Buffer(const Register &alu_output, const Param *params, Instruction ins);
};

struct MEM_WB_Buffer
{
	const Register m_output;
	Register m_write;

	MEM_WB_Buffer(const Register &output, Register write);
};

#endif	// BUFFERS_HPP
