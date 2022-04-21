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

bool RegisterFile::can_read(uint8_t reg_num) const
{
	return m_read_ports_busy < 2 && !m_reg[reg_num].m_dirty;
}

bool RegisterFile::can_write(uint8_t reg_num) const
{
	return m_write_ports_busy < 1 && !m_reg[reg_num].m_dirty;
}

bool RegisterFile::start_write(uint8_t reg_num)
{
	if (can_write(reg_num))
	{
		m_write_ports_busy++;
		m_reg[reg_num].m_dirty = true;
		return true;
	}
	return false;
}

void RegisterFile::stop_write(uint8_t reg_num)
{
	m_write_ports_busy--;
	m_reg[reg_num].m_dirty = false;
	if (m_write_ports_busy < 0)
	{
		m_write_ports_busy = 0;
	}
}
