#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP

#include "Utility.hpp"
#include "Register.hpp"

class RegisterFile
{
private:
	Register Reg[NUM_REGS];
	bool readPort[2];
	bool writePort;
	bool requestProcessed;

public:
	int readFirstPort(int RegNum);
	int readSecondPort(int RegNum);
	int read(int RegNum);
	void write(int RegNum, int data);
};

#endif	// REGISTER_FILE_HPP
