#include "pch.h"

#pragma once
#ifndef BER_H
#define BER_H

/// <summary>
/// Compare two binary strings and return number of bit positions in which the two bits are different.
/// </summary>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns></returns>
uint8_t hammingDistance(uint8_t n1, uint8_t n2);

void toBinaryPrint(uint8_t a);
void binaryCounter(uint8_t a, uint64_t& counter, uint64_t& comp);
#endif // !BER_H


