#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP

#include "Utility.hpp"
#include "Register.hpp"

class RegisterFile
{
public:
	int8_t read(uint8_t reg_num);
	void write(uint8_t reg_num, int8_t data);

private:
	Register m_reg[NUM_REGS];
	bool m_read_port_used[2];
	bool m_write_port_used;
	bool m_request_processed;

    int8_t read_reg_from_port(uint8_t reg_num, uint8_t port);
};

#endif	// REGISTER_FILE_HPP
