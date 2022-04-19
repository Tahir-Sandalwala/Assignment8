#include "Processor.h"

int ALU::ADD(int a, int b)
{
    return a + b;
}

int ALU::SUB(int a, int b)
{
    return a - b;
}

int ALU::MUL(int a, int b)
{
    return a * b;
}

int ALU::INC(int a)
{
    return a + 1;
}

int ALU::AND(int a, int b)
{
    return a & b;
}

int ALU::OR(int a, int b)
{
    return a | b;
}

int ALU::NOT(int a)
{
    return ~a;
}

int ALU::XOR(int a, int b)
{
    return a ^ b;
}

