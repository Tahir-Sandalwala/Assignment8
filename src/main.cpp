#include "Processor.hpp"
#include <chrono>
#include <cstring>
#include <fstream>
#include <thread>

Processor p;

int main()
{
	std::ifstream icache("./ICache.txt", std::ios::in);

	if (!icache.is_open())
	{
		std::cerr << "Cannot find ICache.txt" << std::endl;
		return -1;
	}

	char hex[3];
	uint8_t address = 0;

	while (!icache.eof())
	{
		icache.getline(hex, 3);
		if (strlen(hex) != 2)
		{
			break;
		}
		uint8_t i = strtoul(hex, nullptr, 16);
		p.m_icache.write(address, i);
		++address;
	}

	std::ifstream dcache("./DCache.txt", std::ios::in);

	if (!dcache.is_open())
	{
		std::cerr << "Cannot find DCache.txt" << std::endl;
		return -1;
	}

	address = 0;

	while (!dcache.eof())
	{
		dcache.getline(hex, 3);
		if (strlen(hex) != 2)
		{
			break;
		}
		uint8_t i = strtoul(hex, nullptr, 16);
		p.m_dcache.write(address, i);
		++address;
	}

	std::ifstream rf("./RF.txt", std::ios::in);

	if (!rf.is_open())
	{
		std::cerr << "Cannot find RF.txt" << std::endl;
		return -1;
	}

	uint8_t reg_num = 0;

	while (!rf.eof())
	{
		rf.getline(hex, 3);
		if (strlen(hex) != 2)
		{
			break;
		}
		uint8_t i = strtoul(hex, nullptr, 16);
		p.m_rf.write(reg_num, i);
		++reg_num;
	}

	p.m_if_id_buf.m_valid = false;
	p.m_id_ex_buf.m_valid = false;
	p.m_ex_mem_buf.m_valid = false;
	p.m_mem_wb_buf.m_valid = false;

	while (true)
	{
		// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		p.m_clock++;
		ExecutionStatus stat = p.m_wb_module.write(p.m_mem_wb_buf);
		p.m_mem_wb_buf.m_valid = false;
		if (stat == ExecutionStatus::HALTED)
		{
			break;
		}

		p.m_mem_wb_buf = p.m_mem_module.memory(p.m_ex_mem_buf);
		if (!p.m_mem_wb_buf.m_valid && p.m_mem_wb_buf.m_ins == Instruction::HLT)
		{
			p.m_id_ex_buf.m_valid = false;
			p.m_if_id_buf.m_valid = false;
			p.m_mem_wb_buf.m_valid = true;
		}
		p.m_ex_mem_buf.m_valid = false;
		EX_MEM_Buffer buf = p.m_ex_module.execute(p.m_id_ex_buf);
		p.m_ex_mem_buf = buf;
		p.m_id_ex_buf.m_valid = false;
		if (p.m_ex_mem_buf.m_valid && (p.m_ex_mem_buf.m_ins == Instruction::BEQZ || p.m_ex_mem_buf.m_ins == Instruction::JMP))
		{
			p.m_if_id_buf.m_valid = false;
			p.m_id_ex_buf.m_valid = false;
			p.m_control_stalls++;
			p.m_stalls++;
			continue;
		}
		ID_EX_Buffer idex = p.m_id_module.decode(p.m_if_id_buf);
		if (idex.m_stalled)
		{
			continue;
		}
		p.m_if_id_buf.m_valid = false;
		p.m_id_ex_buf = idex;
		if (idex.m_valid && (idex.m_ins == Instruction::BEQZ || idex.m_ins == Instruction::JMP))
		{
			p.m_control_stalls++;
			p.m_stalls++;
			continue;
		}
		p.m_if_id_buf = p.m_if_module.fetch();
	}

	/*
Total number of instructions executed: 8
Number of instructions in each class
Arithmetic instructions              : 3
Logical instructions                 : 1
Data instructions                    : 3
Control instructions                 : 0
Halt instructions                    : 1
Cycles Per Instruction               : 2.25
Total number of stalls               : 6
Data stalls (RAW)                    : 6
Control stalls                       : 0
    */

	std::cout << "Total number of instructions executed:    " << (uint16_t) p.m_total_instr << std::endl;
	std::cout << "Number of instructions in each class" << std::endl;
	std::cout << "Arithmetic instructions:                  " << (uint16_t) p.m_arithmetic_instr << std::endl;
	std::cout << "Logical instructions:                     " << (uint16_t) p.m_logical_instr << std::endl;
	std::cout << "Data instructions:                        " << (uint16_t) p.m_data_instr << std::endl;
	std::cout << "Control instructions:                     " << (uint16_t) p.m_control_instr << std::endl;
	std::cout << "Halt instructions:                        " << (uint16_t) p.m_halt_instr << std::endl;
	std::cout << "Cycles Per Instruction:                   " << (double) p.m_clock / (double) p.m_total_instr << std::endl;
	std::cout << "Total number of stalls:                   " << (uint16_t) p.m_stalls << std::endl;
	std::cout << "Data stalls (RAW):                        " << (uint16_t) p.m_data_stalls << std::endl;
	std::cout << "Control stalls:                           " << (uint16_t) p.m_control_stalls << std::endl;
}
