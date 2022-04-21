#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "Buffers.hpp"
#include "Modules.hpp"
#include "ALU.hpp"

struct Processor
{
	Processor();

	ALU m_alu;

	RegisterFile m_rf;
	Register m_pc;
	InstructionRegister m_ir;

    ICache m_icache;
    DCache m_dcache;

	IF_Module m_if_module;
	ID_Module m_id_module;
	EX_Module m_ex_module;
	MEM_Module m_mem_module;
	WB_Module m_wb_module;

	IF_ID_Buffer m_if_id_buf;
	ID_EX_Buffer m_id_ex_buf;
	EX_MEM_Buffer m_ex_mem_buf;
	MEM_WB_Buffer m_mem_wb_buf;

	uint16_t m_clock;
	uint8_t m_total_instr;
	uint8_t m_arithmetic_instr;
	uint8_t m_logical_instr;
	uint8_t m_data_instr;
	uint8_t m_control_instr;
	uint8_t m_halt_instr;
	uint8_t m_stall;
	uint8_t m_data_stalls;
	uint8_t m_control_stalls;
};


#endif	// PROCESSOR_HPP
