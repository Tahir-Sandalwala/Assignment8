#include "RegisterFile.hpp"

RegisterFile::RegisterFile() :
	m_read_ports_busy(0),
	m_write_ports_busy(0)
{
}

int8_t RegisterFile::read(uint8_t reg_num) const
{
	return m_reg[reg_num].read();
}

void RegisterFile::write(uint8_t reg_num, int8_t data)
{
	m_reg[reg_num].write(data);
}

bool RegisterFile::can_read()
{
	return m_read_ports_busy < 2;
}

bool RegisterFile::can_write()
{
	return m_write_ports_busy < 1;
}

bool RegisterFile::start_read()
{
	if (can_read())
	{
		m_read_ports_busy++;
		return true;
	}
	return false;
}

bool RegisterFile::start_write()
{
	if (can_write())
	{
		m_write_ports_busy++;
		return true;
	}
	return false;
}

void RegisterFile::stop_read()
{
	m_read_ports_busy--;
	if (m_read_ports_busy < 0)
	{
		m_read_ports_busy = 0;
	}
}

void RegisterFile::stop_write()
{
	m_write_ports_busy--;
	if (m_write_ports_busy < 0)
	{
		m_write_ports_busy = 0;
	}
}
