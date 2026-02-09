/**
 * @file CoinVisitor.cpp
 * @author Eliott Wurst
 */

#include "pch.h"
#include "CoinVisitor.h"
#include "Coin.h"
#include "Football.h"

/**
 * Visit a Coin object and check if it is touching the football
 * @param coin Coin to visit
 */
void CoinVisitor::VisitCoin(Coin* coin)
{
    if (coin->HitTest(mFootball.get()))
    {
        mCoin = coin;
    }
}
