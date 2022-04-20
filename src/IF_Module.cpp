#include "Processor.h"

void IF_Module::execute(IF_ID_Buffer IF_ID)
{
    int address = PC.read();
    int instruction = ICache.read(address);
    IR.write(instruction);
    PC.write(address + 2);
}
