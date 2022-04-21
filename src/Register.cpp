#include "Register.hpp"

Register::Register() :
	m_dirty(false),
	m_data(0)
{
}

int8_t Register::read() const
{
	return (int8_t) m_data;
}

void Register::write(int8_t data)
{
	m_data = (uint8_t) data;
}

InstructionRegister::InstructionRegister() :
	m_data(0)
{
}

int16_t InstructionRegister::read() const
{
	return (int16_t) m_data;
}

void InstructionRegister::write(int16_t data)
{
	m_data = (uint16_t) data;
}

Param::Param() :
	m_param_type(ParamType::INVALID)
{
}
