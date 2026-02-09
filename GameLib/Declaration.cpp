/**
 * @file Declaration.cpp
 * @author Matthew Lopez
 */

#include "pch.h"
#include "Declaration.h"

using namespace std;

/**
 * Constructor
 * @param id ID for the Item object this Declaration holds data for
 * @param name Image file to represent the Item
 */
Declaration::Declaration(std::wstring id, std::wstring name)
    : mId(id), mImageName(name)
{
}

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

