#ifndef REGISTER_HPP
#define REGISTER_HPP

class Register
{
private:
	int data;

public:
	int read();
	void write(int data);
};

#endif	// REGISTER_HPP
