//============================================================================
// Name        : BiddingF.h
// Author      : Amir Hossein Hadinezhad
// Version     : First Assainment
// Description : Nested Class in Player
//============================================================================
#pragma once


class BiddingF
{
public:
	BiddingF();
	~BiddingF();

	int getBid();
	/// <summary>
	/// Set Bid for a nested class, BiddingF,  in Player
	/// </summary>
	/// <param name="bid"> Pointer of Value Bidd</param>
	void setBid(int* bid);

private:
	int bid;

};


