#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP

#include "Register.hpp"
#include "Utility.hpp"

class RegisterFile
{
public:
	RegisterFile();
	int8_t read(uint8_t reg_num) const;
	void write(uint8_t reg_num, int8_t data);

	bool can_write();
	bool can_read();

	bool start_write();
	void stop_write();
	bool start_read();
	void stop_read();

private:
	Register m_reg[NUM_REGS];
	mutable uint8_t m_read_ports_busy;
	mutable uint8_t m_write_ports_busy;
};

#endif	// REGISTER_FILE_HPP
