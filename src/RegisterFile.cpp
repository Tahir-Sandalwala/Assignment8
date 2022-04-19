#include "RegisterFile.hpp"

int RegisterFile::read(int RegNum)
{
    if(!readPort[0])
    {
        return readFirstPort(RegNum);
    }
    else if(!readPort[1])
    {
        return readSecondPort(RegNum);
    }
    else
    {
        requestProcessed = false;
        return 0;
    }
}

int RegisterFile::readFirstPort(int RegNum)
{
    readPort[0] = true;
    requestProcessed = true;
    return Reg[RegNum].read();
}

int RegisterFile::readSecondPort(int RegNum)
{
    readPort[1] = true;
    requestProcessed = true;
    return Reg[RegNum].read();
}

void RegisterFile::write(int RegNum, int data)
{
    if(!writePort)
    {
        writePort = true;
        requestProcessed = true;
        Reg[RegNum].write(data);
    }
    else
    {
        requestProcessed = false;
    }
}
