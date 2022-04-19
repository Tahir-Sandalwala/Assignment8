#include "Register.hpp"

int8_t Register::read()
{
	return (int8_t) m_data;
}

void Register::write(int8_t data)
{
	m_data = (uint8_t) data;
}
