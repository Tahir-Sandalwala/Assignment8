#include "Buffers.hpp"

IF_ID_Buffer::IF_ID_Buffer(InstructionRegister ir, bool validity) :
	m_ir(ir),
	m_valid(validity)
{
}

IF_ID_Buffer::IF_ID_Buffer(bool validity) :
	m_valid(validity)
{
}

ID_EX_Buffer::ID_EX_Buffer(Instruction ins, const Param *params, bool stalled, bool validity) :
	m_ins(ins),
	m_stalled(stalled),
	m_valid(validity)
{
	m_params[0] = params[0];
	m_params[1] = params[1];
	m_params[2] = params[2];
}

ID_EX_Buffer::ID_EX_Buffer(bool validity) :
    m_stalled(false),
	m_valid(validity)
{
}

EX_MEM_Buffer::EX_MEM_Buffer(Register alu_output, const Param *params, Instruction ins, bool validity) :
	m_alu_output(alu_output),
	m_ins(ins),
	m_valid(validity)
{
	m_params[0] = params[0];
	m_params[1] = params[1];
	m_params[2] = params[2];
}

EX_MEM_Buffer::EX_MEM_Buffer(bool validity) :
	m_valid(validity)
{
}

MEM_WB_Buffer::MEM_WB_Buffer(Register output, Register write, Instruction ins, bool validity) :
	m_output(output),
	m_write(write),
	m_ins(ins),
	m_valid(validity)
{
}

MEM_WB_Buffer::MEM_WB_Buffer(bool validity) :
	m_valid(validity)
{
}
