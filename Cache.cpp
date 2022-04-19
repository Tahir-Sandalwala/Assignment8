#include "Processor.h"

int Cache::read(int adress)
{
    int setAdress = adress >> 2;
    int offsetAdress = adress & 3;
    int data = set[setAdress].offset[offsetAdress];
    return data;
}

void Cache::write(int adress, int val)
{
    int setAdress = adress >> 2;
    int offsetAdress = adress & 3;
    set[setAdress].offset[offsetAdress] = val;
}

