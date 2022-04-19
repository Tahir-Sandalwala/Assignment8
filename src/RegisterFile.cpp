#include "RegisterFile.hpp"

int8_t RegisterFile::read(uint8_t reg_num)
{
	if (!m_read_port_used[0])
	{
		return read_reg_from_port(reg_num, 0);
	}
	else if (!m_read_port_used[1])
	{
		return read_reg_from_port(reg_num, 1);
	}

	m_request_processed = false;
	return -1;
}

int8_t RegisterFile::read_reg_from_port(uint8_t reg_num, uint8_t port)
{
	m_read_port_used[port] = true;
	m_request_processed = true;
	return m_reg[reg_num].read();
}


void RegisterFile::write(uint8_t reg_num, int8_t data)
{
	if (!m_write_port_used)
	{
		m_write_port_used = true;
		m_request_processed = true;
		m_reg[reg_num].write(data);
	}
	else
	{
		m_request_processed = false;
	}
}
