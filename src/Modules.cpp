#include "Processor.hpp"

#define init_all_registers() \
	if ((stalled = (!rf.can_read(reg1) || !rf.can_read(reg2) || !rf.start_write(reg0)))) \
	{ \
		break; \
	} \
	params[0] = create_register(rf.read(reg0)); \
	params[0].m_reg.m_reg_num = reg0; \
	params[1] = create_register(rf.read(reg1)); \
	params[1].m_reg.m_reg_num = reg1; \
	params[2] = create_register(rf.read(reg2)); \
	params[2].m_reg.m_reg_num = reg2;

extern Processor p;

IF_ID_Buffer IF_Module::fetch(void)
{
	uint8_t address = p.m_pc.read();
	uint16_t instruction_high = p.m_icache.read(address) << 8;
	uint16_t instruction_low = p.m_icache.read(address + 1);
	uint16_t instruction = instruction_high | instruction_low;
	p.m_ir.write(instruction);
	p.m_pc.write(address + 2);

	return IF_ID_Buffer(p.m_ir);
}

Param ID_Module::create_register(int8_t val)
{
	Param param;
	param.m_param_type = ParamType::REGISTER;
	param.m_reg.write(val);
	return param;
}

Param ID_Module::create_offset(int8_t val)
{
	Param param;
	param.m_param_type = ParamType::OFFSET;
	param.m_offset = val;
	return param;
}

ID_EX_Buffer ID_Module::decode(IF_ID_Buffer if_id_buf)
{
	if (!if_id_buf.m_valid)
	{
		return ID_EX_Buffer(false);
	}
	uint16_t ir_ins = if_id_buf.m_ir.read();
	uint8_t opcode = ir_ins >> 12;
	Instruction ins;
	Param params[3];
	RegisterFile &rf = p.m_rf;

	uint8_t reg0 = (ir_ins >> 8) & 0xf;
	uint8_t reg1 = (ir_ins >> 4) & 0xf;
	uint8_t reg2 = ir_ins & 0xf;  // could also be X
	uint8_t l1_jmp = (ir_ins >> 4) & 0xff;
	uint8_t l1_beqz = ir_ins & 0xff;
	bool stalled = false;

	switch (opcode)
	{
		case 0b0000:
			ins = Instruction::ADD;
			init_all_registers();
			break;
		case 0b0001:
			ins = Instruction::SUB;
			init_all_registers();
			break;
		case 0b0010:
			ins = Instruction::MUL;
			init_all_registers();
			break;
		case 0b0011:
			ins = Instruction::INC;
			if ((stalled = !rf.can_read(reg0) || !rf.start_write(reg0)))
			{
				break;
			}
			params[0] = create_register(rf.read(reg0));
			params[0].m_reg.m_reg_num = reg0;
			break;
		case 0b0100:
			ins = Instruction::AND;
			init_all_registers();
			break;
		case 0b0101:
			ins = Instruction::OR;
			init_all_registers();
			break;
		case 0b0110:
			ins = Instruction::NOT;
			if ((stalled = (!rf.can_read(reg1)) || !rf.start_write(reg0)))
			{
				break;
			}
			params[0] = create_register(rf.read(reg0));
			params[0].m_reg.m_reg_num = reg0;
			params[1] = create_register(rf.read(reg1));
			params[1].m_reg.m_reg_num = reg1;
			break;
		case 0b0111:
			ins = Instruction::XOR;
			init_all_registers();
			break;
		case 0b1000:
			ins = Instruction::LOAD;
			if ((stalled = (!rf.can_read(reg1)) || !rf.start_write(reg0)))
			{
				break;
			}
			params[0] = create_register(rf.read(reg0));
			params[0].m_reg.m_reg_num = reg0;
			params[1] = create_register(rf.read(reg1));
			params[1].m_reg.m_reg_num = reg1;
			params[2] = create_offset(reg2);
			break;
		case 0b1001:
			ins = Instruction::STORE;
			if ((stalled = (!rf.can_read(reg0) || !rf.can_read(reg1))))
			{
				break;
			}
			params[0] = create_register(rf.read(reg0));
			params[0].m_reg.m_reg_num = reg0;
			params[1] = create_register(rf.read(reg1));
			params[1].m_reg.m_reg_num = reg1;
			params[2] = create_offset(reg2);
			break;
		case 0b1010:
			ins = Instruction::JMP;
			params[0] = create_offset(l1_jmp);
			break;
		case 0b1011:
			ins = Instruction::BEQZ;
			if ((stalled = !rf.can_read(reg0)))
			{
				break;
			}
			params[0] = create_register(reg0);
			params[0].m_reg.m_reg_num = reg0;
			params[1] = create_offset(l1_beqz);
			break;
		case 0b1111:
			ins = Instruction::HLT;
			break;
		default:
			ins = Instruction::INVALID;
	}

	if (stalled)
	{
		p.m_data_stalls++;
		p.m_stalls++;
	}

	return ID_EX_Buffer(ins, params, stalled);
}

