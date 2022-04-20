#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "Buffers.hpp"
#include "Modules.hpp"
#include "ALU.hpp"

struct Processor
{
	ALU m_alu;

	IF_Module m_if_module;
	ID_Module m_id_module;
	EX_Module m_ex_module;
	MEM_Module m_mem_module;
	WB_Module m_wb_module;

	IF_ID_Buffer m_if_id_buf;
	ID_EX_Buffer m_id_ex_buf;
	EX_MEM_Buffer m_ex_mem_buf;
	MEM_WB_Buffer m_mem_wb_buf;

	RegisterFile m_rf;
	Register m_pc;
	InstructionRegister m_ir;

    ICache m_icache;
    DCache m_dcache;

private:

};


#endif	// PROCESSOR_HPP
