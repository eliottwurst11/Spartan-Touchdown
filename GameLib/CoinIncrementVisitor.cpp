/**
 * @file CoinIncrementVisitor.cpp
 * @author Beckham lee
 */

#include "pch.h"
#include "CoinIncrementVisitor.h"

/**
 * Visit a coin object and double its value
 * @param coin Coin object to visit
 */
void CoinIncrementVisitor::VisitCoin(Coin* coin)
{
    int newValue = coin->GetValue() * 2;
    coin->SetValue(newValue);
}