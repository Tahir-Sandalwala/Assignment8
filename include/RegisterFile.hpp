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

	bool can_write(uint8_t reg_num) const;
	bool can_read(uint8_t reg_num) const;

	bool start_write(uint8_t reg_num);
	void stop_write(uint8_t reg_num);

private:
	Register m_reg[NUM_REGS];
	mutable int8_t m_read_ports_busy;
	mutable int8_t m_write_ports_busy;
};

#endif	// REGISTER_FILE_HPP