bool EX_Module::check_if_reg(Param param)
{
	return param.m_param_type == ParamType::REGISTER;
}

bool EX_Module::check_if_offset(Param param)
{
	return param.m_param_type == ParamType::OFFSET;
}

EX_MEM_Buffer EX_Module::execute(ID_EX_Buffer id_ex_buf)
{
	if (!id_ex_buf.m_valid)
	{
		return EX_MEM_Buffer(false);
	}
	Instruction ins = id_ex_buf.m_ins;
	Param *params = id_ex_buf.m_params;
	ALU alu = p.m_alu;

	Register alu_output;

	switch (ins)
	{
		case Instruction::ADD:
			std::cout << "ADD" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_arithmetic_instr;
			break;
		case Instruction::SUB:
			std::cout << "SUB" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.SUB(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_arithmetic_instr;
			break;
		case Instruction::MUL:
			std::cout << "MUL" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.MUL(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_arithmetic_instr;
			break;
		case Instruction::INC:
			std::cout << "INC" << std::endl;
			if (!check_if_reg(params[0]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.INC(params[1].m_reg.read()));
			++p.m_arithmetic_instr;
			break;
		case Instruction::AND:
			std::cout << "AND" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.AND(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_logical_instr;
			break;
		case Instruction::OR:
			std::cout << "OR" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.OR(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_logical_instr;
			break;
		case Instruction::NOT:
			std::cout << "NOT" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.NOT(params[1].m_reg.read()));
			++p.m_logical_instr;
			break;
		case Instruction::XOR:
			std::cout << "XOR" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.XOR(params[1].m_reg.read(), params[2].m_reg.read()));
			++p.m_logical_instr;
			break;
		case Instruction::LOAD:
			std::cout << "LOAD" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_offset(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_offset));
			++p.m_data_instr;
			break;
		case Instruction::STORE:
			std::cout << "STORE" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_offset(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_offset));
			++p.m_data_instr;
			break;
		case Instruction::JMP:
			std::cout << "JMP" << std::endl;
			if (!check_if_offset(params[0]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(p.m_pc.read(), params[0].m_offset << 1));
			p.m_pc.write(alu_output.read());
			++p.m_control_instr;
			break;
		case Instruction::BEQZ:
			std::cout << "BEQZ" << std::endl;
			if (!check_if_reg(params[0]) || !check_if_offset(params[1]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(p.m_pc.read(), params[1].m_offset << 1));
			if (params[0].m_reg.read() == 0)
			{
				p.m_pc.write(alu_output.read());
			}
			++p.m_control_instr;
			break;
		case Instruction::HLT:
			std::cout << "HLT" << std::endl;
			++p.m_halt_instr;
			break;
		case Instruction::INVALID:
			std::cout << "INVALID" << std::endl;
			std::cerr << "Invalid instruction. Skipping execution!" << std::endl;
	}

	++p.m_total_instr;

	return EX_MEM_Buffer(alu_output, params, ins);
}

MEM_WB_Buffer MEM_Module::memory(EX_MEM_Buffer ex_mem_buf)
{
	if (!ex_mem_buf.m_valid)
	{
		return MEM_WB_Buffer(false);
	}
	Register alu = ex_mem_buf.m_alu_output;
	Param *params = ex_mem_buf.m_params;
	Instruction ins = ex_mem_buf.m_ins;
	Register lmd;

	if (ins == Instruction::HLT || ins == Instruction::JMP || ins == Instruction::BEQZ)
	{
		return MEM_WB_Buffer(alu, params[0].m_reg, ins, false);
	}
	else if (ins == Instruction::STORE)
	{
		p.m_dcache.write(alu.read(), params[0].m_reg.read());
	}
	else if (ins == Instruction::LOAD)
	{
		lmd.write(p.m_dcache.read(alu.read()));
		return MEM_WB_Buffer(lmd, params[0].m_reg, ins);
	}

	return MEM_WB_Buffer(alu, params[0].m_reg, ins);
}

ExecutionStatus WB_Module::write(MEM_WB_Buffer mem_wb_buf)
{
	if (!mem_wb_buf.m_valid)
	{
		return ExecutionStatus::FINISHED;
	}

	if (mem_wb_buf.m_ins == Instruction::HLT)
	{
		return ExecutionStatus::HALTED;
	}

	uint8_t reg_num = mem_wb_buf.m_write.m_reg_num;
	RegisterFile &rf = p.m_rf;

	// if (!rf.can_write(reg_num))
	// {
	// p.m_stall++;
	// p.m_data_stalls++;
	// return ExecutionStatus::STALLED;
	// }

	rf.write(reg_num, mem_wb_buf.m_output.read());
	return ExecutionStatus::FINISHED;
}
