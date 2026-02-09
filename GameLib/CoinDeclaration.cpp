/**
 * @file CoinDeclaration.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "CoinDeclaration.h"

/**
 * Constructor
 * @param id ID value for the CoinDeclaration, passed by an xml file
 * @param filename Image file for the coin
 * @param value Value for the coin in points
 */
CoinDeclaration::CoinDeclaration(std::wstring id, std::wstring filename, int value) : Declaration(id, filename), mValue(value)
{
}
