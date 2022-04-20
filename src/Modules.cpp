#include "Processor.hpp"

#define init_all_registers() \
	params[0] = create_register(rf.read(reg0)); \
	params[1] = create_register(rf.read(reg1)); \
	params[2] = create_register(rf.read(reg2));

extern Processor p;

IF_ID_Buffer IF_Module::fetch(void)
{
	uint8_t address = p.m_pc.read();
	uint16_t instruction_low = p.m_icache.read(address);
	uint16_t instruction_high = p.m_icache.read(address + 1) << 8;
	uint16_t instruction = instruction_high | instruction_low;
	p.m_ir.write(instruction);
	p.m_pc.write(address + 2);

	return IF_ID_Buffer(p.m_ir);
}

Param ID_Module::create_register(int8_t val)
{
	Param param;
	param.m_param_type = ParamType::Register;
	param.m_reg.write(val);
	return param;
}

ID_EX_Buffer ID_Module::decode(IF_ID_Buffer if_id_buf)
{
	uint16_t ir_ins = if_id_buf.m_ir.read();
	uint8_t opcode = ir_ins >> 12;
	Instruction ins;
	Param params[3];
	const RegisterFile &rf = p.m_rf;

	uint8_t reg0 = (ir_ins >> 8) & 0xf;
	uint8_t reg1 = (ir_ins >> 4) & 0xf;
	uint8_t reg2 = ir_ins & 0xf;  // could also be X
	uint8_t l1_jmp = (ir_ins >> 4) & 0xff;
	uint8_t l1_beqz = ir_ins & 0xff;

	switch (opcode)
	{
		case 0x0000:
			ins = Instruction::ADD;
			init_all_registers();
			break;
		case 0x0001:
			ins = Instruction::SUB;
			init_all_registers();
			break;
		case 0x0010:
			ins = Instruction::MUL;
			init_all_registers();
			break;
		case 0x0011:
			ins = Instruction::INC;
			params[0] = create_register(rf.read(reg0));
			break;
		case 0x0100:
			ins = Instruction::AND;
			init_all_registers();
			break;
		case 0x0101:
			ins = Instruction::OR;
			init_all_registers();
			break;
		case 0x0110:
			ins = Instruction::NOT;
			params[0] = create_register(rf.read(reg0));
			params[1] = create_register(rf.read(reg1));
			break;
		case 0x0111:
			ins = Instruction::XOR;
			init_all_registers();
			break;
		case 0x1000:
			ins = Instruction::LOAD;
			params[0] = create_register(rf.read(reg0));
			params[1] = create_register(rf.read(reg1));
			params[2] = create_offset(reg2);
			break;
		case 0x1001:
			ins = Instruction::STORE;
			params[0] = create_register(rf.read(reg0));
			params[1] = create_register(rf.read(reg1));
			params[2] = create_offset(reg2);
			break;
		case 0x1010:
			ins = Instruction::JMP;
			params[0] = create_offset(l1_jmp);
			break;
		case 0x1011:
			ins = Instruction::BEQZ;
			params[0] = create_register(reg0);
			params[1] = create_offset(l1_beqz);
			break;
		case 0x1111:
			ins = Instruction::HLT;
			break;
		default:
			ins = Instruction::INVALID;
	}

	return ID_EX_Buffer(ins, params);
}

bool EX_Module::check_if_reg(Param param)
{
	return param.m_param_type == ParamType::Register;
}

bool EX_Module::check_if_offset(Param param)
{
	return param.m_param_type == ParamType::Offset;
}

EX_MEM_Buffer EX_Module::execute(ID_EX_Buffer id_ex_buf)
{
	Instruction ins = id_ex_buf.m_ins;
	Param *params = id_ex_buf.m_params;
	ALU alu = p.m_alu;

	Register alu_output;

	switch (ins)
	{
		case Instruction::ADD:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::SUB:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.SUB(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::MUL:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.MUL(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::INC:
			if (!check_if_reg(params[0]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.INC(params[1].m_reg.read()));
			break;
		case Instruction::AND:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.AND(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::OR:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.OR(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::NOT:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.NOT(params[1].m_reg.read()));
			break;
		case Instruction::XOR:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_reg(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.XOR(params[1].m_reg.read(), params[2].m_reg.read()));
			break;
		case Instruction::LOAD:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_offset(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_offset));
			break;
		case Instruction::STORE:
			if (!check_if_reg(params[0]) || !check_if_reg(params[1]) || !check_if_offset(params[2]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(params[1].m_reg.read(), params[2].m_offset));
			break;
		case Instruction::JMP:
			if (!check_if_offset(params[0]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(p.m_pc.read(), params[0].m_offset << 1));
			p.m_pc.write(alu_output.read());
			break;
		case Instruction::BEQZ:
			if (!check_if_reg(params[0]) || !check_if_offset(params[1]))
			{
				throw invalid_param("Invalid param!");
			}
			alu_output.write(alu.ADD(p.m_pc.read(), params[1].m_offset << 1));
			if (params[0].m_reg.read() == 0)
			{
				p.m_pc.write(alu_output.read());
			}
			break;
		case Instruction::HLT:
			break;
		case Instruction::INVALID:
			std::cerr << "Invalid instruction. Skipping execution!" << std::endl;
	}

	return EX_MEM_Buffer(alu_output, params, ins);
}

MEM_WB_Buffer MEM_Module::memory(EX_MEM_Buffer ex_mem_buf)
{
	Register alu = ex_mem_buf.m_alu_output;
	Param *params = ex_mem_buf.m_params;
	Instruction ins = ex_mem_buf.m_ins;
	Register lmd;

	if (ins == Instruction::STORE)
	{
		p.m_dcache.write(alu.read(), params[0].m_reg.read());
	}
	else if (ins == Instruction::LOAD)
	{
		lmd.write(p.m_dcache.read(alu.read()));
		return MEM_WB_Buffer(lmd, params[0].m_reg);
	}

	return MEM_WB_Buffer(alu, params[0].m_reg);
}

void WB_Module::write(MEM_WB_Buffer mem_wb_buf)
{
	mem_wb_buf.m_write.write(mem_wb_buf.m_output.read());
}
