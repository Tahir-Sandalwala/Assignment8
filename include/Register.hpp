#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Utility.hpp"

class Register
{
private:
	uint8_t m_data;

public:
	int8_t read();
	void write(int8_t data);
};

#endif	// REGISTER_HPP
