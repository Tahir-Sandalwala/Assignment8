#include "RegisterFile.hpp"

RegisterFile::RegisterFile() :
	m_read_ports_busy(0),
	m_write_ports_busy(0)
{
	m_reg[0].write(0);
}

int8_t RegisterFile::read(uint8_t reg_num) const
{
	return m_reg[reg_num].read();
}

void RegisterFile::write(uint8_t reg_num, int8_t data)
{
	m_reg[reg_num].write(data);
	m_reg[reg_num].m_dirty = false;
}

bool RegisterFile::can_read(uint8_t reg_num) const
{
	return !m_reg[reg_num].m_dirty;
}

bool RegisterFile::start_write(uint8_t reg_num)
{
	m_reg[reg_num].m_dirty = true;
	return true;
}
