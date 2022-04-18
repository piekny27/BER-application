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

void toBinaryPrint(uint8_t a)
{
    for (uint8_t i = 0x80; i != 0; i >>= 1)
    {
        printf("%c", (a & i) ? '1' : '0');
    }       
    printf(" ");
}

void binaryCounter(uint8_t a, uint16_t& diff, uint16_t& comp)
{
    for (uint8_t i = 0x80; i != 0; i >>= 1)
    {
        if (a & i) diff++;
        comp++;
    }
}