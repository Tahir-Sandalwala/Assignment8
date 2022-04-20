#include "Buffers.hpp"

IF_ID_Buffer::IF_ID_Buffer(const InstructionRegister &ir) :
	m_ir(ir)
{
}

ID_EX_Buffer::ID_EX_Buffer(Instruction ins, const Param *params) :
	m_ins(ins)
{
	m_params[0] = params[0];
	m_params[1] = params[1];
	m_params[2] = params[2];
}

EX_MEM_Buffer::EX_MEM_Buffer(const Register &alu_output, const Param *params, Instruction ins) :
	m_alu_output(alu_output),
	m_ins(ins)
{
	m_params[0] = params[0];
	m_params[1] = params[1];
	m_params[2] = params[2];
}

MEM_WB_Buffer::MEM_WB_Buffer(const Register &output, Register write) :
	m_output(output),
	m_write(write)
{
}
