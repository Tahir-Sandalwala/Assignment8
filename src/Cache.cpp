#include "Cache.hpp"

int Cache::read(int address)
{
    int setAddress = address >> 2;
    int offsetAddress = address & 3;
    int data = set[setAddress].offset[offsetAddress];
    return data;
}

void Cache::write(int address, int val)
{
    int setAddress = address >> 2;
    int offsetAddress = address & 3;
    set[setAddress].offset[offsetAddress] = val;
}
