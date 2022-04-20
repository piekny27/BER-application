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

/// <summary>
/// Print messages to log file
/// </summary>
/// <param name="logFile"></param>
/// <param name="message"></param>
void logFilePrint(std::fstream& logFile, std::string message);

/// <summary>
/// Creates new file with the specified size and hex values
/// </summary>
/// <param name="path"></param>
/// <param name="fileName"></param>
/// <param name="fileSize"></param>
/// <param name="value"></param>
/// <returns>Return true if file is succesfully created</returns>
bool createFile(std::string path, std::string fileName, size_t fileSize, uint8_t value);
#endif // !BER_H


