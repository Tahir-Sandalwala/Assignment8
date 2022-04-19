#ifndef ALU_HPP
#define ALU_HPP

class ALU
{
public:
	int ADD(int a, int b);
	int SUB(int a, int b);
	int MUL(int a, int b);
	int INC(int a);
	int AND(int a, int b);
	int OR(int a, int b);
	int NOT(int a);
	int XOR(int a, int b);
};

#endif	// ALU_HPP
