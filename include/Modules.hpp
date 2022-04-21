#ifndef MODULES_HPP
#define MODULES_HPP

#include "Cache.hpp"
#include "Register.hpp"
#include "RegisterFile.hpp"
#include "Buffers.hpp"
#include <iostream>

class IF_Module
{
public:
	IF_Module() = default;
	IF_ID_Buffer fetch(void);
};

class ID_Module
{
public:
	ID_Module() = default;
	ID_EX_Buffer decode(IF_ID_Buffer if_id_buf);

private:
	Param create_register(int8_t val);
	Param create_offset(int8_t val);
};

class EX_Module
{
public:
	EX_Module() = default;
	EX_MEM_Buffer execute(ID_EX_Buffer id_ex_buf);

private:
	bool check_if_reg(Param param);
	bool check_if_offset(Param param);
};

class MEM_Module
{
public:
	MEM_Module() = default;
	MEM_WB_Buffer memory(EX_MEM_Buffer ex_mem_buf);
};

class WB_Module
{
public:
	WB_Module() = default;
	ExecutionStatus write(MEM_WB_Buffer mem_wb_buf);
};

#endif	// MODULES_HPP
