//============================================================================
// Name        : BiddingF.Cpp
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Description : 
//============================================================================
#pragma once
#include<iostream>
#include "BiddingF.h"


BiddingF::BiddingF()
{
	
}
BiddingF::~BiddingF()
{
}
/// <summary>
/// set the value of Bid
/// </summary>
/// <param name="bidval"> pointer of the value for bid</param>
void BiddingF::setBid(int* bidval)
{
	// setting bid to where pointer is pointting to
		bid = *bidval;
	
}

int BiddingF::getBid()
{
	return bid;
}
