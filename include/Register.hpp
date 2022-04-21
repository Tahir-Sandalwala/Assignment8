#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Utility.hpp"
#include <functional>

class Register
{
public:
	int8_t read() const;
	void write(int8_t data);

    Register();

    bool m_dirty;
    uint8_t m_reg_num;

private:
	uint8_t m_data;
};

class InstructionRegister
{
public:
	int16_t read() const;
	void write(int16_t data);

    InstructionRegister();

private:
	uint16_t m_data;
};

enum class ParamType {
    REGISTER,
    OFFSET,
    INVALID
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
