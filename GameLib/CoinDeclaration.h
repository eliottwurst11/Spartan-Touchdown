/**
 * @file CoinDeclaration.h
 * @author Matthew Lopez
 *
 * Class for a coin declaration. CoinDeclaration objects are used for
 * passing information from a level xml file into Coin object constructors.
 */

#ifndef GAME_COINDECLARATION_H
#define GAME_COINDECLARATION_H

#include "Declaration.h"

/**
 * Class for a coin declaration given by an xml file
 */
class CoinDeclaration : public Declaration {
private:
    /// coin value in points
    int mValue;

public:

    CoinDeclaration(std::wstring id, std::wstring picture, int value);

    /// disable the default constructor
    CoinDeclaration() = delete;

    /// disable the copy constructor
    CoinDeclaration(const Declaration &) = delete;

    /// disable assignment operator
    void operator=(const CoinDeclaration &) = delete;

    /**
     * Gets the value of the coin
     * @return the value of the coin
     */
    int GetValue() override { return mValue; }
};


#endif //GAME_COINDECLARATION_H