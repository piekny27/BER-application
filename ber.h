#include "pch.h"

#pragma once
#ifndef BER_H
#define BER_H

/// <summary>
/// Compare two binary strings and return number of bit positions in which the two bits are different.
/// </summary>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <param name="diffBits"></param>
/// <param name="compBits"></param>
void hammingDistance(uint8_t n1, uint8_t n2, uint64_t& diffBits, uint64_t& compBits);

/// <summary>
/// Print binary representation of byte in console
/// </summary>
/// <param name="a"></param>
void toBinaryPrint(uint8_t a);
#endif // !BER_H


