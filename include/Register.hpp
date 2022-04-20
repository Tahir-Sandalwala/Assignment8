#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Utility.hpp"
#include <functional>

class Register
{
private:
	uint8_t m_data;

public:
	int8_t read() const;
	void write(int8_t data);
};

class InstructionRegister
{
private:
	uint16_t m_data;

public:
	int16_t read() const;
	void write(int16_t data);
};

enum class ParamType {
    Register,
    Offset,
    Invalid
};

struct Param {
    ParamType m_param_type;
    union {
        Register m_reg;
        Offset m_offset;
    };

    Param();
};


#endif	// REGISTER_HPP
