#include "ber.h"

void hammingDistance(uint8_t n1, uint8_t n2, uint64_t& diffBits, uint64_t& compBits)
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;

    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    diffBits += setBits;
    compBits += 8;
}

void toBinaryPrint(uint8_t a)
{
    uint8_t j;
    for (j = 0x80; j != 0; j >>= 1)
    {
        printf("%c", (a & j) ? '1' : '0');
    }       
    printf(" ");
}