#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "Cache.hpp"
#include "Register.hpp"
#include "RegisterFile.hpp"

class IF_Module
{
private:
	Register &m_pc;
	const ICache &m_icache;
	OUT_BUF Register &m_ir;
};

struct IF_ID_Buffer {
    const Register &m_ir;
};

class ID_Module
{
private:
	IN_BUF const Register &m_ir;
    const RegisterFile &rf;
    OUT_BUF Instruction m_ins;
    OUT_BUF Param m_arg[3];
};

struct ID_EX_Buffer
{
    Instruction m_ins;
    Param m_arg[3];
};

class EX_Module
{
    IN_BUF Instruction m_ins;
    IN_BUF Param m_arg[3];
    OUT_BUF Register m_alu_output;
    OUT_BUF Param m_out_param;
};

class EX_MEM_Buffer
{
    const Register &m_alu_output;
    Param m_out_param;
};

class MEM_Module
{
    IN_BUF OUT_BUF const Register &m_alu_output;
    IN_BUF OUT_BUF Param m_out_param;
};

class MEM_WB_Buffer
{
    const Register &m_alu_output;
};

class WB_Module
{
    IN_BUF const Register *m_alu_output;
};

class Processor
{
private:
	IF_Module IF;
	ID_Module ID;
	EX_Module EX;
	MEM_Module MEM;
	WB_Module WB;

	IF_ID_Buffer IF_ID;
	ID_EX_Buffer ID_EX;
	EX_MEM_Buffer EX_MEM;
	MEM_WB_Buffer MEM_WB;

	Register PC;
	Register IR;
};


#endif	// PROCESSOR_HPP
