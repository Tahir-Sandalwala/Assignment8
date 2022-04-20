#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP

#include "Register.hpp"
#include "Utility.hpp"

class RegisterFile
{
public:
	int8_t read(uint8_t reg_num) const;
	void write(uint8_t reg_num, int8_t data);

private:
	Register m_reg[NUM_REGS];
	mutable bool m_read_port_used[2];
	mutable bool m_write_port_used;
	mutable bool m_request_processed;

	int8_t read_reg_from_port(uint8_t reg_num, uint8_t port) const;
};

#endif	// REGISTER_FILE_HPP
