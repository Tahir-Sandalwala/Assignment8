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

struct Param {
    bool m_is_register;
    union {
        std::reference_wrapper<Register> m_reg;
        Offset m_offset;
    };
};


#endif	// REGISTER_HPP
