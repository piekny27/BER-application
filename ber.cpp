#include "ber.h"

uint8_t hammingDistance(uint8_t n1, uint8_t n2) 
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;

    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }

    return setBits;
}