#include "Processor.h"

int Register::read()
{
    return data;
}

void Register::write(int data)
{
    this->data = data;
}

