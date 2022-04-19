#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <iostream>

using namespace std;

#define BLOCK_SIZE 4
#define NUM_SETS 64         // NUM_SETS = CACHE_SIZE/BLOCK_SIZE = 256/4 = 64
#define NUM_REGS 16
#define REG_SIZE 8

class Block
{
    public:
        int offset[BLOCK_SIZE];
};

class Cache
{
    protected:
        Block set[NUM_SETS];

    public:
        int read(int adress);
        void write(int adress, int data);
};

// class DCache : public Cache {};

// class ICache : public Cache {};

class Register
{
    private:
        int data;

    public:
        int read();
        void write(int data);
};

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

class IF_Module
{
    private:
        Register &PC;
        Register &IR;
        Cache &ICache;

    public:
        IF_Module(Register &PC, Register &IR, Cache &ICache);
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


#endif