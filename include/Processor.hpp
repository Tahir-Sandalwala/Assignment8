#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <iostream>

class IF_Module
{
private:
	Register& PC;
	Register& IR;
	Cache& ICache;

public:
	IF_Module(Register& PC, Register& IR, Cache& ICache);
};

class IF_ID_Buffer
{
};

class ID_Module
{
};

class ID_EX_Buffer
{
};

class EX_Module
{
};

class EX_MEM_Buffer
{
};

class MEM_Module
{
};

class MEM_WB_Buffer
{
};

class WB_Module
{
};

class Processor
{
private:
	IF_Module IF;
	ID_Module ID;
	EX_Module EX;
	MEM_Module MEM;
	WB_Module WB;

	IF_ID_Buffer IF_ID;
	ID_EX_Buffer ID_EX;
	EX_MEM_Buffer EX_MEM;
	MEM_WB_Buffer MEM_WB;

	Register PC;
	Register IR;
};


#endif	// PROCESSOR_HPP
